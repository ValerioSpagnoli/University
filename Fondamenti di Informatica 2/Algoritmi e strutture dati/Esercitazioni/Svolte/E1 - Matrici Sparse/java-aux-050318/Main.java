import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.StringTokenizer;

public class Main {

	public static void main(String[] args) {
		MatriceSparsa mat1 = readMatFF();
		System.out.println("Original Matrix:");
		System.out.println(mat1);
		System.out.println("##################################");
		System.out.println("##################################");
		System.out.println("");
		System.out.println("");
		System.out.println("Added -> 0,0,5");
		mat1.set(0, 0, 5);
		System.out.println(mat1);
		System.out.println("");
		System.out.println("Added -> 10,10,45");
		mat1.set(10, 10, 45);
		System.out.println(mat1);
		System.out.println("");
		System.out.println("Added -> 10,10,7");
		mat1.set(10, 10, 7);
		System.out.println(mat1);
		System.out.println("");
		System.out.println("Added -> 24,29,1");
		mat1.set(24, 29, 1);
		System.out.println(mat1);
		System.out.println("");
		System.out.println("Added -> 24,29,5");
		mat1.set(24, 29, 5);
		System.out.println(mat1);
		System.out.println("");
		System.out.println("Added -> 18,17,12");
		mat1.set(18, 17, 12);
		System.out.println(mat1);
		System.out.println("");
	}

	private static MatriceSparsa readMatFF() {
		FileReader fr;
		try {
			fr = new FileReader("mat.dat");
			BufferedReader br = new BufferedReader(fr);
			int m,n;
			String line = br.readLine();
			StringTokenizer st = new StringTokenizer(line);
			m = Integer.parseInt(st.nextToken());
			n = Integer.parseInt(st.nextToken());
			MatriceSparsa mat = new MatriceSparsa(m,n);
			for(int i = 0; i < m; i++) {
				line = br.readLine();
				st = new StringTokenizer(line);
				for(int j = 0; j < n; j++) {
					int x = Integer.parseInt(st.nextToken());
					mat.set(i, j, x);
				}
			}
			br.close();
			return mat;
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return null;
	}

}
