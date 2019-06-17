package e209873;
/**
 * SimulationObject is the abstract base class for all the simulation
 * objects used within the simulator which provides all of their
 * common fields and methods.
 * It includes various state information such as
 * name, position, direction and speed information as
 * well as whether this object is active at that moment.
 *
 * @author ALPUL, Yasin Fatih (e2098739)
 * @version 1.0
 */
public abstract class SimulationObject {
    private final String name;
    private Position position;
    private Position direction;
    private final double speed;
    private boolean active;
    /**
     * Constructs a SimulationObject with given name, position and speed.
     * Direction is set to null by default. Also, this object is initially
     * active by default.
     *
     * @param name  a String that will be used as this object's name
     * @param position  a {@link Position} object that denotes this
     *                  object's position in 2D space
     * @param speed a double-precision floating-value that denotes
     *              this object's moving speed
     */
    public SimulationObject(String name, Position position, double speed) {
        this.name = name;
        this.position = position;
        this.speed = speed;
        this.direction = null;
        this.active = true;
    }

    /**
     * Returns object's name used to identify it.
     *
     * @return object's name
     */
    public String getName() {
        return name;
    }

    /**
     * Returns object's current position.
     *
     * @return object's current position
     */
    public Position getPosition() {
        return position;
    }

    /**
     * Moves object to given position.
     *
     * @param position This will become object's next position.
     */
    public void setPosition(Position position) {
        this.position = position;
    }

    /**
     * Returns object's current direction.
     * Directions always have a length of 1.
     *
     * @return object's current direction
     */
    public Position getDirection() {
        return direction;
    }

    /**
     * Sets object's new direction.
     * Directions should have a length of 1.
     *
     * @param direction This will become object's next direction.
     */
    public void setDirection(Position direction) {
        this.direction = direction;
    }

    /**
     * Returns object's current speed.
     *
     * @return object's current speed
     */
    public double getSpeed() {
        return speed;
    }

    /**
     * Returns <code>true</code> if this object is currently active.
     * Normally, objects lose their active status when they die.
     *
     * @return object's active status
     */
    public boolean isActive() {
        return active;
    }

    /**
     * Sets object's active status, which denotes whether this
     * object is functional in the simulator.
     * Normally, objects should lose their active status
     * when they die.
     *
     * @param active denotes object's next active status.
     *               active should be <code>false</code>
     *               when the object dies.
     */
    public void setActive(boolean active) {
        this.active = active;
    }

    /**
     * Returns this object's next position in the simulation.
     * Next position is calculated by adding the displacement
     * vector to this object's current position where
     * displacement vector is defined as the multiplication
     * of the unit vector <i>direction</i> and scalar
     * <i>speed</i>.
     *
     * @return object's next position
     */
    protected final Position getNextPosition() {
      Position nextPosition = (Position) position.clone();
      Position displacement = (Position) direction.clone();
      displacement.mult(speed);
      nextPosition.add(displacement);
      return nextPosition;
    }
    
    /**
     * Abstract method used that is used for simulating
     * a single step of actions that this object does on
     * each turn.
     *
     * @param controller used by simulated object to interact
     *                   with the simulation environment
     */
    public abstract void step(SimulationController controller);
}
