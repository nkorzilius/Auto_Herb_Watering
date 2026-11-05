#include "Led.h"

Led::Led(int pin): m_pin(pin), m_led_is_on(false)
{}

void Led::ledInit()
{
    pinMode(m_pin, OUTPUT);
    turnOnLed(m_led_is_on);
    Serial.print("Led initialized on pin: "); Serial.println(m_pin);
}

void Led::turnOnLed(bool led_on)
{
    led_on ? digitalWrite(m_pin, HIGH) : digitalWrite(m_pin, LOW);
    m_led_is_on = led_on;
}

void Led::blinkLed(bool blinking)
{
    if(blinking)
    {
        turnOnLed(!m_led_is_on);
    }
    else
    {
        turnOnLed(false);
    }
}