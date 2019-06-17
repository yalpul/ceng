package e209873;
/**
 * Enumerations for {@link Zombie} class representing
 * its child classes.
 * <table border="1">
 * <caption>Zombie Types and Their Attributes</caption>
 * <tr>
 *   <th>Types/Attributes</th>
 *   <th>Collision Range</th>
 *   <th>Detection Range</th>
 *   <th>Speed</th>
 * </tr>
 * <tr>
 *   <td>SLOW</td>
 *   <td>1.0</td>
 *   <td>40.0</td>
 *   <td>2.0</td>
 * </tr>
 * <tr>
 *   <td>REGULAR</td>
 *   <td>2.0</td>
 *   <td>20.0</td>
 *   <td>5.0</td>
 * </tr>
 * <tr>
 *   <td>FAST</td>
 *   <td>2.0</td>
 *   <td>20.0</td>
 *   <td>20.0</td>
 * </tr>
 * </table>
 *
 * @author ALPUL, Yasin Fatih (e2098739)
 * @version 1.0
 * @see Zombie
 */
public enum ZombieType {
    /**
     * Represents a zombie having a slow speed but high detection range.
     */
    SLOW,
    /**
     * Represents an ordinary zombie.
     */
    REGULAR,
    /**
     * Represents a zombie with a fast speed.
     */
    FAST;
}
