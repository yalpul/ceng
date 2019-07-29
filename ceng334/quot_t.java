import java.net.Socket;
import java.net.ServerSocket;
import java.io.PrintWriter;

class Quote {
  private static final String quote = "fortuna favet sapienti";
  public static void main(String[] args) {
    try {
      ServerSocket ss = new ServerSocket(6017);

      while (true) {
        Socket client = ss.accept();
        new Thread(() -> handleRequest(client)).start();
      }
    }
    catch (Exception e) {
      e.printStackTrace();
    }
  }

  private static void handleRequest(Socket client) {
    try {
      PrintWriter pw = new PrintWriter(client.getOutputStream(), true);
      pw.println(quote);
      client.close();
    }
    catch (Exception e) {
      e.printStackTrace();
    }
  }
}
