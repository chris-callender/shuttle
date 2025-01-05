#include "LEDFlasher.h"
#include <Arduino.h>

LEDFlasher::LEDFlasher(int pin) {
  pinMode(pin, OUTPUT);
  _pin = pin;
  LEDFlasher::reset();
}

LEDFlasher::~LEDFlasher() {
}

void LEDFlasher::reset() {
  digitalWrite(_pin, LOW);
  _cycleStartms = millis();
}

void LEDFlasher::run(int c, bool ledOverride) {
  unsigned long cycleTime;
  unsigned int subCycle;
  if (ledOverride) {
    digitalWrite(_pin, HIGH);
  } else {
    cycleTime = millis() - _cycleStartms;
    if (cycleTime > CYCLE) _cycleStartms += CYCLE;
    subCycle = cycleTime >> SUBCYCLESHIFT;
    if (subCycle < 2 * c) digitalWrite(_pin, subCycle & 0b1);
    else digitalWrite(_pin, LOW);
  }
}
