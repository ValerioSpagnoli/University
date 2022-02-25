import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.StringTokenizer;

public class Graph<V> {
	
	private LinkedList <GraphNode<V>> nodes;
	private int numberNodes;
	private int numberEdges;

    public Graph () {
		nodes = new LinkedList <GraphNode<V>> (); // lista di nodi
		numberNodes = 0;
		numberEdges = 0;
	}

    public List<GraphNode<V>> getNodes() {
		LinkedList <GraphNode<V>> ret = new LinkedList<GraphNode<V>>();		//crea una nuova lista ret
		for(GraphNode<V> n : nodes){											//per ogni nodo in node
			try{										
				ret.add((GraphNode<V>)n.clone());							//aggiungi a ret il clone del nodo in node
			} catch (CloneNotSupportedException e){
				e.printStackTrace();
			}
		}
		return ret;															//ritorna ret
		
    }

    public List<GraphNode<V>> getNeighbors(GraphNode<V> n){					//prende in ingresso un nodo n del grafo 
		LinkedList <GraphNode<V>> ret = new LinkedList<GraphNode<V>>();		//crea una nuova lista ret
		for(GraphNode<V> edge : n.outEdges){								//per ogni lato nella lista dei lati di n
			try{
				ret.add((GraphNode<V>) edge.clone());						//aggiungi a ret il clone del lato
			} catch (CloneNotSupportedException e){
				e.printStackTrace();
			}
		}
		return ret;															//ritorna ret
    }

    public GraphNode addNode(V value) {
		for(GraphNode<V> n : nodes){										//per ogni nodo in nodes
			if(n.value.equals(value)){										//se il valore di n è uguale al valore in input
				return n;													//ritorna n
			}
		}																	//altrimenti
		GraphNode<V> n = new GraphNode<V>();								//crea un nuovo nodo n
		n.value = value;													//assegna value a n
		n.state = GraphNode.Status.UNEXPLORED;								//metti -non esplorato- come stato di n
		n.outEdges = new LinkedList<GraphNode<V>>();						//crea una lista vuota di lati di n
		nodes.add(n);														//aggiungi n a nodes
		numberNodes++;														//incrementa il numero di nodi nel grafo
		return n;															//ritorna n
    }

    public void addEdge(GraphNode<V> s, GraphNode<V> t) {					//dati due nodi s e t	
        s.outEdges.add(t);													//aggiunge t alla lista dei vicini di s
        t.outEdges.add(s);													//aggiunge s alla lista dei vicini di t
        numberEdges++;														//incrementa il numero di nodi
    }

    public V getNodeValue(GraphNode<V> n) {									//dato un nodo n							
        return n.value;														//ritorna il valore del nodo
    }

    public void removeEdge(GraphNode<V> v1, GraphNode<V> v2){				//dati due noti v1 e v2 (che formano un arco)
		boolean b1 = false;													
		boolean b2 = false;
											
		if(v1.outEdges.contains(v2)){										//se la lista dei vicini di v1 contiene v2
			v1.outEdges.remove(v2);											//rimuovi dalla lista dei vicini di v1 il nodo v2
			b1 = true;
		} 																
		if(v2.outEdges.contains(v1)){ 										//se la lista dei vicini di v2 contiene v1
			v2.outEdges.remove(v1);											//rimuovi dalla lista dei vicini di v2 il nodo v1
			b2 = true;
		}
		if(b1 && b2) numberEdges--;											//decrementa il numero di archi
    }

    public void removeNode(GraphNode<V> v){									//dato un nodo v
		if(nodes.contains(v)){												//se la lista dei nodi contiene v
			for(GraphNode<V> n : nodes){									//per ogni nodo n nella lista dei nodi 
				removeEdge(n, v);											//elimina l'arco n v
			}
		}
		nodes.remove(v);													//rimuovi il nodo v dalla lista dei nodi
    }


//####################################################################//


    public static <V> Graph<V> readFF(File input){
		Graph<V> ret = new Graph<>();
		try{
			BufferedReader br = new BufferedReader(new FileReader(input));
			String firstLine = br.readLine();
			StringTokenizer tok = new StringTokenizer(firstLine);
			int v = Integer.parseInt(tok.nextToken());
			int e = Integer.parseInt(tok.nextToken());
			for(int i=0; i<e; i++){
				tok = new StringTokenizer(br.readLine());
				while(tok.hasMoreTokens()){
					GraphNode<V> v1 = ret.addNode((V) tok.nextToken());
					GraphNode<V> v2 = ret.addNode((V) tok.nextToken());
					ret.addEdge(v1, v2);
				}	
			}
			br.close();
			if(ret.numberNodes < v){
				int r = v - ret.numberNodes;
				int name = e + 1;
				for(int i = 0; i<r; name++, i++) {
					ret.addNode((V) (name + ""));
				}
			}
		} catch (FileNotFoundException e){
			e.printStackTrace();
		} catch (IOException e){
			e.printStackTrace();
		}
		return ret;
    }

