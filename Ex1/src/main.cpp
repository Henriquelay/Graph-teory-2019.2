#include <iostream>
#include <fstream>

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
            // std::cout << "First: " << int((*it).first - 'a') << " Second: " << int((*it).second - 'a') << std::endl;
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

void Graph::output() {    
    // Mark all the vertices as not visited 
    unsigned int number = 0;
    bool visited[int(this->getnVertices())]; 
    for(unsigned int v = 0; v < this->getnVertices(); v++) 
        visited[v] = false; 

    for (unsigned int v = 0; v < this->getnVertices(); v++) { 
        if (visited[v] == false) { 
            // print all reachable vertices from v 
            DFSUtil(v, visited); 
            number++;
            std::cout << std::endl;
        } 
    }
    std::cout << number << " connect components" << std::endl;
}

void Graph::DFSUtil(unsigned int v, bool visited[]) { 
    // Mark the current node as visited and print it 
    visited[v] = true; 
    // std::cout << "V éh " << v << ", " <<  char(v + 'a') << "  ";
    std::cout << char(v + 'a') << ',';
    // Recur for all the vertices 
    // adjacent to this vertex 
    for(unsigned int i = 0; i < this->getnVertices(); i++)
        if(this->Adj[int(i)][int(v)] != 0)
            if(!visited[int(i)]) 
                DFSUtil(i, visited);
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
Graph::Graph() {}
Graph::Graph(unsigned int V, set<pair<char,char>> E) {
    this->setnVertices(V);
        // std::cout << "N vert: " << E.size() << std::endl;    
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

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

int main() {
    unsigned int nGraphs;
    cin >> nGraphs;

    unsigned int Vertices[nGraphs], nEdges[nGraphs];
    char edge1[nGraphs], edge2[nGraphs];
    set<pair<char,char>> Edges[nGraphs];
    pair<char,char> edge[nGraphs];
    Graph *graph[nGraphs];
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
        graph[g] = new Graph(Vertices[g], Edges[g]);
        cout << "Case #" << g + 1 << ":" << endl;
        graph[g]->output();
        cout << endl;
        delete graph[g];
    }
    cout << endl;
    return 0;
}