#include "src/SoilSensor/SoilSensor.h"
#include "src/WaterSystem/Pump.h"
#include "src/WaterSystem/WaterLevelSensor.h"
#include "src/UserInteraction/Button.h"

unsigned long previousMeasurement = 0; // Store time for first event
const long sensor_read_interval = 1000; // Interval for reading soil moisture level [milliseconds] (5min = 300000)

// Pins:
const int buttonPin = 2;
const int pumpPin = 5;
const int waterLevelPin = 6;
const int yellowLedPin = 13;

// Component Classes
SoilSensor soilSensor(0x36, 10); // After 10 sensor_read_interval's below threshold will signal water needed.
Pump pump(pumpPin);
WaterLevelSensor waterLevel(waterLevelPin);
Button pushButton(buttonPin);

void setup() {
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  soilSensor.sensorInit();
  pump.pumpInit();
  waterLevel.sensorInit();
  pushButton.buttonInit();
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
    else
    {
      // TODO: Remove Else clause 
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}

void calibrateSoilSensor()
{
  // Process:
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
    digitalWrite(LED_BUILTIN, HIGH); // TODO Remove the Led Write!
    pump.pumpWater();
  }
  else
  {
    // TODO Add notifying user to refill reservoir!
    Serial.print("Refill the Reservoir!");
  }
}

void turnOnLed(bool LedOn)
{
  if(LedOn)
  {
    digitalWrite(yellowLedPin, HIGH);
  }
  else
  {
    digitalWrite(yellowLedPin, LOW);
  }
}