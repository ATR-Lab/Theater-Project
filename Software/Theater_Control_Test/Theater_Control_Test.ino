
//This is a test program for rev 0.1.1 of Kent State's
//ATR Lab Theater Project Theater Control Board. Runs a basic
//test of all functions of the system (motors, servos,
//joystick,buttons, etc) via a Serial com port.
//For Arduino Mega

//Dan Maher, ATR Lab Research Assistant
//12/08/2021

#include <Wire.h>
#include <Servo.h>
#include <Adafruit_SSD1306.h> //Display
#include "BasicStepperDriver.h"
#include "pinmap.h" //Reference for pin macros

///////////////////////
//Globals
///////////////////////
//These are just the number of selections to pass to ProcessSelection
static int selectionQuantityMain = 5;
static int selectionQuantityServo = 6;
static int selectionQuantityStepper = 4;
static int selectionQuantityGear = 2;
static int selectionQuantityIOMenu = 2;
static int selectionQuantityIO = 10;

int menuSelection = -1; //Holds the current menu selection. Setup so that '0' is quit

//Servos
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

//Steppers
#define MOTOR_STEPS 200
#define MICROSTEPS 1
#define RPM 120
BasicStepperDriver stepper1(MOTOR_STEPS, STEPPER_MOTOR_1_DIR, STEPPER_MOTOR_1_STEP);
BasicStepperDriver stepper2(MOTOR_STEPS, STEPPER_MOTOR_2_DIR, STEPPER_MOTOR_2_STEP);
BasicStepperDriver stepper3(MOTOR_STEPS, STEPPER_MOTOR_3_DIR, STEPPER_MOTOR_3_STEP);
BasicStepperDriver stepper4(MOTOR_STEPS, STEPPER_MOTOR_4_DIR, STEPPER_MOTOR_4_STEP);

//IO Selection Bank/Pin
int selectedBank;
int selectedPin;

//I2C Display
Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  InitializeServos();
  InitializeStepperMotors();
  InitializeGearMotors();
  InitializeControls();
  InitializeDisplay();
  InitializeIO();
  InitializeSerial();
}

void loop() {
  while (menuSelection < 1) {
    DisplayMenu();
    menuSelection = ProcessSelection(selectionQuantityMain);
  }

  //Main Menu Selection
  switch (menuSelection) {
    case 1: //Servo Menu selected
      while (1) {
        DisplayServoMenu();
        menuSelection = ProcessSelection(selectionQuantityServo);
        if (menuSelection == 0)
          break;
        TestServo(menuSelection);
      }
      break;
    case 2:
      while (1) {
        DisplayGearMenu();
        menuSelection = ProcessSelection(selectionQuantityGear);
        if (menuSelection == 0)
          break;
        TestGearMotor(menuSelection);
      }
      break;
    case 3:
      while (1) {
        DisplayStepperMenu();
        menuSelection = ProcessSelection(selectionQuantityStepper);
        if (menuSelection == 0)
          break;
        TestStepperMotor(menuSelection);
      }
      break;
    case 4:
      TestControls();
      break;
    case 5:
      do {
        DisplayIOMenu1();
        selectedBank = ProcessSelection(selectionQuantityIOMenu);
        if (selectedBank == 0)
          break;
        else if (selectedBank == -1)
          continue;
        do {
          DisplayIOMenu2();
          selectedPin = ProcessSelection(selectionQuantityIO);
          if (selectedPin == 0)
            break;
          else if (selectedPin == -1)
            continue;
          TestIO(selectedBank, selectedPin);
        } while (selectedPin != 0);
      } while (selectedBank != 0);
  }

  menuSelection = -1;
}

