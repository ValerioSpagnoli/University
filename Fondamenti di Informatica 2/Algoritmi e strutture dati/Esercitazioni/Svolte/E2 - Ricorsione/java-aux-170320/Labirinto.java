public class Labirinto {

	private static enum Cella { VUOTA, PIENA };

	private int n;
    private Cella m[][];
    private boolean marcata[][];

    public Labirinto(int n) {
		this.n = n;
		m = new Cella[n][n];
		marcata = new boolean[n][n];
		for(int i = 0; i<n; i++){
			for(int j = 0; j<n; j++){
				m[i][j] = Cella.VUOTA;
				marcata[i][j] = false;
			}
		}
    }

	public void setPiena(int r, int c){
 		m[r][c] = Cella.PIENA;
    }

	private boolean uscita(int r, int c){
  		if(r == n-1 && c == n-1) return true;
		return false;
    }

	public boolean percorribile(int r, int c){
		if(r<n && c<n && r>=0 && c>=0){
			if(m[r][c].equals(Cella.VUOTA) && marcata[r][c] == false){
				return true;
			}
		}
		return false;
    }

	private boolean uscitaRaggiungibileDa(int r, int c){  //ricorsiva
		if(!percorribile(r,c)){
			return false;
		}
		else if(uscita(r,c)){
			marcata[r][c] = true;
			return true;
		}
		else{
			marcata[r][c] = true;
			return uscitaRaggiungibileDa(r+1,c) || uscitaRaggiungibileDa(r,c+1) || uscitaRaggiungibileDa(r-1,c) || uscitaRaggiungibileDa(r,c-1);
		}
		
		


	}

	public boolean risolvibile(){
		if(uscitaRaggiungibileDa(0,0)) return true;
		return false;
	}

	public String toString() {
		String s = "";
		for(int i = 0; i<n ; i++){
			for(int j = 0; j<n; j++){
				if(marcata[i][j] == true){
					s = s+ "+";
				}
				else if(m[i][j].equals(Cella.PIENA)){
					s = s+ "#";
				}
				else if(m[i][j].equals(Cella.VUOTA)){
					s = s+ ".";
				}
			}
			s = s+ "\n";
		}
		return s;
	}
}
