# KetanBot Drink Dispenser
This program controls the KetanBot Drink Dispenser, which uses stepper motors to dispense various drinks. The program is written in C++ and utilizes the Adafruit Motor Shield library to control the stepper motors. The dispenser has four optic sensors, each connected to a specific drink. The user inputs the desired amount of each drink, and the dispenser uses the stepper motors to pour the appropriate amount.

Getting Started
To use the KetanBot Drink Dispenser, you will need:

An Arduino board (such as the Uno)
The Adafruit Motor Shield
Four optic sensors
Four stepper motors
Once you have all the necessary hardware, you can upload the program to your Arduino board and wire everything up according to the instructions.

Usage
The program will start by looking for the location of the limit switch. Once it finds the limit switch, it will wait for user input. The user will input the desired amount of each drink through the serial monitor. Once the program receives the input, it will dispense the drinks and reset the dispenser.

Contributing
If you find any issues or have any suggestions for improving the program, feel free to open an issue or submit a pull request.

Credits
This program was created by Lisul Elvitigala as part of an application for the Coding and Web Design Officer position. It is based on the Adafruit Motor Shield library and was developed during the period of 4/5-4/16.
