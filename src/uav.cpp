#include"uav.h"

using namespace std;

UAV_DLV1::UAV_DLV1(){
        alcance = 4;
        carga = 2;
        performance = 30;
        velocidade = 32;
        posicao = 0;
}



void UAV_DLV1::PrintSpecs(){
    printf("alcance: %f\n", alcance);
    printf("carga: %f\n", carga);
    printf("performance: %f\n", performance);
    printf("velocidade: %i\n", velocidade);
}


float UAV_DLV1::AtualizaCapacidade(float peso){
    float aux_carga = carga - peso; 
    return aux_carga;
}

bool UAV_DLV1::ChacaPeso(float peso){

    //float is_ok = AtualizaCapacidade(peso);
    
    if (carga > 0)
        return true;

    else 
        return false;
}

bool UAV_DLV1::ChecaAlcance(Node node, float** matriz){

    float aux_distancia=0;
    float aux_alcance = performance - (matriz[indicie_atual][node.destino]);
   
    if(caminho.size()<0){
        for(int i=0; i<caminho.size()-1; ++i){
            aux_distancia += matriz[caminho[i].origem][caminho[i].destino];
        }
        
        aux_alcance = aux_alcance - (aux_distancia + (matriz[indicie_atual][node.destino]));
        if (aux_alcance < 0){
            return false;
        }
        else{
            return true;
        }
    }
    else{
        return true;
    }
}


void UAV_DLV1::VoltaBase(Node *node, float** matriz){
    
    node->origem=indicie_atual;
    indicie_atual=0;
    carga = 2;
    performance = 30;
}

void UAV_DLV1::AddNodeCaminho(Node *node, float** matriz, int &indicie_uav, int populacao){
    
    if((performance - matriz[indicie_atual][node->destino]>0) && (carga - node->peso)>=0){
        node->origem=indicie_atual;
        caminho.push_back(*node);

        performance -= (matriz[indicie_atual][node->destino]);
        indicie_atual = node->destino;

        float aux = 0 - node->peso;
        if ((carga-aux) >= 0){
            carga -= aux;
            node->peso = 0;
            node->realizada = true;        
            //cout<<node->indicie<<" foi realizada"<<endl;
        }
        else{
            carga = 0;
            node->peso -= carga;
        }
    }
    else{
        cout<<"carga ou bateria insuficiente no uav: "<<indicie_uav<<endl;
        VoltaBase(node, matriz);
        if(indicie_uav+1 < populacao){
            //cout<<"passando pro proximo\n";
            indicie_uav+=1;
        }
        else{
            //cout<<"entrou aqui\n";
            indicie_uav=0;
        }
    }
}