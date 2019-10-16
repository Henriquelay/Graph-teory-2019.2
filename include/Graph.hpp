#pragma once

#include <iostream>
#include <cstdlib>
#include <set>
#include <tuple>

using std::set;
using std::pair;

class Graph {

private:
    int **Adj;

    unsigned int nVertices;
    unsigned int nEdges;

    // Functions
    int** VEtoAdjMatrix(unsigned int V, set<pair<char,char>> E);
    void DFSUtil(unsigned int v, bool visited[]);

    // Setter
    void setAdj(int **adj);
    void setnVertices(unsigned int nVertices);
    void setnEdges(unsigned int nEdges);

public:
    // Functions
    void printMatrix();
    void output();

    // Getter
    int** getAdj();
    int getAdj(unsigned int i, unsigned int j);
    unsigned int getnVertices();
    unsigned int getnEdges();

    // Constructors
    // Graph(int **Adj);
    Graph();
    Graph(unsigned int V, set<pair<char,char>> E);
    // Destructor
    ~Graph();
};