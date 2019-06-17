package e209873;
/**
 * An special type of zombie with slow speed
 * and high detection range.
 *
 * @author ALPUL, Yasin Fatih (e2098739)
 * @version 1.0
 * @see ZombieType
 */
public class SlowZombie extends Zombie {

    /**
     * Constructs a new SlowZombie object with given
     * name and position.
     * This zombie will have a speed of 2,
     * detection range of 40 and a collision range
     * of 1.
     *
     * @param name Used to identify this zombie in the
     *             simulation
     * @param position used to represent this zombie
     *                 within the simulation using
     *                 2D coordinates
     */
    public SlowZombie(String name, Position position) { // DO NOT CHANGE PARAMETERS
      super(name, position, 2.0, ZombieType.SLOW, 1.0, 40.0);
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
     * Starts following a nearby soldier if there is one, else
     * moves to the next position.
     * Changes direction if out of bounds.
     *
     * @param simCtl simulator object used to interact with
     *               the simulation environment
     */
    private void wanderingAction(SimulationController simCtl) {
      Soldier closestSoldier = simCtl.getClosestSoldier(getPosition());
      if (this.canDetect(closestSoldier)) {
        setState(ZombieState.FOLLOWING);
        return;
      }
      Position nextPosition = getNextPosition();
      if (simCtl.outOfBounds(nextPosition))
        setDirection(Position.generateRandomDirection(true));
      else
        setPosition(nextPosition);
    }

    /**
     * Starts facing at a nearby soldier if there is one, then
     * moves to the next position.
     * Changes direction if out of bounds.
     *
     * @param simCtl simulator object used to interact with
     *               the simulation environment
     */
    private void followingAction(SimulationController simCtl) {
      Soldier closestSoldier = simCtl.getClosestSoldier(getPosition());
      if (this.canDetect(closestSoldier)) {
        setDirectionTo(closestSoldier);
        setState(ZombieState.WANDERING);
      }
      Position nextPosition = getNextPosition();
      if (simCtl.outOfBounds(nextPosition))
        setDirection(Position.generateRandomDirection(true));
      else
        setPosition(nextPosition);
    }
}
