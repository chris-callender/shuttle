#ifndef SWITCHEVENTH
#define SWITCHEVENTH
#define EVENT_NONE 0
#define EVENT_RISING 1
#define EVENT_FALLING 2
#define PRESS_DEBOUNCE 50
#define PRESS_LONG 2000
#include <Arduino.h>


class SwitchEvent
{
  public:
  SwitchEvent(int);
  ~SwitchEvent();
  bool poll();
  unsigned long pressDuration=0;
  unsigned long preemptDuration=0;
  uint8_t eventType=EVENT_NONE;
  uint8_t switchState=LOW;

  private:
  uint8_t lastSwitchState;
  unsigned long downTime;
  int _pin;
};
#endif
