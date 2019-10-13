#include "Graph.hpp"

// Functions
int** Graph::VEtoAdjMatrix(unsigned int V, set<pair<char,char>> E) {
    int **matrix = (int**) malloc(sizeof(int*) * this->getnVertices());
    if(matrix == NULL) return NULL;

    for(unsigned int i = 0; i < V; i++) {
        matrix[i] = (int*) malloc(sizeof(int) * this->getnVertices());
        if(matrix[i] == NULL) return NULL;
    }   // Tenho a matrix reservada.
    

        // limpando a matrix de sujeira
    for(unsigned int i = 0; i < this->getnVertices(); i++) {
        for(unsigned int j = 0; j < this->getnVertices(); j++) {
            matrix[i][j] = 0;
            if(i == j) matrix[i][j]++;  // incidência de um vértice nele mesmo
        }
    }

        // Percorrendo todo o 'E' e anotado sua adjacência
    set<pair<char,char>>::iterator it;
    for(it = E.begin(); it != E.end(); it++) {
        // converte de char para int e desloca o char em 'a' menos.
        std::cout << "First: " << int((*it).first - 'a') << " Second: " << int((*it).second - 'a') << std::endl;
        matrix[int((*it).first - 'a')][int((*it).second - 'a')]++;
        matrix[int((*it).second - 'a')][int((*it).first - 'a')]++;
    }

    return matrix;
}
void Graph::printMatrix() {
    for(unsigned int i = 0; i < this->getnVertices(); i++) {
        for(unsigned int j = 0; j < this->getnVertices(); j++) {
            std::cout << this->getAdj(i, j) << " ";
        }
        std::cout << std::endl;
    }
}


// Setter
void Graph::setAdj(int **adj) {this->Adj = adj;}
void Graph::setnVertices(unsigned int n) {this->nVertices = n;}
void Graph::setnEdges(unsigned int n) {this->nEdges = n;}

// Getter
int** Graph::getAdj() {return this->Adj;}
int Graph::getAdj(unsigned int i, unsigned int j) {return this->Adj[i][j];}
unsigned int Graph::getnVertices() {return this->nVertices;}
unsigned int Graph::getnEdges() {return this->nEdges;}

// Constructors
Graph::Graph(unsigned int V, set<pair<char,char>> E) {
    this->setnVertices(V);
    this->setnEdges(E.size());
    this->Adj = this->VEtoAdjMatrix(V, E);
}
// Destructor
Graph::~Graph() {
    if(this->getAdj() != NULL) {
        for(unsigned int i = 0; i != this->getnVertices(); i++) 
            if(this->Adj[i] != NULL)
                free(this->Adj[i]);
        free(this->getAdj());
    }
}