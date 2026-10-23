#include "SoilSensor.h"

SoilSensor::SoilSensor(int sensorAdress, uint16_t cycleThreshold): m_counter(0), m_adress(sensorAdress), m_cycleThreshold(cycleThreshold)
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
}

bool SoilSensor::plantsNeedWater()
{
  uint16_t capread = m_sensor.touchRead(0);
  Serial.print("Capacitive: "); Serial.println(capread);
  // TODO: Implement Logic:
  // 1) Check if value below certain threshold 
  if (capread < THRESHOLD)
  {
    m_counter++;
    // 2) Check if value was below this threshold for nx 
    if (m_counter >= m_cycleThreshold)
    {
      Serial.print("Exceeded threshold for 10 cycles!");
      m_counter = 0;
      return true;
    }
  }
  return false;
}
