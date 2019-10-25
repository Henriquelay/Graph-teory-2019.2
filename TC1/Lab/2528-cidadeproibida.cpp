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
        set<Aresta*>::iterator itaresta = this->conexoes.begin();
        for(Aresta *itaresta : this->conexoes) {
            delete itaresta;
        }
    }

    void printMe();
};

void Aresta::printMe() {
    cout << "V1 " << this->v1->id << endl;
    cout << "V2 " << this->v2->id << endl;
}


Vertice* menor_dist(set<Vertice*> &Q) {
    Vertice *menor = new Vertice();
    menor->distancia = __INT_MAX__;
    for(Vertice *v : Q) {
            // v->printMe();
        if(v->distancia < menor->distancia) {
            if(menor->distancia == __INT_MAX__) delete menor;
            menor = v;
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
    set<Vertice*> vertices;
    
    Grafo(set<Vertice*> vertices) {
        this->vertices = vertices;
    }
    ~Grafo(){
        this->vertices.clear();
    }

    void print() {
        cout << "Vertices:\n";
        set<Vertice*>::iterator itvert = this->vertices.begin();
        while(itvert != this->vertices.end()) {
            cout << (*itvert)->id << ' ';
            itvert++;
        }
        cout << endl;
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

    in.open(argv[1], ios::in);
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

        for(Aresta* itaresta : arestasssss) {
            itaresta->printMe();
            if(itaresta->v1 == verticeend[e-1] || itaresta->v2 == verticeend[e-1])
                arestasssss.erase(itaresta);
        }

        Grafo* grafo = new Grafo(vertices);
        // grafo->print();

        grafo->dijkstrazinho(verticeend[c-1]);


        cout << verticeend[r-1]->distancia << endl;
        delete grafo;
    }
    in.close();
}