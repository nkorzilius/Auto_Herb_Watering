#include "SoilSensor.h"

SoilSensor::SoilSensor(int sensorAdress, uint16_t cycleThreshold): m_counter(0), 
  m_adress(sensorAdress), m_cycleThreshold(cycleThreshold), m_calibration_state(CalibrationState::INIT)
{
}

void SoilSensor::sensorInit()
{
  if (!m_sensor.begin(m_adress)) 
  {
    Serial.println("ERROR! seesaw not found");
    while(1) delay(1);
  } 
  else 
  {
    Serial.print("Soil Sensor started! version: ");
    Serial.println(m_sensor.getVersion(), HEX);
  }
  m_calibration_state = CalibrationState::DRY;
}

bool SoilSensor::calibrationStateIsDone()
{
  return m_calibration_state == CalibrationState::DONE;
}

bool SoilSensor::calibrationStateIsDry()
{
  return m_calibration_state == CalibrationState::DRY;
}

bool SoilSensor::calibrationStateIsMoist()
{
  return m_calibration_state == CalibrationState::MOIST;
}

void SoilSensor::calibrateDry()
{
  // TODO: Instead of waiting for 5s perform an average measurement here!
  delay(5000); // wait for 5s!
  m_average_dry_value = 400;
  m_calibration_state = CalibrationState::MOIST;
}

void SoilSensor::calibrateMoist()
{
  // TODO: Instead of waiting for 5s perform an average measurement here!
  delay(5000); // wait for 5s!
  m_average_moist_value = 400;
  m_calibration_state = CalibrationState::DONE;
}

bool SoilSensor::plantsNeedWater()
{
  uint16_t capread = m_sensor.touchRead(0);
  Serial.print("Capacitive: "); Serial.println(capread);
  // 1) Check if value below certain threshold 
  if (capread < THRESHOLD)
  {
    m_counter++;
    // 2) Check if value was below this threshold for nx 
    if (m_counter >= m_cycleThreshold)
    {
      m_counter = 0;
      return true;
    }
  }
  else
  {
    m_counter = 0;
  }
  return false;
}
