package e209873;

/**
 * Zombie is the abstract base class for all the zombie types
 * used within the simulator which provides their common
 * fields and methods.
 * It includes state information such as zombie type, zombie
 * state, collision and detection ranges.
 *
 * @author ALPUL, Yasin Fatih (e2098739)
 * @version 1.0
 */

public abstract class Zombie extends SimulationObject {
  private final ZombieType type;
  private ZombieState state;
  private final double collisionRange;
  private final double detectionRange;

  /**
   * Used by child classes to construct zombie objects with
   * their common properties.
   *
   * @param name name of this zombie object used to identify it
   * @param position a {@link Position} object that denotes this
   *                 zombie's position in 2D space
   * @param speed zombie's moving speed
   * @param type type of zombie object
   * @param collisionRange the radius in which this zombie is able
   *                       to attack at nearby soldiers
   * @param detectionRange the radius in which soldiers are
   *                       detectable by this zombie
   */
  protected Zombie(
      String name,
      Position position,
      double speed,
      ZombieType type,
      double collisionRange,
      double detectionRange) {
    super(name, position, speed);
    this.type = type;
    this.state = ZombieState.WANDERING;
    this.collisionRange = collisionRange;
    this.detectionRange = detectionRange;
  }

  /**
   * Moves this zombie to the specified position while logging
   * the action to standard output.
   *
   * @param pos This will become zombie's next position
   */
  @Override
  public void setPosition(Position pos) {
    super.setPosition(pos);
    System.out.printf("%s moved to %s.%n",
        getName(), getPosition());
  }

  /**
   * Sets zombie's new direction.
   * Directions should have a length of 1.
   *
   * @param dir This will become zombie's next direction.
   */
  @Override
  public void setDirection(Position dir) {
    super.setDirection(dir);
    System.out.printf("%s changed direction to %s.%n",
        getName(), getDirection());
  }

  /**
   * Checks for collision with given position.
   *
   * @param pos the position to check for collision
   * @return <code>true</code> if <code>pos</code> is
   * within the collision range
   */
  protected boolean collides(Position pos) {
    double distance = getPosition().distance(pos);
    return distance <= collisionRange;
  }

  /**
   * Returns the state that this zombie is in.
   *
   * @return current state of this zombie
   */
  protected final ZombieState getState() {
    return state;
  }

  /**
   * Puts this zombie into the given state while logging the
   * action to standard output.
   *
   * @param newState This will become this zombie's new state.
   */
  protected final void setState(ZombieState newState) {
    this.state = newState;
    System.out.printf("%s changed state to %s.%n", getName(), state);
  }

  /**
   * Directs this zombie to soldier.
   * Zombie's direction will be pointing at the soldier.
   *
   * @param soldier the soldier to be directed at
   */
  protected final void setDirectionTo(Soldier soldier) {
    setDirection(getPosition().directionTo(soldier.getPosition()));
  }

  /**
   * Returns <code>true</code> if <code>soldier</code> is within
   * the attackable range of this zombie.
   * Attackable range is defined as this zombie's collision range
   * plus <code>soldier</code>'s collision range.
   *
   * @param soldier Soldier to check for being able to attack
   * @return <code>true</code> if <code>this</code> can attack
   *         to the given soldier
   */
  protected final boolean canAttack(Soldier soldier) {
    double distance = soldier.getPosition().distance(getPosition());
    if (distance <= this.collisionRange + soldier.getCollisionRange())
      return true;
    else
      return false;
  }

  /**
   * Returns <code>true</code> if <code>soldier</code> is within
   * the detection range of this zombie.
   *
   * @param soldier Soldier to check for being able to detect
   * @return <code>true</code> if <code>this</code> can detect
   *         the given soldier
   */
  protected final boolean canDetect(Soldier soldier) {
    Position soldierPosition = soldier.getPosition();
    if (soldierPosition.distance(getPosition()) <= detectionRange)
      return true;
    else
      return false;
  }
}
