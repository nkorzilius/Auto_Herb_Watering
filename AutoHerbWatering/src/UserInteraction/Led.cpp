#include "Led.h"

Led::Led(int pin): m_pin(pin), m_led_is_on(false)
{}

void Led::ledInit()
{
    pinMode(m_pin, OUTPUT);
    turnOnLed(m_led_is_on);
    m_prevMeasurement = 0; // Store time for first event
    Serial.print("Led initialized on pin: "); Serial.println(m_pin);
}

void Led::turnOnLed(bool led_on)
{
    led_on ? digitalWrite(m_pin, HIGH) : digitalWrite(m_pin, LOW);
    m_led_is_on = led_on;
}

void Led::blinkLed()
{
    unsigned long currentMillis = millis(); // Time since program started
    if (currentMillis - m_prevMeasurement >= 1000) // Interval is 1s 
    {
        m_prevMeasurement = millis();
        turnOnLed(!m_led_is_on);
    }
}