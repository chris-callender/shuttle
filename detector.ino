#include "Arduino.h"
#include "ShuttleStateMachine.h"
#define DETTRANSITIONS 10
#define DETTHRESH 500
void detectorBegin() {
  analogReference(DEFAULT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
}

int detectorCheck(int activeDetector) {
  static unsigned int history1L[DETTRANSITIONS] = { 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023 };
  static unsigned int history2L[DETTRANSITIONS] = { 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023 };
  static unsigned int history1H[DETTRANSITIONS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  static unsigned int history2H[DETTRANSITIONS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int a1,a2;
  static int idx1L = 0, idx1H = 0, idx2L = 0, idx2H = 0;
  static long lastTime = 0;
  static uint8_t out1 = 0, out2 = 1;
  long sum1L = 1, sum1H = 0, sum2L = 1, sum2H = 0;
  long res1, res2;

  if (millis() == lastTime) return (DETNONE);
  lastTime = millis();
  // Read the inputs
  
a1=analogRead(A1);
a2=analogRead(A2);


  if (out1==0) {history1L[idx1L++] = a1;} else {history1H[idx1H++]=a1;}
  if (out2==0) {history2L[idx2L++]=a2;} else {history2H[idx2H++]=a2;}

  if (idx1L>=DETTRANSITIONS) idx1L=0;
  if (idx1H>=DETTRANSITIONS) idx1H=0;
  if (idx2L>=DETTRANSITIONS) idx2L=0;
  if (idx2H>=DETTRANSITIONS) idx2H=0;
  if (out1==0) out1=1; else out1=0;
  if (out2==0) out2=1; else out2=0;
  digitalWrite(8,out1);
  digitalWrite(7,out2);

 // Detection logic
sum1L=0;
sum2L=0;
sum1H=0;
sum2H=0;
 for (int i=0;i<DETTRANSITIONS;i++)
 {
      sum1L = sum1L + history1L[i];
      sum1H = sum1H + history1H[i];
      sum2L = sum2L + history2L[i];
      sum2H = sum2H + history2H[i];
 }
res1=sum1H-sum1L;
res2=sum2H-sum2L;

if (activeDetector==DETBOTH)
{
      if (res1 >= DETTHRESH) return (DET1);
      if (res2 >= DETTHRESH) return (DET2);
}
if (activeDetector==DET1)
{
      if (res1 >= DETTHRESH) return (DET1);
}
if (activeDetector==DET2)
{
      if (res2 >= DETTHRESH) return (DET2);
}
return(DETNONE);
}