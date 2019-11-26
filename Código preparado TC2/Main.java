import java.util.LinkedList;
import java.util.Scanner;
import java.util.HashSet;

public class Main {
    class Vertice {
        String id;
        LinkedList<Edge> edges;

        Vertice(String id) {
            this.id = id;
            this.edges = new LinkedList<Edge>();
        }

        Vertice(String id, LinkedList<Edge> edges) {
            this.id = id;
            this.edges = edges;
        }

        @Override
        public String toString() {
            return this.id;
        }
    }

    class Edge {
        Vertice from;
        Vertice to;

        int cost;

        Edge(Vertice from, Vertice to) {
            this.from = from;
            this.to = to;
            this.cost = 1;
        }

        Edge(Vertice from, Vertice to, int cost) {
            this.from = from;
            this.to = to;
            this.cost = cost;
        }

        @Override
        public String toString() {
            return this.from + " ---" + this.cost + "--> " + this.to;
        }
    }

    static class Graph {
        HashSet<Vertice> vertices;
        
        int nVertices;
        int nEdges;

        void addVertice(Vertice v) {
            this.vertices.add(v);
            this.nVertices++;
            this.nEdges += v.edges.size();
        }

        Graph() {
            this.vertices = new HashSet<Vertice>();
            this.nVertices = 0;
            this.nEdges = 0;
        }

        Graph(LinkedList<Vertice> vertices) {
            this.vertices = new HashSet<Vertice>();
            this.vertices.addAll(vertices);
            this.nVertices += this.vertices.size();
            this.nEdges = 0;
            for(Vertice v : this.vertices) {
                this.nEdges += v.edges.size();
            }
        }

        @Override
        public String toString() {
            String str = "";
            for(Vertice v : this.vertices) {
                str += v.toString() + "\n";
            }
            return str;
        }
    }

    public static void main(String args[]) {
        Scanner scanner = new Scanner(System.in);

        LinkedList<Vertice> vertices = new LinkedList<Vertice>();
        String line = "";
        while((line = scanner.nextLine()) != "0 0") {
            String in[] = line.split(" ");
            int nVertices = Integer.parseInt(in[0]);
            int nArestas = Integer.parseInt(in[1]);
            for(int i = 1; i <= nVertices; i++) {
                String str = String.valueOf(i);
                Vertice v = new Vertice(str);
                vertices.add(v);
            }
            for(int i = 1; i <= nArestas; i++) {
                
            }
        }

        scanner.close();
    }
}