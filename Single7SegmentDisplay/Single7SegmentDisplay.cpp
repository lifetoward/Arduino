#include "Arduino.h"
#include "Single7SegmentDisplay.h"

#define self Single7SegmentDisplay
#define SetPin(which,how) digitalWrite(this->pins.which, how)
#define InitPin(which,val) pinMode(this->pins.which, OUTPUT); SetPin(which, val)

self::self( PinsViaShift pinAssign )
{
  this->mode = ViaShift;
  this->pins.s = pinAssign;

  InitPin(s.SerialOut, LOW);
  InitPin(s.ShiftTrigger, LOW);
  InitPin(s.Latch, LOW);
  if (pins.s.ClearShift != NO_PIN) {
    InitPin(s.ClearShift, HIGH); // pull high to clear
    SetPin(s.ClearShift, LOW);   // resume
  }
  if (pins.s.DisableOutput != NO_PIN) {
    InitPin(s.DisableOutput, LOW);  // disable
    SetPin(s.DisableOutput, HIGH);  // re-enable
  }
}

self::self( PinsDirect pinAssign )
{
  this->mode = Direct;
  this->pins.d = pinAssign;
  for (byte x = 0; x < 8; x++) {
    InitPin(b[x], LOW);
  }
}

#define ShiftTriggerDelay 50
#define LatchDelay 50

void self::displayRaw( byte layout )
{
  if (this->mode == ViaShift) {
    // ensure we're "off the record"
    SetPin(s.Latch, LOW);
    
    // shift in the entire byte of content
    for (byte x = 0; x < 8; x++) {
      SetPin(s.SerialOut, bitRead(layout, x) ? HIGH : LOW);
      SetPin(s.ShiftTrigger, HIGH);
      delay(ShiftTriggerDelay);
      SetPin(s.ShiftTrigger, LOW);
    }

    // Shake the latch to put it on the record
    SetPin(s.Latch, HIGH);
    delay(LatchDelay);
    SetPin(s.Latch, LOW);

  } else if (this->mode == Direct) {

  }
}

byte self::displayHex( byte digit, bool decPt = false ) 
{  
    byte layout = hexDigits[digit] | (decPt ? 1 : 0);
    displayRaw( layout );
    return layout;
} 

const byte self::hexDigits[] = {
  0b11111100, 0b01100000, 0b11011010, 0b11110010, // 0, 1, 2, 3
  0b01100110, 0b10110110, 0b10111110, 0b11100000, // 4, 5, 6, 7
  0b11111110, 0b11110110, 0b11101110, 0b00111110, // 8, 9, A, b
  0b10011100, 0b01111010, 0b10011110, 0b10001110, // C, d, E, F    
};

#undef self
