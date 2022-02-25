import java.util.LinkedList;
import java.util.List;

public class GraphServices<V>{

	public static <V> void sweep(Graph<V> g) {
		g.resetStatus();													//reset
			
		int loctime = 0;													//poni la variabile local time a 0
		
		for(Graph.GraphNode<V> n : g.getNodes()){							//per ogni nodo in del grafo
			System.out.println("Root : " + n.value);						//stampa il nodo (che sta facendo da radice)
			loctime = loctime + sweep(n, loctime);							//chiama sweep
		}	
	}
	
	public static <V> int sweep(Graph.GraphNode<V> n, int time){
		if(n.state != Graph.GraphNode.Status.UNEXPLORED) return 0;			//se il nodo è stato esplorato (o sta in esplorazione)
																			//return 0
		int loctime = 1;													//poni local time a 1
		n.state = Graph.GraphNode.Status.EXPLORING;							//etichetta il nodo come in esplorazione
		n.timestamp = time;													//poni timestamp = time (in input = local time totale)
		
		for(Graph.GraphNode<V> e : n.outEdges){								//per ogni vicino e di n
			
			System.out.print("\t" + n.value + "(" + n.timestamp + ") " + " -> " + e.value + "(" + e.timestamp + ") ");
			
			if(e.state == Graph.GraphNode.Status.UNEXPLORED){				//se e non è stato esplorato l'arco è tree
				System.out.println("{TREE EDGE}\n");
				loctime = loctime + sweep(e, time+1);						//fai ricorsione su e
			}
			else if(e.state == Graph.GraphNode.Status.EXPLORING){			//se e sta in esplorazione  l'arco è back
				System.out.println("{BACK EDGE}\n");
			}
			else if(e.state == Graph.GraphNode.Status.EXPLORED){			//se e è stato esplorato
				if(n.timestamp < e.timestamp){								//se e è stato esplorato prima dopo n l'arco è foward
					System.out.println("{FOWARD EDGE}\n");
				}
				else {														//altrimenti l'arco è cross
					System.out.println("{CROSS EDGE}\n");
				}
			}
		}
		n.state = Graph.GraphNode.Status.EXPLORED;							//etichetta il nodo come esplorato
		return loctime;
	}


//####################################################################//	
	
	public static <V> void topologicalSort(Graph<V> g) {
		g.resetStatus();															//reset
		
		LinkedList<Graph.GraphNode<V>> l = new LinkedList<Graph.GraphNode<V>>();	//crea la lista l
		
		for(Graph.GraphNode<V> n : g.getNodes()){									//per ogni nodo n del grafo
			if(n.state == Graph.GraphNode.Status.UNEXPLORED){						//se n non è stato esplorato
				if(DDFS(n,l)>0){ 													//se la DDFS trova un back								
					System.out.println("Impossibile esegure l'ordinamento topologico -> G non è un DAG");
					return;
				}
			}
		}
		
		for(Graph.GraphNode<V> n : l){												//per ogni nodo in l
			System.out.print(n.value + " ");										//stampa il valore del nodo
		}
		System.out.println();
	}
	
	private static<V> int DDFS (Graph.GraphNode<V> n, LinkedList<Graph.GraphNode<V>> l){ //variante DFS che aggiunge i nodi a l e restituisce un int > 0 se trova un arco foward o cross
		if(n.state == Graph.GraphNode.Status.EXPLORING)	return 1; 		//arco back -> no DAG
		if(n.state == Graph.GraphNode.Status.EXPLORED) return 0;  		//arco foward o cross -> DAG
		
		n.state = Graph.GraphNode.Status.EXPLORING;						//etichetta lo stato di n come in esplorazione
		int ret = 0;											
		
		for(Graph.GraphNode<V> e : n.outEdges){							//per ogni vicino di n
			ret = ret + DDFS(e, l);										//fai ricorsione
		}
		
		n.state = Graph.GraphNode.Status.EXPLORED;						//etichetta lo stato di n come esplorato
		l.addFirst(n);													//aggiungi n a l
		return ret;	
	}
	
		
//####################################################################//	

	private static <V> void transposedDFS(Graph.GraphNode<V> n, LinkedList<Graph.GraphNode<V>> l){ //variante DFS che naviga
		if(n.state != Graph.GraphNode.Status.UNEXPLORED) return;								   //gli archi in senso opposto
		n.state = Graph.GraphNode.Status.EXPLORING;												   //e aggiunge i nodi alla lista l
		for(Graph.GraphNode<V> e : n.inEdges){													   //nell'ordine di visita
			transposedDFS(e, l);
		}
		l.addLast(n);
		n.state = Graph.GraphNode.Status.EXPLORED;
	}
	
