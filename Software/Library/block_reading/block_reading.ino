#include "commandList.h"

unsigned long previousMillis = 0; 
unsigned long startTimer = 0; 

int currentIndex = 0;

bool isFinish = false;

void setup() {
  Serial.begin(9600);

  InitLED();
  
  startTimer = millis();
}

void loop() {
  if (!isFinish){
    if (millis() >= startTimer + inputCommandList[currentIndex].startTime * 1000) {
      
      switch (inputCommandList[currentIndex].itemName){
        case D_LED:
          LEDControl(inputCommandList[currentIndex]);
          break;
        case D_SERVO:
          LEDControl(inputCommandList[currentIndex]);
          break;
      }

      currentIndex += 1;
    }

    if (currentIndex >= sizeof(inputCommandList)){
      isFinish = true;
      Serial.println("Finished");
    }
  }
}

void LEDControl(InputCommand _input){
  Serial.println("led getting input");
  digitalWrite(LED_BUILTIN, _input.value);
}

void ServoControl(InputCommand _input){
  Serial.println("servo getting input");
  digitalWrite(LED_BUILTIN, _input.value);
}

void InitLED(){
  pinMode(LED_BUILTIN, OUTPUT);
}
