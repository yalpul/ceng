public class Agent extends MazeObject{
    
    private final int id;
    private int collectedGold;
    private boolean active;
    public Agent(Position position, int id) {
        super(position, MazeObjectType.AGENT);
        this.id = id;
        this.collectedGold = 0;
        this.active = true;
    }

    public boolean isActive() {
      return this.active;
    }

    public void setActive(boolean b) {
      this.active = b;
    }

    public void collectGold() {
      this.collectedGold++;
    }

    public int getID() {
      return this.id;
    }

    public int getGolds() {
      return this.collectedGold;
    }
}
