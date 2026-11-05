#ifndef LED_H
#define LED_H

#include "Arduino.h"

class Led
{
public:
    Led(int pin);
    void ledInit();
    void turnOnLed(bool led_on);
private:
    int m_pin;
};

#endif // LED_H