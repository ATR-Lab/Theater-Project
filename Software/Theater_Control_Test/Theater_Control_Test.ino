
//This is a test program for rev 0.1.1 of Kent State's
//ATR Lab Theater Project Theater Control Board. Runs a basic 
//test of all functions of the system (motors, servos, 
//joystick,buttons, etc) via a serial com port.
//For Arduino Mega

//Dan Maher, ATR Lab Research Assistant
//12/08/2021

#include <Wire.h>
#include <Servo.h>
#include "A4988.h"
#include <Adafruit_SSD1306.h> //Display
#include "pinmap.h" //Reference for pin macros

///////////////////////
//Globals
///////////////////////
//These are just the number of selections to pass to ProcessSelection
static int selectionQuantityMain = 4;
static int selectionQuantityServo = 7;
static int selectionQuantityStepper = 5;
static int selectionQuantityGear = 3;

int menuSelection = -1; //Holds the current menu selection. Setup so that '0' is quit

//Servos
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

//Steppers
A4988 stepper1(200, STEPPER_MOTOR_1_STEP, STEPPER_MOTOR_1_DIR, 34, 35, 36);
A4988 stepper2(200, STEPPER_MOTOR_2_STEP, STEPPER_MOTOR_2_DIR, 34, 35, 36);
A4988 stepper3(200, STEPPER_MOTOR_3_STEP, STEPPER_MOTOR_3_DIR, 34, 35, 36);
A4988 stepper4(200, STEPPER_MOTOR_4_STEP, STEPPER_MOTOR_4_DIR, 34, 35, 36);

//I2C Display
Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  InitializeServos();
  InitializeStepperMotors();
  InitializeGearMotors();
  InitializeControls();
  InitializeDisplay();
  InitializeSerial();
}

void loop() {
  while(menuSelection < 1){
    DisplayMenu();
    menuSelection = ProcessSelection(selectionQuantityMain);
  }

  //Main Menu Selection
  switch(menuSelection){
    case 1: //Servo Menu selected
      while(1){
        DisplayServoMenu();
        menuSelection = ProcessSelection(selectionQuantityServo);
        if(menuSelection == 0)
          break;
        TestServo(menuSelection);
      }
      break;
    case 2:
      while(1){
        DisplayGearMenu();
        menuSelection = ProcessSelection(selectionQuantityGear);
        if(menuSelection == 0)
          break;
        TestGearMotor(menuSelection);
      }
      break;
    case 3:
      while(1){
        DisplayStepperMenu();
        menuSelection = ProcessSelection(selectionQuantityStepper);
        if(menuSelection == 0)
          break;
        TestStepperMotor(menuSelection);
      }
      break;
    case 4:
      TestControls();
      break;
  }

  menuSelection = -1;
}

