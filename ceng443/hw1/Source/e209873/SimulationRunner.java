package e209873;

import java.util.logging.Level;
import java.util.logging.Logger;
/**
 *
 *
 * @author ALPUL, Yasin Fatih (e2098739)
 * @version 1.0
 */
public class SimulationRunner {

    public static void main(String[] args) {
        SimulationController simulation = new SimulationController(50, 50);

        
        simulation.addSimulationObject(new RegularSoldier("Soldier1", new Position(10, 10)));
        simulation.addSimulationObject(new RegularZombie("Zombie1", new Position(40, 40)));
        

        while (!simulation.isFinished()) {
            simulation.stepAll();
            try {
                Thread.sleep(1000);
            } catch (InterruptedException ex) {
                Logger.getLogger(SimulationRunner.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
}
