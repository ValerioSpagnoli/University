public class Kth {
	
	private Heap minHeap;
	private Heap maxHeap;
	private int k;
	
	
    public Kth(int k) {
		this.minHeap = new Heap(Heap.HEAP_TYPE.MIN_HEAP, k);
		this.maxHeap = new Heap(Heap.HEAP_TYPE.MAX_HEAP, k);
		this.k = k;
	}
	
    public void insert(int key) {
		if(maxHeap.size() < k){
			maxHeap.add(key);
		}
		else if(key >= maxHeap.peek()){
			minHeap.add(key);
		}
		else{
			int old = maxHeap.poll();
			maxHeap.add(key);
			minHeap.add(old);
		}
    }

    public int get() {
		if(maxHeap.size() == k){
			return maxHeap.peek();
		}
		return 0;
    }

    public void remove() {
        if(minHeap.size() == 0){
			maxHeap.poll();
		}
		else{
			int key = minHeap.poll();
			maxHeap.poll();
			maxHeap.add(key);
		}
    }

}
