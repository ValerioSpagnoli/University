public class Heap {
   
//######################################################################  classe entry annidata

    public static class HeapEntry {
		int key;
		public HeapEntry(int k){
			this.key = k;
		}
		public int getKey(){
			return this.key;
		}
		public void setKey(int newKey){
			this.key = newKey;
		}
	}
	
//###################################################################### funzioni base

	public enum HEAP_TYPE {MAX_HEAP, MIN_HEAP};
	
	public HeapEntry heap[];
	HEAP_TYPE type;
	int size;
	int capacity;

    public Heap(HEAP_TYPE type, int capacity) {
		this.heap = new HeapEntry[capacity];
		this.type = type;
		this.size = 0;
		this.capacity = capacity;
		for(int i = 0; i<capacity; i++){
			heap[i] = null;
		}
	}
	
	public boolean isEmpty(){
		return size() == 0;
	}
	
	public int parent(int i){
		if(i != 0)
			return (i-1)/2;
		return -1;
	}
	
	public boolean hasLeft(int i){
		if(2*i+1 < size) return true;
		return false;
	}
	
	public boolean hasRight(int i){
		if(2*i+2 < size) return true;
		return false;
	}
	
	public int left(int i){
		if(hasLeft(i)) return 2*i+1;
		return -1;
	}
	
	public int right(int i){
		if(hasRight(i)) return 2*i+2;
		return -1;
	}
		
    public HEAP_TYPE getType() {
        return this.type;
    }

    public int peek() {
        return heap[0].getKey();
    }
    
    public int size() {
        return this.size;
    }
    
    public int getEntryKey(HeapEntry e) {
        return e.getKey();
    }
    
//######################################################################  ordinamento
    
    public int smallestChild(int i){
		int min = left(i);
		if(!hasRight(i)) return min;
		else if(heap[right(i)].getKey() < heap[left(i)].getKey()) min = right(i);
		return min;
	}
	
	public int biggestChild(int i){
		int max = left(i);
		if(!hasRight(i)) return max;
		else if(heap[right(i)].getKey() > heap[left(i)].getKey()) max = right(i);
		return max;
	}
	
	public void swap(int i, int j){
		int temp = heap[i].getKey();
		heap[i].setKey(heap[j].getKey());
		heap[j].setKey(temp);
	}
    
    private int upHeapMax(int i){
		while(i>0){
			if(heap[i].getKey() > heap[parent(i)].getKey()){
				swap(i, parent(i));
				i = parent(i);
			}
			else break;
		}
		return i;
	}
	
	private int downHeapMax(int i){
		while(hasLeft(i)){
			int max = biggestChild(i);
			if(heap[i].getKey() < heap[max].getKey()){
				swap(i, max);
				i = max;
			}
			else break;
		}
		return i;
	}
	
	private int upHeapMin(int i){
		while(i>0){
			if(heap[i].getKey() < heap[parent(i)].getKey()){
				swap(i, parent(i));
				i = parent(i);
			}
			else break;
		}
		return i;
	}
	
	private int downHeapMin(int i){
		while(hasLeft(i)){
			int min = smallestChild(i);
			if(heap[i].getKey() > heap[min].getKey()){
				swap(i, min);
				i = min;
			}
			else break;
		}
		return i;
	}
	
	private void heapify(){
		int start = parent(size-1);
		for(int j = start; j>=0; j--){
			if(getType().equals(HEAP_TYPE.MAX_HEAP)){
				downHeapMax(j);
			}
			else if(getType().equals(HEAP_TYPE.MIN_HEAP)){
				downHeapMin(j);
			}
		}
	}

//######################################################################  costruzione
    
    public HeapEntry add(int key) {
        HeapEntry e = new HeapEntry(key);
        int t = size;
        if(isEmpty()){
			heap[0] = e;
			size++;
		}
		else{
			int i = size();
			if(size()<capacity){
				heap[i] = e;
				size++; 
			}
			if(getType().equals(HEAP_TYPE.MAX_HEAP)){
				t = upHeapMax(i);
			}
			else if(getType().equals(HEAP_TYPE.MIN_HEAP)){
				t = upHeapMin(i);
			}
		}
		return heap[t];   
    }

    public int poll() {
		int res = heap[0].getKey();
        if(!isEmpty()){
			heap[0].setKey(heap[size-1].getKey());
			heap[size-1] = null;
			size--;	
			if(getType().equals(HEAP_TYPE.MAX_HEAP)){
				downHeapMax(0);
			}
			else if(getType().equals(HEAP_TYPE.MIN_HEAP)){
				downHeapMin(0);
			}
		}
		return res;
    }

    public static Heap array2heap(int[] array, HEAP_TYPE type) {
        Heap res = new Heap(type, array.length);
        for(int i = 0; i<array.length; i++){
			HeapEntry e = new HeapEntry(array[i]);
			res.heap[i] = e; 
			res.size++;
		}
		res.heapify();
        return res;
    }

    public void print() {
		System.out.print(" ");
        for(int i = 0; i<size; i++){
			System.out.print(heap[i].getKey() + " ");
		}
		System.out.println();
    }

    public static void heapSort(int[] array) {
        Heap res = array2heap(array, HEAP_TYPE.MIN_HEAP);
        for(int i = 0; i<array.length; i++){
			array[i] = res.poll();
		}
    }

    public void updateEntryKey(HeapEntry e, int key) {
		e.setKey(key);
		heapify();
    }

}
