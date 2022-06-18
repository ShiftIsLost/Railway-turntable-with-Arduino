# Railway turntable with Arduino

This is a simple Arduino project made for home hobbyist. It's a Arduino Nano (will also work with most other Arduinos) connected to a stepper driver which drives a stepper moter. There is also an analog keyboard for which is used to remember stepper positions and 2 digital buttons for manual driving and setting stepper motor positions.

## Components

The project contains the next list of components:

- Arduino Nano  
- Analog keypad 3x4 
  - 12x buttons
  - 3x 1.5k Ohm resistor
  - 1x 4.7k Ohm resistor
  - 1x 2.2k Ohm resistor
  - 1x 10k Ohm resistor
- Limit switch (KW12)
- 2x buttons
- 2x 10k Ohm resistor
- Stepper motor driver (A4988)
- Stepper motor (ST4118S0706-A)

- Wires
- Breadboard

## Circuit

![circuit](https://user-images.githubusercontent.com/76057973/174337352-54a4f0b8-b6a3-4f97-b7cd-17a0448065a3.png)

## Arduino libraries

Libraries used in this project:
- AccelStepper.h
- ezAnalogKeypad.h
- EEPROM.h

## How to use

Before loading the program u will need to calibrate the analog keypad values(you can do that with this example https://github.com/ArduinoGetStarted/Analog-Keypad/blob/main/examples/Calibration/Calibration.ino).
To move left or right press one of the digital buttons. To save the possition to one of the analog buttons press the left and right button at once then the desired keypad button. 
