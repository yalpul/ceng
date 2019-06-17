import java.util.Scanner;
import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;

public class Simulator {
  private static ExecutorService es;
  private static Smelter[] smelters;
  private static Constructor[] constructors;
  private static Transporter[] transporters;

  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    
    int smelterCount = scanner.nextInt();
    smelters = createSmelters(scanner, smelterCount);

    int constructorCount = scanner.nextInt();
    constructors = createConstructors(scanner, constructorCount);

    int transporterCount = scanner.nextInt();
    transporters = createTransporters(scanner, transporterCount);

    es = Executors.newFixedThreadPool(
        smelterCount + constructorCount + transporterCount);
    submitJobs();
    es.shutdown();
  }

  public static Smelter getSmelter(int index) {
    return smelters[index-1];
  }

  public static Constructor getConstructor(int index) {
    return constructors[index-1];
  }

  private static Smelter[] createSmelters(Scanner scanner, int count) {
    Smelter[] smelters = new Smelter[count];
    for (int i = 0; i < count; i++) {
      int interval = scanner.nextInt();
      int capacity = scanner.nextInt();
      int type = scanner.nextInt();
      int total = scanner.nextInt();
      smelters[i] = new Smelter(i+1, interval, capacity, type, total);
    }
    return smelters;
  }

  private static Constructor[] createConstructors(Scanner s, int count) {
    Constructor[] constructors = new Constructor[count];
    for (int i = 0; i < count; i++) {
      int interval = s.nextInt();
      int capacity = s.nextInt();
      int type = s.nextInt();
      constructors[i] = new Constructor(i+1, interval, capacity, type);
    }
    return constructors;
  }

  private static Transporter[] createTransporters(Scanner s, int count) {
    Transporter[] tranporters = new Transporter[count];
    for (int i = 0; i < count; i++) {
      int interval = s.nextInt();
      int smelter = s.nextInt();
      int constructor = s.nextInt();
      tranporters[i] = new Transporter(i+1, interval, smelter, constructor);
    }
    return tranporters;
  }

  private static void submitJobs() {
    HW2Logger.InitWriteOutput();
    for (Smelter s : smelters)
      es.execute(s);
    for (Constructor c : constructors)
      es.execute(c);
    for (Transporter t : transporters)
      es.execute(t);
  }
}

