#include <vector>
#include <list>
#include "ACO.h"
//#include "headers/demandas.h"

using namespace std;


void Colonia::faz_movimento(){
    int indicie_uav = 0;
    int limite = 100, c=0;
    while(!DemandasRealizadas()){
        if(uavs[indicie_uav].caminho.empty()){
            uavs[indicie_uav].VoltaBase(&demanda[0], matriz_adj);
        }
        vector<pair<int ,int> > nos_possiveis;
        nos_possiveis.clear();     
        while(nos_possiveis.size() == 0 && c<=limite){
            c++;
            for(int indicie_node=1; indicie_node < total_demandas; ++indicie_node){
                if(demanda[indicie_node].realizada == false){
                    if(uavs[indicie_uav].ChacaPeso(demanda[indicie_node].peso)){
                        if(uavs[indicie_uav].ChecaAlcance(demanda[indicie_node], matriz_adj)){
                            nos_possiveis.push_back(make_pair(uavs[indicie_uav].indicie_atual, indicie_node));
                            //cout<<"nos: "<<nos_possiveis.size()<<endl;
                        }
                    }       
                }
            }
        }
        if(nos_possiveis.empty()){
            if(indicie_uav+1<tamanho_populacao){
                if(uavs[indicie_uav].indicie_atual != 0){
                    uavs[indicie_uav].VoltaBase(&demanda[0], matriz_adj);
                }
                indicie_uav += 1;
            }
            else{
                cout << "nao foi possivel relizar todas as entregas.\n";
                break;
            }
        }
        else{
            int indicie_proximo_no;
            if(GeraNoAleatorio() < limiar){
                indicie_proximo_no = nos_possiveis[rand() % nos_possiveis.size()].second;
            }
            else{
                vector<double> ups, probs, soma_acumulada;
                double soma = 0.0;
                for(auto nos_possiveis : nos_possiveis){
                    double up = CalculaProbalilidade(nos_possiveis.first, nos_possiveis.second);
                    soma += up;
                    ups.push_back(up);
                }
                for (auto up : ups){
                    probs.push_back(up / soma);
                }
                soma_acumulada.push_back(probs.front());
                for(int i=0; i<probs.size()-1; ++i){
                    probs[i+1] += probs[i];
                    soma_acumulada.push_back(probs[i+1]);
                }
                int indicie_candidato, melhor_indicie;
                double candidato_v;
                double melhor_v = init_distancia;
                double r = GeraNoAleatorio();
                for(int x=0; x<soma_acumulada.size(); ++x){
                    if (r <= soma_acumulada[x]){
                        indicie_candidato = x;
                        candidato_v = soma_acumulada[x];
                        if(candidato_v < melhor_v){
                            melhor_indicie = indicie_candidato;
                            melhor_v = candidato_v;
                        }
                    }
                }
                if (melhor_v == init_distancia){
                    break;
                }
                indicie_proximo_no = nos_possiveis[melhor_indicie].second;
            }
            uavs[indicie_uav].AddNodeCaminho(&demanda[indicie_proximo_no], matriz_adj, indicie_uav, tamanho_populacao);
        }
    }
    if(uavs[indicie_uav].indicie_atual !=0){
        uavs[indicie_uav].VoltaBase(&demanda[0], matriz_adj);
    }
}


double Colonia::CalculaProbalilidade(int indicie_node_atual, int indicie_proximo_node) const{
    double ETAij = pow (etha_matriz[indicie_node_atual][indicie_proximo_node], beta);
    double TAUij = pow (matriz_feromonio[indicie_node_atual][indicie_proximo_node], alpha);
    return ETAij * TAUij;
}


double Colonia::GeraNoAleatorio() const{
    random_device aleatorio;
    mt19937 generator(aleatorio());
    uniform_real_distribution<double> distr(0, 1);
    return distr(generator);
}


void Colonia::AtualizaMatrizFeromonio(double &distancia_total_caminho, int &visitados){

    for(int i=0; i < tamanho_populacao; ++i){
        double distancia_caminho = 0.0;        
        CalculaDistanciaCaminho(uavs[i].caminho, distancia_caminho);
        distancia_total_caminho += distancia_caminho;
        visitados += uavs[i].caminho.size();
        
        for(int j=0; j<uavs[i].caminho.size(); ++j){
            if(j+1 != uavs[i].caminho.size()){
                matriz_feromonio[uavs[i].caminho[j].origem][uavs[i].caminho[j+1].destino] = 
                decaimento * matriz_feromonio[uavs[i].caminho[j].origem][uavs[i].caminho[j+1].destino] + 
                q / distancia_caminho;
            }
        }
    }
    
}

void Colonia::AtualizaLimiar(){
    limiar*=rho;
}


void Colonia::Reseta(){


    for(int i=0; i<tamanho_populacao; ++i){
        uavs[i].caminho.clear();
        uavs[i].carga = 4;
        uavs[i].indicie_atual = 0;
    }

    free(demanda);
    LoadDemandas();
  
}


void Colonia::Run(){

    double menor_distancia = init_distancia;
    int mais_visitados = init_caminho;

    for (int i=0; i < max_iteracao; ++i){
        printf("\n%d iteracao de %d\n", i, max_iteracao);
        faz_movimento();
        double distancia_total_caminho = 0.0;
        int visitados = 0;
        AtualizaMatrizFeromonio(distancia_total_caminho, visitados);
        if(distancia_total_caminho < menor_distancia && mais_visitados < visitados){
            menor_distancia = distancia_total_caminho;
            mais_visitados = visitados;
       }
        PrintCaminho();
        AtualizaLimiar();
        Reseta();

    }
    cout<<"\n\nok final\n\n"<<max_iteracao<<endl;
    cout<<"melhor distancia: "<<menor_distancia<<endl;
    cout<<"mais nos visitados: "<<mais_visitados<<endl;
}


Colonia::Colonia() : Grafo()
{   
	matriz_feromonio = new double* [num_node];
	etha_matriz = new double* [num_node]; 
	for(int i = 0; i < num_node; i++){
		matriz_feromonio[i] = new double [num_node];
		etha_matriz[i] = new double [num_node];
		for(int j = 0; j < num_node; j++){
			matriz_feromonio[i][j] = 0;
			etha_matriz[i][j] = 0;
		}
	}

	for(int i = 0; i < num_node; i++){
		for(int j = i + 1; j < num_node; j++){
			matriz_feromonio[i][j] = matriz_feromonio[j][i] = tau;
			etha_matriz[i][j] = etha_matriz[j][i] = q / matriz_adj[i][j];
		}
	}
}