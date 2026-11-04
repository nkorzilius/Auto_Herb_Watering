#include "src/SoilSensor/SoilSensor.h"
#include "src/WaterSystem/Pump.h"
#include "src/WaterSystem/WaterLevelSensor.h"
#include "src/UserInteraction/Button.h"

unsigned long previousMeasurement = 0; // Store time for first event

const long interval = 1000; // Interval for reading soil moisture level [milliseconds]

SoilSensor soilSensor(0x36, 10);
Pump pump(5);
WaterLevelSensor waterLevel(6);
Button pushButton(2);

void setup() {
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  soilSensor.sensorInit();
  pump.pumpInit();
  waterLevel.sensorInit();
  pushButton.buttonInit();
}

void loop() 
{ 
  unsigned long currentMillis = millis(); // Time since program started
  // TODO: First check if button pressed (if True -> call activatePump())
  if (pushButton.buttonPressed())
  {
    activatePump();
  }
  // Check if interval milliseconds have passed before executing loop:
  if (currentMillis - previousMeasurement >= interval) 
  {
    previousMeasurement = millis();

    if (soilSensor.plantsNeedWater())
    {
      activatePump();
    }
    else
    {
      // TODO: Remove Else clause 
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}

void activatePump()
{
  if (waterLevel.waterLevelSufficient())
  {
    digitalWrite(LED_BUILTIN, HIGH); // TODO Remove the Led Write!
    pump.pumpWater();
  }
  else
  {
    // TODO Add notifying user to refill reservoir!
    Serial.print("Refill the Reservoir!");
  }
}