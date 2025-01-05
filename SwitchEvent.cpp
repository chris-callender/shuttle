#include "SwitchEvent.h"
#include <Arduino.h>

SwitchEvent::SwitchEvent(int pin)
{
  _pin=pin;
  pinMode(pin,INPUT_PULLUP);
}

SwitchEvent::~SwitchEvent()
{

}

bool SwitchEvent::poll()
{
  switchState=!digitalRead(_pin);
  if (switchState==LOW && lastSwitchState==HIGH) eventType=EVENT_FALLING;
  if (switchState==HIGH && lastSwitchState==LOW) eventType=EVENT_RISING;
  if (switchState==lastSwitchState) eventType=EVENT_NONE;
  lastSwitchState=switchState;

  if (eventType==EVENT_RISING) { downTime=millis(); }
  if (switchState==HIGH) {preemptDuration = millis()-downTime; }
  if (eventType==EVENT_FALLING) 
  { 
    pressDuration=millis()-downTime;
    preemptDuration=0;
    return(true);
  }
  else return false;
}
