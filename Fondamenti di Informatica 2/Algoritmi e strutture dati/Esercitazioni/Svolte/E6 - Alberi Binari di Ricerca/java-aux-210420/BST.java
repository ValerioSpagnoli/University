public class BST<V> {
	
	private Node<V> root;
	
	private class Node<V>{
		private int key;
		private V value;
		private Node<V> left;
		private Node<V> right;
		
		public Node(int key, V value){
			this.key = key;
			this.value = value;
		}
	}
	
    public BST(int key, V value) {
		this.root = new Node(key, value);
    }

//###################################################################### INSERIMENTO

    public void insert(int k, V v) {					
        if(this.root == null){
			this.root = new Node<V>(k, v);
		}
		else{
			insert(this.root, k, v);
		}
    }
    
    private void insert(Node<V> node, int k, V v){	
		if(node.key == k){								// se il nodo ha chiave k
			node.value = v;								// aggiorna il valore	
		}
		else if(k < node.key){							// se il nodo corrente ha chiave maggiore di k (la chiave k sta in left)
			if(node.left == null){						// se il sotto albero sinitro è null
				node.left = new Node(k,v);				// inserisci un nuovo nodo nel sotto albero sinistro
			}											// altrimenti
			else insert(node.left, k, v);				// scendi sul sotto albero sinistro
		}
		else if(k > node.key){							// se il nodo corrente ha chiave miniore di k (la chiave k sta in right)
			if(node.right == null){						// se il sotto albero destro è null
				node.right = new Node(k,v);				// inserisci un nuovo nodo nel sotto albero destro
			}											// altrimenti
			else insert(node.right, k, v);				// scendi nel sotto albero destro
		}
	}

//###################################################################### RICERCA

    public V find(int k) {
		if(this.root == null) return null;
		else return find(this.root, k);
    }
   
    private V find(Node<V> node, int k){							
		if(node == null){								// se il nodo corrente è null -> fallimento
			return null;			
		}
		else if(node.key == k){							// se il nodo corrente ha chiave k 
			return node.value;							// ritorna il valore del nodo corrrente  -> successo
		}
		else if(k < node.key){							// se il nodo corrente ha chiave maggiore di k (la chiave k sta in left)
			return find(node.left, k);					// scendi nel sotto albero sinistro
		}
		else { 											// altrimenti (la chiave k sta in right)
			return find(node.right, k);					// scendi nel sotto albero destro
		}
	}
	
//###################################################################### RICERCA DEL NODO CON CHIAVE MINIMA

    public int findMin() {								
        if(this.root == null) return -1;				
        else return findMin(this.root).key;
    }
    
    private Node<V> findMin(Node<V> node){				// il  nodo con chiave minima è quello che si trova più a sinistra
		if(node.left == null){							// se il sotto albero sinistro è null 
			return node;								// il nodo corrente è quello più a sinistra -> ricerca finita
		}
		else {											// altrimenti
			return findMin(node.left);					// scendi nel sotto albero sinistro
		}
	}
    
//###################################################################### RIMOZIONE DEL NODO CON CHIAVE MINIMA

    public void removeMin() {
        if(this.root == null) return;					// se la radice è null -> nessuna rimozione da effettuare
		this.root = removeMin(this.root);				// altrimenti assegnaalla radice il risultato della ricorsione sulla radice
    }
    
    private Node<V> removeMin(Node<V> node){			// il  nodo con chiave minima è quello che si trova più a sinistra
		if(node.left == null){							// se il sotto albero sinistro è null
			return node.right;							// ritorna il sotto albero destro
		}												// altrimenti assegna al sotto albero sinsitro il risultato della ricorsione
		node.left = removeMin(node.left);				// sul sotto albero sinsitro (assegnerà null oppure il fratello destro del min)
		return node;									// ritorna il nodo corrente
	}
    
//######################################################################

    public void remove(int k) {
        if(this.root == null){							// se la radice è null -> nessuna rimozione da effettuare
			return; 	
		}				
        this.root = remove(this.root, k);				// altrimenti assegna alla radice il risultato della ricorsione sulla radice
    }
    
    private Node<V> remove(Node<V> node, int k){			
		if(node == null){								// se il nodo corrente è null
			return null;								// ritorna null
		}
		else if(k < node.key){							// se il nodo corrente ha chiave maggiore di k (la chiave k si trova in left)
			node.left = remove(node.left, k);			// assegna al sotto albero sinistro il risultato della ricorsione sul
		}												// sotto albero sinsitro
		else if(k > node.key){							// se il nodo corrente ha chiave minore di k (la chiave k si trova in right)
			node.right = remove(node.right, k);			// assegna al sotto albero destro il risultato della ricorsione sul
		}												// sotto albero destro
		else {
														// CASO 1 : un figlio 
			if(node.right == null){						// se il sotto albero destro è null
				return node.left;						// ritorna il sotto albero sinsitro (che va a sostituire il nodo da eliminare)
			}							
			if(node.left == null){						// se il sotto albero sinsitro è null
				return node.right;						// ritorna il sotto albero destro (che va a sostituire il nodo da eliminare)
			}
														// CASO 2: due figli
            Node<V> to_remove = node;					// memorizza il nodo corrente in to_remove
            node = findMin(to_remove.right);			// assegna al nodo corrente il predecessore di to_remove (ovvero di node)
            Node<V> nn = new Node<V>(node.key, node.value); // crea un nuovo nodo con chiave e valore del predecessore
            nn.right = removeMin(to_remove.right);		// assegna al sotto albero destro di nn il nodo minimo del sotto albero destro di to_remove
            nn.left = to_remove.left;					// assegna al sotto albero sinistro di nn il sotto albero sinsitro di to_remove
            node = nn;									// assegna al predecessore il nuovo nodo
							
		}
		return node;									// ritorna il nodo corrente
	}
    
//######################################################################

    void print(){
		print(this.root);
		System.out.println();
    }
    
    private void print(Node<V> node){
		if(node == null) return;
		print(node.left);
		System.out.print("(" + node.key + ", " + node.value + ") ");
		print(node.right);
	}
	
 
    public int predecessor(int k) {
		Node<V> predecessor = predecessor(this.root, k);// cerca il predecessore partendo dalla radice
        if(this.root == null) return -1;				// se la radice è null -> non c'è il predecessore
        return predecessor.key;							// altrimenti ritorna la chiave del predecessore
    }
    
    private Node<V> predecessor(Node<V> node, int k){
		if(node == null) return null;					// se il nodo corrente è null ritorna null
		else if(k <= node.key){							// se il nodo corrente ha chiave maggiore di k (il predecessore si trova in left)
			return predecessor(node.left, k);			// scendi nel sotto albero sinistro
		}
		Node<V> n = predecessor(node.right, k);			// altrimenti scendi nel sotto albero destro
		if(n == null) return node;						// se il sotto albero destro è null ritorna il nodo corrente
		return n;										// altrimenti ritorna n
	}

}
