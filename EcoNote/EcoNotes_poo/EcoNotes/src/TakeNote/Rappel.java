package TakeNote;

import java.util.Timer;
import java.util.TimerTask;

public class Rappel {
    private Timer timer;

    public void activerRappel(String message, int delaiSecondes) {
        if (timer == null) {
            timer = new Timer();
        }

        long delaiMillisecondes = delaiSecondes * 1000;

        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                System.out.println("Rappel : " + message);
            }
        }, delaiMillisecondes);
    }

    public void annulerRappel() {
        if (timer != null) {
            timer.cancel();
            timer = null;
        }
    }
}
