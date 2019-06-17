package e209873;

import java.util.LinkedList;
import java.util.ArrayList;
import java.util.Iterator;
/**
 * Simulator class that manages other {@link SimulationObject}
 * objects and provides the environment for simulations.
 * Provides facilities for adding to and removing objects
 * from the simulation and stepping through the objects until
 * the simulation is finished.
 *
 * @author ALPUL, Yasin Fatih (e2098739)
 * @version 1.0
 */
public class SimulationController {
    private final double height;
    private final double width;

    // containers for SimulationObjects
    private LinkedList<Soldier> soldierList;
    private LinkedList<Zombie> zombieList;
    private ArrayList<Bullet> bulletList;
    private ArrayList<Bullet> nextBulletList;


    /**
     * Constructs a new simulator object with given width
     * and height values representing the scale of this
     * simulation environment.
     * Also, initializes the containers for
     * {@link SimulationObject} objects.
     *
     * @param width width of this simulation area
     * @param height height of this simulation area
     */
    public SimulationController(double width, double height) {
        this.width = width;
        this.height = height;

        // initialize lists
        this.soldierList = new LinkedList<Soldier>();
        this.zombieList = new LinkedList<Zombie>();
        this.bulletList = new ArrayList<Bullet>();
        this.nextBulletList = new ArrayList<Bullet>();
    }
    
    /**
     * Returns the height of this simulation area.
     *
     * @return the height of this simulation area
     */
    public double getHeight() {
        return height;
    }

    /**
     * Returns the width of this simulation area.
     *
     * @return the width of this simulation area
     */
    public double getWidth() {
        return width;
    }

    /**
     * Simulates all of the registered objects.
     * Also, clears the battlefield from dead
     * bodies and makes it ready for next round.
     */
    public void stepAll() {
      for (Soldier soldier : soldierList)
        soldier.step(this);
      for (Zombie zombie : zombieList)
        zombie.step(this);
      for (Bullet bullet : bulletList)
        bullet.step(this);

      bulletList = nextBulletList;
      nextBulletList = new ArrayList<Bullet>();
      removeCorpses();
    }

    /**
     * Adds the given object to this simulation environment.
     * SimulationObject is dealt with properly according
     * to its type.
     *
     * @param obj the object that will be added to this simulator
     */
    public void addSimulationObject(SimulationObject obj) {
      if (obj instanceof Soldier)
        soldierList.add((Soldier) obj);
      else if (obj instanceof Zombie)
        zombieList.add((Zombie) obj);
      else if (obj instanceof Bullet)
        bulletList.add((Bullet) obj);
      else
        throw new IllegalArgumentException("Illegal object type given");
    }
    
    /**
     * Removes the given object from this simulation environment.
     * SimulationObject is dealt with properly according to
     * its type.
     *
     * @param obj the object that will be removed from this simulator
     */
    public void removeSimulationObject(SimulationObject obj) {
      if (obj instanceof Soldier)
        soldierList.remove((Soldier) obj);
      else if (obj instanceof Zombie)
        zombieList.remove((Zombie) obj);
      else if (obj instanceof Bullet)
        bulletList.remove((Bullet) obj);
      else
        throw new IllegalArgumentException("Illegal object type given");
    }
    
    /**
     * Returns <code>true</code> if simulation is finished.
     * The state of simulation is determined based on whether
     * there is any object left in this simulation or there is
     * only a single type of object, namely, only soldiers
     * or only zombies.
     *
     * @return <code>true</code> if simulation is finished
     */
    public boolean isFinished() {
      return soldierList.size() == 0 || zombieList.size() == 0;
    }

    /**
     * Returns the closest soldier to the given position
     * in this simulation.
     * Returns a <code>null</code> value if there is no
     * soldier in this simulator.
     *
     * @param pos specifies the position to find the closest
     *            soldier to
     * @return the closest soldier to given position
     */
    public Soldier getClosestSoldier(Position pos) {
      double minDistance = Double.MAX_VALUE;
      Soldier closestSoldier = null;
      for (Soldier soldier : soldierList) {
        double distance = soldier.getPosition().distance(pos);
        if (distance < minDistance) {
          minDistance = distance;
          closestSoldier = soldier;
        }
      }
      return closestSoldier;
    }

    /**
     * Returns the closest zombie to the given position
     * in this simulation.
     * Returns a <code>null</code> value if there is no
     * zombie in this simulator.
     *
     * @param pos specifies the position to find the closest
     *            zombie to
     * @return the closest zombie to given position
     */
    public Zombie getClosestZombie(Position pos) {
      double minDistance = Double.MAX_VALUE;
      Zombie closestZombie = null;
      for (Zombie zombie : zombieList) {
        double distance = zombie.getPosition().distance(pos);
        if (distance < minDistance) {
          minDistance = distance;
          closestZombie = zombie;
        }
      }
      return closestZombie;
    }

    /**
     * Determines whether given position is out
     * of bounds of this simulation environment.
     * The simulation boundaries are:
     * [0, width) x [0, height)
     *
     * @param pos position to check for being
     *            in this simulation area
     * @return <code>true</code> if given position
     *         is not within the boundaries of
     *         this simulation environment
     */
    public boolean outOfBounds(Position pos) {
      double x = pos.getX(), y = pos.getY();
      return x >= width || x < 0 || y >= height || y < 0;
    }

    /**
     * Adds given bullet to this simulator to be used in
     * next round for simulation.
     * Registered bullets are not immediately used in
     * current round.
     *
     * @param bullet the bullet to be added to this simulator
     */
    public void registerBullet(Bullet bullet) {
      nextBulletList.add(bullet);
    }

    /**
     * Clears the battlefield from dead bodies of the last
     * simulation step.
     * Optimized for {@link LinkedList} containers.
     */
    private void removeCorpses() {
      Iterator<Soldier> itSoldier = soldierList.iterator();
      while (itSoldier.hasNext()) {
        Soldier soldier = itSoldier.next();
        if (!soldier.isActive())
          itSoldier.remove();
      }

      Iterator<Zombie> itZombie = zombieList.iterator();
      while (itZombie.hasNext()) {
        Zombie zombie = itZombie.next();
        if (!zombie.isActive())
          itZombie.remove();
      }
    }
}
