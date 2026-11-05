#include "Button.h"

Button::Button(int buttonPin): m_pin(buttonPin), m_buttonState(0)
{}

void Button::buttonInit()
{
    pinMode(m_pin, INPUT);
    Serial.print("Button initialized on pin: "); Serial.println(m_pin);
}

bool Button::buttonPressed()
{
    int currentState = digitalRead(m_pin);
    bool justPressed = false;
    // Check if currentState == HIGH & changed!
    if ((currentState == HIGH) && (currentState != m_buttonState))
    {
        justPressed = true;
    }

    m_buttonState = currentState;
    return justPressed;
}