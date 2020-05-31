/*
 * Controller for a single 7-segment LED display.
 * 
 * Consult the README (./README.md) for how to use this library.
 */
#ifndef Single7SegmentDisplay_h
#include "Arduino.h"

#define NO_PIN 0xFF

struct PinsViaShift {
  byte              // Connections to 74HC595
    SerialOut,      // Pin 14 
    Shift,          // Pin 11
    Latch,          // Pin 12
    ClearShift,     // Pin 10 (optional, use NO_PIN if not connected)
    DisableOutput;  // Pin 13 (optional, use NO_PIN if not connected)
};

struct PinsDirect {
  // Connections to the 7 seg display, i.e. via 220ohm resistors.
  byte A, B, C, D, E, F, G, P;
};

class Single7SegmentDisplay 
{
  public:

    Single7SegmentDisplay( PinsViaShift pinAssign );

    Single7SegmentDisplay( PinsDirect pinAssign );

    void displayRaw( byte layout );

    byte displayHex( byte digit, bool decPt = false );

    void enableOutput( bool setting );

    const static byte point, hyphen, on, off, hexDigits[];

  protected:

    enum Mode { Direct, ViaShift } mode;
    union Pins {
      PinsDirect    d;
      byte          b[8]; // for simple initialization of Direct mode
      PinsViaShift  s;
    } pins;

};

#define Single7SegmentDisplay_h
#endif