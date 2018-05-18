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
}

int randomPattern[NUMBER_OF_RANDOM_LIGHTS_BLINKING];

void generateRandomPattern(){
  int count = 0;
  while(count < NUMBER_OF_RANDOM_LIGHTS_BLINKING){
    int candidate = random(0, numKeys);
    for(int index=0; index < count; index++){
      if(candidate == randomPattern[index]){
        // Check if the number has been drawn?
        break;
      }
      if(index == count - 1){
        // If this is a new previously undrawn number increase counter!
        count++;
      }
    }
  }
}

void loop() {
  delay(30); // 30ms delay is required, dont remove me!
  // Generate random pattern
}
