#include "analogIO.h"

#define ST_LIM CUR9_0A
#define LT_LIM CUR6_0A
#define LT_SAMPLES 100


void overCurrentShutdown()
{
if (checkCurrentLimit(A3,ST_LIM,LT_LIM,LT_SAMPLES))
{
  RunMotor(false,0);
  while(true) ; // Loop forever with motor off, will need a reset
 }
return;
}

bool checkCurrentLimit(int pin, int stLim, int ltLim, int countMax)
{
  int iVal;
  static int count=0;
  bool res;

  iVal=analogRead(pin);

  if (iVal<=stLim) res=false; else res=true;
  if (iVal<=ltLim) count=0;
  if (!res) 
    {
      if (iVal>ltLim) count++;
      if (count>countMax) res=true;
    }
  //traceCurrentMeas(iVal);
  return(res);
}

void analogSetup() {
  // put your setup code here, to run once:
  analogReference(DEFAULT);
  pinMode(A3,INPUT);
}
