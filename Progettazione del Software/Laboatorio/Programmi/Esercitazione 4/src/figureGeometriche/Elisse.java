package figureGeometriche;

public class Elisse extends FiguraGeometrica{
	
	//proprietà
	private final double semiasseMaggiore, semiasseMinore;
	
	//costruttori
	public Elisse(double a, double b) {
		if(a>b) {
			this.semiasseMaggiore = a;
			this.semiasseMinore = b;
		}
		else {
			this.semiasseMaggiore = b;
			this.semiasseMinore = a;
		}
	}
	
	public Elisse(double a, double b, String descrizione) {
		super(descrizione);
		if(a>b) {
			this.semiasseMaggiore = a;
			this.semiasseMinore = b;
		}
		else {
			this.semiasseMaggiore = b;
			this.semiasseMinore = a;
		}
	}
	
	//metodi
	public double getSemiasseMaggiore() {
		return semiasseMaggiore;
	}
	public double getSemiasseMinore() {
		return semiasseMinore;
	}
	
	//serivi
	public double area() {
		return Math.PI * semiasseMaggiore * semiasseMinore;
	}
	
	public double perimetro(){
		return 2*Math.PI * Math.sqrt((Math.pow(semiasseMaggiore, 2) + Math.pow(semiasseMinore, 2))/2); 
	}
	
	public String toString() {
		return "Elisse " + getDescrizione() + " semiasse Maggiore =  " + semiasseMaggiore + ", semiasseMinore = " + semiasseMinore + 
				", area = " + this.area() + ", perimetro = " + this.perimetro();
	}
	

	
	
	
	
	
	
}
