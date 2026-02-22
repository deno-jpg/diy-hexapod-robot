#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>
#include <Arduino.h>

void setup() {
  Serial.begin(9600); 
  
  Dabble.begin(9600, 3, 2);

  Serial.println("--- SYSTEM START ---");
  Serial.println("1. Connect Phone to JDY module");
  Serial.println("2. Open Gamepad in Dabble App");
}

void loop() {
  Dabble.processInput(); 

  if (GamePad.isUpPressed()) {
    Serial.println("BT Command: UP");
  }

  if (GamePad.isDownPressed()) {
    Serial.println("BT Command: DOWN");
  }
}