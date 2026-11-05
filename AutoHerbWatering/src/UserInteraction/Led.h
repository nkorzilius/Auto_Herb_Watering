#ifndef LED_H
#define LED_H

#include "Arduino.h"

class Led
{
public:
    Led(int pin);
    void ledInit();
    void turnOnLed(bool led_on);
    void blinkLed(bool blinking);
private:
    int m_pin;
    bool m_led_is_on;
};

#endif // LED_H