    public String printAdj() {
		String buf = "";
		for(GraphNode<V> n : nodes){
			buf = buf + n.value + ": ";
			for(GraphNode<V> e : n.outEdges){
				buf = buf + e.value + " ";
			}
			buf = buf + "\n";
		}
		return buf;
    }
    
    @Override
    public String toString(){
		String buf = "";
		buf = buf + numberNodes + " " + numberEdges + "\n";
		for(GraphNode<V> n : nodes){
			if(n.state == GraphNode.Status.UNEXPLORED){
				DFSprintEdges(n, buf);
			}
		}
		return buf;
    }

    private void DFSprintEdges(GraphNode<V> node, String buf) {
		if(node.state != GraphNode.Status.UNEXPLORED) return;				//se il nodo è stato esplorato -> return
		node.state = GraphNode.Status.EXPLORING;							//etichetta il nodo come in esplorazione
		for(GraphNode<V> e : node.outEdges){								//per ogni nodo e nella lista dei vicini di node
			if(e.state == GraphNode.Status.UNEXPLORED){						//se e non è stato esplorato
				buf = buf + node.value + " " + e.value + "\n";				//aggiungi al buf la stampa di e
			}			
		}										
		for(GraphNode<V> e : node.outEdges){								//per ogni nodo e nella lista dei vicini di node
			if(e.state == GraphNode.Status.UNEXPLORED){						//se e non è stato esplorato
				DFSprintEdges(e, buf);										//fai ricorsione sul nodo e
			}
		}
		node.state = GraphNode.Status.EXPLORED;								//etichetta il nodo come esplorato
	}

	public int nConComp(){					
		int ret = 0;								
		for(GraphNode<V> e : nodes){										//per ogni nodo e nella lista dei nodi
			if(e.state == GraphNode.Status.UNEXPLORED){						//se il nodo e non è stato esplorato (la DFS non lo ha raggiunto)
				ret++;														//significa che appartiene ad una nuova componente connessa
				DFS(e);														//chiama la DFS su questo nodo (che visiterà tutta la sua componente connessa)
			}
		}
		return ret;
    }
    
    public List<Graph<V>> getConComp(){
		LinkedList<Graph<V>> ret = new LinkedList<Graph<V>>();				//crea una lista di grafi
		for(GraphNode<V> node : nodes){										//per ogni nodo nella lista di nodi
			if(node.state == GraphNode.Status.UNEXPLORED){					//se il nodo non è stato esplorato
				Graph<V> g = new Graph<V>();								//crea un nuovo grafo
				ret.add(g);													//aggiungi il grafo alla lista di grafi
				DFSadd(node, g.nodes);										//chiama la DFSadd per riempire il grafo con i nodi 
			}																//della componente connessa di node;
		}
		return ret;
    }
    
    public void DFSadd(GraphNode<V> node, LinkedList<GraphNode<V>> list){	
		if(node.state != GraphNode.Status.UNEXPLORED) return;				//se il nodo è stato esplorato -> return
		node.state = GraphNode.Status.EXPLORING;							//etichetta il nodo come in esplorazione
		list.add(node);														//aggiungi il nodo alla lista
		for(GraphNode<V> n : node.outEdges){								//per ogni nodo n nella dei vicini del nodo in input
			if(n.state == GraphNode.Status.UNEXPLORED){						//se n non è stato esplorato
				DFSadd(n, list);											//fai ricorsione su n
			}
		}
		node.state = GraphNode.Status.EXPLORED;								//etichetta il nodo come esplorato
	}

    private void DFS(GraphNode<V> node) {
		if(node.state != GraphNode.Status.UNEXPLORED) return;				//se il nodo è stato esplorato -> return
		node.state = GraphNode.Status.EXPLORING;							//etichetta il nodo come in esplorazione
		for(GraphNode<V> e : node.outEdges){								//per ogni nodo e nella lista dei vicini di node
			if(e.state == GraphNode.Status.UNEXPLORED){					//se e non è stato esplorato
				DFS(e);														//fai ricorsione su e
			}	
		}											
		node.state = GraphNode.Status.EXPLORED;								//etichetta il nodo come esplorato
	}

	

//####################################################################//
    
    
	public static class GraphNode<V> implements Cloneable{

        public enum Status {UNEXPLORED, EXPLORED, EXPLORING}

        protected V value;
        protected LinkedList<GraphNode<V>> outEdges;

        // keep track status
        protected Status state;

		@Override
		public String toString() {
			return "GraphNode [value=" + value + ", state=" + state + "]";
		}

		@Override
		protected Object clone() throws CloneNotSupportedException {
			return super.clone();
		}
		
		
    }

}
