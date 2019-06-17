import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;
import java.util.Random;

public class Constructor implements Runnable {
  private final int id, ingotType, capacity, interval, ingotNeeded;
  private boolean active, full;
  private final long randDuration;
  private final Semaphore ingots;
  private final Object spaceLock;

  public Constructor(int id, int interval, int capacity, int type) {
    this.id = id;
    this.interval = interval;
    this.capacity = capacity;
    this.ingotType = type;
    this.active = true;
    this.full = false;
    this.ingotNeeded = ingotType == 0 ? 2 : 3;
    this.ingots = new Semaphore(0);
    this.spaceLock = new Object();
    this.randDuration = (long) new Random(System.currentTimeMillis())
      .doubles(1, interval-interval*0.01, interval+interval*0.01)
      .findFirst().getAsDouble();
  }

  public void run() {
    HW2Logger.WriteOutput(0, 0, id, Action.CONSTRUCTOR_CREATED);
    while (true) {
      if (timeoutWhileWaiting())
        break;
      HW2Logger.WriteOutput(0, 0, id, Action.CONSTRUCTOR_STARTED);
      produceItem();
      notifyProduced();
      HW2Logger.WriteOutput(0, 0, id, Action.CONSTRUCTOR_FINISHED);
      try {
        Thread.sleep(randDuration);
      }
      catch (Exception e) {
        e.printStackTrace();
      }
    }
    constructorStopped();
    HW2Logger.WriteOutput(0, 0, id, Action.CONSTRUCTOR_STOPPED);
  }

  public void newIngot() {
    ingots.release();
    if (ingots.availablePermits() >= capacity)
      full = true;
  }

  private boolean timeoutWhileWaiting() {
    try {
      if (!ingots.tryAcquire(ingotNeeded, 3, TimeUnit.SECONDS))
        return true;
      else
        return false;
    }
    catch (Exception e) {
      e.printStackTrace();
    }
    return true;
  }

  private void notifyProduced() {
    synchronized (spaceLock) {
      this.full = false;
      spaceLock.notifyAll();
    }
  }

  private void produceItem() {
    try {
      Thread.sleep(randDuration);
    }
    catch (Exception e) {
      e.printStackTrace();
    }
  }

  public void waitForSpace() {
    synchronized (spaceLock) {
      try {
        while (full)
          spaceLock.wait();
      }
      catch (Exception e) {
        e.printStackTrace();
      }
    }
  }

  private void constructorStopped() {
    this.active = false;
  }

  public boolean isActive() {
    return this.active;
  }
}
