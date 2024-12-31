#include "storeEEPROM.h"
#include <EEPROM.h>

void storeEEPROM::init()
{
  struct EE_Entry toStore;
  toStore.magic=EXPECTEDMAGIC;
  toStore.maxSpeed=50; // 50% default for max speed
  toStore.speedChange_ms=0.05; // Ramp up to 50% in 1 second (0.05*1000 = 50)
  toStore.stopDelay=10000; // 10 Seconds stop delay
  write(toStore);
}

struct EE_Entry storeEEPROM::read()
{
  struct EE_Entry fromStore;
  EEPROM.get(ADDR,fromStore);
  return(fromStore);
}

void storeEEPROM::write(struct EE_Entry toEEPROM)
{
  EEPROM.put(ADDR,toEEPROM);
}
