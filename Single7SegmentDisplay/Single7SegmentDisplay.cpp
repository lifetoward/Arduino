#include "Arduino.h"
#include "Single7SegmentDisplay.h"

#define self Single7SegmentDisplay
#define SetPin(which,how) digitalWrite(this->pins.which, how)
#define InitPin(which,val) pinMode(this->pins.which, OUTPUT); SetPin(which, val)
#define PulseWidth 0 // can ensure that a Pulse is not so short as to be missed
#define PulseUp(which) SetPin(which, HIGH); delay(PulseWidth); SetPin(which, LOW)

self::self( PinsViaShift pinAssign )
{
  this->mode = ViaShift;
  this->pins.s = pinAssign;

  InitPin(s.SerialOut, LOW);
  InitPin(s.Shift, LOW);
  InitPin(s.Latch, LOW);
  if (pins.s.ClearShift != NO_PIN) {
    InitPin(s.ClearShift, HIGH); // pull high to clear
    SetPin(s.ClearShift, LOW);   // resume
  }
  if (pins.s.DisableOutput != NO_PIN) {
    InitPin(s.DisableOutput, LOW);  // disable
    SetPin(s.DisableOutput, HIGH);  // re-enable
  }
  this->displayRaw(this->on);
}

self::self( PinsDirect pinAssign )
{
  this->mode = Direct;
  this->pins.d = pinAssign;
  for (byte x = 0; x < 8; x++) {
    InitPin(b[x], HIGH);
  }
}

void self::displayRaw( byte layout )
{
  byte x; // a simple index for loops

  if (this->mode == ViaShift) {
    // ensure we're "off the record"
    SetPin(s.Latch, LOW);
    
    // shift in the entire byte of content
    for (x = 0; x < 8; x++) {
      SetPin(s.SerialOut, bitRead(layout, x) ? HIGH : LOW);
      PulseUp(s.Shift);
    }

    // Shake the latch to put it on the record
    PulseUp(s.Latch);

  } else if (this->mode == Direct) {

    for (x = 0; x < 8; x++) {
      SetPin(b[x], bitRead(layout, 7-x) ? HIGH : LOW);
    }
  }
}

byte self::displayHex( byte digit, bool decPt = false ) 
{  
  byte layout = hexDigits[digit] | (decPt ? 1 : 0);
  displayRaw( layout );
  return layout;
} 

void self::enableOutput( bool setting = true )
{
  if (this->mode != ViaShift || this->pins.s.DisableOutput == NO_PIN)
    return;
  SetPin(s.DisableOutput, setting ? LOW : HIGH);
}

const byte
  self::hexDigits[] = {
    0b11111100, 0b01100000, 0b11011010, 0b11110010, // 0, 1, 2, 3
    0b01100110, 0b10110110, 0b10111110, 0b11100000, // 4, 5, 6, 7
    0b11111110, 0b11110110, 0b11101111, 0b00111111, // 8, 9, A, b
    0b10011101, 0b01111011, 0b10011111, 0b10001111, // C, d, E, F    
  }, 
  self::point = 0b00000001,
  self::hyphen = 0b00000010,
  self::on = 0b11111111,
  self::off = 0b00000000;

#undef self