void DisplayMenu() {
  Serial.print("Please Select Option (1-5");
  Serial.println("):\n----------------------------");
  Serial.println("1.  Servo Tests");
  Serial.println("2.  Gear Motor Tests");
  Serial.println("3.  Stepper Motor Tests");
  Serial.println("4.  Test Controls");
  Serial.println("5.  I/O Banks");
  Serial.println();
}
void DisplayServoMenu() {
  Serial.print("Please Select Option (0-6");
  Serial.println("):\n----------------------------");
  Serial.println("0.  Previous Menu");
  Serial.println("1.  Test Servo 1");
  Serial.println("2.  Test Servo 2");
  Serial.println("3.  Test Servo 3");
  Serial.println("4.  Test Servo 4");
  Serial.println("5.  Test Servo 5");
  Serial.println("6.  Test Servo 6");
  Serial.println();
}
void DisplayGearMenu() {
  Serial.print("Please Select Option (0-2");
  Serial.println("):\n----------------------------");
  Serial.println("0.  Previous Menu");
  Serial.println("1.  Test Gear Motor 1");
  Serial.println("2.  Test Gear Motor 2");
  Serial.println();
}
void DisplayStepperMenu() {
  Serial.print("Please Select Option (0-4");
  Serial.println("):\n----------------------------");
  Serial.println("0.  Previous Menu");
  Serial.println("1.  Test Stepper Motor 1");
  Serial.println("2.  Test Stepper Motor 2");
  Serial.println("3.  Test Stepper Motor 3");
  Serial.println("4.  Test Stepper Motor 4");
  Serial.println();
}

void DisplayIOMenu1() {
  Serial.print("Please Select Option (0-2");
  Serial.println("):\n----------------------------");
  Serial.println("0.  Previous Menu");
  Serial.println("1.  Bank 1");
  Serial.println("2.  Bank 2");
  Serial.println();
}
void DisplayIOMenu2() {
  Serial.print("Please Select Option (0-10");
  Serial.println("):\n----------------------------");
  Serial.println("0.     Previous Menu");
  Serial.println("1-10.  I/O port");
  Serial.println();
}

int ProcessSelection(int selectionQuantity) {
  while (!Serial.available()) {

  }

  int selection = Serial.parseInt();
  if (selection < 0 || selection > selectionQuantity) {
    Serial.print("Invalid selection! Enter a number between 0 and ");
    Serial.println(selectionQuantity);
    return -1;
  } else {
    return selection;
  }
}

void TestServo(int servo) {
  Serial.print("Testing Servo ");
  Serial.print(servo);
  Serial.println("...\n");

  Servo activeServo;
  switch (servo) {
    case 1:
      activeServo = servo1;
      break;
    case 2:
      activeServo = servo2;
      break;
    case 3:
      activeServo = servo3;
      break;
    case 4:
      activeServo = servo4;
      break;
    case 5:
      activeServo = servo5;
      break;
    case 6:
      activeServo = servo6;
      break;
  }

  activeServo.write(180);
  delay(2000);
  activeServo.write(90);

  Serial.println("\nServo Test Complete!\n");
}

void TestGearMotor(int motor) {
  Serial.print("Testing Gear Motor ");
  Serial.print(motor);
  Serial.println("...\n");

  int direction;
  int speed;

  switch (motor) {
    case 1:
      direction = GEAR_MOTOR_1_DIR;
      speed = GEAR_MOTOR_1_SPEED;
      break;
    case 2:
      direction = GEAR_MOTOR_2_DIR;
      speed = GEAR_MOTOR_2_SPEED;
      break;
  }

  Serial.println("Configuring Gear Motor 1 for Forward Rotation...");
  digitalWrite(direction, HIGH);
  delay(100);
  Serial.println("Rotating Gear Motor 1 Forward...");
  analogWrite(speed, 255);
  delay(4000);
  Serial.println("Braking Gear Motor 1...");
  analogWrite(speed, 0);
  delay(100);
  Serial.println("Configuring Gear Motor 1 for Reverse Rotation...");
  digitalWrite(direction, LOW);
  delay(100);
  Serial.println("Rotating Gear Motor 1 in Reverse...");
  analogWrite(speed, 255);
  delay(4000);
  Serial.println("Braking Gear Motor 1...");
  analogWrite(speed, 0);

  Serial.println("\nMotor Test Complete!\n");
}

