# Final Project

## Code

### Setup Arduino

- Download and open the Arduino IDE ([Download](https://www.arduino.cc/en/software))
- Open Preferences 
- Copy and paste the following link ([https://dl.espressif.com/dl/package_esp32_index.json](https://dl.espressif.com/dl/package_esp32_index.json)) into `Additonal Boards Manager URLs` to add the ESP package
- Select `Tools > Boards > Boards Manager`, then search for `esp32` and install the most recent version
- Select `Tools > Boards > ESP32 Arduino > TTGO T1`
- Select `Tools > Manage Libraries`, then search for `TFT_eSPI` and install the most recent version
- In your file storage system, find the Arduino folder
- Open `Arduino/libraries/TFT_eSPI/User_Setup_Select.h`
- Comment out the line that says `#include <User_Setup.h>`
- Uncomment the line that says `#include <User_Setups/Setup25_TTGO_T_Display.h>` 
### Upload Device Code
- Open the Arduino IDE
- Open `cesfinalproj.ino` from the Arduino IDE
- Plug in the ESP32
- Select `Sketch > Upload`
---
## Component Wiring
### Servo Motor
- Connect the orange wire (first wire) to `GPIO Pin #13`slot on breadboard
- Connect the red wire (second wire) to the 5V slot on breadboard
- Connect the brown wire (third wire) to a ground slot on breadboard
### Stepper Motor
- Connect IN1 to `GPIO Pin #15` slot on breadboard
- Connect IN2 to `GPIO Pin #27` slot on breadboard
- Connect IN3 to `GPIO Pin #26` slot on breadboard
- Connect IN4 to `GPIO Pin #25` slot on breadboard
On the side with 2 pins
- Connect (-) pin to the ground slot on breadboard
- Connect (+) pin to the 5V slot on breadboard
### Motion Sensor
With the motion sensor oriented downward we the pins are at the bottom
- Connect leftmost pin to 5V slot on breadboard
- Connect middle pin to `GPIO Pin #17` slot on breadboard
- Connect rightmost pin to ground slot on breadboard
### LED Strip
- Connect the red wire (first wire) to  the 5V slot on breadboard
- Connect the green wire (second wire) to `GPIO Pin #2` slot on breadboard
- Connect the white wire (third wire) to a ground slot on breadboard
### Potentiometer
Using image at bottom:
- Connect the pin `1` to 3V slot on breadboard
- Connect the pin `2` to `GPIO Pin #12`slot on breadboard
- Connect the pin `3` to ground slot on breadboard
---
### Build Enclosure
- Use .svg files to build up enclosures
- Note: Due to issues with software one file contains the laser cutting information for the front cloosure, the second has a slot for the window side and the third has a slot of the motion sensor
-- Using the certain software such as Adobe Illustrator will allow you copy and paste these components into one svg file if preferred
- remove joystick slot (bigger circle next to smaller circle)
- remove ESP display slot (rectangle next to small circle)
  Suggestions:
    - For easy detachment, glue all the sides of the box piece except the top and back side(or just the top) and press the side(s) on
---
### Modifying front and bottom enclosure
- On the side that aligns with the LED strips, use the dremel to smooth out 6 or 7 of the teeth on both the front and bottom piece of enclosure
---
### LED strip usage
- Wrap LED strip through first slot and wrap through second and third then wrap the remainder through the slots horizontally
---
### Component assembly
- Use hot glue and electric tape to hold pieces in place, however you deem fit.
---
### Decorative Components
- Cotton balls to cover LED strip slots
- Use 3D sun and cylinder to hot glue on top of the stepper motor
---
### Resources:
- https://cults3d.com/en/3d-model/various/geometric-figures-3d
- https://cults3d.com/en/3d-model/tool/baphomet-v3
- https://www.thingiverse.com/thing:4725461
---
Youtube link:https://www.youtube.com/watch?v=IFtez64X5I4

 
