import java.util.concurrent.Semaphore;
import java.util.stream.DoubleStream;
import java.util.Random;

public class Smelter implements Runnable {
  private final int id, ingotType, capacity, interval, totalIngot;
  private boolean active;
  private final Semaphore ingots, lockedIngots;
  private final long randDuration;
  private final Object loadLock;
  private int produced = 0;
  
  public Smelter(int id, int interval, int capacity, int type, int total) {
    this.id = id;
    this.interval = interval;
    this.capacity = capacity;
    this.ingotType = type;
    this.totalIngot = total;
    this.active = true;
    this.ingots = new Semaphore(0);
    this.lockedIngots = new Semaphore(0);
    this.loadLock = new Object();
    this.randDuration = (long) new Random(System.currentTimeMillis())
      .doubles(1, interval-interval*0.01, interval+interval*0.01)
      .findFirst().getAsDouble();
  }

  public void run() {
    HW2Logger.WriteOutput(id, 0, 0, Action.SMELTER_CREATED);
    while (produced < totalIngot) {
      waitCanProduce();
      HW2Logger.WriteOutput(id, 0, 0, Action.SMELTER_STARTED);
      produceIngot();
      HW2Logger.WriteOutput(id, 0, 0, Action.SMELTER_FINISHED);
      produced++;
      try {
        Thread.sleep(randDuration);
      }
      catch (Exception e) {
        e.printStackTrace();
      }
    }
    smelterStopped();
    HW2Logger.WriteOutput(id, 0, 0, Action.SMELTER_STOPPED);
  }

  public void waitNextLoad() {
    try {
      ingots.acquire();
    }
    catch (Exception e) {
      e.printStackTrace();
    }
  }

  private void produceIngot() {
    try {
      Thread.sleep(randDuration);
      ingots.release();
      lockedIngots.release();
      if (1+produced == totalIngot)
        smelterStopped();
    }
    catch (Exception e) {
      e.printStackTrace();
    }
  }

  private void waitCanProduce() {
    synchronized (loadLock) {
      try {
        while (lockedIngots.availablePermits() >= capacity)
          loadLock.wait();
      }
      catch (Exception e) {
        e.printStackTrace();
      }
    }
  }

  public void loaded() {
    synchronized (loadLock) {
      try {
        lockedIngots.acquire();
        loadLock.notifyAll();
      }
      catch (Exception e) {
        e.printStackTrace();
      }
    }
  }

  private void smelterStopped() {
    this.active = false;
  }

  public boolean hasIngots() {
    return ingots.availablePermits() > 0;
  }

  public boolean isActive() {
    return this.active;
  }
}
