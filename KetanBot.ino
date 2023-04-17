/*
Lisul Elvitigala
Coding and Web Design Officer Application
4/5-4/16
*/

#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #1 (M1 and M2)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(48, 1);
Adafruit_StepperMotor *myMotor1 = AFMS.getStepper(48, 2);
const int limitSwitchPin = 2;
const int greenPin = 10;
const int redPin = 9;
int bluePin = A1;

int numberCollector;
byte serialNumber;
const int opticCount = 4;
const int parameterCount = 3;
const int parameterSize = 2;

int drinkMatrix[opticCount][parameterCount] = {};

int prevButtonState = 0;
int currentButtonState = 0;

bool limitSwitchFound = false;
bool drinkRequested = false;

void setup()
{
    Serial.begin(9600); 
    while (!Serial)
        ;
    Serial.println("Program running!");
    if (!AFMS.begin())
    { 
        Serial.println("Could not find Motor Shield. Check wiring.");
        while (1)
            ;
    }
    Serial.println("Motor Shield found.");

    pinMode(limitSwitchPin, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(redPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    pinMode(greenPin, OUTPUT);

    myMotor->setSpeed(600); 
    myMotor1->setSpeed(600);
}

void loop()
{
    if (limitSwitchFound == false) {
        Serial.println("KetanBot does not know the location of the limit switch!")
        setColor(255, 0, 0);
        delay(1000);
        
        Serial.println("KetanBot is looking for the raft...");
        currentButtonState = digitalRead(limitSwitchPin);
        while(currentButtonState == LOW && limitSwitchFound == false) {
            myMotor->step(10, FORWARD, SINGLE);
            currentButtonState = digitalRead(buttonPin);
        }
        limitSwitchFound = true;

        Serial.println("KetanBot has found the raft!");
        myMotor.release();
        setColor(0, 255, 0);
        delay(500);
    }
}