package e209873;

/**
 * Public class representing
 * Bullet objects deriving from
 * SimulationObject
 *
 * @author ALPUL, Yasin Fatih (e2098739)
 * @version 1.0
 */

public class Bullet extends SimulationObject {
  private static int bulletNo = 0;

  /**
   * Constructs a Bullet object with given position, speed and direction.
   * Each bullet object shares a static field denoting their respective
   * number. It starts from 0 and gets incremented with each new Bullet
   * object creation.
   *
   * @param position  denotes this bullet's position in the 2D
   *                  simulation space
   * @param speed     denotes this bullet object's moving speed
   * @param direction denotes this bullet's moving direction
   *                  which should have a length of 1
   */
  public Bullet(Position position, double speed, Position direction) {
    super("Bullet"+bulletNo++, position, speed);
    setDirection(direction);
  }

  /**
   * Simulates this bullet for a single step in the simulation.
   * While executing, logs its actions to standard output.
   * At a high level, the actions are described as the following:
   * <ul>
   * <li>Move through the trajectory one unit at a time
   * <li>If this bullet hits a zombie:
   *  <ul>
   *  <li>Kill the zombie
   *  <li>Stop being part of the simulation
   *  </ul>
   * <li>No hit:
   *  <ul>
   *  <li>Run out of bounds or drop to ground depending
   *      on the simulation environment and the range
   *      of the bullet
   *  </ul>
   * </ul>
   *
   * @param simCtl the simulator in which this bullet is
   *               being simulated. Used by this bullet to
   *               interact with the simulation environment
   */
  @Override
  public void step(SimulationController simCtl) {
    Position pos = getPosition();
    for (
          int i = 0, range = (int)getSpeed();
          i < range;
          i++, pos.add(getDirection()), setPosition(pos)
        )
    {
        Zombie closestZombie = simCtl.getClosestZombie(getPosition());
        if (closestZombie.collides(getPosition())) {
          closestZombie.setActive(false);
          this.setActive(false);
          System.out.printf("%s hit %s.%n",
              getName(), closestZombie.getName());
          return;
        }
        if (simCtl.outOfBounds(getPosition())) {
          System.out.println(getName()+" moved out of bounds.");
          return;
        }
    }
    System.out.printf("%s dropped to the ground at %s.%n",
        getName(), getPosition());
  }
}
