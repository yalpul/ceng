import java.util.ArrayList;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.io.Serializable;

public class Maze
  extends UnicastRemoteObject
  implements IMaze, Serializable
{
  private MazeObject[][] maze;
  private final ArrayList<Agent> agentList;

  public Maze() throws RemoteException {
  }

  @Override
  public void create(int h, int w) throws RemoteException {
    maze = new MazeObject[h][w];
    agentList = new ArrayList<>();
  }

  @Override
  public MazeObject getObject(Position p) throws RemoteException {
    final int x = p.getX(), y = p.getY();
    final MazeObject mo = maze[y][x];
    return mo;
  }

  @Override
  public boolean createObject(Position p, MazeObjectType t)
    throws RemoteException
  {
    final int x = p.getX(), y = p.getY();
    final MazeObject mo = maze[y][x];
    if (mo != null)
      return false;
    if (t == MazeObjectType.AGENT) {
      Agent agent = new Agent(p, agentList.size());
      maze[y][x] = agent;
      agentList.add(agent);
    }
    else
      maze[y][x] = new MazeObject(p, t);
    return true;
  }

  @Override
  public boolean deleteObject(Position p) throws RemoteException {
    final int x = p.getX(), y = p.getY();
    if (maze[y][x] == null)
      return false;
    if (maze[y][x].getType() == MazeObjectType.AGENT)
      ((Agent)maze[y][x]).setActive(false);
    maze[y][x] = null;
    return true;
  }

  @Override
  public Agent[] getAgents() throws RemoteException {
    return agentList.
      stream().
      filter(a -> a.isActive()).
      toArray(Agent[]::new);
  }

  @Override
  public boolean moveAgent(int id, Position p) throws RemoteException {
    final Agent agent = agentList.get(id);
    final Position agentPos = agent.getPosition();
    final int x = p.getX(), y = p.getY();
    final int oldx = agentPos.getX(), oldy = agentPos.getY();
    if (agentPos.distance(p) == 1) {
      if (maze[y][x] == null) {
        maze[y][x] = agent;
        agent.setPosition(new Position(x, y));
      }
      else
        switch (maze[y][x].getType()) {
          case AGENT:
          case WALL:
            return false;
          case HOLE:
            agent.setActive(false);
            break;
          case GOLD:
            maze[y][x] = agent;
            agent.setPosition(new Position(x, y));
            agent.collectGold();
            break;
        }
    }
    else
      return false;
    maze[oldy][oldx] = null;
    return true;
  }

  @Override
  public String print() throws RemoteException {
    StringBuilder mazeStr = new StringBuilder("+");
    for (int i = 0; i < maze[0].length; i++)
      mazeStr.append('-');
    mazeStr.append("+\n");
    for (int i = 0; i < maze.length; i++) {
      mazeStr.append('|');
      for (int j = 0; j < maze[0].length; j++)
        if (maze[i][j] == null)
          mazeStr.append(' ');
        else
          mazeStr.append(maze[i][j].toString());
      mazeStr.append("|\n");
    }
    mazeStr.append('+');
    for (int i = 0; i < maze[0].length; i++)
      mazeStr.append('-');
    mazeStr.append("+\n");
    return mazeStr.toString();
  }
}
