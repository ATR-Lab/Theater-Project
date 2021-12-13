//This is a test program for rev 0.01 of Kent State's
//ATR Lab Theater Project custom PCB. Runs a basic 
//test of all functions of the system (motors, servos, 
//leds, LIDAR, QTR, motor encoders) via a serial com
//port.

//Dan Maher, ATR Lab Research Assistant
//09/17/2021

#include <Wire.h>
#include <Servo.h>
#include <QTRSensors.h>
#include <TFLI2C.h>
#include "pinmap.h"

//Globals
int ledPin[7] {4, 13, QTR1, QTR2, QTR3, SDA, SCL};
static int numberOfSelections = 7;
int menuSelection = -1;
bool testAllFlag = false;
Servo servo1;
Servo servo2;
Servo servo3;

void setup() {
  initializeMotors();
  initializeLEDs();
  initializeServos();
  initializeSerial();
}

void loop() {
  while(menuSelection < 1){
    displayMenu();
    menuSelection = processSelection();
  }

  switch(menuSelection){
    case 7:
      Serial.println("Running all tests...\n");
      testAllFlag = true;
      menuSelection = 1;
    case 1:
      testServos();
      if(testAllFlag)
        menuSelection++;
      else
        break;
    case 2:
      testMotors();
      if(testAllFlag)
        menuSelection++;
      else
        break;
    case 3:
      testLEDs();
      if(testAllFlag)
        menuSelection++;
      else
        break;
    case 4:
      testQTR();
      if(testAllFlag)
        menuSelection++;
      else
        break;
    case 5:
      testLIDAR();
      if(testAllFlag)
        menuSelection++;
      else
        break;
    case 6:
      testEncoders();
      if(testAllFlag)
        menuSelection++;
      else
        break;      
    default:
      Serial.println("All tests complete!\n");
      testAllFlag = false;
  }
  menuSelection = -1;
}

void displayMenu(){
  Serial.print("Please Select Option (1-");
  Serial.print(numberOfSelections);
  Serial.println("):\n----------------------------");
  Serial.println("1.  Test Servos");
  Serial.println("2.  Test Motors");
  Serial.println("3.  Test LEDs");
  Serial.println("4.  Test QTR");
  Serial.println("5.  Test LIDAR");
  Serial.println("6.  Test Encoders");
  Serial.println("7.  RUN ALL TESTS\n");
}

int processSelection(){
  while(!Serial.available());
  
  int selection = Serial.parseInt();
  if(selection <= 0 || selection > numberOfSelections){
    Serial.print("Invalid selection! Enter a number between 1 and ");
    Serial.println(numberOfSelections);
    return -1;
  }else{
    return selection;
  }
}

void testServos(){
  Serial.println("Testing Servos...\n");
  
  Serial.println("Rotating Servo One for Two Seconds...");
  servo1.write(180);
  delay(2000);
  servo1.write(90);

  Serial.println("Rotating Servo Two for Two Seconds...");
  servo2.write(180);
  delay(2000);
  servo2.write(90);

  Serial.println("Rotating Servo Three for Two Seconds...");
  servo3.write(180);
  delay(2000);
  servo3.write(90);

  Serial.println("\nServo Test Complete!\n");
}

void testMotors(){
  Serial.println("Testing Motors...\n");

  //Motor A Test
  Serial.println("Configuring Motor A for Forward Rotation...");
  digitalWrite(motorForwardPin_A, HIGH);
  digitalWrite(motorReversePin_A, LOW);
  delay(100);

  Serial.println("Increasing speed on Motor A...");
  for (int i = 0; i < 256; i++){
    analogWrite(motorSpeedPin_A, i);
    delay(50);
  }
  Serial.println("Motor A at Max Speed...");
  delay(2000);
  Serial.println("Braking Motor A...");
  digitalWrite(motorForwardPin_A, LOW);
  digitalWrite(motorReversePin_A, LOW);
  analogWrite(motorSpeedPin_A, 0);
  delay(100);

  Serial.println("Configuring Motor A for Reverse Rotation...");
  digitalWrite(motorForwardPin_A, LOW);
  digitalWrite(motorReversePin_A, HIGH);
  delay(100);

  Serial.println("Increasing speed on Motor A...");
  for (int i = 0; i < 256; i++){
    analogWrite(motorSpeedPin_A, i);
    delay(50);
  }
  Serial.println("Motor A at Max Speed...");
  delay(2000);
  Serial.println("Braking Motor A...\n");
  digitalWrite(motorForwardPin_A, LOW);
  digitalWrite(motorReversePin_A, LOW);
  analogWrite(motorSpeedPin_A, 0);
  delay(100);

  //Motor B Test
  Serial.println("Configuring Motor B for Forward Rotation...");
  digitalWrite(motorForwardPin_B, HIGH);
  digitalWrite(motorReversePin_B, LOW);
  delay(100);

  Serial.println("Increasing speed on Motor B...");
  for (int i = 0; i < 256; i++){
    analogWrite(motorSpeedPin_B, i);
    delay(50);
  }
  Serial.println("Motor B at Max Speed...");
  delay(2000);
  Serial.println("Braking Motor B...");
  digitalWrite(motorForwardPin_B, LOW);
  digitalWrite(motorReversePin_B, LOW);
  analogWrite(motorSpeedPin_B, 0);
  delay(100);

  Serial.println("Configuring Motor B for Reverse Rotation...");
  digitalWrite(motorForwardPin_B, LOW);
  digitalWrite(motorReversePin_B, HIGH);
  delay(100);

  Serial.println("Increasing speed on Motor B...");
  for (int i = 0; i < 256; i++){
    analogWrite(motorSpeedPin_B, i);
    delay(50);
  }
  Serial.println("Motor B at Max Speed...");
  delay(2000);
  Serial.println("Braking Motor B...");
  digitalWrite(motorForwardPin_B, LOW);
  digitalWrite(motorReversePin_B, LOW);
  analogWrite(motorSpeedPin_B, 0);
  delay(100);

  Serial.println("\nMotor Test Complete!\n");
}

