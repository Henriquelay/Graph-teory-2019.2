#include "Graph.hpp"
#include "defines.h"
#include <iostream>
#include <fstream>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

int main(/* int argc, char* argv[] */) {
    unsigned int nGraphs;
    cin >> nGraphs;

    unsigned int Vertices[nGraphs], nEdges[nGraphs];
    char edge1[nGraphs], edge2[nGraphs];
    set<pair<char,char>> Edges[nGraphs];
    pair<char,char> edge[nGraphs];
    Graph graph[nGraphs];
    // cout << "NGrafos: " << nGraphs << endl;
    unsigned int g;
    for(g = 0; g < nGraphs; g++) {
        cin >> Vertices[g];
        cin >> nEdges[g];
        // cout << "nVertices grafo " << g+1 << ": " << Vertices << endl;
        // cout << "nEdges grafo " << g+1 << ": " << nEdges << endl;
        for(unsigned int v = 0; v < nEdges[g]; v++) {
            cin >> edge1[g];
            cin >> edge2[g];
            // cout << "Edge1 do edge nº " << v+1 << ": " << edge1 << endl;
            // cout << "Edge2 do edge nº " << v+1 << ": " << edge2 << endl;
            edge[g] = std::make_pair(edge1[g], edge2[g]);
            Edges[g].insert(edge[g]);
        }
    }
    for(g = 0; g < nGraphs; g++) {
        graph[g] = Graph(Vertices[g], Edges[g]);
        cout << "Case #" << g+1 << ":" << endl;
        graph[g].output();
        cout << endl;
    }
    return 0;
}