#include "Single7SegmentDisplay.h"

Single7SegmentDisplay dsp7((PinsViaShift){ 8, 9, 10, NO_PIN, NO_PIN });
//Single7SegmentDisplay dsp7((PinsDirect){ 3,4,5,6,7,8,9,10 });

byte counter = 0;

void setup() {
  // we constructed our display controller
  // and we set the value of our play counter
}

#define CycleTime 300

void loop() {
  delay(CycleTime);
  dsp7.displayHex(counter++);
  counter &= 0xF;
  delay(CycleTime);
  dsp7.displayRaw(dsp7.hyphen);
}