void TestStepperMotor(int motor) {
  Serial.print("Testing Stepper Motor ");
  Serial.print(motor);
  Serial.println("...\n");

  BasicStepperDriver stepper(MOTOR_STEPS, STEPPER_MOTOR_1_DIR, STEPPER_MOTOR_1_STEP);

  switch (motor) {
    case 1:
      stepper = stepper1;
      break;
    case 2:
      stepper = stepper2;
      break;
    case 3:
      stepper = stepper3;
      break;
    case 4:
      stepper = stepper4;
      break;
  }

  for (int x = 0; x < 5; x++) {
    stepper.rotate(360);
    stepper.move(-MOTOR_STEPS * MICROSTEPS);
    delay(100);
  }

  Serial.println("\nStepper Motor Test Complete!\n");
}

void TestControls() {
  Serial.println("Testing Controls, Enter 'q' to Quit...\n");
  while (Serial.read() != 'q') {
    Serial.print("X: ");
    Serial.print(analogRead(JOYSTICK_X));
    Serial.print("  Y: ");
    int x = analogRead(JOYSTICK_Y);
    delay(100);
    Serial.print(x);
    Serial.print("  SW1: ");
    Serial.print(digitalRead(SW1));
    Serial.print("  SW2: ");
    Serial.print(digitalRead(SW2));
    Serial.print("  SW3: ");
    Serial.print(digitalRead(SW3));
    Serial.print("  SW4: ");
    Serial.print(digitalRead(SW4));
    Serial.print("  SW5: ");
    Serial.print(digitalRead(SW5));
    Serial.print("  SW6: ");
    Serial.print(digitalRead(SW6));
    Serial.print("  SW7: ");
    Serial.println(digitalRead(SW7));
    delay(500);
  }

  Serial.println("\nControls Test Complete!\n");
}

void TestIO(int bank, int pin) {
  Serial.print("Flashing bank ");
  Serial.print(bank);
  Serial.print(" pin ");
  Serial.print(pin);
  Serial.println("...\n");

  switch (bank) {
    case 1:
      switch (pin) {
        case 1:
          pin = BANK_1_PIN_1;
          break;
        case 2:
          pin = BANK_1_PIN_2;
          break;
        case 3:
          pin = BANK_1_PIN_3;
          break;
        case 4:
          pin = BANK_1_PIN_4;
          break;
        case 5:
          pin = BANK_1_PIN_5;
          break;
        case 6:
          pin = BANK_1_PIN_6;
          break;
        case 7:
          pin = BANK_1_PIN_7;
          break;
        case 8:
          pin = BANK_1_PIN_8;
          break;
        case 9:
          pin = BANK_1_PIN_9;
          break;
        case 10:
          pin = BANK_1_PIN_10;
          break;
      }
      break;
    case 2:
      switch (pin) {
        case 1:
          pin = BANK_2_PIN_1;
          break;
        case 2:
          pin = BANK_2_PIN_2;
          break;
        case 3:
          pin = BANK_2_PIN_3;
          break;
        case 4:
          pin = BANK_2_PIN_4;
          break;
        case 5:
          pin = BANK_2_PIN_5;
          break;
        case 6:
          pin = BANK_2_PIN_6;
          break;
        case 7:
          pin = BANK_2_PIN_7;
          break;
        case 8:
          pin = BANK_2_PIN_8;
          break;
        case 9:
          pin = BANK_2_PIN_9;
          break;
        case 10:
          pin = BANK_2_PIN_10;
          break;
      }
      break;
  }

  for (int x = 0; x < 4; x++) {
    digitalWrite(pin, HIGH);
    delay(100);
    digitalWrite(pin, LOW);
    delay(100);
  }

  Serial.println("\nI/O Test Complete!\n");
}


