import java.util.ArrayList;
import java.util.Scanner;

class Vertice {
	int identificador;
	boolean verificado;
	ArrayList<Aresta> conexoes;
	
	public Vertice(int identificador, ArrayList<Aresta> conexoes) {
		super();
		this.identificador = identificador;
		this.conexoes = conexoes;
		this.verificado = false;
	}
	public Vertice(int identificador) {
		this.identificador = identificador;
		this.conexoes = new ArrayList<Aresta>();
		this.verificado = false;
	}
	public int getIdentificador() {
		return identificador;
	}
	public void setIdentificador(int identificador) {
		this.identificador = identificador;
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

class Aresta{
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

class Grafo{
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
	boolean verificarConexidade() {
		boolean fconexo = true;
		for(Vertice v1 : this.getVertices()) {
			for (Vertice v2 : this.getVertices() ) {
				if (v1 != v2 && fconexo) {
					fconexo = verificarCaminho(v1, v2);
					if(fconexo) {
						// System.out.println("Há caminho de " + v1.getIdentificador() + " a " + v2.getIdentificador());
						// System.out.println("---");
					}
					setarVerificado();
				}
			}
		}		
		return fconexo;		
	}
	
	void setarVerificado() {
		for (Vertice v : this.getVertices()) {
			v.setVerificado(false);
		}
	}

	void printarArestas(){
		for(Aresta a : this.getArestas()){
			System.out.println(a.getVerticePartida() + " -> " + a.getVerticeDestino());			
		}
	}

	boolean verificarCaminho(Vertice a, Vertice b) {
		//System.out.println("No vértice " + a.getIdentificador());
		a.setVerificado(true);

		for (int i = 0; i < a.getConexoes().size(); i++) {
				// System.out.println("Númeto de arestas de " + a.getIdentificador() + " = " + a.getConexoes().size());
			if(this.getVertices().get(a.getConexoes().get(i).getVerticeDestino()-1) == b){
				//this.setFconexo(true);
				return true;
			}
			if(! this.getVertices().get(a.getConexoes().get(i).getVerticeDestino()-1).isVerificado()) {
					// System.out.println("Não é o vértice " + b.getIdentificador() +" ainda");
					// System.out.println("Vamos para o vértice " + this.getVertices().get(a.getConexoes().get(i).getVerticeDestino()-1).getIdentificador());
				if(verificarCaminho(this.getVertices().get(a.getConexoes().get(i).getVerticeDestino()-1), b)){
					return true;
				}
			}			
		}
		
		//System.out.println("Vo retorna falso fodase");
		return false;
	}
}

public class Main {

	public static void main(String[] args) {
		int n, m;
		int v, w, p;
		
		Scanner entrada = new Scanner(System.in);
		n = entrada.nextInt();
		m = entrada.nextInt();
		
		while (n != 0 && m != 0) {
			Grafo grafo = new Grafo();
			for (int i = 0; i < n; i++) {
				Vertice ver = new Vertice(i+1);
				grafo.getVertices().add(ver);
			}
			
			for (int j = 0; j < m; j++) {
				v = entrada.nextInt();
				w = entrada.nextInt();
				p = entrada.nextInt();
				Aresta a = new Aresta(v, w);
				grafo.getArestas().add(a);				
				grafo.vertices.get(v-1).getConexoes().add(a);
				if(p == 2) {
					Aresta a2 = new Aresta(w, v);
					grafo.getVertices().get(w-1).getConexoes().add(a2);
					grafo.getArestas().add(a2);
				}
			}
			
			
			// grafo.printarArestas();
			int resposta = (grafo.verificarConexidade()) ? 1 : 0;
			System.out.println(resposta);
			n = entrada.nextInt();
			m = entrada.nextInt();			
		}
		entrada.close();
	}	
	
}
