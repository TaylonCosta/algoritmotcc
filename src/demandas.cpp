#include <random>
#include <fstream>
#include"uav.h"


using namespace std;

constexpr int FLOAT_MIN = 0.5;
constexpr int FLOAT_MAX = 2;

void Demandas::addLinhaDemanda(Node* node, int idx, int nodeentrega, float peso){

    node->destino = nodeentrega;
    node->indicie = idx;
    node->peso = peso;
    node->realizada = 0;
}


void Demandas::GeraDemandas(int n){
    
    random_device rd;
    default_random_engine eng(rd());
    uniform_real_distribution<> distr(FLOAT_MIN, FLOAT_MAX);
    srand(time(NULL));

    total_demandas = n;
    int rnode;
    float rpeso=0;

    for(int i=0; i<n; ++i){
        
        rnode = rand() % 10 + 1;
        cout << setprecision(2);
        rpeso = distr(eng);
        //addLinhaDemanda(i, rnode, rpeso);
    }
}

void Demandas::LoadDemandas(){

    cout<<"carregando demandas\n";
    ifstream filein;
    int aux=0;
    filein.open("50");
    //filein.open("100");
    //filein.open("150");
    filein>>total_demandas;
    cout<<total_demandas<<endl;
    demanda = new Node[total_demandas];
    float vet[3];
    int it = 0;
    while(!filein.eof()){
        for(int i=0;i<3;i++){
            filein>>vet[i];
        }
        addLinhaDemanda(&demanda[it], vet[0], vet[1], vet[2]*100);
        ++it;
        cout << "Linha " << it << "adcionada\n";
    }
    cout << sizeof(demanda) << endl;
    cout<<"Carregou tudo certo\n";
}



void Demandas::Print(){
    int i=0;
    for(i=0; i<50;++i){
            cout << "indicie: " << demanda[i].indicie << " ";
            cout << "entrega: " << demanda[i].destino << " ";
            cout << "peso: " << demanda[i].peso << "\n";
    }
}


bool Demandas::DemandasRealizadas(){

    for(int i=0; i<total_demandas; ++i){
        if(!demanda[i].realizada){
            return false;
            cout << "opa";
        }
    }
}