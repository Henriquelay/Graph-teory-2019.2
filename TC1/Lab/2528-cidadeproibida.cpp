#include <set>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <limits>
#include <unordered_map>

using namespace std;

class Aresta;
class Vertice;

class Aresta{
public:
    Vertice* v1, *v2;

    Aresta(){}
    Aresta(Vertice* v1, Vertice* v2);
    ~Aresta();

    void printMe();
};

class Vertice {
public:
    int id;
    int distancia;
    set<Aresta*> conexoes;

    Vertice() {
        this->id = -1;
        this->distancia = __INT_MAX__;
        }
    Vertice(int id) {
        this->id = id;
        this->distancia = __INT_MAX__;
    }
    ~Vertice() {
        this->conexoes.clear();
    }

    void printMe();
};

Aresta::Aresta(Vertice* v1, Vertice* v2) {
    this->v1 = v1;
    this->v2 = v2;
    this->v1->conexoes.insert(this);
    this->v2->conexoes.insert(this);
}

Aresta::~Aresta() {
    this->v1->conexoes.erase(this);
    this->v2->conexoes.erase(this);
}

void Aresta::printMe() {
    cout << "V1 " << this->v1->id << endl;
    cout << "V2 " << this->v2->id << endl;
}


Vertice* menor_dist(unordered_map<int,Vertice*> &Q) {
    Vertice *menor = new Vertice();
    menor->distancia = __INT_MAX__;
    for(auto& v : Q) {
            // v->printMe();
        if(v.second->distancia < menor->distancia) {
            if(menor->distancia == __INT_MAX__) delete menor;
            menor = v.second;
        }
    }
    return menor;
}

set<Vertice*> vizinhos(Vertice *u) {
    set<Vertice*> vizinhanca;
    for(Aresta* a : u->conexoes) {
        Vertice *v = a->v1 == u ? a->v2 : a->v1;
        vizinhanca.insert(v);
    }
    return vizinhanca;
}

void Vertice::printMe() {
    cout << "ID: " << this->id;
    cout << " Dist: " << this->distancia << endl << " Conexões: ";
    for(Vertice *v : vizinhos(this))
        cout << this->id << ", ";
    cout << endl;
}

class Grafo {
public:
    unordered_map<int, Vertice*> vertices;
    
    Grafo(unordered_map<int,Vertice*> vertices) {
        this->vertices = vertices;
    }
    ~Grafo(){
        this->vertices.clear();
    }

    void print() {
        cout << "Vertices:\n";
        for(pair<int,Vertice*> itVert : this->vertices)
            cout << itVert.first << ' ';
        cout << endl;
    }

    void dijkstrazinho(Vertice* ini) {
        unordered_map<int,Vertice*> Q;
        Q = this->vertices; //copia os vert
        ini->distancia = 0;

        Vertice *u;

        // for(Vertice* vertPrint : Q)
        //     vertPrint->printMe();

        while(!Q.empty()) {
            // cout << "ANTES" << endl;
            // u->printMe();
            u = menor_dist(Q);
            // cout << "DEPOIS" << endl;
            // u->printMe();
            for(Vertice *v : vizinhos(u)) {
                int p = u->distancia + 1;
                if(p < v->distancia) {
                    v->distancia = p;
                }
            }
            Q.erase(u->id);
        }
    }
};

int main(int argc, char* argv[]){
    // ifstream cin;
    int n, m;           // n = vertices; m = arestas;
                        // c = Curytyba (start); r = Riacho de Fevereiro (sumidouro); E = Estadunido;
    int a, b;
    int c, r, e;
    unordered_map<int, Vertice*> mapvertices;
    unordered_map<int, Aresta*> maparestas;

    while (cin >> n){
        if(n == cin.eof()) return 0;
            // cout << "N = " << n << endl;
        for(int i = 1; i <= n; i++)
            mapvertices[i] = new Vertice(i);

        cin >> m;
            // cout << "M=" << m << endl;
        for(int i = 1; i <= m; i++){
            cin >> a;
            cin >> b;
            maparestas[i] = new Aresta(mapvertices[a], mapvertices[b]);
        }
        cin >> c;
        cin >> r;
        cin >> e;
            // cout << "ESTADUNIDO = " << e << endl;

        
        mapvertices.erase(e);

        Grafo* grafo = new Grafo(mapvertices);
        // grafo->print();

        grafo->dijkstrazinho(mapvertices[c]);
        cout << mapvertices[r]->distancia << endl;

        delete grafo;
    }
    // cin.close();
}