#include "Led.h"

Led::Led(int pin): m_pin(pin)
{}

void Led::ledInit()
{
    pinMode(m_pin, OUTPUT);
    Serial.print("Led initialized on pin: "); Serial.println(m_pin);
}

void Led::turnOnLed(bool led_on)
{
    led_on ? digitalWrite(m_pin, HIGH) : digitalWrite(m_pin, LOW);
}