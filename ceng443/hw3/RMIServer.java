import java.rmi.Naming;

public class RMIServer {
    public static void main(String[] args) throws Exception {
      IMazeHub mazeHub = new MazeHub();
      Naming.rebind("hub", mazeHub);
    }
}
