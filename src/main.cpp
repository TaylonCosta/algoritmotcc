#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <ctime>

#include "grafo.h"
#include "uav.h"
#include "ACO.h"


using namespace std;


int main()
{
    //inicializa o grafo
    int tamanho=0, i;
    float n;
    //UAV_DLV1* u1 = new UAV_DLV1;
    //Demandas d = Demandas();
    Colonia* c = new Colonia();
    
    cout<<"\nretornou ok\n";
    c->Run();
    //g->Print();
    //g->CalculaMatrizAdj();

    //printa specs do uav
    //u1->PrintSpecs();
    //c->Print();
    //c->CalculaMatrizAdj();

    //inicializa das demandas aleatorias
    //d.LoadDemandas();
    //d.Print();

    return 0;

}