void testLEDs(){
  Serial.println("Testing LEDs...\n");

  for(int i = 1; i < 8; i++){
    Serial.print("Blinking LED ");
    Serial.print(i);
    Serial.println(" five times...");   
    for(int j = 0; j < 5; j++){
      digitalWrite(ledPin[i - 1], HIGH); 
      delay(200);
      digitalWrite(ledPin[i - 1], LOW);
      delay(200);
    }
  }
  Serial.println("\nLED Test Complete!\n");
}

void testQTR(){
  Serial.println("Testing QTR...\n");

  Serial.println("Configuring QTR Input Pins...");
  QTRSensors qtr;
  const uint8_t SensorCount = 3;
  uint16_t sensorValues[SensorCount];
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){QTR1, QTR2, QTR3}, SensorCount);

  Serial.println("Reading Sensor Array, Enter 'q' to Quit");
  while(Serial.read() != 'q'){
    qtr.read(sensorValues);
    Serial.print("\nQTR 1 (Right):  ");
    Serial.println(sensorValues[0]);
    Serial.print("QTR 2 (Center): ");
    Serial.println(sensorValues[1]);
    Serial.print("QTR 3 (Left):   ");
    Serial.println(sensorValues[2]);
    delay(200);
  }

  initializeLEDs();
  Serial.println("\nQTR Test Complete!\n");  
}

void testLIDAR(){
  Serial.println("Testing LIDAR...\n");
  Serial.println("Configuring LIDAR...");
  TFLI2C tflI2C;
  int16_t  tfDist;
  int16_t  tfAddr = TFL_DEF_ADR;
  Wire.begin();

  Serial.println("Reading LIDAR Data, Enter 'q' to Quit");

  while(Serial.read() != 'q'){
    if( tflI2C.getData( tfDist, tfAddr))
    {
       Serial.print("Distance: ");
       Serial.print(tfDist);  
       Serial.println(" centimeters");
    }
   else{
     Serial.print("ERROR: ");
     tflI2C.printStatus(); 
     Serial.println('\n');
    }
    delay(200);
  }
  initializeLEDs();
  Serial.println("\nLIDAR Test Complete!\n");  
}

void testEncoders(){
  Serial.println("Testing Encoders...\n");  
  
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
  Serial.println("\nEncoder Test Complete!\n");  
}

void initializeMotors(){
  //Motor & Encoder Pins
  pinMode(motorForwardPin_A,     OUTPUT);
  pinMode(motorReversePin_A,     OUTPUT);
  pinMode(motorSpeedPin_B,       OUTPUT);
  pinMode(motorEncoderOutput1_A, INPUT );
  pinMode(motorEncoderOutput2_A, INPUT );

  pinMode(motorForwardPin_B,     OUTPUT);
  pinMode(motorReversePin_B,     OUTPUT);
  pinMode(motorSpeedPin_B,       OUTPUT);
  pinMode(motorEncoderOutput1_B, INPUT );
  pinMode(motorEncoderOutput2_B, INPUT );
}


void initializeServos(){
  //Servo initialization
  servo1.attach(servoPin_1);
  servo2.attach(servoPin_2);
  servo3.attach(servoPin_3);

  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
}

void initializeLEDs(){
  for(int i = 0; i < 7; i++){
    pinMode(ledPin[i], OUTPUT);
  }
  for(int i = 0; i < 7; i++){
    digitalWrite(ledPin[i], LOW);
  }
}

void initializeSerial(){
  Serial.begin(9600);
  while (!Serial);
}
