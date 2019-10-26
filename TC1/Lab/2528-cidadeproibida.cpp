#include <set>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <limits>
#include <unordered_map>

using namespace std;

class Vertice;

typedef pair<Vertice*,Vertice*> Aresta;
typedef unordered_map<int,Vertice*> VerticeMap;
typedef unordered_map<int,Aresta> ArestaMap;

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
        for(Aresta* a : this->conexoes) {
            if(a->first == this)
                a->second->conexoes.erase(a);
            else
                a->first->conexoes.erase(a);
        }
        this->conexoes.clear();
    }

    void printMe() {
        cout << "ID: " << this->id;
        cout << " Dist: " << this->distancia << endl << " Conexões: ";
        for(Aresta *v : this->conexoes){
            if(v->second != this)
                cout << v->second->id << ", ";
            else
                cout << v->first->id << ", ";
        }
        cout << endl;
    }
};

Vertice* menor_dist(VerticeMap &Q) {
    Vertice *menor = new Vertice();
    menor->distancia = __INT_MAX__;
    for(pair<int,Vertice*> v : Q) {
            // cout << "MenorDist" << endl;
            // v->printMe();
        if(v.second->distancia < menor->distancia) {
            if(menor->distancia == __INT_MAX__)
                delete menor;
            menor = v.second;
        }
    }
    return menor;
}

class Grafo {
public:
    VerticeMap vertices;
    
    Grafo(VerticeMap &vertices) {
        this->vertices = vertices;
    }
    ~Grafo(){
        this->vertices.clear();
    }

    void print() {
        cout << "Vertices:\n";
        for(pair<int,Vertice*> itParVert : this->vertices)
            itParVert.second->printMe();
            cout << endl;
    }

    void dijkstrazinho(Vertice* ini) {
        VerticeMap Q = VerticeMap(this->vertices); //copia os vert
            // cout << "Tam do putão: " << Q.size() << endl;
        ini->distancia = 0;

        Vertice *proximo;

            // for(pair<int,Vertice*> v : Q)
            //     v.second->printMe();

        while(!Q.empty()) {
                // cout << "Dijkstra vértice" << endl;
                // cout << "ANTES" << endl;
                // proximo->printMe();
            proximo = menor_dist(Q);
                // cout << "DEPOIS" << endl;
                // proximo->printMe();
            for(Aresta *a : proximo->conexoes) {
                // cout << "Dijkstra Aresta" << endl;
                Vertice *vizinho = a->first == proximo ? a->second : a->first;
                int p = proximo->distancia + 1;
                if(p < vizinho->distancia) {
                    vizinho->distancia = p;
                }
            }
            Q.erase(proximo->id);
        }
    }
};

int main(){
    int n, m;       // n = vertices; m = arestas;
    int a, b;
    int c, r, e;    // c = Curytyba (start); r = Riacho de Fevereiro (sumidouro); E = Estadunido;
    VerticeMap mapvertices;
    ArestaMap maparestas;

    while (cin >> n){
        if(n == cin.eof()) return 0;
        for(int i = 1; i <= n; i++)
            mapvertices[i] = new Vertice(i);

        cin >> m;
        for(int i = 1; i <= m; i++){
            cin >> a;
            cin >> b;
            maparestas[i] = make_pair(mapvertices[a], mapvertices[b]);
            mapvertices[a]->conexoes.insert(&maparestas[i]);
            mapvertices[b]->conexoes.insert(&maparestas[i]);
        }
        cin >> c;
        cin >> r;
        cin >> e;

        delete mapvertices[e];
        mapvertices.erase(e);

        Grafo* grafo = new Grafo(mapvertices);
        // grafo->print();

        grafo->dijkstrazinho(mapvertices[c]);
        cout << mapvertices[r]->distancia << endl;
        
        delete grafo;

        for(pair<int,Vertice*> i : mapvertices)
            delete i.second;
        mapvertices.clear();
        maparestas.clear();
    }
}