package figureGeometriche;

public abstract class FiguraGeometrica {
	
	//proprietà
	private String descrizione = "";
	
	//costruttori
	public FiguraGeometrica() {};
	
	public FiguraGeometrica(String descrizione) {
		this.descrizione = descrizione;
	}
	
	//servizi
	public abstract double area();
	public abstract double perimetro();
	public abstract String toString();
	
	//metodi
	public String getDescrizione() {
		return descrizione;
	}
	
	public void setDescrizione(String descrizione) {
		this.descrizione = descrizione;
	}
	
	

}
