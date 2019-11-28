import java.util.LinkedList;
import java.util.Scanner;
import java.util.TreeMap;
import java.util.HashSet;

public class Main {
    public static void main(String args[]) {
        Scanner scanner = new Scanner(System.in);

        TreeMap<String,Vertice> vertices = new TreeMap<String,Vertice>();
        String line = "";
        line = scanner.nextLine().trim();
        while(line != "0 0") {
            System.out.println("LINHA " + line);
            String in[] = line.split(" ");
            for(String s : in) {s = s.trim();}
            int nVertices = Integer.parseInt(in[0]);
            int nArestas = Integer.parseInt(in[1]);
            
            // Cria os vértices de 1 à nVertices
            for(int i = 1; i <= nVertices; i++) {
                Vertice v = new Vertice(String.valueOf(i));
                vertices.put(String.valueOf(i), v);
            }
            // Configura as arestas
            for(int i = 0; i < nArestas; i++) {
                line = scanner.nextLine();
                in = line.split(" ");
                for(String s : in) {s = s.trim();}
                Edge e = new Edge(vertices.get(in[0]), vertices.get(in[1]), Integer.parseInt(in[2]));
                vertices.get(in[0]).edges.add(e);
                vertices.get(in[1]).edges.add(e);
            }
            if(scanner.hasNextLine()) {
                line = scanner.nextLine().trim();
            } else {
                line = "0 0";
            }
            
            Graph grafo = new Graph(new LinkedList<Vertice>(vertices.values()));
            System.out.println(grafo);
            grafo.dijkstra(vertices.firstEntry().getValue());System.out.println(grafo);
        }



        scanner.close();
    }

    static public Vertice menorDist(HashSet<Vertice> H) {
        Vertice menor = null;
        for(Vertice v : H) {
            if(menor == null) {
                menor = v;
            }
            if(v.dist < menor.dist) {
                menor = v;
            }
        }
        return menor;
    }
}

class Vertice {
    String id;
    int dist;
    LinkedList<Edge> edges;

    Vertice(String id) {
        this.id = id;
        this.dist = Integer.MAX_VALUE;
        this.edges = new LinkedList<Edge>();
    }

    Vertice(String id, LinkedList<Edge> edges) {
        this.id = id;
        this.dist = Integer.MAX_VALUE;
        this.edges = edges;
    }

    @Override
    public String toString() {
        return this.id + " (" + this.dist + ")";
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

class Graph {
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
            if(v.edges.isEmpty()) {
                str += v.toString() + "\n";
            } else {
                for(Edge e : v.edges) {
                    str += e.toString() + "\n";
                }
            }
        }
        return str;
    }

    public boolean hasVertice(Vertice v) {
        return this.vertices.contains(v);
    }
    
    public void dijkstra(Vertice initial) {
        HashSet<Vertice> Q = new HashSet<Vertice>(this.vertices);
		// this.getVertices();

        Vertice prox;
        initial.dist = 0;

		while (Q.size() > 1) {
			prox = Main.menorDist(Q);
			for (Edge a : prox.edges) {
				Vertice vizinho = Q.contains(a.from) ? a.to
						: a.from;
				if (Q.contains(vizinho)) {
					int d = prox.dist + 1;
					//System.out.println("Distancia: " + d);
					if (d < vizinho.dist) {
						vizinho.dist = d;
						for (Vertice v : this.vertices) {
							if (vizinho.id == v.id) {
								v.dist = d;
								break;
							}
						}
					}
				}

			}
			// System.out.println("VERTICE " + (prox.getIdentificador()));
			Q.remove(prox);
		}
    }
}