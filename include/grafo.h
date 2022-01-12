#include <list>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <stdio.h>
#include "uav.h"
#ifndef GRAFO_H
#define GRAFO_H

class Grafo{
    public:
        int num_node = 0;
        int tamanho_populacao = 5;//numero de agentes
        int total_demandas = 0; //numero de demandas
        Node* demanda;
        UAV_DLV1* uavs;
        std::vector<std::list<float>> adj;
        std::vector<std::list<float> > vetor;
        float** matriz_adj;
        Grafo();
        void addEdge(int, int, float);
        void CalculaMatrizAdj();
        void CalculaDistanciaCaminho(std::vector<Node>, double&) const;
        void PrintCaminho() const;
        void addLinhaDemanda(Node*, int x, int j, float p);
        void PrintGrafo();
        void Clear();
        void PrintDemandas();
        void PrintMatrizAdj();
        void LoadDemandas();
        int TotalRealizadas();
        bool DemandasRealizadas();
};

#endif 