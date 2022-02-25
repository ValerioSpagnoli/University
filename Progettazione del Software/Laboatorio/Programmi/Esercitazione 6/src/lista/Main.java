package lista;

import java.util.List;

public class Main {
	public static void main(String[] args) {
		testMiaLista();
	}
	
	public static void testMiaLista() {
		List<String> s1 = new MiaLista<>();
		
		for(int i = 0; i<20; i++) {
			s1.add(String.valueOf(i));
		}
		System.out.println(s1);
		
		//prova iterazione con iteratore
		for(String s : s1) {
			System.out.print(s+ ", ");
		}
		System.out.println();
		
		s1.remove(2);
		System.out.println(s1);
		
		s1.remove(1);
		System.out.println();
		
		//prova iterazione con iteratore
		for(String s : s1) {
			System.out.print(s+ ", ");
		}
		System.out.println();
		
	}
	
	

}
