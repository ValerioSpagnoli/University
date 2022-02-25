package server;

import java.awt.Color;
import java.io.PrintWriter;
import java.util.HashSet;
import java.util.Set;

public class SenderThread implements Runnable {

	private PrintWriter pw;
	private boolean flag;
	private Color[] coldColors = { new Color(20,20,128), Color.CYAN, Color.BLUE.brighter(),
			Color.BLUE.brighter().brighter(), Color.BLUE.brighter().brighter().brighter(), Color.CYAN };
	private Color[] hotColors = { new Color(179,20,10), Color.RED.brighter(), Color.RED.brighter().brighter(),
			Color.RED.brighter().brighter().brighter(),Color.RED, Color.RED , Color.RED };
	Set<Integer> positions = new HashSet<Integer>();

	public SenderThread(PrintWriter pw) {
		flag = false;
		this.pw = pw;
		
		for(int i = 1; i < coldColors.length; i++){
			coldColors[i] = coldColors[i-1].brighter();
		}
		for(int i = 1; i < hotColors.length; i++){
			hotColors[i] = hotColors[i-1].brighter();
		}
	}

	@Override
	public void run() {
		flag = true;
		while (flag) {
			double position = Math.random();
			Integer num = new Integer((int) (position * 16 * 16));

			while (positions.contains(num)) {
				num = (num + 1) % (16 * 16);
				if (!flag) {
					return;
				}
			}

			positions.add(num);
			int check = (int) (num / 16) + (int) num % 16;
			pw.println(num.toString() + ";"
					+ (check % 2 == 0 ? coldColors[(int) (Math.random() * coldColors.length)].getRGB()
							: hotColors[(int) (Math.random() * hotColors.length)].getRGB()));
			pw.flush();
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}

		}

	}

	public void stop() {
		// chiusura del pw delegata al chiamante
		flag = false;

		pw.println("-1;-1");
		pw.flush();
	}

}