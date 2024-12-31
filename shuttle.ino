#include "LEDFlasher.h"
#include "SwitchEvent.h"
#include "settingsADC.h"
#include "storeEEPROM.h"#
#include "ShuttleStateMachine.h"
LEDFlasher builtinLED(LED_BUILTIN);
SwitchEvent pushSwitch(2);
SettingsADC sADC(A0);
struct EE_Entry EEData;
ShuttleStateMachine sm;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  detectorBegin();
  pwmSetup();
  EEData = storeEEPROM::read();
  if (EEData.magic != EXPECTEDMAGIC) {
    storeEEPROM::init();
    EEData = storeEEPROM::read();
  }
  Serial.println("Starting");
}


void loop() {
  // put your main code here, to run repeatedly:
  static int idx = 0;
  
  if (pushSwitch.poll()) {
    if (pushSwitch.pressDuration >= PRESS_DEBOUNCE && pushSwitch.pressDuration < PRESS_LONG) {
      idx++;
      if (idx > 3) idx = 0;
      if (pushSwitch.pressDuration > PRESS_LONG) idx = 0;
      builtinLED.reset();
    }
    if (pushSwitch.pressDuration >= PRESS_LONG) {
      EEData.maxSpeed = sADC.maxSpeed;
      EEData.speedChange_ms = sADC.speedChange_ms;
      EEData.stopDelay = sADC.stopDelay;
      EEData.magic = EXPECTEDMAGIC;
      storeEEPROM::write(EEData);
      idx = 0;
      builtinLED.reset();
    }
  }
  builtinLED.run(idx);
  sADC.update(idx, EEData);
  sm.update(sADC,detectorCheck(sm.activeDetector));
  Serial.print(sm.activeDetector);
  Serial.print("\t");
  Serial.print(sm.speed);
  Serial.print("\t");
  Serial.println(sm.direction);
  RunMotor(sm.direction,sm.speed);
  overCurrentShutdown();
}
