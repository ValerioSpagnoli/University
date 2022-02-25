package client;

import java.awt.Color;


import javax.swing.BorderFactory;
import javax.swing.JTextField;

public class ColoredButton extends JTextField{
	

	private static final Color defaultColor = Color.LIGHT_GRAY;
	private static final Color winColor = Color.GREEN;
	private static final Color loseColor = Color.RED;
	
	private String number;
	
	public ColoredButton() {
		this.setBackground(defaultColor);
		this.setText("");
		this.setBorder(BorderFactory.createLineBorder(Color.BLACK));
		this.setHorizontalAlignment(JTextField.CENTER);
	}
	
	public boolean checkNumber() {
		if(Integer.parseInt(number)<0 || Integer.parseInt(number)>9) return false;
		else return true;
	}
	
	public void setNumber(String n) {
		number = n;
	}
	
	public String getNumber() {
		return number;
	}
	
	public void setWinColor() {
		this.setBackground(winColor);
	}
	
	public void setLoseColor() {
		this.setBackground(loseColor);
	}
	
	public void setDefaultColor() {
		this.setBackground(defaultColor);
	}
	
	


	
}
