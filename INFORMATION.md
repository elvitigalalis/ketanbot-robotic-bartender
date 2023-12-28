# KetanBot - Robotic Bartender
KetanBot is a robotic bartender powered by an Adafruit Motor Shield and an Arduino microcontroller. It can mix and pour drinks automatically based on input received through serial communication. In this guide, we will go over the hardware and software requirements, as well as the installation and usage instructions.

## Hardware Requirements
- Arduino Uno or compatible board
- Adafruit Motor Shield v2
- Stepper motors (2)
- Limit switch
- RGB LED
- Various wires and breadboard
- 8mm Steel Rod
- Linear Bearings
- Timing Belt and Pulley (2m or 5m version)
- Contact Switch

## Software Requirements
- Adafruit Motor Shield library
- Arduino IDE

## Installation
  1) Install the Adafruit Motor Shield library in the Arduino IDE by going to Sketch > Include Library > Manage Libraries and searching for "Adafruit Motor Shield".
  2) Connect the hardware components as shown in the wiring diagram. The 8mm steel rod and linear bearings should be used to create a linear actuator for the pouring mechanism.
  3) Upload the KetanBot.ino sketch to the Arduino board using the Arduino IDE.

## Usage
  1) Connect the Arduino board to a computer via USB.
  2) Open the Serial Monitor in the Arduino IDE.
  3) Input drink instructions in the following format: XX YY ZZ, where XX is the number of steps for the X-axis motor, YY is the time to pour the drink in milliseconds, and ZZ is the number of pours.
  4) Press Enter to send the drink instructions to KetanBot.
  5) KetanBot will automatically mix and pour the drink.
  6) When KetanBot is finished, the RGB LED will turn blue and a message will be displayed in the Serial Monitor.

## Code Explanation
The KetanBot.ino sketch uses the Adafruit Motor Shield library to control the stepper motors and limit switch. The stepper motors are used to control the X and Y axes of the pouring mechanism, while the limit switch is used to detect when the mechanism has reached its starting position.

The code uses serial communication to receive input from the user in the format mentioned above. Once the input is received, the appropriate stepper motors are moved the specified number of steps to position the pouring mechanism over the appropriate container. The motor is then run for the specified time to pour the drink, and the process is repeated for the specified number of pours.

Once the pouring process is complete, the RGB LED is turned blue and a message is sent to the Serial Monitor.

## Contributors
Lisul Elvitigala

## License
This project is licensed under the MIT License. See the LICENSE file for more information.
