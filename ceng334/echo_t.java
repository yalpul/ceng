import java.net.ServerSocket;
import java.net.Socket;

import java.io.InputStream;
import java.io.OutputStream;

class Echo {
  public static void main(String[] args) {
    try {
      ServerSocket ss = new ServerSocket(1234);

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
      InputStream is = client.getInputStream();
      OutputStream os = client.getOutputStream();

      while (true) {
        int read = is.read();
        if (read == -1)
          break;
        os.write(read);
      }
      client.close();
    }
    catch (Exception e) {
      e.printStackTrace();
    }
  }
}
