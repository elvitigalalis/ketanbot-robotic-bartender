#include <Adafruit_MotorShield.h>

/*
Lisul Elvitigala
Coding and Web Design Officer Application
4/5-4/16
*/

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

int numberGroup;
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
  if (limitSwitchFound == false)
  {
    Serial.println("KetanBot does not know the location of the limit switch!");
    setColor(255, 0, 0);
    delay(1000);

    Serial.println("KetanBot is looking for the raft...");
    currentButtonState = digitalRead(limitSwitchPin);
    while (currentButtonState == LOW && limitSwitchFound == false)
    {
      myMotor->step(10, BACKWARD, SINGLE);
      currentButtonState = digitalRead(limitSwitchPin);
    }
    limitSwitchFound = true;

    Serial.println("KetanBot has found the raft!");
    myMotor->release();
    setColor(0, 255, 0);
    delay(500);
  }

  // Check if a drink has been requested
  if (drinkRequested)
  {
    // Loop through each optic
    for (int i = 0; i < opticCount; i++)
    {
      // Move the X-axis motor to the appropriate position
      myMotor->step(drinkMatrix[i][0] * 10, FORWARD, SINGLE);
      myMotor->release();

      // Move the Y-axis motors to pour the appropriate amount of drink
      while (drinkMatrix[i][2] > 0 && limitSwitchFound)
      {
        delay(500);
        // Move a second motor to position the glass
        myMotor1->step(1825, FORWARD, DOUBLE);
        delay((drinkMatrix[i][1]) * 100);
        myMotor1->step(1825, BACKWARD, DOUBLE);
        myMotor1->release();
        drinkMatrix[i][2]--;
        delay(500);
      }
    }

    // Indicate that the drink is ready and reset the machine
    Serial.println("KetanBot has prepared your drink!");
    Serial.println("Enjoy!!!");
    setColor(0, 0, 255);
    drinkRequested = false;
    limitSwitchFound = false;

    // Wait for new drink instructions
    while (drinkRequested == false)
    {
      if (Serial.available())
      {
        // Parse input from user to determine drink instructions
        for (int i = 0; i < opticCount; i++)
        {
          for (int j = 0; j < parameterCount; j++)
          {
            for (int k = 0; k < parameterSize; k++)
            {
              if (Serial.available())
              {
                serialNumber = Serial.read();
                serialNumber -= 48;
                numberGroup = numberGroup * 10 + serialNumber;
              }
              else
              {
                delay(250);
                serialNumber = Serial.read();
                serialNumber -= 48;
              }
            }
            drinkMatrix[i][j] = numberGroup;
            numberGroup = 0;
            serialNumber = Serial.read();
          }
        }
        // Print the current drink instructions
        serialPrintArray();
        Serial.println("KetanBot has finished inputting!");
        drinkRequested = true;
      }
    }
  }
}

// Print out the current drink instructions
void serialPrintArray()
{
  for (int i = 0; i < opticCount; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      Serial.print(drinkMatrix[i][j]);
      Serial.print(", ");
    }
    Serial.println();
  }
}

// Set the LED color
void setColor(int red, int green, int blue)
{
#ifdef COMMON_ANODE
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
#endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}