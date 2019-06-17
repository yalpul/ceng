package e209873;
/**
 * An ordinary type of zombie with no specialization
 * in a particular area.
 * Regular zombies have an average speed, collision
 * and detection ranges.
 *
 * @author ALPUL, Yasin Fatih (e2098739)
 * @version 1.0
 * @see ZombieType
 */
public class RegularZombie extends Zombie {

    private int stateCounter;
    /**
     * Constructs a new RegularZombie object with given
     * name and position.
     * This zombie will have a speed of 5,
     * detection range of 20 and a collision range
     * of 2.
     *
     * @param name Used to identify this zombie in the
     *             simulation
     * @param position used to represent this zombie
     *                 within the simulation using
     *                 2D coordinates
     */
    public RegularZombie(String name, Position position) { // DO NOT CHANGE PARAMETERS
      super(name, position, 5.0, ZombieType.REGULAR, 2.0, 20.0);
      stateCounter = 1;
        
    }

    /**
     * Simulates this zombie for a single step in the
     * simulation according to this zombie's current
     * state.
     * The exact specifications for the behaviour of
     * this zombie is in the text.
     *
     * @param simCtl simulator object used to interact
     *               with the simulation environment
     * @throws IllegalArgumentException if this zombie is
     *                                  in an illegal state
     * @see SoldierState
     */
    @Override
    public void step(SimulationController simCtl) {
      if (getDirection() == null)
        setDirection(Position.generateRandomDirection(true));
      Soldier closestSoldier = simCtl.getClosestSoldier(getPosition());
      if (this.canAttack(closestSoldier)) {
        closestSoldier.setActive(false);
        System.out.printf("%s killed %s.%n",
            getName(), closestSoldier.getName());
        return;
      }
      switch (getState()) {
        case WANDERING:
          wanderingAction(simCtl);
          break;
        case FOLLOWING:
          followingAction(simCtl);
          break;
        default:
          throw new IllegalArgumentException("Illegal state given");
      }
    }

    /**
     * Attempts to move to the next location, changes direction if
     * out of bounds, then, starts following a nearby soldier if
     * there is one.
     *
     * @param simCtl simulator object used to interact with
     *               the simulation environment
     */
    private void wanderingAction(SimulationController simCtl) {
      Position nextPosition = getNextPosition();
      if (simCtl.outOfBounds(nextPosition))
        setDirection(Position.generateRandomDirection(true));
      else
        setPosition(nextPosition);
      Soldier closestSoldier = simCtl.getClosestSoldier(getPosition());
      if (this.canDetect(closestSoldier)) {
        setDirectionTo(closestSoldier);
        setState(ZombieState.FOLLOWING);
      }
    }

    /**
     * Charges at a nearby soldier for a predefined amount of
     * steps, then goes back to WANDERING state.
     *
     * @param simCtl simulator object used to interact with
     *               the simulation environment
     * @see ZombieState
     */
    private void followingAction(SimulationController simCtl) {
      Position nextPosition = getNextPosition();
      if (simCtl.outOfBounds(nextPosition))
        setDirection(Position.generateRandomDirection(true));
      else
        setPosition(nextPosition);
      if (stateCounter == 4) {
        stateCounter = 1;
        setState(ZombieState.WANDERING);
      }
      else
        stateCounter++;
    }
}
