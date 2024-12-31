#ifndef STOREEEPROM_H
#define STOREEEPROM_H
#define ADDR 0
#define EXPECTEDMAGIC 0xabcd1234
struct EE_Entry
{
    unsigned long magic;
    int maxSpeed;
    float speedChange_ms;
    long stopDelay;
};

class storeEEPROM
{
public:
  static void init();
  static struct EE_Entry read();
  static void write(struct EE_Entry toStore);
};
#endif