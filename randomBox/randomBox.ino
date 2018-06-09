/***************************************************
  This is a test example for the Adafruit Trellis w/HT16K33

  Designed specifically to work with the Adafruit Trellis
  ----> https://www.adafruit.com/products/1616
  ----> https://www.adafruit.com/products/1611
 ****************************************************/

#include <Wire.h>
#include "Adafruit_Trellis.h"

/***************************************************
  This example shows reading buttons and setting/clearing buttons in a loop
  "momentary" mode has the LED light up only when a button is pressed
  "latching" mode lets you turn the LED on/off when pressed

  Up to 8 matrices can be used but this example will show 4 or 1
 ****************************************************/

// Set the number of lights that blink during the initialisation phase.
#define NUMBER_OF_RANDOM_LIGHTS_BLINKING 5

// Set the number of initalisation phases
#define NUMBER_OF_INITALISATION_PHASES 3

// Pause between blinks
#define BLINK_PAUSE 200

// Combination Lock Answer
#define LOCKSOLUTION 1234

/*
Define STANDARD PATTERNS TO DISPLAY
*/


#define lenSadSmiley 6
#define lenHappySmiley 6
#define lenZero 10
#define lenOne 7
#define lenTwo 7
#define lenThree 8
#define lenFour 8
#define lenFive 8
#define lenSix 10
#define lenSeven 6
#define lenEight 6
#define lenNine 9
int sadSmiley[lenSadSmiley] = {1, 2, 9, 10, 12, 15};
int happySmiley[lenHappySmiley] = {1, 2, 8, 11, 13, 14};
int zero[lenZero] {1,2,3, 5,7,9,11,13,14,15};
int one[lenOne] = {2, 5, 6, 10, 13, 14, 15};
int two[lenTwo] = {2, 5, 7, 10, 13, 14, 15};
int three[lenThree] = {2, 3, 5, 7, 8, 10, 12, 13};
int four[lenFour] = {1, 3, 5, 7, 9, 10, 11, 15};
int five[lenFive] = {2, 5, 7, 8, 10, 12, 13, 14};
int six[lenSix] = {1, 2, 3, 5, 9, 10 , 11, 13, 14, 15};
int seven[lenSeven] = {1,2,3,6,9,13};
int eight[lenEight] = {2, 5, 7, 8, 10, 13};
int nine[lenNine] = {1,2,3,5,7,9, 10, 11, 15};

// DEBUG MODE
#define DEBUG 1

Adafruit_Trellis matrix = Adafruit_Trellis();

// Just one
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix);

// set to however many you're working with here, up to 8
#define NUMTRELLIS 1

#define numKeys (NUMTRELLIS * 16)

// Connect Trellis Vin to 5V and Ground to ground.
// Connect the INT wire to pin #A2 (can change later!)
#define INTPIN A2
// Connect I2C SDA pin to your Arduino SDA line
// Connect I2C SCL pin to your Arduino SCL line
// All Trellises share the SDA, SCL and INT pin!
// Even 8 tiles use only 3 wires max

void setup() {
  Serial.begin(9600);
  Serial.println("RandomBox:");

  // INT pin requires a pullup
  pinMode(INTPIN, INPUT);
  digitalWrite(INTPIN, HIGH);

  // begin() with the addresses of each panel in order
  // I find it easiest if the addresses are in order
  trellis.begin(0x70);  // only one
  // trellis.begin(0x70, 0x71, 0x72, 0x73);  // or four!

  // light up all the LEDs in order
  for (uint8_t i=0; i<numKeys; i++) {
    trellis.setLED(i);
    trellis.writeDisplay();
    delay(50);
  }
  // then turn them off
  for (uint8_t i=0; i<numKeys; i++) {
    trellis.clrLED(i);
    trellis.writeDisplay();
    delay(50);
  }
  if(DEBUG){
    clearDisplay();
    writePattern(sadSmiley, 6);
    delay(1000);
    clearDisplay();
    writePattern(happySmiley, 6);
    delay(1000);
    clearDisplay();
    writePattern(zero, lenZero);
    delay(1000);
    clearDisplay();
    writePattern(one, lenOne);
    delay(1000);
    clearDisplay();
    writePattern(two, lenTwo);
    delay(1000);
    clearDisplay();
    writePattern(three, lenThree);
    delay(1000);
    clearDisplay();
    writePattern(four, lenFour);
    delay(1000);
    clearDisplay();
    writePattern(five, lenFive);
    delay(1000);
    clearDisplay();
    writePattern(six, lenSix);
    delay(1000);
    clearDisplay();
    writePattern(seven,lenSeven);
    delay(1000);
    clearDisplay();
    writePattern(eight, lenEight);
    delay(1000);
    clearDisplay();
    writePattern(nine, lenNine);
    delay(1000);
    clearDisplay();
  }
}

