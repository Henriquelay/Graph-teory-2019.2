#ifndef GRAFO_H_
#define GRAFO_H_

#include <iostream>
#include <vector>
#include <ctime>
// #include <string>

class Grafo{
    private:
        int **matrizAdjacencia;
        int **matrizIncidencia;
        int vertices;
        int arestas;

        // Propriedades; pode ser que seja dada em questões, pode ser útil para resolver problemas mais rapidamente
        bool isCompleto;
        bool isConexo;
        bool isKPartido;
        bool isBiPartido;
        bool isKRegular;
};

#endif