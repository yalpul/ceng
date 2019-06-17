import java.util.ArrayList;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.io.Serializable;

public class MazeHub
  extends UnicastRemoteObject
  implements IMazeHub, Serializable
{
  private final ArrayList<IMaze> mazeList;

  public MazeHub() throws RemoteException {
    mazeList = new ArrayList<>();
  }

  @Override
  public void createMaze(int w, int h) throws RemoteException {
    IMaze maze = new Maze();
    maze.create(h, w);
    mazeList.add(maze);
  }

  @Override
  public IMaze getMaze(int idx) throws RemoteException {
    if (idx < 0 || idx >= mazeList.size())
      return null;
    else
      return mazeList.get(idx);
  }

  @Override
  public boolean removeMaze(int idx) throws RemoteException {
    if (idx < 0 || idx >= mazeList.size())
      return false;
     mazeList.remove(idx);
     return true;
  }
}
