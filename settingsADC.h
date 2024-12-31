#ifndef SETTINGSADC_H
#define SETTINGSADC_H
#include "storeEEPROM.h"
class SettingsADC
{
  public:
    void update(int idx,struct EE_Entry data);
    SettingsADC(int pin);
    int maxSpeed;
    float speedChange_ms;
    long stopDelay;
  private:
    int _pin;
};
#endif
