#include <list>
#include <iostream>
#include <vector>

class Graph {
    public:
        std::vector<std::vector<int>> custo;
        std::list<int> vertices;
    
        Graph(int nV) {
            this->custo = std::vector<std::vector<int> >(nV);
            for(int i = 0; i < nV; i++) {
                this->custo[i] = std::vector<int>(nV);
                for(int j = 0; j < nV; j++) {
                    this->custo[i][j] = __INT_MAX__;
                }
            }
            for(int i = 1; i < nV + 1; i++) {
                this->vertices.push_back(i);
            }
        }
    
        ~Graph() {}

        void att(int partida, int destino, int custo) {
            this->custo[partida][destino] = custo;
            this->custo[destino][partida] = custo;
        }

        void prim() {
            int custoTotal = 0, i = 0;
            std::list<int> vertex;
            vertex.push_back(this->vertices.front());
            std::list<int> vLinha = this->vertices;
            vLinha.remove(this->vertices.front());
            int tam = vLinha.size();
            
            while(i < tam) {
                int custo_min = __INT_MAX__;
                int menor = -1;
                for(int v1: vertex) {
                    for(int v2: vLinha) {
                        int custo = this->custo[v1-1][v2-1];    
                        if(custo < custo_min) {
                            menor = v2;
                            custo_min = custo;
                        }
                    }
                }
                if(custo_min < __INT_MAX__) {
                    custoTotal += custo_min;
                    vertex.push_back(menor);
                    vLinha.remove(menor);
                }
                ++i;
            }

            std::cout << custoTotal << std::endl;
        }
};

int main() {
    int N, M;
    std::cin >> N;
    std::cin >> M;

    Graph* g = new Graph(N);
    
    for(int i = 0; i < M; i++) {
        int p, d, c;
        std::cin >> p;
        std::cin >> d;
        std::cin >> c;
        g->att(p - 1, d - 1, c);
    }
    g->prim();
    delete(g);

    return 0;
}