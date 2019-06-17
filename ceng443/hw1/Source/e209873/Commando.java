package e209873;
/**
 * A special type of soldier specialized in
 * close range combat with a high moving speed.
 * Commando objects don't lose any time aiming
 * at a zombie. They directly shoot at the
 * zombie wherever it is within the shooting
 * range.
 *
 * @author ALPUL, Yasin Fatih (e2098739)
 * @version 1.0
 * @see SoldierType
 */
public class Commando extends Soldier {

    /**
     * Constructs a new Commando object with given
     * name and position.
     * This commando will have a speed of 10,
     * shooting range of 10 and a collision range
     * of 2.
     *
     * @param name Used to identify this commando in the
     *             simulation
     * @param position used to represent this comando
     *                 within the simulation using
     *                 2D coordinates
     */
    public Commando(String name, Position position) { // DO NOT CHANGE PARAMETERS
      super(name, position, 10.0, SoldierType.COMMANDO, 2.0, 10.0);
    }

    /**
     * Fires a new bullet from this commando's position
     * and at this commando's direction while logging
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
     * Simulates this commando for a single step in the
     * simulation according to this commando's current
     * state.
     * The exact specifications for the behaviour of
     * this commando is in the text.
     *
     * @param simCtl simulator object used to interact
     *               with the simulation environment
     * @throws IllegalArgumentException if this commando is
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
          throw new IllegalArgumentException(
              "Commandos shouldn't be in AIMING state");
        case SHOOTING:
          shootingAction(simCtl);
          break;
        default:
          throw new IllegalArgumentException("Illegal state given");
      }
    }

    /**
     * Starts shooting at a nearby zombie if there is one,
     * else, moves to the next position, then, again
     * starts shooting at a nearby zombie if there is one.
     * While moving, changes direction randomly if out of bounds.
     *
     * @param simCtl simulator object used to interact
     *               with the simulation environment
     */
    private void searchingAction(SimulationController simCtl) {
      Zombie closestZombie = simCtl.getClosestZombie(getPosition());
      if (withinRange(closestZombie)) {
        setDirectionTo(closestZombie);
        setState(SoldierState.SHOOTING);
        return;
      }
      Position nextPosition = getNextPosition();
      if (simCtl.outOfBounds(nextPosition))
        setDirection(Position.generateRandomDirection(true));
      else
        setPosition(nextPosition);
      closestZombie = simCtl.getClosestZombie(getPosition());
      if (withinRange(closestZombie)) {
        setDirectionTo(closestZombie);
        setState(SoldierState.SHOOTING);
      }
    }

    /**
     * Fires a bullet and adds it to the simulator, then, starts
     * facing at a nearby zombie if there is one.
     * Changes direction randomly if there is no zombie around.
     *
     * @param simCtl simulator object used to interact
     *               with the simulation environment
     */
    private void shootingAction(SimulationController simCtl) {
      Bullet bullet = fireBullet();
      simCtl.registerBullet(bullet);
      Zombie closestZombie = simCtl.getClosestZombie(getPosition());
      if (withinRange(closestZombie))
        setDirectionTo(closestZombie);
      else {
        setDirection(Position.generateRandomDirection(true));
        setState(SoldierState.SEARCHING);
      }
    }
}
