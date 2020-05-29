/*
 *
 */
#ifndef Single7SegmentDisplay_h
#include "Arduino.h"

#define NO_PIN 0xFF

struct PinsViaShift {
  byte              // Connection to 74HC595
    SerialOut,      // Pin 14 
    ShiftTrigger,   // Pin 11
    Latch,          // Pin 12
    ClearShift,     // Pin 10 (optional, use NO_PIN if not connected)
    DisableOutput;  // Pin 13 (optional, use NO_PIN if not connected)
};

struct PinsDirect {
  // Connections via 220-Ohm resistors to the 7 seg display.
  byte A, B, C, D, E, F, G, P;
};

#define self Single7SegmentDisplay

class Single7SegmentDisplay 
{
  public:

    self( PinsViaShift pinAssign );

    self( PinsDirect pinAssign );

    void displayRaw( byte layout );

    byte displayHex( byte digit, bool decPt );

    const static byte 
      point = 0b00000001,
      minus = 0b00000010,
      allOn = 0b11111111,
      allOff = 0b00000000,
      underscore = 0b00010000,
      hexDigits[];

  protected:

    enum Mode { Direct, ViaShift } mode;
    union Pins {
      PinsDirect    d;
      byte          b[8]; // for simple initialization of Direct mode
      PinsViaShift  s;
    } pins;

};

#undef self

#define Single7SegmentDisplay_h
#endif