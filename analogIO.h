bool checkCurrentLimit(int pin, int stLim, int ltLim, int countMax);


//Threshold for limiting current
//Eg for 3A limit, 0.1 ohm Rsense, Vlimit=0.3v
//Assuming 5v Nano supply, 10 bit ADC
//Threshhold = (0.3/5)*1024 = 61.44
// These are now set in EEPROM
#define RSENSE 0.25
// Ohms law
#define CUR0_5A  (int)(0.5*(1024.0/5.0)*RSENSE)
#define CUR1_0A  (int)(1.0*(1024.0/5.0)*RSENSE)
#define CUR1_5A  (int)(1.5*(1024.0/5.0)*RSENSE)
#define CUR2_0A  (int)(2.0*(1024.0/5.0)*RSENSE)
#define CUR2_5A  (int)(2.5*(1024.0/5.0)*RSENSE)
#define CUR3_0A  (int)(3.0*(1024.0/5.0)*RSENSE)
#define CUR3_5A  (int)(3.5*(1024.0/5.0)*RSENSE)
#define CUR4_0A  (int)(4.0*(1024.0/5.0)*RSENSE)
#define CUR4_5A  (int)(4.5*(1024.0/5.0)*RSENSE)
#define CUR5_0A  (int)(5.0*(1024.0/5.0)*RSENSE)
#define CUR5_5A  (int)(5.5*(1024.0/5.0)*RSENSE)
#define CUR6_0A  (int)(6.0*(1024.0/5.0)*RSENSE)
#define CUR6_5A  (int)(6.5*(1024.0/5.0)*RSENSE)
#define CUR7_0A  (int)(7.0*(1024.0/5.0)*RSENSE)
#define CUR7_5A  (int)(7.5*(1024.0/5.0)*RSENSE)
#define CUR8_0A  (int)(8.0*(1024.0/5.0)*RSENSE)
#define CUR8_5A  (int)(8.5*(1024.0/5.0)*RSENSE)
#define CUR9_0A  (int)(9.0*(1024.0/5.0)*RSENSE)
