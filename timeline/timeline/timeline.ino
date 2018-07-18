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

#define SECRET 4028

#define NOT_CONNECTED 400

int MALE[8] = {MALE0, MALE1, MALE2 ,MALE3, MALE4, MALE5, MALE6, MALE7};
int FEMALE[8] = {FEMALE0, FEMALE1, FEMALE2, FEMALE3, FEMALE4, FEMALE5, FEMALE6, NOT_CONNECTED};

int state[8];

int ANSWERS[8] = {
  FEMALE1,
  FEMALE6,
  FEMALE4,
  FEMALE5,
  FEMALE3,
  FEMALE2,
  FEMALE0,
  NOT_CONNECTED
};

void revealSecret(){
  matrix.print(SECRET, DEC);
  matrix.blinkRate(1);
  matrix.writeDisplay();
  delay(1000);
  matrix.blinkRate(0); 
//  matrix.writeDisplay(); 
}

int retriveConnection(int maleID){
  digitalWrite(MALE[maleID], LOW);
  for(int j=0; j < 7; j++){
//    Serial.print(maleID);
//    Serial.print(j);
//    Serial.println(digitalRead(FEMALE[j]));
    if(!digitalRead(FEMALE[j])){
        // Return index of connected female
//        Serial.println("Female low");
        digitalWrite(MALE[maleID], HIGH);
        return j;
      }
    // If nothing was found return address to NOT_CONNECTED
  }
  digitalWrite(MALE[maleID], HIGH);
  return 7;
}

bool updateState(int maleID, int femaleID){
    if(femaleID != state[maleID]){
      Serial.println("Update state");
      Serial.print("Female ID: ");
      Serial.print(femaleID);
      Serial.print(" Male ID: ");
      Serial.println(maleID);
      state[maleID] = femaleID;
      return true;
    }
    return false;
}

bool checkConnection(int maleID, int femaleID){
  if(ANSWERS[maleID] == FEMALE[femaleID]){
    Serial.println("These Are Connected");
    Serial.print(maleID);
    Serial.print(", ");
    Serial.print(ANSWERS[maleID]);
    Serial.print(" -> ");
    Serial.print(femaleID);
    Serial.print(", ");
    Serial.println(FEMALE[femaleID]);
    return true;
  }
  return false;
}

bool trueSolution(){
  for(int i=0; i<8; i++){
    if(ANSWERS[i] != FEMALE[state[i]]){
      return false;
    }
  }
  return true;
}

void resetDisplay(){
  matrix.print(10000, DEC);
  matrix.blinkRate(0);
  matrix.writeDisplay();
}

void positiveTick(int maleID, int femaleID){
  matrix.writeDigitNum(1, maleID);
  matrix.writeDigitNum(4, femaleID);
  matrix.writeDisplay();
  delay(1000);
  resetDisplay();
}

void negativeTick(int maleID, int femaleID){
  matrix.writeDigitNum(0, maleID);
  matrix.writeDigitNum(3, femaleID);
//  matrix.blinkRate(1);
  matrix.writeDisplay();
  delay(10);
  resetDisplay();
}


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
//  Initialize state
  for(int i=0; i < 8; i++){
    state[i] = 7;
  }
  resetDisplay();
}

void loop() {
  for(int maleID=0; maleID < 8; maleID++){ 
    int femaleID = retriveConnection(maleID);
    if(updateState(maleID, femaleID)){
      if(checkConnection(maleID, femaleID)){
        positiveTick(maleID, femaleID);
      } else {
        negativeTick(maleID, femaleID);
      }
    }
  }

  if(trueSolution()){
    revealSecret();
  }

  delay(10);
}
