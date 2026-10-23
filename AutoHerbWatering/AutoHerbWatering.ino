#include "src/SoilSensor/SoilSensor.h"

unsigned long previousMeasurement = 0; //store time for first event

const long interval = 1000; //interval for reading soil moisture level [milliseconds]

SoilSensor soilSensor(0x36, 10);

void setup() {
  Serial.begin(115200);

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  soilSensor.sensorInit();
}

void loop() 
{ 
  //check time since program started, and store in "currentMillis"
  unsigned long currentMillis = millis();

  //conditional that checks whether 1 second has passed since last sensor read
  if (currentMillis - previousMeasurement >= interval) {
    previousMeasurement = millis();
    //execute a piece of code, every *1 second*
    if (soilSensor.plantsNeedWater())
    {
      // TODO: Replace code with Watering logic:
      // Check water level, if enough in reservoir: Activate pump
      digitalWrite(LED_BUILTIN, HIGH);
      delay(2000); // sleep for 2s to have buildin led on high!
    }
    else
    {
      // TODO: Remove Else clause 
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}
