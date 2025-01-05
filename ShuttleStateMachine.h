#ifndef SHUTTLESMH
#define SHUTTLESMH
#include "settingsADC.h"
#define RUN 0
#define DECEL 1
#define STOP 2

#define DETNONE 0
#define DET1 1
#define DET2 2
#define DETBOTH 3

class ShuttleStateMachine {
public:
  ShuttleStateMachine();
  ~ShuttleStateMachine();
  void update(SettingsADC settings,int det);
  int speed;
  bool direction;
  int activeDetector;
private:
  int state;
  long lastStateChange_ms;
  int _speedReached;
};
#endif