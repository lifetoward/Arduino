/*
 * Controller for a single 7-segment LED display.
 * 
 * Consult the README (./README.md) for how to use this library.
 */
#ifndef Single7SegmentDisplay_h
#include "Arduino.h"

#define NO_PIN 0xFF

/**
 * Pins* structures contain pin identifiers on the MCU which will
 * be used for digital output to control the 7 segment display.
 * For example, if in Direct mode you connect your Uno's pin 10 to 
 * the top segment anode on the display via a resistor, then provide
 * 10 as the value of A in the PinsDirect structure along with 
 * all the other pin specifications. Then pass that structure to the
 * Single7SegmentDisplay constructor to configure this driver.
 * 
 * See README.md for more details.
 */

struct PinsViaShift {
  byte  
    Data,     // to Pin 14 on the 74HC595 
    Shift,    // to Pin 11 on the 74HC595
    Latch,    // to Pin 12 on the 74HC595
    Clear,    // to Pin 10 (optional, use NO_PIN if not connected)
    Disable;  // to Pin 13 (optional, use NO_PIN if not connected)
};

struct PinsDirect {
  // Connections to the 7 seg display, i.e. via 220ohm resistors.
  byte A, B, C, D, E, F, G, P;
  // Connecting P is optional; use NO_PIN if not connected
};

class Single7SegmentDisplay 
{
  public:

    Single7SegmentDisplay( PinsViaShift pinAssign );

    Single7SegmentDisplay( PinsDirect pinAssign );

    void displayRaw( byte layout );

    byte displayHex( byte digit, bool decPt = false );

    void enableOutput( bool setting = true );

    const static byte point, hyphen, on, off, hexDigits[];

  protected:

    enum Mode { Direct, ViaShift } mode;
    union Pins {
      PinsDirect    d;
      PinsViaShift  s;
      byte          b[8]; // for programmatic access for Direct mode
    } pins;

};

#define Single7SegmentDisplay_h
#endif