int randomPattern[NUMBER_OF_RANDOM_LIGHTS_BLINKING];

// Generates a random pattern.
void generateRandomPattern(){
  int count = 1;
  int candidate = 0;
  while(count < NUMBER_OF_RANDOM_LIGHTS_BLINKING + 1){
    candidate = random(0, numKeys);
//    Serial.println(candidate);
//    delay(1000);
    for(int index=0; index < count; index++){
//      Serial.print("index = "); Serial.println(index);
      if(candidate == randomPattern[index]){
//         Check if the number has been drawn?
//        Serial.println("Break Happend");
        break;
      }
      if(index == count - 1){
//        Set new value in randompattern variable
        randomPattern[index] = candidate;
//        Serial.print(randomPattern[index]);
//        Serial.println(index);
//        Serial.println(count);
//        Serial.println("Count increase");
        // If this is a new previously undrawn number increase counter!
        count++;
        break;
      }
    }
  }
  for(int index=0; index < NUMBER_OF_RANDOM_LIGHTS_BLINKING; index++){
    Serial.print(randomPattern[index]);
  }
  Serial.println("");
}

// Writes a given pattern
void writePattern(int *pattern, int length){
  clearDisplay();
  for(int index=0;index<length;index++){
    trellis.setLED(pattern[index]);
    Serial.print(pattern[index]);
  }
  trellis.writeDisplay();
  delay(50);
}

//void writeSymbol(bool *symbol){
//  int length = 0;
//  int *pattern;
//  // Determine the length of symbol
//  for(int index=0; index<numKeys; index++){
//    if(symbol[index] == true){
//      length++;
//    }
//  }
//
//  pattern = (int *)malloc(length);
//
//  for (int index=length; index>=0; index--){
//    pattern[index] =
//  }
//
//  free(pattern);
//}

// Clears display
void clearDisplay(){
   for(int index=0; index<numKeys; index++){
     trellis.clrLED(index);
   }
   trellis.writeDisplay();
//  trellis.clear();
  delay(50);
}

// Function to retrieve answer
int retrieveAnswer(){
  bool givenAnswer = false;
  int answer = 0;
  trellis.clear();
  delay(100);
  while(!givenAnswer) {
    if(trellis.readSwitches()){
      for (uint8_t i=0; i<numKeys; i++) {
        // if it was pressed, turn it on
        if (trellis.isKeyPressed(i)) {
          answer = i;
          givenAnswer = true;
          break;
        }
      }
    }
    delay(30);
  }
  writePattern(&answer,1);
  delay(BLINK_PAUSE);
  clearDisplay();
  return answer;
}

// Random Sequence
void sendRandomSequence(){
  for(int index=0; index < NUMBER_OF_INITALISATION_PHASES; index++){
    generateRandomPattern();
    writePattern(randomPattern, NUMBER_OF_RANDOM_LIGHTS_BLINKING);
    delay(BLINK_PAUSE);
    clearDisplay();
    delay(BLINK_PAUSE/4);
  }
}

void blinkAllLights(){
  int pattern[numKeys];
  for (int index=0; index< numKeys; index++){
    pattern[index] = index;
  }
  writePattern(pattern, numKeys);
  delay(BLINK_PAUSE);
  clearDisplay();
  delay(BLINK_PAUSE/4);
}

// Reveal Positive Answer
void revealPositiveAnswer(){
  blinkAllLights();
  for(int index=0; index<3; index++){
    writePattern(happySmiley, lenHappySmiley);
    delay(BLINK_PAUSE);
    clearDisplay();
    delay(BLINK_PAUSE/4);
  }
  // TODO printout solution
}


// Reveal Negative Answer
void deliverNegativeAnswer(){
  blinkAllLights();
  for(int index=0; index<3; index++){
    writePattern(sadSmiley, lenSadSmiley);
    delay(BLINK_PAUSE);
    clearDisplay();
    delay(BLINK_PAUSE/4);
  }
}


void loop() {
  delay(30); // 30ms delay is required, dont remove me!
  // Generate random pattern
  if(DEBUG){
    Serial.println("Generating Random Sequence");
  }
  sendRandomSequence();
  if(DEBUG){
    Serial.println("Generate Random Answer");
  }
  // Generate random answer
  int randomAnswer = random(0, numKeys);
  // Retrieve guess from user
  if(DEBUG){
    Serial.println("Retrieve guess from user");
  }
  int guess = retrieveAnswer();
  // Evaluate
  if(DEBUG){
    Serial.println("Evaluate Answer");
  }
  if(randomAnswer == guess){
    revealPositiveAnswer();
  } else {
    deliverNegativeAnswer();
  }

}
