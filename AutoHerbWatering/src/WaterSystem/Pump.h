#ifndef PUMP_H
#define PUMP_H

#include "Arduino.h"

class Pump
{
  public:
    Pump(int pin);

    void pumpInit();
    void pumpWater();
  private:

};

#endif // PUMP_H
