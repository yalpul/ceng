import java.util.Scanner;
import java.rmi.Naming;



public class RMIClient {
    public static void main(String[] args) throws Exception {
        IMazeHub mazeHub = (IMazeHub) Naming.lookup("rmi://127.0.0.1/hub");
        IMaze maze = null;
        
        
        Scanner scanner = new Scanner(System.in);
        ParsedInput parsedInput = null;
        String input;
        while( true ) {
            input = scanner.nextLine();
            try {
                parsedInput = ParsedInput.parse(input);
            }
            catch (Exception ex) {
                parsedInput = null;
            }
            if ( parsedInput == null ) {
                System.out.println("Wrong input format. Try again.");
                continue;
            }
            Object[] parsedArgs = parsedInput.getArgs();
            switch(parsedInput.getType()) {
                case CREATE_MAZE:
                    mazeHub.createMaze(
                        (int)parsedArgs[0], (int)parsedArgs[1]);
                    break;
                case DELETE_MAZE:
                    if (mazeHub.getMaze((int)parsedArgs[0]) == maze)
                      maze = null;
                    if (mazeHub.removeMaze((int)parsedArgs[0]))
                      success();
                    else
                      fail();
                    break;
                case SELECT_MAZE:
                    maze = mazeHub.getMaze((int)parsedArgs[0]);
                    if (maze != null)
                      success();
                    else
                      fail();
                    break;
                case PRINT_MAZE:
                    System.out.print(maze.print());
                    break;
                case CREATE_OBJECT:
                    if (maze != null && maze.createObject(
                          new Position((int)parsedArgs[0],
                                       (int)parsedArgs[1]),
                          (MazeObjectType)parsedArgs[2]))
                      success();
                    else
                      fail();
                    break;
                case DELETE_OBJECT:
                    if (maze != null && 
                        maze.deleteObject(
                          new Position((int)parsedArgs[0],
                                       (int)parsedArgs[1])))
                      success();
                    else
                      fail();
                    break;
                case LIST_AGENTS:
                    listAgents(maze.getAgents());
                    break;
                case MOVE_AGENT:
                    if (maze != null && maze.moveAgent(
                          (int)parsedArgs[0],
                          new Position((int)parsedArgs[1],
                                       (int)parsedArgs[2])))
                      success();
                    else
                      fail();
                    break;
                case QUIT:
                    System.exit(0);
                    break;
            }
        }
    }

    private static void success() {
      System.out.println("Operation Success.");
    }

    private static void fail() {
      System.out.println("Operation Failed.");
    }

    private static void listAgents(Agent[] agents) {
      for (Agent agent : agents)
        System.out.printf("Agent%d at %s. Gold collected: %d.%n",
            agent.getID(), agent.getPosition().toString(),
            agent.getGolds());
    }
}
