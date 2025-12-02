# Smart Piggy Bank

## Problem Statement

Tracking and saving coins can be more fun and interactive when combined with smart features.  
The goal of this project is to create a **Smart Piggy Bank** that automatically counts coins when they are dropped and controls an automatic lid using a servo motor.

## Design

- **Light Sensor (LDR)**  
  The LDR detects changes in light levels when a coin passes by.  
  A large drop in light intensity indicates that a coin has been inserted.  
  The Arduino reads the values through the analog pin and detects this change.

- **Servo Motor**  
  The servo automatically opens and closes the piggy bank lid.  
  The lid opens briefly when a coin is detected, allowing the coin to pass through, then closes again.

- **LCD 16x2 (Non-I2C)**  
  The LCD displays the total number of coins saved.  
  It is connected directly using multiple digital pins on the Arduino (RS=12, E=11, D4=5, D5=4, D6=3, D7=2).

- **EEPROM Memory**  
  The Arduino stores the total number of coins in EEPROM memory.  
  The stored value is loaded when the device restarts, ensuring your savings aren’t lost after power-off.

- **Calibration**  
  The system calibrates the light sensor at startup to ensure accurate coin detection under current lighting conditions.

## Bill of Materials

- Arduino Uno R3  
- LDR Sensor  
- 16x2 LCD Display (Non-I2C)  
- Servo Motor  
- 10kΩ Resistor (for LDR voltage divider)  
- 220Ω Resistor (for LCD backlight)  
- Breadboard  
- Wires  

## Schematics

See schematics diagram below (based on shown setup):  
![Schematic](docs/shematic.png)

## Setup and Usage Guide

1. **Connect hardware** according to the schematic.  
2. **Upload the given Arduino code** to your Uno board.  
3. Place the following components on the workspace:  
   - Arduino Uno R3  
   - LDR Sensor  
   - 16x2 LCD Display (non-I2C)  
   - 10kΩ Resistor (for LDR)  
   - 220Ω Resistor (for LCD backlight)  
   - Servo Motor  
   - Breadboard and wires  
4. Connect all components based on the provided schematic (`docs/schematics.png`).  
5. Copy and paste the Arduino `.ino` code into the Tinkercad or Arduino IDE editor.  
6. Start the simulation or power up the device.  
7. Drop coins through the slot — the lid opens and closes automatically.  
8. Track the total number of coins saved on the LCD display.

## What Worked

- The LDR successfully detected coin drops through light changes.  
- Servo lid control worked smoothly for opening and closing.  
- LCD correctly displayed the total coin count.  
- EEPROM properly stored and restored the number of saved coins after power reset.  

## What Didn’t

- The first version used two separate strings for opening and closing the lid, which was too complex to manage mechanically.  
  The single-servo setup worked better and was simpler to control.  

## Future Improvements

- Add a **reset button** to clear the total stored coin count.  
- Add **different denominations detection** using sensors or weight measurement for more accurate tracking.
