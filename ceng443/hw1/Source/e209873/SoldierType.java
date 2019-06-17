package e209873;
/**
 * Enumerations for {@link Soldier} class representing
 * its child classes.
 * <table border="1">
 * <caption>Soldier Types and Their Attributes</caption>
 * <tr>
 *   <th>Types/Attributes</th>
 *   <th>Collision Range</th>
 *   <th>Shooting Range</th>
 *   <th>Speed</th>
 * </tr>
 * <tr>
 *   <td>REGULAR</td>
 *   <td>2.0</td>
 *   <td>20.0</td>
 *   <td>5.0</td>
 * </tr>
 * <tr>
 *   <td>COMMANDO</td>
 *   <td>2.0</td>
 *   <td>10.0</td>
 *   <td>10.0</td>
 * </tr>
 * <tr>
 *   <td>SNIPER</td>
 *   <td>5.0</td>
 *   <td>40.0</td>
 *   <td>2.0</td>
 * </tr>
 * </table>
 *
 * @author ALPUL, Yasin Fatih (e2098739)
 * @version 1.0
 * @see Soldier
 */
public enum SoldierType {
    /**
     * Represents an ordinary soldier.
     */
    REGULAR,
    /**
     * Represents a high-speed close range soldier.
     */
    COMMANDO,
    /**
     * Represents a soldier with a high shooting range.
     */
    SNIPER;
}
