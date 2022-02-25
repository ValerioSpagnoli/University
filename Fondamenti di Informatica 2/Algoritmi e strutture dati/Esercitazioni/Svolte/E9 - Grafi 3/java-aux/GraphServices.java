import java.util.*;

public class GraphServices {

	
	public static <V> void bfs(Graph<V> g) {								
		LinkedList<Node<V>> l = new LinkedList<Node<V>>();					//crea una lista l di nodi
		for(Node<V> n : g.getNodes()){										//per ogni nodo n del grafo
			if(n.stato == Node.Stato.UNEXPLORED){							//se il nodo non è stato esplorato
				bfs(g, n, l);												//chiama la bfs su quel nodo
			}
		}
	}
	
	private static <V> void bfs(Graph<V> g, Node<V> n, LinkedList<Node<V>> l) {
		if(n.stato != Node.Stato.UNEXPLORED) return;						//se il nodo n è stato esplotato -> ritorna
		n.stato = Node.Stato.EXPLORED;										//etichetta il nodo n come esplorato 
		l.addLast(n);														//aggiungi n alla fine di l
		while(!l.isEmpty()){												//finchè l non è vuota
			Node<V> u = l.removeFirst();									//sia u il primo nodo di l, rimuovi u
			System.out.println(u.getElement());								//stampa u
			for(Edge<V> e : g.getOutEdges(u)){								//per ogni lato tra i lati uscenti di u
				Node<V> v = e.getTarget();									//sia v il nodo destinazione del lato (u,v)
				if(v.stato == Node.Stato.UNEXPLORED){						//se v non è stato esplorato
					v.stato = Node.Stato.EXPLORED;							//etichetta v come esplorato
					l.addLast(v);											//aggiungi v alla fine di l
				}
			}
		}		
	}

	public static <V> void sssp(Graph<V> g, Node<V> source) {
		final int INF = 100000;												//distanza infinita
		MinHeap <Node<V>> h = new MinHeap<>();								//coda prioritaria H per rappresentare la nuvola
		HashMap <Node<V>, HeapEntry<Node<V>>> m = new HashMap<>();			//hashmap M di supporto per gestire il rapporto nodo-entry
		
		for(Node<V> u : g.getNodes()){										//per ogni nodo del grafo	
			if(u == source){												//se il nodo è la sorgente
				HeapEntry <Node<V>> hu = h.insert(0, u);					//inserisci il nodo in H con etichetta D[u] = 0
				m.put(u, hu);												//inserisci il nodo e l'entry del nodo in M
			}
			else{															//altrimenti
				HeapEntry <Node<V>> hu = h.insert(INF, u);					//inserisci il nodo in H con etichetta D[u] = INF
				m.put(u, hu);												//inserisci il nodo e l'entry del nodo in M
			} 
		}
		
		while(!h.isEmpty()){												//finchè H non è vuota
			HeapEntry<Node<V>> hu = h.removeMin();							//estrai l'entry hu minimima da h
			Node<V> u = hu.getValue();										//prendo il nodo u dal valore di hu
			
			for(Edge<V> e : g.getOutEdges(u)){								//per ogni arco e nell'insieme degli archi uscenti da u
				Node<V> v = e.getTarget();									//sia v il nodo target
				if(m.get(u).getKey() + e.getWeight() < m.get(v).getKey()){	//se D[u] + peso(e) < D[v]
					h.replaceKey(m.get(v), m.get(u).getKey() + e.getWeight());//modifica la chiave corrispondente a v in H così:
				}															// D[v] = D[u] + peso(e)
			}	
		}
		
		for(Node<V> u : g.getNodes()){
			System.out.println(u + " " + m.get(u).getKey());
		}
	}
	
	public static <V> void mst(Graph<V> G) {
		int i = 0;															//mappa ogni nodo del grafo con un intero 
		for(Node<V> n : G.getNodes()){										//per eseguire le operazioni union-find che
			n.map = i;														//operano su interi
			i++;
		}
		
		Partition<V> P = new Partition(G.getNodes());						//crea una partizione con tutti i nodi del grafo
		MinHeap<Edge<V>> Q = new MinHeap<Edge<V>>();						//crea una coda prioritaria Q per tutti i lati del grafo 
		
		for(Edge<V> e : G.getEdges()){										//per ogni lato del grafo
			Q.insert(e.getWeight(), e);										//aggiunge il lato a Q con chiave il peso del lato
		}
		
		while(!Q.isEmpty()){												//finchè Q non è vuota
			Edge<V> e = Q.removeMin().getValue();							//rimuove il lato e con peso minimo da Q
			Node<V> u = e.getSource();										//u è il nodo sorgente di e
			Node<V> v = e.getTarget();										//v è il nodo destinazione di e
			List<Node<V>> Cu = P.find(u.map);								//Cu è il cluster che contiene il nodo u
			List<Node<V>> Cv = P.find(v.map);								//Cv è il cluster che contiene il nodo v
			if(Cu != Cv){													//se i due cluster sono diversi
				System.out.println(u.getElement() + " " + v.getElement());	//stampa l'arco (u,v)
				P.union(u.map, v.map);										//unisci i due cluster in un unico cluster
			}
		}
	}
	
	
	
	
	
	
}




