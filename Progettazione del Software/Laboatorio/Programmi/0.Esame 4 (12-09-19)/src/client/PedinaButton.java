package client;

import java.awt.Color;

import javax.swing.BorderFactory;
import javax.swing.JPanel;

public class PedinaButton extends JPanel{
	
	public static final Color defaultColor = Color.LIGHT_GRAY;
	public static final Color cyanColor = Color.CYAN;
	public static final Color yellowColor = Color.YELLOW;
	
	
	public PedinaButton() {
		this.setBackground(defaultColor);
		this.setBorder(BorderFactory.createLineBorder(Color.BLACK));
	}
	
	public void setDefaultColor() {
		this.setBackground(defaultColor);
	}
	public void setCyanColor() {
		this.setBackground(cyanColor);
	}
	public void setYellowColor() {
		this.setBackground(yellowColor);
	}
	public Color getColor() {
		return this.getBackground();
	}
	
	
}
