#ifndef SOILSENSOR_H
#define SOILSENSOR_H

#include "Arduino.h"
#include "Adafruit_seesaw.h"

enum CalibrationState {
  INIT,
  DRY,
  MOIST,
  DONE
};

class SoilSensor
{
  public:
    SoilSensor(int sensorAdress, uint16_t cycleThreshold);
    void sensorInit();
    bool plantsNeedWater();

    bool calibrationStateIsDone();
    bool calibrationStateIsDry();
    bool calibrationStateIsMoist();

    void calibrateDry();
    void calibrateMoist();
    void calculateThreshold();

  private:
    int m_adress;
    Adafruit_seesaw m_sensor;

    uint16_t m_counter;
    uint16_t m_cycleThreshold;
    uint16_t m_capacitive_threshold;

    CalibrationState m_calibration_state;
    uint16_t m_average_dry_value;
    uint16_t m_average_moist_value;

    uint16_t measureAverage();
};

#endif // SOILSENSOR_H