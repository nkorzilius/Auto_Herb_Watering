#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"
class Button
{
  public:
    Button(int buttonPin);
    void buttonInit();
    bool buttonPressed();

  private:
    const int m_pin;
    int m_buttonState;
};
#endif // BUTTON_H