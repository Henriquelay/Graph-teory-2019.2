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
    // if(argc != 2) {
    //     cerr << _BOLDRED << "Check inputs!" << _RESET << endl;
    //     return 1;
    // }
    // string fileInput = argv[1];
    // std::ifstream infile;

    // infile.open(fileInput, std::ios::in);
    // if(!infile.is_open()) {
    //     cerr << _BOLDRED << "Check file!" << _RESET << endl;
    // }

    unsigned int nGraphs;
    unsigned int Vertices, nEdges;
    char edge1, edge2;
    set<pair<char,char>> Edges;
    pair<char,char> edge;
    cin >> nGraphs;
    cout << "NGrafos: " << nGraphs << endl;
    for(unsigned int g = 0; g < nGraphs; g++) {
        cin >> Vertices;
        cin >> nEdges;
        // cout << "nVertices grafo " << g+1 << ": " << Vertices << endl;
        // cout << "nEdges grafo " << g+1 << ": " << nEdges << endl;
        for(unsigned int v = 0; v < nEdges; v++) {
            cin >> edge1;
            cin >> edge2;
            // cout << "Edge1 do edge nº " << v+1 << ": " << edge1 << endl;
            // cout << "Edge2 do edge nº " << v+1 << ": " << edge2 << endl;
            edge = std::make_pair(edge1, edge2);
            Edges.insert(edge);
        }
        Graph G = Graph(Vertices, Edges);
        G.printMatrix();
    }

    return 0;
}