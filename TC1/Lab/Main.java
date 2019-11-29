import java.util.LinkedList;
import java.util.Scanner;

class Vertice {
	int identificador;
	int distancia;
	boolean verificado;
	LinkedList<Aresta> conexoes;
	
		public int getIdentificador() {return identificador;}
		public int getDistancia() {return distancia;}
		public void setIdentificador(int identificador) {this.identificador = identificador;}
		public void setDistancia(int dist) {this.distancia = dist;}
		public LinkedList<Aresta> getConexoes() {return conexoes;}
		public void setConexoes(LinkedList<Aresta> conexoes) {this.conexoes = conexoes;}
		public boolean isVerificado() {return verificado;}
		public void setVerificado(boolean verificado) {this.verificado = verificado;}

	public Vertice(int identificador, LinkedList<Aresta> conexoes) {
		super();
		this.setDistancia(Integer.MAX_VALUE);// 2147483647;
		this.setIdentificador(identificador);
		this.setConexoes(conexoes);
		this.setVerificado(false);
	}

	public Vertice(int identificador) {
		this.setDistancia(Integer.MAX_VALUE);
		this.setIdentificador(identificador);
		this.setConexoes(new LinkedList<Aresta>());
		this.setVerificado(false);
	}

	@Override
	public String toString() {
		String str = this.getIdentificador() + ": \n";
		for(Aresta e : this.getConexoes()) {
			str += e.toString() + "\n";
		}
		return str;
	}
}

class Aresta {
	Vertice verticePartida, verticeDestino;
	int custo;

	public Aresta(Vertice verticePartida, Vertice verticeDestino, int custo) {
		super();
		this.setVerticePartida(verticePartida);
		this.setVerticeDestino(verticeDestino);
		this.setCusto(custo);
	}

	public Vertice getVerticePartida() {return this.verticePartida;}
	public void setVerticePartida(Vertice verticePartida) {this.verticePartida = verticePartida;}
	public Vertice getVerticeDestino() {return this.verticeDestino;}
	public void setVerticeDestino(Vertice verticeDestino) {this.verticeDestino = verticeDestino;}
	public int getCusto() {return this.custo;}
	public void setCusto(int custo) {this.custo = custo;}

	@Override
	public String toString() {
		return this.getVerticePartida().getIdentificador() + " --(" + this.getCusto() + ")-- " + this.getVerticeDestino();
	}
}

class Grafo {
	LinkedList<Vertice> vertices;
	LinkedList<Aresta> arestas;
	boolean fconexo;

	public Grafo(LinkedList<Vertice> vertices, LinkedList<Aresta> arestas) {
		this.setVertices(vertices);
		this.setArestas(arestas);
	}

	public Grafo() {
		this.setVertices(new LinkedList<Vertice>());
		this.setArestas(new LinkedList<Aresta>());
	}

	public LinkedList<Vertice> getVertices() {return vertices;}
	public void setVertices(LinkedList<Vertice> vertices) {this.vertices = vertices;}
	public LinkedList<Aresta> getArestas() {return arestas;}
	public void setArestas(LinkedList<Aresta> arestas) {this.arestas = arestas;}

	public static Vertice vizinhoMaisProximo(LinkedList<Vertice> Q) {
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
		int N, M;
		int U, V, C;

		Scanner entrada = new Scanner(System.in);

		LinkedList<Aresta> edges = new LinkedList<Aresta>();
		LinkedList<Vertice> vertices = new LinkedList<Vertice>();

		while (entrada.hasNextInt()) {
			N = entrada.nextInt();
			M = entrada.nextInt();
			for (int i = 0; i < N; i++) {
				Vertice v = new Vertice(i);
				vertices.add(v);
			}
			for (int i = 0; i < M; i++) {
				U = entrada.nextInt() - 1;	// Pq as entradas começam do 1
				V = entrada.nextInt() - 1;
				C = entrada.nextInt() - 1;
				Aresta ar = new Aresta(vertices.get(U), vertices.get(V), C);
				edges.add(ar);
				vertices.get(U).getConexoes().add(ar);
				vertices.get(V).getConexoes().add(ar);
			}
			entrada.close();

			Grafo g = new Grafo(vertices, edges);
			System.out.println(g);
		}
	}
}
