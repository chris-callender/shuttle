void analogWriteVarF(byte pin, byte percent)
{
    unsigned int value;
    value = ((unsigned long)ICR1 * (unsigned long)percent) / 99UL;
    
    
    switch (pin) {
        case 9:
            OCR1A = value;
            break;
        case 10:
            OCR1B = value;
            break;
        default:
            // no other pin will work
            break;
    }
}

void set_freq(unsigned int freq, unsigned int ps)
{
  unsigned int val;
  val = (unsigned int)(16000000UL/((unsigned long)freq*(unsigned long)ps));
  ICR1 = val-1;
  Serial.print("PWM freq:");
  Serial.println(freq);
  
}

void RunMotor(bool direction, byte speed)
{ 
  static byte TCCR1Ashadow = _BV(COM1A1) | _BV(WGM11);
  static bool old_dir=true;
  static bool init=false;

  //traceRunMotor(direction,speed);
   
  if (old_dir!=direction || !init) // To avoid glitch if direction doesn't change as this will switch all MOSFETS off
  {
    init=true;
    // First everything off, carefully
    analogWriteVarF(9, 0); // Speed 0 FWD
    analogWriteVarF(10, 0);// Speed 0 FWD
    delay(50); // 50ms delay for safety

        digitalWrite(9,LOW); // OC1A = fwd PWM
        digitalWrite(10,LOW); // OC1B = rev PWM
        digitalWrite(11,HIGH); 
        digitalWrite(12,HIGH);
     
        TCCR1A = _BV(WGM11); 

        if (direction) 
          { 
            TCCR1Ashadow = _BV(COM1A1) | _BV(WGM11);
            digitalWrite(11,LOW); digitalWrite(12,HIGH);
          }
          else
          {
            TCCR1Ashadow = _BV(COM1B1)  | _BV(WGM11);
            digitalWrite(11,HIGH); digitalWrite(12,LOW);
          }
          old_dir=direction;
          TCCR1A = _BV(WGM11);
          //analogWriteVarF(9, 0);
          //analogWriteVarF(10, 0);
  } else
    {
    if (speed==0) TCCR1A = _BV(WGM11); else 
      {
      TCCR1A = TCCR1Ashadow;
      analogWriteVarF(9, speed);
      analogWriteVarF(10, speed);
      }
    }
}



void pwmSetup()
{
 
    // Configure Timer 1 for PWM
  // Output is on OC1A (FWD) to begin with
  // Mode is 14 (fast PWM with TOP in ICR1)
  // Prescaler is 8 
  // (giving maxfreq ~= 16000000/(50*8) = 40kHz (2% resolution in speed setting)
  // Min freq = 16000000/(65536*8) = 30Hz (16 bit ICR1)

    TCCR1A = 0;           // undo the configuration done by...
    TCCR1B = 0;           // ...the Arduino core library
    TCNT1  = 0;           // reset timer
    TCCR1A = _BV(COM1A1)  // non-inverted PWM on ch. A, fwd by default
           | _BV(WGM11);  // mode 14: fast PWM, TOP = ICR1
    TCCR1B = _BV(WGM13)   // ditto
     | _BV(WGM12)
           | _BV(CS11);   // prescaler = 8
    set_freq(4000,8); //8 kHz PWM with prescaler = 8 gives ICR1=124 (clk=8e6 /(ps=8 * frq=8000))-1

    // Set the PWM pins as output.
    pinMode( 9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode( 11, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
    
    RunMotor(false,0);
}
