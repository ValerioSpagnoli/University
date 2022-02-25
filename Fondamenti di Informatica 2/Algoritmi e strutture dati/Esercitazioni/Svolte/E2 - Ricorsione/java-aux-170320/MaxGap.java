public class MaxGap {

    public static int maxGap(int[] array, int start, int end) {
		if(start == 0) return maxGap(array, start+1, end);
		int n = end-start;
		if(n == 1){
			return array[end-1]-array[start-1];
		}
		int left = maxGap(array, start, start+n/2);
		int right = maxGap(array, start + n/2, end);
		return max(left, right);
    }

    
    
    private static int max(int a, int b){
		if(a>=b) return a;
		else return b;
	}
    
}
