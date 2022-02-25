
import java.util.*;

public class InvertiLista {

	public static void invertiLista(LinkedList<Integer> list) {
		invertiListaAux(list, 0, list.size()-1);
	}
	
	private static void invertiListaAux(LinkedList<Integer> list, int low, int high){
		if(low<=high){
			int temp = list.get(low);
			list.set(low, list.get(high));
			list.set(high, temp);
			invertiListaAux(list, low+1, high-1);
		}	
	}
	
}