void TestEncoders() {
  Serial.println("Testing Encoders...\n");
  /*

    Serial.println("Configuring Motors for Forward Rotation...");
    digitalWrite(motorForwardPin_A, HIGH);
    digitalWrite(motorReversePin_A, LOW);
    digitalWrite(motorForwardPin_B, HIGH);
    digitalWrite(motorReversePin_B, LOW);
    delay(100);

    Serial.println("Rotating Motors at 50% speed");
    analogWrite(motorSpeedPin_A, 128);
    analogWrite(motorSpeedPin_B, 128);
    delay(100);

    Serial.println("Reading Encoder Outputs, enter 'q' to Quit\n");

    while(Serial.read() != 'q'){
    Serial.print("\nEncoder A, Output 1: ");
    Serial.println(digitalRead(motorEncoderOutput1_A));
    Serial.print("Encoder A, Output 2: ");
    Serial.println(digitalRead(motorEncoderOutput2_A));
    Serial.print("Encoder B, Output 1: ");
    Serial.println(digitalRead(motorEncoderOutput1_B));
    Serial.print("Encoder B, Output 2: ");
    Serial.println(digitalRead(motorEncoderOutput2_B));
    delay(200);
    }

    Serial.println("Braking Motors...");
    digitalWrite(motorForwardPin_A, LOW);
    digitalWrite(motorReversePin_A, LOW);
    analogWrite(motorSpeedPin_A, 0);
    digitalWrite(motorForwardPin_B, LOW);
    digitalWrite(motorReversePin_B, LOW);
    analogWrite(motorSpeedPin_B, 0);
  */
  Serial.println("\nEncoder Test Complete!\n");

}

void InitializeServos() {
  //Servo initialization
  servo1.attach(SERVO_1);
  servo2.attach(SERVO_2);
  servo3.attach(SERVO_3);
  servo4.attach(SERVO_4);
  servo5.attach(SERVO_5);
  servo6.attach(SERVO_6);
}

void InitializeGearMotors() {
  pinMode(GEAR_MOTOR_1_DIR, OUTPUT);
  pinMode(GEAR_MOTOR_1_SPEED, OUTPUT);
  pinMode(GEAR_MOTOR_2_DIR, OUTPUT);
  pinMode(GEAR_MOTOR_2_SPEED, OUTPUT);
}

void InitializeStepperMotors() {
  stepper1.begin(RPM, MICROSTEPS);
  stepper2.begin(RPM, MICROSTEPS);
  stepper3.begin(RPM, MICROSTEPS);
  stepper4.begin(RPM, MICROSTEPS);
}

void InitializeControls() {
  //joystick initializtion
  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);

  //button initializations;
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(SW3, INPUT_PULLUP);
  pinMode(SW4, INPUT_PULLUP);
  pinMode(SW5, INPUT_PULLUP);
  pinMode(SW6, INPUT_PULLUP);
  pinMode(SW7, INPUT_PULLUP);
}

void InitializeDisplay() {
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("TEST MODE");
  display.setCursor(0, 16);
  display.setTextSize(1);
  display.println("Open Serial terminal");
  display.println("to run tests");
  display.display();

}

void InitializeIO() {
  pinMode(BANK_1_PIN_1, OUTPUT);
  pinMode(BANK_1_PIN_2, OUTPUT);
  pinMode(BANK_1_PIN_3, OUTPUT);
  pinMode(BANK_1_PIN_4, OUTPUT);
  pinMode(BANK_1_PIN_5, OUTPUT);
  pinMode(BANK_1_PIN_6, OUTPUT);
  pinMode(BANK_1_PIN_7, OUTPUT);
  pinMode(BANK_1_PIN_8, OUTPUT);
  pinMode(BANK_1_PIN_9, OUTPUT);
  pinMode(BANK_1_PIN_10, OUTPUT);
  pinMode(BANK_2_PIN_1, OUTPUT);
  pinMode(BANK_2_PIN_2, OUTPUT);
  pinMode(BANK_2_PIN_3, OUTPUT);
  pinMode(BANK_2_PIN_4, OUTPUT);
  pinMode(BANK_2_PIN_5, OUTPUT);
  pinMode(BANK_2_PIN_6, OUTPUT);
  pinMode(BANK_2_PIN_7, OUTPUT);
  pinMode(BANK_2_PIN_8, OUTPUT);
  pinMode(BANK_2_PIN_9, OUTPUT);
  pinMode(BANK_2_PIN_10, OUTPUT);
}


void InitializeSerial() {
  Serial.begin(9600);
  while (!Serial);
}
