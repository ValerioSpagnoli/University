package client;

import java.util.Arrays;

public class Character implements Comparable<Character> {

	private String name;
	private String surname;
	private String casata;
	private String role; //M or S --> M = main character | S = secondary character

	public Character(String name, String surname, String casata, String role) {
		this.name = name;
		this.surname = surname;
		this.casata = casata;
		this.role = role;
	}

	public String getName() {
		return name;
	}
	
	public String getSurname() {
		return surname;
	}

	public String getCasata() {
		return casata;
	}
	
	public String getRole() {
		return role;
	}


	@Override
	public int compareTo(Character c) {
		if(c!=null) {
			if(c.getRole().equals("M") && this.getRole().equals("S")) { //c è maggiore di this
				return 1;
			}
			else if(c.getRole().equals("S") && this.getRole().equals("M")) { //this è maggiore di c
				return -1;
			}
		
			else { //hanno lo stesso ruolo
			
				int compareSurname = this.getSurname().compareTo(c.getSurname());
			
				if(compareSurname > 0) { // c è maggiore di this
					return 1;
				}
				else if(compareSurname < 0) { //this è maggiore di c
					return -1;
				}
				else { //sono uguali per cognome
				
					int compareName = this.getName().compareTo(c.getName());
				
					if(compareName > 0) { //c è maggiore di this
						return 1;
					}
					else if(compareName < 0) { //this è maggiore di c
						return -1;
					}
					else { //sono uguali
					return 0;
					}
				}
			}
		}
		else return -1;
	}

	@Override
	public String toString() {
		return getName() + " "+ getSurname() + " - "+getRole();
	}
	
	
	
	
}
