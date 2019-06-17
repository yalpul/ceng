package e209873;
/**
 * Enumerations for {@link Soldier} class representing
 * its states.
 * <ul>
 * <li><b>SEARCHING:</b> Soldier is searching for a zombie
 * <li><b>AIMING:</b> Soldier is aiming at a nearby zombie
 * <li><b>SHOOTING:</b> Soldier is shooting at a nearby zombie
 * </ul>
 *
 * @author ALPUL, Yasin Fatih (e2098739)
 * @version 1.0
 * @see Soldier
 */
public enum SoldierState {
    /**
     * Soldier is searching for a zombie.
     */
    SEARCHING,
    /**
     * Soldier is aiming at a nearby zombie.
     */
    AIMING,
    /**
     * Soldier is shooting at a nearby zombie.
     */
    SHOOTING;
}
