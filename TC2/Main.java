import java.util.Collection;
import java.util.HashMap;
import java.util.LinkedHashSet;
import java.util.Scanner;

class Vertice {
	int identificador;
	// int distancia;
	boolean verificado;
	LinkedHashSet<Aresta> conexoes;

	public int getIdentificador() {return identificador;}
	public void setIdentificador(int identificador) {this.identificador = identificador;}
	public LinkedHashSet<Aresta> getConexoes() {return conexoes;}
	public void setConexoes(LinkedHashSet<Aresta> conexoes) {this.conexoes = conexoes;}
	public boolean isVerificado() {return verificado;}
	public void setVerificado(boolean verificado) {this.verificado = verificado;}

	public Vertice(int identificador, LinkedHashSet<Aresta> conexoes) {
		super();
		// this.setDistancia(Integer.MAX_VALUE);// 2147483647;
		this.setIdentificador(identificador);
		this.setConexoes(new LinkedHashSet<Aresta>(conexoes));
		this.setVerificado(false);
	}

	public Vertice(int identificador) {
		// this.setDistancia(Integer.MAX_VALUE);
		this.setIdentificador(identificador);
		this.setConexoes(new LinkedHashSet<Aresta>());
		this.setVerificado(false);
	}

	@Override
	public String toString() {
		String str = this.getIdentificador() + ": \n";
		for (Aresta e : this.getConexoes()) {
			if(e.getVerticePartida() == this) { 
				str += e.toString() + "\n";
			}
		}
		return str;
	}

	public int menorDistancia(Vertice v) {
		int menor = Integer.MAX_VALUE;
		LinkedHashSet<Aresta> intersection = new LinkedHashSet<Aresta>(this.getConexoes());
		intersection.retainAll(v.getConexoes());
		for(Aresta a : intersection) {
			if(a.getCusto() < menor) {
				menor = a.getCusto();
			}
		}
		return menor;
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

	public Vertice oOutro(Vertice v) {
		if (this.getVerticePartida() != v && this.getVerticeDestino() != v) {
			return null;
		}
		return this.getVerticePartida() == v ? this.getVerticeDestino() : this.getVerticePartida();
	}

	@Override
	public String toString() {
		return this.getVerticePartida().getIdentificador() + " --(" + this.getCusto() + ")-- "
				+ this.getVerticeDestino().getIdentificador();
	}
}

class Grafo {
	LinkedHashSet<Vertice> vertices;
	LinkedHashSet<Aresta> arestas;

	public Grafo(Collection<Vertice> vertices, LinkedHashSet<Aresta> arestas) {
		this.setVertices(new LinkedHashSet<Vertice>(vertices));
		this.setArestas(arestas);
	}

	public Grafo() {
		this.setVertices(new LinkedHashSet<Vertice>());
		this.setArestas(new LinkedHashSet<Aresta>());
	}

	public LinkedHashSet<Vertice> getVertices() {return vertices;}
	public void setVertices(LinkedHashSet<Vertice> vertices) {this.vertices = vertices;}
	public LinkedHashSet<Aresta> getArestas() {return arestas;}
	public void setArestas(LinkedHashSet<Aresta> arestas) {this.arestas = arestas;}

	@Override
	public String toString() {
		String str = "";
		for(Vertice v : this.getVertices()) {
			str += v.toString() + "\n";
		}
		return str;
	}

	void primMST() { 
		int pesoT = 0;
		LinkedHashSet<Vertice> vertex = new LinkedHashSet<Vertice>();
		vertex.add(this.getVertices().iterator().next());
		LinkedHashSet<Vertice> vLinha = new LinkedHashSet<Vertice>(this.getVertices());
		vLinha.remove(this.getVertices().iterator().next());

		while(!vLinha.isEmpty()) {
			int custo_min = Integer.MAX_VALUE;
			// Vertice va = null;
			Vertice vb = null;
			for(Vertice v1: vertex) {
				for(Vertice v2: vLinha) {
					int custo = v1.menorDistancia(v2);
					if(custo < custo_min) {
						// va = v1;
						vb = v2;
						custo_min = custo;
					}
				}
			}
			if(custo_min < Integer.MAX_VALUE) {
				vertex.add(vb);
				vLinha.remove(vb);
				pesoT += custo_min;
			}
		}

		System.out.println(pesoT);
	}
}

public class Main {
	public static void main(String[] args) {
		int N, M;
		int U, V, C;

		Scanner entrada = new Scanner(System.in);
		LinkedHashSet<Aresta> edges = new LinkedHashSet<Aresta>();

		HashMap<Integer,Vertice> vertices = new HashMap<Integer,Vertice>();

		try {
			N = entrada.nextInt();
			M = entrada.nextInt();
			for (int i = 0; i < N; i++) {
				Vertice v = new Vertice(i);
				vertices.put(i,v);
			}
			for (int i = 0; i < M; i++) {
				U = entrada.nextInt() - 1;	// Pq as entradas começam do 1
				V = entrada.nextInt() - 1;
				C = entrada.nextInt();
				Aresta ar = new Aresta(vertices.get(U), vertices.get(V), C);
				edges.add(ar);
				vertices.get(U).getConexoes().add(ar);
				vertices.get(V).getConexoes().add(ar);
			}
			
			Grafo g = new Grafo(vertices.values(), edges);
			g.primMST();
		}
		finally {
			entrada.close();
		}
	}
}
