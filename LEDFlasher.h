#ifndef LEDFLASHER_H
#define LEDFLASHER_H
#define CYCLE 2048
#define SUBCYCLESHIFT 7
class LEDFlasher
{
  public:
  LEDFlasher( int pin);
  ~LEDFlasher();
  void run(int value);
  void reset();
  private:
  unsigned long _cycleStartms;
  unsigned int _pin;
};
#endif