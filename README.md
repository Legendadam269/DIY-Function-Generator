# DIY-Function-Generator
This project is a function generator system built using an AD9833 programmable waveform generator, an Arduino Nano, and a TL071 op-amp output stage.
The system generates sine, square, and triangle waveforms with adjustable frequency. A
rotary encoder is used for user input, allowing the frequency and waveform type to be modified
in real time. A 16×2 I2C LCD display shows the selected waveform and current frequency.
The circuit includes a dual ±12V power supply and a regulated +5V output using LM7812,
LM7912, and LM7805 regulators to power the op-amp, Arduino, and display. The TL071
op-amp amplifies and conditions the AD9833 output before it is sent to a BNC connector for
external use.
Overall, this design produces a compact, user-controlled digital function generator suitable for
lab use, testing circuits, and signal analysis.
