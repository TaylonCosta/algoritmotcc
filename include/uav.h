#include <stdio.h>
#include <vector>
#include <list>
#include <iostream>
#include <random>
#include <iomanip>
#ifndef UAV_H
#define UAV_H


class Node{
    public:
        int origem=-1, destino, indicie;
        double peso;
        bool realizada;
};


class Demandas{
    public:
        int total_demandas;
        Node* demanda;
        void GeraDemandas(int n);
        void LoadDemandas();
        void addLinhaDemanda(Node*, int x, int j, float p);
        void Print();
        bool DemandasRealizadas();
};


class UAV_DLV1 {
    public:
        float alcance = 4;
        float carga = 200;
        double performance = 300;
        int velocidade = 32;
        int indicie_atual=-1;
        int posicao = 0;
        Node* node = new Node;
        std::vector<Node> caminho;
        UAV_DLV1();
        void PrintSpecs();
        void AddNodeCaminho(Node*, float**, int&, int);
        void VoltaBase(Node*, float**);
        bool ChacaPeso(float);
        bool ChecaAlcance(Node, float**);
        float AtualizaCapacidade(float);
        

};
#endif