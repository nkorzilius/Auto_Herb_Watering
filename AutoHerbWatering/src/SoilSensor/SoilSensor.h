#ifndef SOILSENSOR_H
#define SOILSENSOR_H

#include "Arduino.h"
#include "Adafruit_seesaw.h"

// TODO: Test & calibrate this value!
const uint16_t THRESHOLD = 600;

class SoilSensor
{
  public:
    SoilSensor(int sensorAdress, uint16_t cycleThreshold);
    void sensorInit();
    bool plantsNeedWater();

  private:
    int m_adress;
    Adafruit_seesaw m_sensor;

    uint16_t m_counter;
    uint16_t m_cycleThreshold;
};

#endif // SOILSENSOR_H