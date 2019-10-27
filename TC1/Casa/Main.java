import java.util.ArrayList;
import java.util.Scanner;

class Vertice {
	int identificador;
	int distancia;
	boolean verificado;
	ArrayList<Aresta> conexoes;

	public Vertice(int identificador, ArrayList<Aresta> conexoes) {
		super();
		this.distancia = Integer.MAX_VALUE;// 2147483647;
		this.identificador = identificador;
		this.conexoes = conexoes;
		this.verificado = false;
	}

	public Vertice(int identificador) {
		this.distancia = Integer.MAX_VALUE;
		this.identificador = identificador;
		this.conexoes = new ArrayList<Aresta>();
		this.verificado = false;
	}

	public int getIdentificador() {
		return identificador;
	}

	public int getDistancia() {
		return distancia;
	}

	public void setIdentificador(int identificador) {
		this.identificador = identificador;
	}

	public void setDistancia(int dist) {
		this.distancia = dist;
	}

	public ArrayList<Aresta> getConexoes() {
		return conexoes;
	}

	public void setConexoes(ArrayList<Aresta> conexoes) {
		this.conexoes = conexoes;
	}

	public boolean isVerificado() {
		return verificado;
	}

	public void setVerificado(boolean verificado) {
		this.verificado = verificado;
	}
}

class Aresta {
	int verticePartida, verticeDestino;

	public Aresta(int verticePartida, int verticeDestino) {
		super();
		this.verticePartida = verticePartida;
		this.verticeDestino = verticeDestino;
	}

	public int getVerticePartida() {
		return verticePartida;
	}

	public void setVerticePartida(int verticePartida) {
		this.verticePartida = verticePartida;
	}

	public int getVerticeDestino() {
		return verticeDestino;
	}

	public void setVerticeDestino(int verticeDestino) {
		this.verticeDestino = verticeDestino;
	}

}

class Grafo {
	ArrayList<Vertice> vertices;
	ArrayList<Aresta> arestas;
	boolean fconexo;

	public Grafo(ArrayList<Vertice> vertices, ArrayList<Aresta> arestas) {
		super();
		this.vertices = vertices;
		this.arestas = arestas;
		this.fconexo = false;
	}

	public Grafo() {
		this.vertices = new ArrayList<Vertice>();
		this.arestas = new ArrayList<Aresta>();
		this.fconexo = false;
	}

	public ArrayList<Vertice> getVertices() {
		return vertices;
	}

	public void setVertices(ArrayList<Vertice> vertices) {
		this.vertices = vertices;
	}

	public ArrayList<Aresta> getArestas() {
		return arestas;
	}

	public void setArestas(ArrayList<Aresta> arestas) {
		this.arestas = arestas;
	}

	public boolean isFconexo() {
		return fconexo;
	}

	public void setFconexo(boolean fconexo) {
		this.fconexo = fconexo;
	}


	void setarVerificado() {
		for (Vertice v : this.getVertices()) {
			v.setVerificado(false);
		}
	}



	Vertice procuraVertice(int id, ArrayList<Vertice> vertices) {
		for (Vertice v : vertices) {
			if (v.getIdentificador() == id) {
				return v;
			}
		}
		return null;
	}

	int didijkstra(Vertice ini) {
		ArrayList<Vertice> Q = new ArrayList<Vertice>(this.getVertices());
		// this.getVertices();
		ini.setDistancia(0);
		
		Vertice prox;

		while (Q.size() > 1) {
			prox = menorDist(Q);
			for (Aresta a : prox.getConexoes()) {
				Vertice vizinho = procuraVertice(a.verticePartida, Q) == prox ? procuraVertice(a.verticeDestino, Q)
						: procuraVertice(a.verticePartida, Q);
				if (Q.contains(vizinho)) {
					int d = prox.getDistancia() + 1;
					//System.out.println("Distancia: " + d);
					if (d < vizinho.getDistancia()) {
						vizinho.setDistancia(d);
						for (Vertice v : this.getVertices()) {
							if (vizinho.getIdentificador() == v.getIdentificador()) {
								v.setDistancia(d);
								break;
							}
						}
					}
				}

			}
			// System.out.println("VERTICE " + (prox.getIdentificador()));
			Q.remove(prox);
		}
		return 0;
	}

	public static Vertice menorDist(ArrayList<Vertice> Q) {
		if (Q == null)
			return null;
		Vertice menor = Q.get(0);
		for (Vertice v : Q)
			if (v.getDistancia() < menor.getDistancia())
				menor = v;

		return menor;
	}
}

public class Main {

	public static void main(String[] args) {
		int n, m;
		int a, b;
		int c, r, e;

		Scanner entrada = new Scanner(System.in);

		while (entrada.hasNextInt()) {
			Grafo g = new Grafo();
			n = entrada.nextInt();
			m = entrada.nextInt();
			for (int i = 0; i < n; i++) {
				Vertice v = new Vertice(i + 1);
				g.getVertices().add(v);
			}
			for (int j = 0; j < m; j++) {
				a = entrada.nextInt();
				b = entrada.nextInt();
				Aresta ar = new Aresta(a, b);
				g.getArestas().add(ar);
				g.getVertices().get(a - 1).getConexoes().add(ar);
				g.getVertices().get(b - 1).getConexoes().add(ar);
			}
			c = entrada.nextInt();
			r = entrada.nextInt();
			e = entrada.nextInt();

			for (Aresta ar : g.getVertices().get(e - 1).getConexoes()) {
				g.getArestas().remove(ar);
			}
			g.getVertices().remove(e - 1);
			for (Vertice v : g.getVertices()) {
				if (v.getIdentificador() == c) {
					g.didijkstra(v);
				}
			}

			for (Vertice v : g.getVertices()) {
				if (v.getIdentificador() == r) {
					System.out.println(v.getDistancia());
				}
			}
		}
		entrada.close();
	}
}
