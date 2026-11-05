#include "src/SoilSensor/SoilSensor.h"
#include "src/WaterSystem/Pump.h"
#include "src/WaterSystem/WaterLevelSensor.h"
#include "src/UserInteraction/Button.h"
#include "src/UserInteraction/Led.h"

enum Pins{
  BUTTON = 2,
  PUMP = 5,
  WATERLEVEL = 6,
  LED_YELLOW = 11,
  LED_GREEN = 12,
  LED_RED = 13
};

// Component Classes
SoilSensor soilSensor(0x36, 10); // After 10 sensor_read_interval's below threshold will signal water needed.
Pump pump(Pins::PUMP);
WaterLevelSensor waterLevel(Pins::WATERLEVEL);
Button pushButton(Pins::BUTTON);
Led yellowLed(Pins::LED_YELLOW);
Led redLed(Pins::LED_RED);
Led greenLed(Pins::LED_GREEN);

void setup() {
  Serial.begin(115200);

  yellowLed.ledInit();
  redLed.ledInit();
  greenLed.ledInit();

  soilSensor.sensorInit();
  pump.pumpInit();
  waterLevel.sensorInit();
  pushButton.buttonInit();
}

void loop() 
{ 
  unsigned long currentMillis = millis(); // Time since program started
  // Calibrating the Soil Sensor on System Startup:
  while (!soilSensor.calibrationStateIsDone())
  {
    calibrateSoilSensor();
  }

  if (pushButton.buttonPressed())
  {
    activatePump();
  }
  else if (soilSensor.plantsNeedWater())
  {
    activatePump();
  }
}

void calibrateSoilSensor()
{
  if (soilSensor.calibrationStateIsDry())
  {
    redLed.blinkLed();
    // TODO: If adding Display -> Instruct user to put the Probe in Dry Soil & press button to start measuring!
    if (pushButton.buttonPressed())
    {
      redLed.turnOnLed(true);
      soilSensor.calibrateDry();
      redLed.turnOnLed(false);
    }
  }
  else if (soilSensor.calibrationStateIsMoist())
  {
    yellowLed.blinkLed();
    // TODO: If adding Display -> Instruct user to put the Probe in Moist Soil & press button to start measuring!
    if (pushButton.buttonPressed())
    {
      yellowLed.turnOnLed(true);
      soilSensor.calibrateMoist();
      soilSensor.calculateThreshold();
      yellowLed.turnOnLed(false);
      if (soilSensor.calibrationStateIsDone())
      {
        greenLed.turnOnLed(true);
      }
    }
  }
}

void activatePump()
{
  if (waterLevel.waterLevelSufficient())
  {
    pump.pumpWater();
  }
  else
  {
    // TODO Add notifying user to refill reservoir!
    Serial.print("Refill the Reservoir!");
  }
}
