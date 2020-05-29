# Arduino libraries

Work was begun in late May 2020 with an Elegoo Uno R3 starter kit.

Go to [Arduino's website](http://arduino.cc/en/Guide/Libraries) to learn about what's special about implementing libraries. (Hint: Hello, C++!!)

## Libraries

- [Single7SegmentDisplay](Single7SegmentDisplay/README.md) - Control a single 7 segment LED display (with decimal point!) by direct pinout or through a 74HC595 shift register which will hold the value for you as you do other things with your pins.

## Conventions

Look for the sketch subdirectory in each library directory. It will usually contain an example sketch which demonstrates use of the library. The wiring diagram can often be found as the .fzz file therein.

We share the .vscode configuration of our editor environment via symlinks. This helps a lot with getting symbols resolved.

We are liking the approach of using defined structures to configure pin connections used. Overloaded constructors neatly handle multiple approaches to the library's purpose.

