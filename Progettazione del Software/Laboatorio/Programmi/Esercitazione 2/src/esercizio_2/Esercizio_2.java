package esercizio_2;

public class Esercizio_2 {
	public static void main (String[] args) {
		String s1 = "massimo pericolo";
		String output = "";
		int l = s1.length();
		for(int i = 0; i < l; i++) {
			
			if(i%2!=0) {
				output = output + s1.substring(i, i+1).toUpperCase();
			}
			
			else {
				output = output + s1.substring(i, i+1);
			}
			
		}
		
		System.out.println(output);	
	}
}