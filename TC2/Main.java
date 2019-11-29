import java.util.HashSet;
import java.util.LinkedList;
import java.util.Scanner;

class Vertice implements Comparable {
	int identificador;
	// int distancia;
	boolean verificado;
	LinkedList<Aresta> conexoes;

	public int getIdentificador() {return identificador;}
	public void setIdentificador(int identificador) {this.identificador = identificador;}
	public LinkedList<Aresta> getConexoes() {return conexoes;}
	public void setConexoes(LinkedList<Aresta> conexoes) {this.conexoes = conexoes;}
	public boolean isVerificado() {return verificado;}
	public void setVerificado(boolean verificado) {this.verificado = verificado;}

	public Vertice(int identificador, LinkedList<Aresta> conexoes) {
		super();
		// this.setDistancia(Integer.MAX_VALUE);// 2147483647;
		this.setIdentificador(identificador);
		this.setConexoes(conexoes);
		this.setVerificado(false);
	}

	public Vertice(int identificador) {
		// this.setDistancia(Integer.MAX_VALUE);
		this.setIdentificador(identificador);
		this.setConexoes(new LinkedList<Aresta>());
		this.setVerificado(false);
	}

	public Vertice vizinhoMaisProximo() {
		Vertice proximo = null;
		int menorCusto = Integer.MAX_VALUE;
		for (Aresta a : this.getConexoes()) {
			if (a.getCusto() < menorCusto) {
				proximo = a.getVerticeDestino() == this ? a.getVerticePartida() : a.getVerticeDestino();
			}
		}
		return proximo;
	}

	public int cheapestAresta() {
		int menorCusto = Integer.MAX_VALUE;
		for (Aresta a : this.getConexoes()) {
			if (a.getCusto() < menorCusto) {
				menorCusto = a.getCusto();
			}
		}
		return menorCusto;
	}

	@Override
	public String toString() {
		String str = this.getIdentificador() + ": \n";
		for (Aresta e : this.getConexoes()) {
			str += e.toString() + "\n";
		}
		return str;
	}

	@Override
	public int compareTo(Vertice arg0) {
		return this.cheapestAresta() < arg0.cheapestAresta();
	}
}

class Aresta implements Comparable {
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

	@Override
	public int compareTo(Object o) {
		return this.getCusto().compareTo(o.getCusto());
	}
}

class Grafo {
	LinkedList<Vertice> vertices;
	LinkedList<Aresta> arestas;

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

	@Override
	public String toString() {
		String str = "";
		for(Vertice v : this.getVertices()) {
			str += v.toString() + "\n";
		}
		return str;
	}

	Aresta menorConexao() {
		Aresta menor = null;
		for(Aresta a : this.getArestas()) {
			if(menor == null || a.getCusto() < menor.getCusto()) {
				menor = a;
			}
		}
		return menor;
	}

	Grafo primMST() { 
		if(this.getVertices().isEmpty()) {
			return null;
		}
		int cheapConToV[] = new int[this.getVertices().size()];
		Aresta cheapestEdge[] = new Aresta[this.getVertices().size()];
		for(int i = 0; i < this.getVertices().size(); i++) {
			cheapConToV[i] = Integer.MAX_VALUE;
			cheapestEdge[i] = null;
		}
		Grafo prim = new Grafo();
		HashSet<Vertice> Q = new HashSet<Vertice>(this.getVertices());
		while(!Q.isEmpty()) {
			Vertice menorCusto = Collection.min(Q);
			prim.getVertices().add(menorCusto);
			Q.remove(menorCusto);
			if(cheapestEdge[menorCusto.getIdentificador()] != null) {
				prim.getArestas().add(cheapestEdge[menorCusto.getIdentificador()]);
			}
			for(Aresta a : menorCusto.getConexoes()) {
				Vertice oOutro = a.oOutro(menorCusto);
				if(Q.contains(oOutro) && a.getCusto() < cheapConToV[oOutro.getIdentificador()] && oOutro != null) {
					cheapConToV[oOutro.getIdentificador()] = a.getCusto();
					cheapestEdge[oOutro.getIdentificador()] = a;
				}
			}
		}
		return prim;
	}
}

public class Main {
	public static void main(String[] args) {
		int N, M;
		int U, V, C;

		Scanner entrada = new Scanner(System.in);

		LinkedList<Aresta> edges = new LinkedList<Aresta>();
		LinkedList<Vertice> vertices = new LinkedList<Vertice>();

		try {
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
			
			Grafo g = new Grafo(vertices, edges);
			// System.out.println(g);
			Grafo prim = g.primMST();
			System.out.println("cu");
		}
		finally {
			entrada.close();
		}
	}
}
