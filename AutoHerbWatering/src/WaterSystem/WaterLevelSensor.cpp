#include "WaterLevelSensor.h"

WaterLevelSensor::WaterLevelSensor(int pin)
{}

void WaterLevelSensor::sensorInit()
{
  // TODO Implement initialization!
  Serial.println("Water Level Sensor Initialized!");
}

bool WaterLevelSensor::waterLevelSufficient()
{
  // TODO Implement logic:
  // read sensor -> compare to threshold
  return true;
}