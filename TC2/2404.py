from collections import defaultdict
from math import inf

class Vertice:
    def __init__(self, id):
        self.id = id
        self.edges = []
    
    def __str__(self):
        out = "ID: " + str(self.id)
        for e in self.edges:
            out += '\n' + e.__str__()
        return out

class Edge:
    def __init__(self, de, para, cost):
        self.de = de
        self.para = para
        self.cost = cost

    def __str__(self):
        return str(self.de.id) + " -(" + str(self.cost) + ")-> " + str(self.para.id)

class Grafo:
    def __init__(self, listVertices):
        self.vertices = listVertices

    def __str__(self):
        out = ""
        for v in self.vertices:
            out += v.__str__() + '\n'
        return out

if __name__ == "__main__":
    while True:
        try:
            entrada = input().strip().split(' ')
            # print(entrada)
            N = int(entrada[0]) # Nº vertices
            M = int(entrada[1]) # Nº edges
            listVertices = []
            for idVert in range(N):
                listVertices.append(Vertice(idVert))
                # print(listVertices[idVert])
        except EOFError:
            break

        for vertice in range(M):
            entradaArestas = input().strip().split(' ')
            # print("Arestas = " + entradaArestas.__str__())
            # Subtraindo 1 pois vértices do grafo começam do 0
            U = int(entradaArestas[0]) - 1  # De
            V = int(entradaArestas[1]) - 1  # Para
            C = int(entradaArestas[2])  # Custo
            e = Edge(listVertices[U], listVertices[V], C) # Edge
            listVertices[U].edges.append(e)
            # print(e)

            graph = Grafo(listVertices)
            print(graph)
        
