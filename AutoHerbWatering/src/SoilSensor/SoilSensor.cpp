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
  m_average_dry_value = measureAverage();
  Serial.print("Average Dry: "); Serial.println(m_average_dry_value);
  m_calibration_state = CalibrationState::MOIST;
}

void SoilSensor::calibrateMoist()
{
  m_average_moist_value = measureAverage();
  Serial.print("Average Moist: "); Serial.println(m_average_moist_value);
  m_calibration_state = CalibrationState::DONE;
}

uint16_t SoilSensor::measureAverage()
{
  uint16_t total = 0;
  uint16_t amount_measurements = 20;
  // Take n measurements over m seconds -> divide by n x m 
  for (int i = 0; i < amount_measurements; i++)
  {
    total += m_sensor.touchRead(0);
    delay(500); // Wait for 0.5s for the Next reading 
  }
  return total / amount_measurements;
}

void SoilSensor::calculateThreshold()
{
  if(m_average_dry_value < m_average_moist_value)
  {
    m_capacitive_threshold = m_average_dry_value;
    Serial.print("Calibration Completed, threshold value= "); Serial.println(m_capacitive_threshold);
  }
  else // Sth failed in calibration! 
  {
    Serial.println("Calibration failed! Values for Dry soil too high compared to Moist soil!");
    m_calibration_state = CalibrationState::DRY;
  }
}

bool SoilSensor::plantsNeedWater()
{
  uint16_t capread = m_sensor.touchRead(0);
  Serial.print("Capacitive: "); Serial.println(capread);
  // 1) Check if value below certain threshold 
  if (capread < m_capacitive_threshold)
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
