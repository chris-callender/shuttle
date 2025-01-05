#include "ShuttleStateMachine.h"
#include "Arduino.h"

ShuttleStateMachine::ShuttleStateMachine()
{
  lastStateChange_ms=millis();
  state=RUN;
  activeDetector=DETBOTH;
  speed=0;
  _speedReached=0;
  direction=false;
}

ShuttleStateMachine::~ShuttleStateMachine()
{

}

void ShuttleStateMachine::update(SettingsADC settings, int det)
{
  long currentStateTime_ms;
  

  currentStateTime_ms=millis()-lastStateChange_ms;
  switch(state)
  {
    case RUN:
      if (speed<settings.maxSpeed) 
      {
        speed=(float)currentStateTime_ms*(float)settings.speedChange_ms;
      } else speed=settings.maxSpeed;
      // If an active detector fires...
      if (det==1 || det==2) 
      {
        state=DECEL;
        lastStateChange_ms=millis();
        if (det==1) activeDetector=DET2; else activeDetector=DET1;
        _speedReached=speed;
      }
      break;
    case DECEL:
      if (speed>0)
      {
        speed=_speedReached-((float)currentStateTime_ms*(float)settings.speedChange_ms);
      }
      else
      {
        speed=0;
        state=STOP;
        lastStateChange_ms=millis();
      }
      break;
      case STOP:
      {
        speed=0;
        if (currentStateTime_ms>=settings.stopDelay)
        {
          direction=!direction;
          state=RUN;
          lastStateChange_ms=millis();
        }
        break;
      }
      default:
      break;
  }
}

