package e100920.TicketCell;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

public class TicketCell extends JLabel {
    // NOTA BENE: non sono riuscito a far colorare questa Jlabel,
    // si colora  nel momento in cui la istanzio ma nel fare setSelected(boolean)
    // non funziona il colore.
    private static ArrayList<Integer> NUMBERS;
    private boolean selected = false;

    public TicketCell() {
        super(String.valueOf(getRandomNumber()));
        setBorder(BorderFactory.createLineBorder(Color.BLACK));
        setOpaque(true);
    }

    public int getValue() {
       return Integer.parseInt(getText());
    }


    public void setSelected(boolean selected) {
        this.selected = selected;
        if (selected) {
            setBackground(Color.GREEN);
        } else {
            setBackground(Color.WHITE);
        }
    }

    public boolean isSelected() {
        return selected;
    }

    private static int getRandomNumber() {
        if (NUMBERS == null) {
            NUMBERS = new ArrayList<>();
            for (int i=1; i<=90; i++) {
                NUMBERS.add(i);
            }
        }
        int res = NUMBERS.get((int) (Math.random() * NUMBERS.size()));
        NUMBERS.remove((Integer) res);
        return res;
    }

}
