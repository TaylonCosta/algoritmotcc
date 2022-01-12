#include <list>
#include <iostream>
#include <vector>
#include <random>
#include "demandas.h"
#include "grafo.h"
#ifndef ACO_H
#define ACO_H

class Colonia : public Grafo{
    public:
        const int max_iteracao = 50; //numero maxino de iteracoes
        const double tau = 1.0; //valor inicial do feromonio
        const double alpha = 3.0; //valor exponencial do feromonio
        const double beta = 5; //valor do peso do feromonio
        const double rho = 0.9; //taxa de evaporacao do feromonio
        const double decaimento = 0.95;
        const double q = 1;
        double limiar = 0.5;
        int init_distancia = 9999;
        int init_caminho = 9999;
        double** matriz_feromonio;
	    double** etha_matriz;
        std::vector<std::list<float> > dem;
        Colonia();
        ~Colonia();
        void faz_movimento();
        //void Inicializa(auto demandas, auto uav);
        double GeraNoAleatorio() const;
        double CalculaProbalilidade(int, int) const;
        void AtualizaMatrizFeromonio(double&, int&);
        void AtualizaLimiar();
        void Reseta();
        void Run();
        

};
#endif