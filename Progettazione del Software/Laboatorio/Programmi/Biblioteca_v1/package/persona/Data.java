package persona;

import java.util.StringTokenizer;

public class Data {
	int giorno;
	int mese;
	int anno;
	
	public Data(String d) {
		StringTokenizer st = new StringTokenizer(d, "/");
		this.giorno = Integer.parseInt(st.nextToken());
		this.mese = Integer.parseInt(st.nextToken());
		this.anno = Integer.parseInt(st.nextToken());
	}
}
