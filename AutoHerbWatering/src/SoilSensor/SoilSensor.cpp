#include "SoilSensor.h"

SoilSensor::SoilSensor(int sensorAdress, uint16_t cycleThreshold): m_counter(0), m_cap_total(0),
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
    m_calibration_state = CalibrationState::DRY;
    m_prevMeasurement = 0;
  } 
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
  m_average_dry_value = measureAverage(20);
  Serial.print("Average Dry: "); Serial.println(m_average_dry_value);
  m_calibration_state = CalibrationState::MOIST;
}

void SoilSensor::calibrateMoist()
{
  m_average_moist_value = measureAverage(20);
  Serial.print("Average Moist: "); Serial.println(m_average_moist_value);
  m_calibration_state = CalibrationState::DONE;
}

uint16_t SoilSensor::measureAverage(uint16_t amount_of_measurements)
{
  uint16_t total = 0;
  for (int i = 0; i < amount_of_measurements; i++)
  {
    total += m_sensor.touchRead(0);
    delay(200); // Wait for 0.2s for the Next reading, BLOCKING!
  }
  return total / amount_of_measurements;
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
  uint16_t avg_cap = 0;
  // Averaging non blocking:
  unsigned long currentMillis = millis(); // Time since program started
  if (currentMillis - m_prevMeasurement >= 1000) // Interval is 1s 
  {
    m_prevMeasurement = millis();

    m_cap_total += m_sensor.touchRead(0);
    m_averaging_counter++;
    if (m_averaging_counter > 10)
    {
      avg_cap = m_cap_total / m_averaging_counter;
      m_cap_total = 0;
      m_averaging_counter = 0;
      return averageExceedsThreshold(avg_cap);
    }
    return false;
  }
}

bool SoilSensor::averageExceedsThreshold(uint16_t average)
{
  Serial.print("Capacitive: "); Serial.println(average);
  // 1) Check if value below certain threshold 
  if (average < m_capacitive_threshold)
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