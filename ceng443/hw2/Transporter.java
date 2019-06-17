import java.util.Random;

public class Transporter implements Runnable {
  private final int id, smelterId, constructorId, interval;
  private final Smelter smelter;
  private final Constructor constructor;
  private final long randDuration;

  public Transporter
    (int id, int interval, int smelterId, int constructorId)
  {
    this.id = id;
    this.interval = interval;
    this.smelterId = smelterId;
    this.constructorId = constructorId;
    this.smelter = Simulator.getSmelter(smelterId);
    this.constructor = Simulator.getConstructor(constructorId);
    this.randDuration = (long) new Random(System.currentTimeMillis())
      .doubles(1, interval-interval*0.01, interval+interval*0.01)
      .findFirst().getAsDouble();
  }

  public void run() {
    HW2Logger.WriteOutput(0, id, 0, Action.TRANSPORTER_CREATED);
    while ((smelter.isActive() || smelter.hasIngots())
        && constructor.isActive())
    {
      smelter.waitNextLoad();
      HW2Logger.WriteOutput(smelterId, id, 0, Action.TRANSPORTER_TRAVEL);
      sleep();
      HW2Logger.WriteOutput(smelterId, id, 0, Action.TRANSPORTER_TAKE_INGOT);
      sleep();
      smelter.loaded();
      constructor.waitForSpace();
      HW2Logger.WriteOutput(0, id, constructorId, Action.TRANSPORTER_TRAVEL);
      sleep();
      HW2Logger.WriteOutput(0, id, constructorId, Action.TRANSPORTER_DROP_INGOT);
      sleep();
      constructor.newIngot();
    }
    HW2Logger.WriteOutput(0, id, 0, Action.TRANSPORTER_STOPPED);
  }

  private void sleep() {
    try {
      Thread.sleep(randDuration);
    }
    catch (Exception e) {
      e.printStackTrace();
    }
  }
}
