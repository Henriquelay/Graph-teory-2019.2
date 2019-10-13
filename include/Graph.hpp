#pragma once

#include <iostream>
#include <cstdlib>
#include <set>
#include <tuple>

using std::set;
using std::pair;

class Graph {

private:
    unsigned int **Adj;

    unsigned int nVertices;
    unsigned int nEdges;

    // Functions
    unsigned int** VEtoAdjMatrix(unsigned int V, set<pair<char,char>> E);

    // Setter
    void setAdj(unsigned int **adj);
    void setnVertices(unsigned int nVertices);
    void setnEdges(unsigned int nEdges);

public:
    // Functions
    void printMatrix();

    // Getter
    unsigned int** getAdj();
    unsigned int getAdj(unsigned int i, unsigned int j);
    unsigned int getnVertices();
    unsigned int getnEdges();

    // Constructors
    // Graph(int **Adj);
    Graph(unsigned int V, set<pair<char,char>> E);
    // Destructor
    ~Graph();
};