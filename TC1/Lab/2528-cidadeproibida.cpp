#include <set>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <limits>

using namespace std;

class Aresta;
class Vertice;



class Aresta{
public:
    Vertice* v1, *v2;

    Aresta(){}
    Aresta(Vertice* v1, Vertice* v2) {
        this->v1 = v1;
        this->v2 = v2;
    }
    ~Aresta(){}
};

class Vertice {
public:
    int id;
    int distancia;
    set<Aresta*> conexoes;

    Vertice() {
        this->distancia = __INT_MAX__;
        set<Aresta*> porra;
        this->conexoes = porra;
        }
    Vertice(int id) {
        this->id = id;
        this->distancia = __INT_MAX__;
        set<Aresta*> porra;
        this->conexoes = porra;
    }
    ~Vertice() {
        set<Aresta*>::iterator itaresta = this->conexoes.begin();
        while(itaresta != this->conexoes.end()) {
            delete *itaresta;
            itaresta++;
        }
    }

    void printMe();
};

Vertice* menor_dist(set<Vertice*> &Q) {
    Vertice *menor;
    for(Vertice *v : Q) {
        // v->printMe();
        if(v->distancia < menor->distancia) menor = v;
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
    cout << "ID: " << this->id << " Dist: " << this->distancia << endl << " Conexões: ";
    for(Vertice *v : vizinhos(this))
        cout << this->id << ", ";
    cout << endl;
}

class Grafo {
public:
    set<Vertice*> vertices;
    set<Aresta*> arestas;
    
    Grafo(set<Vertice*> vertices, set<Aresta*> arestas) {
        this->vertices = vertices;
        this->arestas = arestas;
    }
    ~Grafo(){
        set<Vertice*>::iterator itVertice = this->vertices.begin();
        while(itVertice != this->vertices.end()) {
            delete *itVertice;
            itVertice++;
        }
        this->vertices.clear();
        set<Aresta*>::iterator itAresta = this->arestas.begin();
        while(itAresta != this->arestas.end()) {
            delete *itAresta;
            itAresta++;
        }
        this->arestas.clear();
    }

    void print() {
        cout << "Vertices:\n";
        set<Vertice*>::iterator itvert = this->vertices.begin();
        while(itvert != this->vertices.end()) {
            cout << (*itvert)->id << ' ';
            itvert++;
        }
        cout << endl;
        cout << "Arestas:\n";
        set<Aresta*>::iterator itaresta = this->arestas.begin();
        while(itaresta != this->arestas.end()) {
            cout << (*itaresta)->v1->id << ", " << (*itaresta)->v2->id << endl;
            itaresta++;
        }
        cout << endl;
    }

    void dijkstrazinho(Vertice* ini) {
        set<Vertice*> Q;
        for(Vertice *v : this->vertices)
            Q.insert(v);
        ini->distancia = 0;

        Vertice *u;

        
        // for(Vertice* vertPrint : Q)
        //     vertPrint->printMe();

        while(!Q.empty()) {
            cout << "ANTES ";
            u->printMe();
            u = menor_dist(Q);
            cout << "DEPOIS ";
            u->printMe();
            for(Vertice *v : vizinhos(u)) {
                int p = u->distancia + 1;
                if(p < v->distancia) {
                    v->distancia = p;
                }
            }
            Q.erase(u);
        }
    }
};

int main(int argc, char* argv[]){
    ifstream in;
    int n, m;           // n = vertices; m = arestas;
                        // c = Curytyba (start); r = Riacho de Fevereiro (sumidouro); E = Estadunido;
    int a, b;
    int c, r, e;
    set<Vertice*> vertices;
    set<Aresta*> arestas;

    in.open(argv[argc-1], ios::in);
    if(!in.is_open()){
        cout << "Arquivo zicado.\n";
        exit(1);
    }
    while (in >> n){
            // cout << "N=" << n << endl;
        Vertice* verticeend[n];
        for(int i = 0; i < n; i++){
            Vertice* v = new Vertice(i+1);
            vertices.insert(v);
            verticeend[i] = v;
        }
        in >> m;
            // cout << "M=" << m << endl;
        set<Aresta*> arestasssss;
        for(int i = 0; i < m; i++){
            in >> a;
            in >> b;
            Aresta* ar = new Aresta(verticeend[a-1],verticeend[b-1]);
            arestasssss.insert(ar);
            verticeend[a-1]->conexoes.insert(ar);
            verticeend[b-1]->conexoes.insert(ar);
        }
        in >> c;
        in >> r;
        in >> e;
            // cout << "ESTADUNIDO = " << e << endl;
        for(int i = 0; i < n; i++) {
            if(verticeend[i]->id == e){
                vertices.erase(verticeend[i]);
                verticeend[i] = NULL;
            }
        }
        Grafo* grafo = new Grafo(vertices, arestasssss);
        // grafo->print();

        grafo->dijkstrazinho(verticeend[c-1]);


        cout << verticeend[r-1]->distancia << endl;
        // delete grafo;
    }
    in.close();
}