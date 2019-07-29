import java.net.Socket;
import java.net.ServerSocket;
import java.io.PrintWriter;

class Quote {
  public static void main(String[] args) {
    final String quote = "fortuna favet sapienti";
    try {
      ServerSocket ss = new ServerSocket(6017);

      while (true) {
        Socket client = ss.accept();

        PrintWriter pw = new PrintWriter(client.getOutputStream(), true);

        pw.println(quote);

        client.close();
      }
    }
    catch (Exception e) {
      e.printStackTrace();
    }
  }
}
