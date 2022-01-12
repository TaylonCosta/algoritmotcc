#include <fstream>
#include <list>
#include <vector>
#include <iostream>
#include "grafo.h"

using namespace std;


void Grafo::addEdge(int u, int v, float wt){
    
    
    list<float> l;
    l.push_back(u);
    l.push_back(v);
    l.push_back(wt);
    
    matriz_adj[u][v]=wt;
    
    //vetor.insert(vetor.end(), l);
}

void Grafo::PrintGrafo(){
       
    for (vector<list<float>>::iterator it = vetor.begin(); it != vetor.end(); ++it){
        for (list<float>::iterator it2 = it->begin(); it2 != it->end(); ++it2){
            printf("%.1f ",*it2);
        }
        cout << "\n";
    }

}

void Grafo::CalculaMatrizAdj(){

    cout<<num_node<<endl;
    matriz_adj = new float* [num_node];
    for (int i=0; i<num_node; ++i){
        matriz_adj[i] = new float [num_node];
        for (int j=0; j<num_node; ++j){
            matriz_adj[i][j]=0;
        }
    }
    /*
    int aux[2];
    float aux2;
    for (vector<list<float>>::iterator it = vetor.begin(); it != vetor.end(); ++it){
        int i=0;
        for (list<float>::iterator it2 = it->begin(); it2 != it->end(); ++it2){
            if (i == 2)
                aux2= *it2;
            else
                aux[i]= *it2;
            i++;
        }
        matriz_adj[aux[0]][aux[1]]= aux2;
        matriz_adj[aux[1]][aux[0]]= aux2;

    }
    */  
}

int Grafo::TotalRealizadas(){

    int counter=0; 

    for (int i=0; i<sizeof(demanda); ++i){
        if(demanda[i].realizada == 1){
            counter++;
        }
    }
    return counter;
}


void Grafo::CalculaDistanciaCaminho(vector<Node>caminho, double &distancia_caminho) const{

    if(caminho.size() > 2){
        for(int i=0; i<caminho.size()-1; ++i){
            distancia_caminho += matriz_adj[caminho[i].origem][caminho[i+1].destino];
        }
    }
}

void Grafo::PrintCaminho() const {

    double distancia_total_caminho = 0.0;
    int total_visitado = 0;
    for(int i=0; i<tamanho_populacao; ++i){
        if(uavs[i].caminho.size()>1){
            cout<<"\n\nUAV: " << i <<" caminho: \n";
            double distancia_caminho = 0.0;
            for(int j=0; j<uavs[i].caminho.size(); ++j){
                cout << "indicie: " << uavs[i].caminho[j].indicie<<" origem: " << uavs[i].caminho[j].origem << " Destino: "<<uavs[i].caminho[j].destino<<endl;
            }
            CalculaDistanciaCaminho(uavs[i].caminho, distancia_caminho);
            distancia_total_caminho += distancia_caminho;
            cout << distancia_caminho<<"km";
            cout << ", Demandas realizadas: " << uavs[i].caminho.size()-2<<endl;
            total_visitado += uavs[i].caminho.size()-2;
        }
        else{
            cout << "\nUAV " << i << " nao utilizado.\n";
        }
    }
    cout << "total visitado: "<<total_visitado << "/" << total_demandas;
    cout << "\ndistancia: "<< distancia_total_caminho <<"km\n";
}

void Grafo::addLinhaDemanda(Node* node, int idx, int entrega, float peso){

    node->destino = entrega;
    node->indicie = idx;
    node->peso = peso;
    node->realizada = false;
}


void Grafo::Clear(){

    adj.clear();

}

void Grafo::PrintMatrizAdj(){
    cout<<"Matriz de adj:\n";
    
    for (int i=0; i<num_node; ++i){
        for (int j=0; j<num_node; ++j){
            cout << matriz_adj[i][j]<<"\t";
        }
        cout << "\n";
    }  
}

void Grafo::PrintDemandas(){

    for(int i=0; i<50;++i){
            cout << "indicie: " << demanda[i].indicie << " ";
            cout << "entrega: " << demanda[i].destino << " ";
            cout << "peso: " << demanda[i].peso << "\n";
    }
}


bool Grafo::DemandasRealizadas(){

    for(int i=0; i<total_demandas; ++i){
        if(!demanda[i].realizada){
            return false;
        }
    }
}

void Grafo::LoadDemandas(){
    
    ifstream filedemanda;
    //filedemanda.open("50");
    filedemanda.open("100");
    //filein.open("150");
    filedemanda>>total_demandas;
    demanda = new Node[total_demandas];

    int it = 0;
    
    while(!filedemanda.eof()){
        filedemanda>>demanda[it].indicie;
        filedemanda>>demanda[it].destino;
        filedemanda>>demanda[it].peso;
        demanda[it].realizada = 0;
        ++it;
    }
}

Grafo::Grafo(){
    
    uavs = new UAV_DLV1[tamanho_populacao]; 

    ifstream filegrafo;


    filegrafo.open("grafopontos.txt");
    filegrafo>>num_node;
    int v[2];
    float aux;
    
    CalculaMatrizAdj();
    while(!filegrafo.eof()){
        for(int i=0;i<2;++i){
            filegrafo>>v[i];
        }
        filegrafo>>aux;
        matriz_adj[v[0]][v[1]]=aux;
        matriz_adj[v[1]][v[0]]=aux;
        //cout<<matriz_adj[v[0]][v[1]]<<" na " << v[0]<<" - "<<v[1]<<endl;
        //cout<<matriz_adj[v[1]][v[0]]<<" na " << v[1]<<" - "<<v[0]<<endl;
    }

    PrintMatrizAdj();
    LoadDemandas();
    PrintDemandas();
    
}