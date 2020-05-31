# Arduino libraries

Work was begun in late May 2020 with an Elegoo Uno R3 starter kit.

Go to [Arduino's CLI website](https://arduino.github.io/arduino-cli/latest/) to learn about what's special about building Arduino code and implementing libraries. (Hint: Hello, C++!!) 

Note that we do not yet conform with the specification of how to submit a library to the registry, but it's close in the important ways, and maybe better than even their guidance in some ways. For now we just put additional source files, structured as would be needed for submission as a library, into the sketch directory. It builds fine this way. Making the library suitable for registry means tweaking the directory structure, adding some metadata, and more [as described here](https://arduino.github.io/arduino-cli/latest/library-specification/)

## Libraries (as sketches for now)

- [Single7SegmentDisplay](Single7SegmentDisplay/) - Control a single 7 segment LED display (with decimal point!) by direct pinout or through a 74HC595 shift register which will hold the value for you as you do other things with your pins.

## Conventions

We are liking the approach of using defined structures to configure pin connections used. Overloaded constructors neatly handle multiple approaches to the library's purpose. This model is super easy to consume for inexperienced programmers. Constructing the controller while passing in the configuration data is about as easy as it gets. 