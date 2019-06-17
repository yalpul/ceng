package e209873;
/**
 * An ordinary type of soldier with no specialization
 * in a particular area.
 * Regular soldiers have an average speed, collision
 * and shooting distances.
 *
 * @author ALPUL, Yasin Fatih (e2098739)
 * @version 1.0
 * @see SoldierType
 */
public class RegularSoldier extends Soldier {

    /**
     * Constructs a new RegularSoldier object with given
     * name and position.
     * This soldier will have a speed of 5,
     * shooting range of 20 and a collision range
     * of 2.
     *
     * @param name Used to identify this soldier in the
     *             simulation
     * @param position used to represent this soldier
     *                 within the simulation using
     *                 2D coordinates
     */
    public RegularSoldier(String name, Position position) { // DO NOT CHANGE PARAMETERS
      super(name, position, 5.0, SoldierType.REGULAR, 2.0, 20.0);
        
    }

    /**
     * Fires a new bullet from this soldier's position
     * and at this soldier's direction while logging
     * the action to standard output.
     * Bullet will have a speed of 40.
     *
     * @return the newly created bullet
     */
    @Override
    protected Bullet fireBullet() {
      Bullet bullet = new Bullet(getPosition(), 40.0, getDirection());
      System.out.printf("%s fired %s to direction %s.%n",
          getName(), bullet.getName(), getDirection());
      return bullet;
    }

    /**
     * Simulates this soldier for a single step in the
     * simulation according to this soldier's current
     * state.
     * The exact specifications for the behaviour of
     * this soldier is in the text.
     *
     * @param simCtl simulator object used to interact
     *               with the simulation environment
     * @throws IllegalArgumentException if this soldier is
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
     * Moves to the next position and starts aiming at a
     * nearby zombie if there is one.
     * While moving, changes direction if out of bounds.
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
      Zombie closestZombie = simCtl.getClosestZombie(getPosition());
      if (withinRange(closestZombie))
        setState(SoldierState.AIMING);
    }

    /**
     * Starts facing at a nearby zombie if there is one,
     * then starts shooting, else continues searching.
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
     * else changes direction randomly and continues
     * searching.
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
