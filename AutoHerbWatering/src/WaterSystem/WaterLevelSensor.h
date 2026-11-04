#ifndef WATER_LEVEL_SENSOR_H
#define WATER_LEVEL_SENSOR_H

#include "Arduino.h"

class WaterLevelSensor
{
  public:
    WaterLevelSensor(int pin);

    void sensorInit();
    bool waterLevelSufficient();
  private:

};

#endif // WATER_LEVEL_SENSOR_H
