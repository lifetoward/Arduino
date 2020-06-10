# Single7SegmentDisplay

### Control a single 7 segment LED display (with decimal point) 
---

We provide two modes by which to control the display and they are wired very differently.

The first option, `Direct`, assigns a digital output pin to each of the LEDs in the display. `Direct` is better if you don't have a shift register IC, or just want to simplify the wiring of the project or take more direct control of the LEDs on the display.

The second option called `ViaShift` uses a 74HC595 shift register IC to set the LEDs in the display. `ViaShift` requires the use of fewer pins on your MCU and has the advantage of adding a storage location for the display's pattern which is independent of the pins on your MCU. 


## Wiring 

The [7 segment display](https://en.wikipedia.org/wiki/Seven-segment_display) we're using ([UA5621-11-R](https://www.jameco.com/z/UC5621-11-R-LED-Display-7-Segment-Green-0-56-Inch-Common-Cathode-RHDP-2-9mcd_334862.html)) has a common cathode and a pin for each LED anode. It does not include any resistors, so at 5V on the MCU's output pins, each LED's anode should be connected via a [220 ohm resistor](https://www.jameco.com/z/CF1-4W221JRC-Carbon-Film-Resistor-220-Ohm-1-4-Watt-5-_690700.html). If you don't put resistors on each input separately, the current and therefore brightness of the LEDs will vary depending on how many are lit concurrently. It's a very simple device, really just a physical arrangement of 8 shaped LEDs.

To wire the display in `Direct` mode, just connect a digital output pin on your MCU to each of the LED input pins on the display via 220 ohm resistors to get the current flow right. The display's common anode pin should be connected to ground. Control pins on your MCU will be set HIGH (5v) to turn on the individual LED elements. This library takes care of that for you, so all you need to worry about is passing it an appropriate display pattern

See `sketch/ViaShift.fzz` for a Fritzing diagram of the `ViaShift` configuration. The shift register chip we use is the [74HC595](https://www.jameco.com/z/74HC595-Major-Brands-IC-74HC595-8-Bit-Shift-Register-Output-Latches-and-Eight-3-State-Outputs_46105.html).

For a quicker wire-up, consider using an 8-resistor network chip like the [4116R-1-221](https://www.jameco.com/webapp/wcs/stores/servlet/ProductDisplay?storeId=10001&langId=-1&catalogId=10001&pa=108564&productId=108564).

## Programming

As in the pattern for most Arduino libraries, you'll include the header file (`<Single7SegmentDisplay.h>`) for the library and construct a controller object of class `Single7SegmentDisplay` on which you'll invoke the methods to display digits or other arbitrary patterns on the display.

You'll pass the contents of one of two structures to the constructor. Use `PinsViaShift` for configuring the pins connected to a 74HC595, i.e. in `ViaShift` mode. Use `PinsDirect` for configuring the pins connected to the pins on the 7 segment LED display itself, i.e. in `Direct` mode.

Here's the snippet from the header file which defines the pin configuration structures.

```cpp
#define NO_PIN 0xFF

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
```

Here's an example of the configuration/declaration of a controller object used in `ViaShift` mode:

`Single7SegmentDisplay dsp7((PinsViaShift){ 8, 9, 10, NO_PIN, NO_PIN });`

For any pin which is not connected, use the `NO_PIN` macro instead of a pin identifier. This is only relevant for the optional members of the `PinsViaShift` structure or for the `P` member of the `PinsDirect` structure.

Once you have the controller object (as `dsp7` in the example above), here's an example of how you'd call the methods:

`dsp7.displayHex(14);`

This would place an "E" on the display.


## Methods

### displayHex( unsigned value )

The value must be less than 0x10, i.e. represented with a single hexadecimal digit. 

To help clarify the difference between alphabetic and numeric representations, we add the decimal point to the alphabetic representations and exclude it from the numerals. This may help `b` appear distinct from `B` and from `8`, as well as `d` from `D` and from `0`.

### displayRaw( byte pattern )

Patterns are specified in MSBFIRST order, mapping to display segments A - G + P as represented in [this diagram](https://upload.wikimedia.org/wikipedia/commons/thumb/e/ed/7_Segment_Display_with_Labeled_Segments.svg/150px-7_Segment_Display_with_Labeled_Segments.svg.png). Several useful patterns are provided as static members of the class. They include:
- hyphen
- off
- on
- point

Here are a couple of example patterns to demonstrate how the bits map to the display:
- `0b10000000` - Displays only the top segment.
- `0b00111010` - Displays a square on the bottom half.
- `0b00000001` - Displays only the decimal point.

### enableOutput( [ boolean(true) ] )

This method only works with the `ViaShift` mode because it makes use of a capability on the shift register chip which stores the LED light status outputs on its 8 output pins. It also requires that you wire and configure the `DisableOutput` pin, as that's the only means we have to control this behavior on the shift register chip.

You can simply enable or disable all elements of the display with this method. Pass `true` (or nothing) to enable the display, and pass `false` to disable it. Importantly, the value of the pattern remains stored in the output register even as the output is disabled. This makes it different than simply sending an 0 pattern to the device.

Output is briefly disabled and then re-enabled during initialization (assuming the pin is configured) using this same technique.

## History and Context

Controlling a 7-segment display is not a particularly difficult thing to accomplish, but this project was more about learning some conventions for designing and building Arduino libraries than about the practical application. If you're interested in this project's less obvious purposes, read on.

We've explored and tried to achieve some exemplary models for everything from the git repository model to the conventions of assigning pins, to the structure of README files like this one. We've documented these findings and ideas in the [parent of this directory](../) in the repo. Even though it's simple in function, it is still a useful little library, for code reference if not for use with applications of the 7 segment display.

We don't use the IDE, and prefer a well configured CLI instead. 
---

