package figureGeometriche;

public class Rettangolo extends FiguraGeometrica {
	
	private final double base, altezza;
	
	public Rettangolo(double b, double h) {
		this.base = b;
		this.altezza = h;
	}
	
	public Rettangolo(double b, double h, String descrizione) {
		super(descrizione);
		this.base = b;
		this.altezza = h;
	}
	
	public double getBase() {
		return base;
	}
	public double getAltezza() {
		return altezza;
	}
	
	public double area() {
		return base * altezza;
	}
	
	public double perimetro() {
		return (2*base + 2*altezza);
	}
	
	public String toString() {
		return "Rettangolo " + getDescrizione() + " base = " + this.base + ", altezza = " + this.altezza + 
				", area = " + this.area() + ", perimetro = " + this.perimetro();
	}
	
}
