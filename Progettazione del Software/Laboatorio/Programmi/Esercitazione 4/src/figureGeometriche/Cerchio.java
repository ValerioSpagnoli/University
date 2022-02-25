package figureGeometriche;

public class Cerchio extends Elisse{

	//costruttori
	public Cerchio(double raggio) {
		super(raggio, raggio);
	}
	
	public  Cerchio(double raggio, String descrizione) {
		super(raggio, raggio, descrizione);
	}
	
	//metodi
	public double getRaggio() {
		return super.getSemiasseMaggiore();
	}
	
	//servizi
	public String toString() {
		return "Cerchio " + this.getDescrizione() + " raggio = " + this.getSemiasseMaggiore() + ", area = " + this.area() + 
				", perimetro = " + this.perimetro();
	}
}
