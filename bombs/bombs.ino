//We always have to include the library
#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn
 pin 11 is connected to the CLK
 pin 10 is connected to LOAD
 We have only a single MAX72XX.
 */

// Data pin for display
#define DN 4
// Load pin for display
#define CS 3
// Clock pin for display
#define CLK 2

// Button pin for turn on switch
#define BUTTON 10

#define TIMEDELAY 100

// DEGUBBING mode
#define DEBUG false

/*
Define the length of the timer
 */
#define MINUTES 30
#define NUMBER_OF_SUBSECONDS 7

#define codeSecond1 2
#define codeSecond2 3

#define SECRET_CODE 4789
#define SECRET_CODE_OFFSET 1
#define A -295/MINUTES
#define B 300

LedControl lc=LedControl(DN,CLK,CS,1);
int subseconds[NUMBER_OF_SUBSECONDS];

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
//  writePlayzone();
  clearDisplay();
  // Set display in power saving mode
  lc.shutdown(0,true);
  //  Make the button input
  pinMode(BUTTON, INPUT_PULLUP);

  double step = 100./NUMBER_OF_SUBSECONDS;
  for(int index=0; index<NUMBER_OF_SUBSECONDS; index++){
    subseconds[index]= (int)(step * index);
  }

  if(DEBUG){
    Serial.begin(9600);
    for(int index=0; index<8; index++){
      Serial.println(subseconds[index]);
    }
  }
}



//void writePlayzone() {
//    lc.setChar(0,7,'P',false);
//    lc.setChar(0,6,'L',false);
//    lc.setChar(0,5,'A',false);
//    lc.setDigit(0,4,4,false); // 4 ergibt ein "Y"
//    lc.setDigit(0,3,2,false); // 2 ergibt ein "Z"
//    lc.setChar(0,2,'0',false);
//    lc.setRow(0,1,B01110110); // N
//    lc.setChar(0,0,'E',false);
//}

void showSecret() {
  clearDisplay();
  int s4 = (int)SECRET_CODE % 10;
  int s5 = ((int)SECRET_CODE / 10) % 10;
  int s6 = ((int)SECRET_CODE / 100) % 10;
  int s7 = ((int)SECRET_CODE / 1000) % 10;
  lc.setDigit(0,SECRET_CODE_OFFSET,s4,false);
  lc.setDigit(0,SECRET_CODE_OFFSET + 1,s5,false);
  lc.setDigit(0,SECRET_CODE_OFFSET + 2,s6,false);
  lc.setDigit(0,SECRET_CODE_OFFSET + 3,s7,false);
//  delay(MILISECONDS_SECRET_CODE_IS_VISIABLE);
}

void clearDisplay() {
  lc.setChar(0,0,' ', false);
  lc.setChar(0,1,' ', false);
  lc.setChar(0,2,' ', false);
  lc.setChar(0,3,' ', false);
  lc.setChar(0,4,' ', false);
  lc.setChar(0,5,' ', false);
  lc.setChar(0,6,' ', false);
  lc.setChar(0,7,' ', false);
}


void setupDisplay() {
  lc.setChar(0,7,' ',false);
  lc.setChar(0,6,' ',false);
  lc.setChar(0,5,'0',false);
  lc.setChar(0,4,'0',false);
  lc.setChar(0,3,'0',false);
  lc.setChar(0,2,'0',false);
  lc.setChar(0,1,'0',false);
  lc.setChar(0,0,'0',false);
  lc.setChar(0,2,'.',true);
  lc.setChar(0,4,'.',true);
//  lc.setChar(0,6,'.',true);
  lc.setChar(0,2,'0',true);
  lc.setChar(0,4,'0',true);
//  lc.setChar(0,6,'0',true);
}

void resetDisplay(int s5, int s4, int s3, int s2, int s1, int s0){
  setupDisplay();
  lc.setDigit(0,0,s0,false);
  lc.setDigit(0,1,s1,false);
  lc.setDigit(0,2,s2,true);
  lc.setDigit(0,3,s3,false);
  lc.setDigit(0,4,s4,true);
  lc.setDigit(0,5,s5,false);
}

bool detectSwitch() {
  static bool previousStateButton;
//  Serial.println(previousStateButton);
  int state = digitalRead(BUTTON);
  if(state == previousStateButton){
    return false;
  }
  previousStateButton = state;
  if (DEBUG){
    Serial.println("Switch changed");
  }
  return true;
}

void boom() {
  clearDisplay();
  lc.setChar(0,0,'b',false);
  lc.setChar(0,1,'O',false);
  lc.setChar(0,2,'O',false);
  lc.setChar(0,3,'O',false);
  lc.setChar(0,4,'O',false);
  lc.setChar(0,5,'O',false);
  lc.setChar(0,6,'O',false);
  lc.setChar(0,3,'m',false);
}

int s0,s1,s2,s3,s4,s5;
void loop() {
//  Wait until button is pressed
  while(digitalRead(BUTTON)){
    delay(50);
  }
  lc.shutdown(0,false);
  lc.clearDisplay(0);
  setupDisplay();
  int numberOfTriggers = 0;
  for(int minute=MINUTES - 1; minute >= 0; minute--){
    s4 = minute % 10;
    s5 = minute / 10;
    lc.setDigit(0,4,s4,true);
    lc.setDigit(0,5,s5,false);
    for(int second=59; second >= 0; second--){

      if(detectSwitch()){
        numberOfTriggers += 1;
        if(numberOfTriggers < 30){
          minute = max(minute - 5, 5);
          second = 0;
          break;
        }
      }
      s2 = second % 10;
      s3 = second/10;
      lc.setDigit(0,2,s2,true);
      lc.setDigit(0,3,s3,false);
      for(int subSecond = NUMBER_OF_SUBSECONDS - 1; subSecond >= 0; subSecond--){
          s0 = subseconds[subSecond] % 10;
          s1 =  subseconds[subSecond]/10;
//          if(DEBUG){
//            Serial.print(s1); Serial.print(s0);
//            Serial.println();
//          }
          lc.setDigit(0,0,s0,false);
          lc.setDigit(0,1,s1,false);
          if(s3 == codeSecond1 && s2 == codeSecond2 ){
            showSecret();
//           int dy = (2 >> minute )* 500 + 50;
            int dy = A * minute + B;
            if(DEBUG){
              Serial.print("Secret Delay:");
              Serial.println(dy);
            }
            delay(dy);
            resetDisplay(s5, s4, s3, s2, s1, s0);
            break;
          } else{
            delay(TIMEDELAY);
          }
      }
    }
//    Serial.print("Minute ");
//    Serial.println(minute);
  }
  // Flash the explotion
  for(int index=0; index < 3; index++){
    boom();
    delay(1000);
    clearDisplay();
    delay(500);
  }
  lc.shutdown(0,true);
}
