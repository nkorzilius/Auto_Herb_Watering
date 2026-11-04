# Auto Herb Watering
System running on a Arduino Uno, when soil of herbs gets too dry will water the plants. 

## Hardware

- Micro Controller: Arduino Uno R3
- Soil Sensor: [Adafruit Seesaw I2C Soil Sensor](https://learn.adafruit.com/adafruit-stemma-soil-sensor-i2c-capacitive-moisture-sensor)
- Basic Push Button

![Wiring Diagram](/images/WiringDiagram.png)


## Code

Main Arduino loop: `AutoHerbWatering.ino` 

Uses:

- SoilSensor (Depends on: Adafruit_seesaw.h)


## Libraries

Install the following libraries through the Arduino IDE (in Toolbar: Sketch > Include Libary > Manage Libraries...)

- Adafruit seesaw