	private static <V> void ordinaryDFS(Graph.GraphNode<V> n, LinkedList<Graph.GraphNode<V>> l){ 	//variante DFS che naviga
		if(n.state != Graph.GraphNode.Status.UNEXPLORED) return;								    //gli archi in senso ordinario
		n.state = Graph.GraphNode.Status.EXPLORING;													//e aggiunge i nodi alla lista l
		for(Graph.GraphNode<V> e : n.outEdges){														//nell'ordine di visita
			ordinaryDFS(e, l);
		}
		l.addFirst(n);
		n.state = Graph.GraphNode.Status.EXPLORED;
	}
	
	public static <V> void strongConnectedComponents(Graph<V> g) {					
		g.resetStatus();															//reset
		
		LinkedList<Graph.GraphNode<V>> l1 = new LinkedList<Graph.GraphNode<V>>();	//crea una lista l1
		for(Graph.GraphNode<V> n : g.getNodes()){									//per ogni nodo n del grafo
			if(n.state == Graph.GraphNode.Status.UNEXPLORED){						//se n non è stato esplorato
				ordinaryDFS(n, l1);													//chiama la DFS ordinaria (che aggiunge i nodi ad l1)
			}
		}	  
	  
		g.resetStatus();															//reset
		
		for(Graph.GraphNode<V> n : l1){												//per ogni nodo n in l1 (che contiene i nodi visitati da DFS ordinaria)
			if(n.state == Graph.GraphNode.Status.UNEXPLORED){						//se n non è stato esplorato
				LinkedList<Graph.GraphNode<V>> l2 = new LinkedList<Graph.GraphNode<V>>();	//crea una lista l2
				transposedDFS(n, l2);												//chiama la DFS trasposta (che aggiunge i nodi ad l2)
				System.out.println("Strong connect component:");					//per la componente fortemente connsessa trovata 
				for(Graph.GraphNode<V> e : l2){										//per ogni nodo e  in l2
					System.out.print(e.value + " ");								//stampa il valore di e
				}
				System.out.println();
			}
		}  
	}
	
	
	
	
//####################################################################// QUESITO 1 ESAME GIUGNO 2020 A	

	public static <V> void connectedComponent(Graph<V> g, Graph.GraphNode<V> s, int k){
		g.resetStatus();
		LinkedList<Graph.GraphNode<V>> l = new LinkedList<>();
		l.addFirst(s);
		s.state = Graph.GraphNode.Status.EXPLORING;
		connectedComponent(g, s, k, l);
		s.state = Graph.GraphNode.Status.EXPLORED;
		
        if(l.size()>k) System.out.println("NULL : l.size() > k");
        else{
			for(Graph.GraphNode<V> n : l){
				System.out.print(n.value + " ");
			}
			System.out.println();
		}
	}

	
	public static <V> void connectedComponent(Graph<V> g, Graph.GraphNode<V> s, int k, LinkedList<Graph.GraphNode<V>> l){
		s.state = Graph.GraphNode.Status.EXPLORING;
		for(Graph.GraphNode<V> n : s.outEdges){
			if(n.state == Graph.GraphNode.Status.UNEXPLORED){
				l.addFirst(n);
				connectedComponent(g, n, k, l);
			}
		}
		s.state = Graph.GraphNode.Status.EXPLORED;	
	}


//####################################################################// QUESITO 1 ESAME GIUGNO 2020 B
	
	public static <V> LinkedList<Graph.GraphNode<V>> viciniEntroK (Graph<V> g, Graph.GraphNode<V> s, int k){
		g.resetStatus();
		LinkedList<Graph.GraphNode<V>> l = new LinkedList<>();
		LinkedList<Graph.GraphNode<V>> Q = new LinkedList<>();
		LinkedList<Graph.GraphNode<V>> aux = new LinkedList<>();
		Q.addLast(s);
		l.addLast(s);
		
		int x = 0;
		
		while(!Q.isEmpty() && x<=k){
			Graph.GraphNode<V> u = Q.removeFirst();
			while(!aux.isEmpty()){
				Graph.GraphNode<V> a = aux.remove();
				if(!l.contains(a)) l.addLast(a);
			}
			for(Graph.GraphNode<V> n : u.outEdges){
				if(n.state == Graph.GraphNode.Status.UNEXPLORED){
					n.state = Graph.GraphNode.Status.EXPLORED;
					Q.addLast(n);
					aux.addLast(n);
				}
			}
			x++;	
		}
		return l;
	}
	


	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}
