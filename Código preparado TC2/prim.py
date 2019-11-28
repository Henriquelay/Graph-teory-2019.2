from collections import defaultdict
from math import inf

class Vertice:
    def __init__(self, id):
        self.id = id

class Edge:
    def __init__(self, de, para, cost):
        self.de = de
        self.para = para
        self.cost = cost

    def __str__(self):
        return self.de.id + " --(" + self.cost + ")-> " + self.para.id

class Grafo:
    def __init__(self, listVertices):
        self.vertices = listVertices

if __name__ == "__main__":
    while True:
        try:
            entrada = input().strip().split(' ')
            # print(entrada)
            N = int(entrada[0])
            M = int(entrada[1])
            listVertice = range(N)
        except EOFError:
            break

        for vertice in range(M):
            entradaArestas = input().strip().split(' ')
            # print(entradaArestas)
            # Subtraindo 1 pois vértices do grafo começam do 0
            U = int(entradaArestas[0]) - 1  # De
            V = int(entradaArestas[1]) - 1  # Para
            C = int(entradaArestas[1]) - 1  # Custo
            e = Edge(U, V, C) # Edge
            print(e)
