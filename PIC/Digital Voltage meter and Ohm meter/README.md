# Digital Voltage meter and Ohm meter
This project creates two different meters, a voltage meter and an ohm meter.

For the voltage meter, a potentiometer is connected to pin AN0. The program will convert the analog readings from this pin to a voltage and output it to a dual 7-segment display. The output will also be displayed to TeraTerm for verification and more precise readings.

For the ohm meter, resistors of unknown values are connected to a reference resistor. The program measures the voltage at AN3 and uses KVL/KCL laws to compute the value of the unknown resistor. This resistor value is displayed in Kohms on a dual 7-segment display and also to Teraterm. Two RBG LEDs will also change colors to reflect the range of the value of the unknown resistor. Finally, a buzzer will activate if the unknown resistor value is below 70 ohms.

## License

MIT License

Copyright (c) 2023 Caden Nihart

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
