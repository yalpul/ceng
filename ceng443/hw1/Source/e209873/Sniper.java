package e209873;
/**
 * A special type of soldier specialized in
 * long range combat with a slow moving speed.
 * Sniper objects are capable of shooting
 * zombies at a long distance. However,
 * they are vulnerable in close range and
 * they move at a slow speed.
 * range.
 *
 * @author ALPUL, Yasin Fatih (e2098739)
 * @version 1.0
 * @see SoldierType
 */
public class Sniper extends Soldier {

    /**
     * Constructs a new Sniper object with given
     * name and position.
     * This sniper will have a speed of 2,
     * shooting range of 40 and a collision range
     * of 5.
     *
     * @param name Used to identify this sniper in the
     *             simulation
     * @param position used to represent this sniper
     *                 within the simulation using
     *                 2D coordinates
     */
    public Sniper(String name, Position position) { // DO NOT CHANGE PARAMETERS
      super(name, position, 2.0, SoldierType.SNIPER, 5.0, 40.0);
        
    }

    /**
     * Fires a new bullet from this sniper's position
     * and at this sniper's direction while logging
     * the action to standard output.
     * Bullet will have a speed of 100.
     *
     * @return the newly created bullet
     */
    @Override
    protected Bullet fireBullet() {
      Bullet bullet = new Bullet(getPosition(), 100.0, getDirection());
      System.out.printf("%s fired %s to direction %s.%n",
          getName(), bullet.getName(), getDirection());
      return bullet;
    }

    /**
     * Simulates this sniper for a single step in the
     * simulation according to this sniper's current
     * state.
     * The exact specifications for the behaviour of
     * this sniper is in the text.
     *
     * @param simCtl simulator object used to interact
     *               with the simulation environment
     * @throws IllegalArgumentException if this sniper is
     *                                  in an illegal state
     * @see SoldierState
     */
    @Override
    public void step(SimulationController simCtl) {
      if (getDirection() == null)
        setDirection(Position.generateRandomDirection(true));
      switch (getState()) {
        case SEARCHING:
          searchingAction(simCtl);
          break;
        case AIMING:
          aimingAction(simCtl);
          break;
        case SHOOTING:
          shootingAction(simCtl);
          break;
        default:
          throw new IllegalArgumentException("Illegal state given");
      }
    }

    /**
     * Moves to the next position and starts aiming.
     * Changes direction randomly if out of bounds.
     *
     * @param simCtl simulator object used to interact
     *               with the simulation environment
     */
    private void searchingAction(SimulationController simCtl) {
      Position nextPosition = getNextPosition();
      if (simCtl.outOfBounds(nextPosition))
        setDirection(Position.generateRandomDirection(true));
      else
        setPosition(nextPosition);
      setState(SoldierState.AIMING);
    }

    /**
     * Starts facing towards a nearby zombie, if there is one,
     * and starts shooting.
     *
     * @param simCtl simulator object used to interact
     *               with the simulation environment
     */
    private void aimingAction(SimulationController simCtl) {
      Zombie closestZombie = simCtl.getClosestZombie(getPosition());
      if (withinRange(closestZombie)) {
        setDirectionTo(closestZombie);
        setState(SoldierState.SHOOTING);
      }
      else
        setState(SoldierState.SEARCHING);
    }

    /**
     * Fires a bullet and adds it to the simulator, then
     * starts aiming at a nearby zombie if there is one,
     * else changes direction randomly.
     *
     * @param simCtl simulator object used to interact
     *               with the simulation environment
     */
    private void shootingAction(SimulationController simCtl) {
      Bullet bullet = fireBullet();
      simCtl.registerBullet(bullet);
      Zombie closestZombie = simCtl.getClosestZombie(getPosition());
      if (withinRange(closestZombie))
        setState(SoldierState.AIMING);
      else {
        setDirection(Position.generateRandomDirection(true));
        setState(SoldierState.SEARCHING);
      }
    }
}
