public class Heap {

    public enum HEAP_TYPE {MAX_HEAP, MIN_HEAP};

    public static class HeapEntry {}

    public Heap(HEAP_TYPE type, int capacity) {}

    public HEAP_TYPE getType() {
        return HEAP_TYPE.MAX_HEAP;
    }

    public int peek() {
        return 0;
    }

    public HeapEntry add(int key) {
        return null;
    }

    public int getEntryKey(HeapEntry e) {
        return 0;
    }

    public int size() {
        return 0;
    }

    public int poll() {
        return 0;
    }

    public static Heap array2heap(int[] array, HEAP_TYPE type) {
        return null;
    }

    public void print() {
        return;
    }

    public static void heapSort(int[] array) {
        return;
    }

    public void updateEntryKey(HeapEntry e, int key) {
        return;
    }

}
