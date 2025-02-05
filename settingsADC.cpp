#include "settingsADC.h"
#include "Arduino.h"
#include <math.h>
#include "storeEEPROM.h"

SettingsADC::SettingsADC(int pin)
{
  _pin=pin;
  pinMode(pin,INPUT);
}
void SettingsADC::update(int idx,struct EE_Entry data)
{
  float fADC;
  int iADC;
  iADC=analogRead(_pin);
  fADC=(float)iADC*(1.0/1024.0);
    maxSpeed=data.maxSpeed;
    speedChange_ms=data.speedChange_ms;
    stopDelay=data.stopDelay;
  //Now potentially override one of the settings from EEPROM
  switch(idx)
  {
    case 0:

      break;
    case 1:
      fADC=fADC*100.0;
      maxSpeed=fADC;
      break;
    case 2:
      fADC=5.0-(fADC*4.0); //Time to do the acceleration in seconds
      speedChange_ms=(maxSpeed/(fADC*1000)); //Speed change in 1ms
      break;
    case 3:
      stopDelay=(fADC*240.0)*1000.0; // time to stop for in ms
      break;
  }
}
