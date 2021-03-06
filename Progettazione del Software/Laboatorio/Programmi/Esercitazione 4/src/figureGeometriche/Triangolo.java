package figureGeometriche;

public class Triangolo extends FiguraGeometrica{
	
	//proprietà
	private final double l1;
	private final double l2;
	private final double l3;
	
	//costruttori
	public Triangolo(double a, double b, double c) {
		this.l1 = a;
		this.l2 = b;
		this.l3 = c;
	}
	
	public Triangolo(double a, double b, double c, String descrizione) {
		super(descrizione);
		this.l1 = a;
		this.l2 = b;
		this.l3 = c;
	}
	
	//metodi
	public double getLatoUno() {
		return l1;
	}
	public double getLatoDue() {
		return l2;
	}
	public double getLatoTre() {
		return l3;
	}
	
	//servizi
	public double area() {
		double sp = perimetro()/2;
		return Math.sqrt(sp * (sp-l1) * (sp-l2) * (sp-l3));
	}
	
	public  double perimetro() {
		return l1+l2+l3;
	}
	
	public String toString() {
		return "Triangolo" + getDescrizione() + "lati: " + l1 + ", " + l2 + ", " + l3 + ", " +
				"area: " + area() + "perimetro: " + perimetro();
	}

	
}
