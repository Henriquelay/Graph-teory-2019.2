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

    Vertice(int id) {
        this->id = id;
        this-> distancia = numeric_limits<int>::max();
    }
    ~Vertice() {
        set<Aresta*>::iterator itaresta = this->conexoes.begin();
        while(itaresta != this->conexoes.end()) {
            delete *itaresta;
            itaresta++;
        }
    }
};

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
        int distancia_ini = 0;
        int custo = 0;
        ini -> distancia = 0;        
        set<Vertice*> fechado;
        set<Vertice*> aberto = this -> vertices;
        fechado.insert(ini);
        aberto.erase(ini);

        //set<Vertice*>::iterator itVert = this->vertices.begin();
        Vertice* k = ini;
        Vertice* anterior = ini;
        while(!aberto.empty()){
            set<Aresta*>::iterator itAdjacente = anterior->conexoes.begin();
            
            Vertice* adjacencia = ((*itAdjacente) -> v1 == anterior) ?  (*itAdjacente) -> v2 : (*itAdjacente) -> v1;
            while(aberto.find(adjacencia) == aberto.end()){
                if(anterior->conexoes.find(*itAdjacente) == anterior->conexoes.end()){
                    return;
            }
                adjacencia = ((*itAdjacente) -> v1 == anterior) ?  (*itAdjacente) -> v2 : (*itAdjacente) -> v1;
                itAdjacente++;
            }
            k = adjacencia;
            
            fechado.insert(k);
            aberto.erase(k);
            set<Aresta*>::iterator itAresta = k->conexoes.begin();
            while(itAresta != k->conexoes.end()) {
                Vertice* vizinho = (*itAresta) -> v1;
                if(vizinho == ini)
                    vizinho = (*itAresta) -> v2;

                if(aberto.find(vizinho) != aberto.end()){
                    custo = (k-> distancia +1 > vizinho -> distancia) ? k-> distancia +1 : vizinho -> distancia;
                    if(custo < vizinho -> distancia){
                        vizinho-> distancia = custo;
                        anterior = k;                        
                    }
                }
                itAresta++;
            }
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
            cout << "N=" << n << endl;
        Vertice* verticeend[n];
        for(int i = 0; i < n; i++){
            Vertice* v = new Vertice(i+1);
            vertices.insert(v);
            verticeend[i] = v;
        }
        in >> m;
            cout << "M=" << m << endl;
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
            cout << "ESTADUNIDO = " << e << endl;
        for(int i = 0; i < n; i++) {
            if(verticeend[i]->id == e){
                vertices.erase(verticeend[i]);
                verticeend[i] = NULL;
            }
        }
        Grafo* grafo = new Grafo(vertices, arestasssss);
        grafo->print();

        grafo->dijkstrazinho(verticeend[c-1]);

        // vertices.clear();
        // arestas.clear();
        cout << verticeend[r-1]->distancia;
        // delete grafo;    
    }
    in.close();
}