package e209873;
/**
 * Enumerations for {@link Zombie} class representing
 * its state.
 * <ul>
 * <li><b>WANDERING:</b> 
 *    Zombie is wandering in the simulation environment
 * <li><b>FOLLOWING:</b> 
 *    Zombie is following a nearby soldier
 * </ul>
 *
 * @author ALPUL, Yasin Fatih (e2098739)
 * @version 1.0
 * @see Zombie
 */
public enum ZombieState {
    /**
     * Zombie is wandering in the simulation environment.
     */
    WANDERING,
    /**
     * Zombie is following a nearby soldier.
     */
    FOLLOWING;
}
