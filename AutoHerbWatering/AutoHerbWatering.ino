#include "src/SoilSensor/SoilSensor.h"
#include "src/WaterSystem/Pump.h"
#include "src/WaterSystem/WaterLevelSensor.h"
#include "src/UserInteraction/Button.h"
#include "src/UserInteraction/Led.h"

unsigned long previousMeasurement = 0; // Store time for first event
const long sensor_read_interval = 1000; // Interval for reading soil moisture level [milliseconds] (5min = 300000)

enum Pins{
  BUTTON = 2,
  PUMP = 5,
  WATERLEVEL = 6,
  LED_YELLOW = 13
};

// Component Classes
SoilSensor soilSensor(0x36, 10); // After 10 sensor_read_interval's below threshold will signal water needed.
Pump pump(Pins::PUMP);
WaterLevelSensor waterLevel(Pins::WATERLEVEL);
Button pushButton(Pins::BUTTON);
Led yellowLed(Pins::LED_YELLOW);

void setup() {
  Serial.begin(115200);

  yellowLed.ledInit();
  soilSensor.sensorInit();
  pump.pumpInit();
  waterLevel.sensorInit();
  pushButton.buttonInit();

  calibrateSoilSensor();
}

void loop() 
{ 
  unsigned long currentMillis = millis(); // Time since program started
  if (pushButton.buttonPressed())
  {
    activatePump();
  }
  // Check if interval milliseconds have passed before executing loop:
  else if (currentMillis - previousMeasurement >= sensor_read_interval) 
  {
    previousMeasurement = millis();

    if (soilSensor.plantsNeedWater())
    {
      activatePump();
    }
  }
}

void calibrateSoilSensor()
{
  // Process:
  yellowLed.turnOnLed(true);
  // Red Light: Nothing calibrated -> Put sensor in Dry Soil -> Press button to calibrate
  // Yellow Light: blinking) calibration in process
  // Yellow Light: (normal) put Sensor in soil just watered -> Press button to calibrate
  // Yellow Light- Blinking calibration in process
  // Green Light: calibration done!
 
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