void DisplayMenu(){
  Serial.print("Please Select Option (1-5");
  Serial.println("):\n----------------------------");
  Serial.println("1.  Servo Tests");
  Serial.println("2.  Gear Motor Tests");
  Serial.println("3.  Stepper Motor Tests");
  Serial.println("4.  Test Controls");
  Serial.println();
}
void DisplayServoMenu(){
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
void DisplayGearMenu(){
  Serial.print("Please Select Option (0-2");
  Serial.println("):\n----------------------------");
  Serial.println("0.  Previous Menu");
  Serial.println("1.  Test Gear Motor 1");
  Serial.println("2.  Test Gear Motor 2");
  Serial.println();
}
void DisplayStepperMenu(){
  Serial.print("Please Select Option (0-4");
  Serial.println("):\n----------------------------");
  Serial.println("0.  Previous Menu");
  Serial.println("1.  Test Stepper Motor 1");
  Serial.println("2.  Test Stepper Motor 2");
  Serial.println("3.  Test Stepper Motor 3");
  Serial.println("4.  Test Stepper Motor 4");
  Serial.println();
}

int ProcessSelection(int selectionQuantity){
  while(!Serial.available()){
    
  }
  
  int selection = Serial.parseInt();
  if(selection < 0 || selection > selectionQuantity){
    Serial.print("Invalid selection! Enter a number between 0 and ");
    Serial.println(selectionQuantity);
    return -1;
  }else{
    return selection;
  }
}

void TestServo(int servo){
  Serial.print("Testing Servo ");
  Serial.print(servo);
  Serial.println("...\n");

  switch(servo){
    case 1:
      servo1.write(180);
      delay(2000);
      servo1.write(90);
      break;
    case 2:
      servo2.write(180);
      delay(2000);
      servo2.write(90);
      break;
    case 3:
      servo3.write(180);
      delay(2000);
      servo3.write(90);
      break;
    case 4:
      servo4.write(180);
      delay(2000);
      servo4.write(90);
      break;
    case 5:
      servo5.write(180);
      delay(2000);
      servo5.write(90);
      break;
    case 6:
      servo6.write(180);
      delay(2000);
      servo6.write(90);
      break;
  }
  Serial.println("\nServo Test Complete!\n");
}

void TestGearMotor(int motor){
  Serial.print("Testing Gear Motor ");
  Serial.print(motor);
  Serial.println("...\n");
  
  switch(motor){
    case 1:
      Serial.println("Configuring Gear Motor 1 for Forward Rotation...");
      digitalWrite(GEAR_MOTOR_1_DIR, HIGH);
      delay(100);
      Serial.println("Rotating Gear Motor 1 Forward...");
      analogWrite(GEAR_MOTOR_1_SPEED, 255);
      delay(4000);
      Serial.println("Braking Gear Motor 1...");
      analogWrite(GEAR_MOTOR_1_SPEED, 0);
      delay(100);
      Serial.println("Configuring Gear Motor 1 for Reverse Rotation...");
      digitalWrite(GEAR_MOTOR_1_DIR, LOW);
      delay(100);
      Serial.println("Rotating Gear Motor 1 in Reverse...");
      analogWrite(GEAR_MOTOR_1_SPEED, 255);
      delay(4000);
      Serial.println("Braking Gear Motor 1...");
      analogWrite(GEAR_MOTOR_1_SPEED, 0);
    /*
      Serial.println("Configuring Motor A for Forward Rotation...");
      digitalWrite(GEAR_MOTOR_1_DIR, HIGH);
      delay(100);

      Serial.println("Increasing speed on Motor A...");
      for (int i = 0; i < 256; i++){
        analogWrite(GEAR_MOTOR_1_SPEED, i);
        delay(50);
      }
      Serial.println("Motor A at Max Speed...");
      delay(2000);
      Serial.println("Braking Motor A...");
      analogWrite(GEAR_MOTOR_1_SPEED, 0);
      delay(100);

      Serial.println("Configuring Motor A for Reverse Rotation...");
      digitalWrite(GEAR_MOTOR_1_DIR, LOW);
      delay(100);

      Serial.println("Increasing speed on Motor A...");
      for (int i = 0; i < 256; i++){
        analogWrite(GEAR_MOTOR_1_SPEED, i);
        delay(50);
      }
      Serial.println("Motor A at Max Speed...");
      delay(2000);
      Serial.println("Braking Motor A...\n");
      analogWrite(GEAR_MOTOR_1_SPEED, 0);
      delay(100);
      */
      break;
    case 2:
      Serial.println("Configuring Motor A for Forward Rotation...");
      digitalWrite(GEAR_MOTOR_2_DIR, HIGH);
      delay(100);

      Serial.println("Increasing speed on Motor A...");
      for (int i = 0; i < 256; i++){
        analogWrite(GEAR_MOTOR_2_SPEED, i);
        delay(50);
      }
      Serial.println("Motor A at Max Speed...");
      delay(2000);
      Serial.println("Braking Motor A...");
      analogWrite(GEAR_MOTOR_2_SPEED, 0);
      delay(100);

      Serial.println("Configuring Motor A for Reverse Rotation...");
      digitalWrite(GEAR_MOTOR_2_DIR, LOW);
      delay(100);

      Serial.println("Increasing speed on Motor A...");
      for (int i = 0; i < 256; i++){
        analogWrite(GEAR_MOTOR_2_SPEED, i);
        delay(50);
      }
      Serial.println("Motor A at Max Speed...");
      delay(2000);
      Serial.println("Braking Motor A...\n");
      analogWrite(GEAR_MOTOR_2_SPEED, 0);
      delay(100);
      break;
  }

  Serial.println("\nMotor Test Complete!\n");
}

void TestStepperMotor(int motor){
  Serial.print("Testing Stepper Motor ");
  Serial.print(motor);
  Serial.println("...\n");

  switch(motor){
    case 1:
      stepper1.begin(1, 1);
      stepper1.rotate(360);
      break;
    case 2:
      stepper2.begin(1, 1);
      stepper2.rotate(360);
      break;
    case 3:
      stepper3.begin(1, 1);
      stepper3.rotate(360);
      break;
    case 4:
      stepper4.begin(1, 1);
      stepper4.rotate(360);
      break;
  }

  Serial.println("\nStepper Motor Test Complete!\n");
}

void TestControls(){
  Serial.println("Testing Controls, Enter 'q' to Quit...\n");
   while(Serial.read() != 'q'){
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


void TestEncoders(){
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

void InitializeStepperMotors(){
  /*
  stepper1 = Stepper(1, STEPPER_MOTOR_1_STEP, STEPPER_MOTOR_1_DIR);
  stepper1.setMaxSpeed(1000);
  stepper2 = AccelStepper(1, STEPPER_MOTOR_2_STEP, STEPPER_MOTOR_2_DIR);
  stepper2.setMaxSpeed(1000);
  stepper3 = AccelStepper(1, STEPPER_MOTOR_3_STEP, STEPPER_MOTOR_3_DIR);
  stepper3.setMaxSpeed(1000);
  stepper4 = AccelStepper(1, STEPPER_MOTOR_4_STEP, STEPPER_MOTOR_4_DIR);
  stepper4.setMaxSpeed(1000);
  */
}


void InitializeServos(){
  //Servo initialization
  servo1.attach(SERVO_1);
  servo2.attach(SERVO_2);
  servo3.attach(SERVO_3);
  servo4.attach(SERVO_4);
  servo5.attach(SERVO_5);
  servo6.attach(SERVO_6);
}

void InitializeGearMotors(){
  pinMode(GEAR_MOTOR_1_DIR, OUTPUT);
  pinMode(GEAR_MOTOR_1_SPEED, OUTPUT);
  pinMode(GEAR_MOTOR_2_DIR, OUTPUT);
  pinMode(GEAR_MOTOR_2_SPEED, OUTPUT);
}

void InitializeControls(){
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

void InitializeDisplay(){
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0,0);
  display.println("TEST MODE");
  display.setCursor(0, 16);
  display.setTextSize(1);
  display.println("Open serial terminal");
  display.println("to run tests");
  display.display();
  
}

void InitializeSerial(){
  Serial.begin(9600);
  while (!Serial);
}
