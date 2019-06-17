package e209873;

/**
 * Soldier is the abstract base class for all the soldier types
 * used within the simulator which provides their common
 * fields and methods.
 * It includes state information such as soldier type, soldier
 * state, collision and shooting ranges.
 *
 * @author ALPUL, Yasin Fatih (e2098739)
 * @version 1.0
 */

public abstract class Soldier extends SimulationObject {
  private final SoldierType type;
  private SoldierState state;
  private final double collisionRange;
  private final double shootingRange;

  /**
   * Used by child classes to construct soldier object with
   * their common properties.
   *
   * @param name name of this soldier object used to identify it
   * @param position a {@link Position} object that denotes this
   *                 soldier's position in 2D space
   * @param speed soldier's moving speed
   * @param type type of this soldier object
   * @param collisionRange the radius in which this soldier
   *                       becomes vulnerable to nearby zombies
   * @param shootingRange the radius in which this soldier is
   *                      able to shoot at nearby zombies
   */
  protected Soldier(
      String name,
      Position position,
      double speed,
      SoldierType type,
      double collisionRange,
      double shootingRange) {
    super(name, position, speed);
    this.type = type;
    this.state = SoldierState.SEARCHING;
    this.collisionRange = collisionRange;
    this.shootingRange = shootingRange;
  }

  /**
   * Moves this soldier to specified position while logging
   * the action to standard output.
   *
   * @param pos This will become soldier's next position.
   */
  @Override
  public void setPosition(Position pos) {
    super.setPosition(pos);
    System.out.printf("%s moved to %s.%n",
        getName(), getPosition());
  }

  /**
   * Sets soldier's new direction.
   * Directions should have a length of 1.
   *
   * @param dir This will become soldier's next direction.
   */
  @Override
  public void setDirection(Position dir) {
    super.setDirection(dir);
    System.out.printf("%s changed direction to %s.%n",
        getName(), getDirection());
  }

  /**
   * Abstract method that creates a new {@link Bullet} object
   * based on soldier's type and properties.
   * 
   * @return newly created Bullet object
   */
  protected abstract Bullet fireBullet();

  /**
   * Returns this soldier's collision range in which this
   * soldier becomes vulnerable to zombie attacks.
   *
   * @return soldier's collision range
   */
  public final double getCollisionRange() {
    return this.collisionRange;
  }

  /**
   * Directs this soldier to zombie.
   * Soldier's direction will be pointing at the zombie.
   *
   * @param zombie the zombie to be directed at
   */
  protected final void setDirectionTo(Zombie zombie) {
    setDirection(getPosition().directionTo(zombie.getPosition()));
  }

  /**
   * Returns <code>true</code> if <code>zombie</code> is
   * within the shooting range of this soldier.
   *
   * @param zombie Zombie to check for being able to shoot at
   * @return <code>true</code> if <code>this</code> can shoot
   *         at given zombie
   */
  protected final boolean withinRange(Zombie zombie) {
    Position zombiePosition = zombie.getPosition();
    if (zombiePosition.distance(getPosition()) <= shootingRange)
      return true;
    else
      return false;
  }

  /**
   * Returns the state that this soldier is in.
   *
   * @return current state of this soldier
   */
  protected final SoldierState getState() {
    return state;
  }

  /**
   * Puts this soldier into the given state while logging the
   * action to standard output.
   *
   * @param newState This will become this soldier's new state.
   */
  protected final void setState(SoldierState newState) {
    this.state = newState;
    System.out.printf("%s changed state to %s.%n",
        getName(), state);
  }
}
