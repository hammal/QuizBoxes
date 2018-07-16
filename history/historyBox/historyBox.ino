#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();

#define MALE0 A0
#define MALE1 A1
#define MALE2 A2
#define MALE3 A3
#define MALE4 13 // SCK
#define MALE5 11 // MOSI
#define MALE6 12 // MISO
#define MALE7 7

#define FEMALE0 4
#define FEMALE1 3
#define FEMALE2 2
#define FEMALE3 10
#define FEMALE4 9
#define FEMALE5 6
#define FEMALE6 5

int MALE[8] = {MALE0, MALE1, MALE2 ,MALE3, MALE4, MALE5, MALE6, MALE7};
int FEMALE[7] = {FEMALE0, FEMALE1, FEMALE2, FEMALE3, FEMALE4, FEMALE5, FEMALE6};

void setup() {
#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("History Quiz");
#endif
  matrix.begin(0x70);
  for(int index=0; index < 8; index++){
    pinMode(MALE[index], OUTPUT);
    digitalWrite(MALE[index], HIGH);
    if(index < 7){
      pinMode(FEMALE[index], INPUT_PULLUP);  
    } 
  }
}

void loop() {
  for(int i=0; i < 8; i++){ 
    digitalWrite(MALE[i], LOW);
    for(int j=0; j < 7; j++){ 
      if(!digitalRead(FEMALE[j])){
        matrix.print(FEMALE[j], DEC);
        matrix.writeDisplay();
        delay(1000); 
      }
    }
  }
  matrix.print(9999, DEC);
  matrix.writeDisplay();
  delay(10);
}
