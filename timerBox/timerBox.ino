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
#define DN 12
// Load pin for display
#define CS 10
// Clock pin for display
#define CLK 11

// Button pin for turn on switch
#define BUTTON 13

// DEGUBBING mode
#define DEBUG false

/*
Define the length of the timer
 */
#define MINUTES 30
#define NUMBER_OF_SUBSECONDS 7

#define codeSecond1 1
#define codeSecond2 1

#define SECRET_CODE 4789
#define SECRET_CODE_OFFSET 4
//#define MILISECONDS_SECRET_CODE_IS_VISIABLE 200
#define MIN_TIME_DELAY 10
#define MAX_TIME_DELAY 25

#define SPEED_UP 2
#define TICK_PERIOD 100

LedControl lc=LedControl(DN,CLK,CS,1);
int subseconds[NUMBER_OF_SUBSECONDS];

void writePlayzone();

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
  //  Make the button input
  pinMode(BUTTON, INPUT);

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
  lc.setDigit(0,4,s4,false);
  lc.setDigit(0,5,s5,false);
  lc.setDigit(0,6,s6,false);
  lc.setDigit(0,7,s7,false);
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

void loop() {
//  Wait until button is pressed
  while(digitalRead(BUTTON)){
    delay(50);
  }
  int s0,s1,s2,s3,s4,s5;
  int timeDelay = TICK_PERIOD;
  lc.clearDisplay(0);
  setupDisplay();
  for(int minute=MINUTES; minute >= 0; minute--){
    s4 = minute % 10;
    s5 = minute / 10;
    lc.setDigit(0,4,s4,true);
    lc.setDigit(0,5,s5,false);
    for(int second=59; second >= 0; second--){
      if(digitalRead(BUTTON)){
        if(timeDelay > MIN_TIME_DELAY){
        timeDelay = timeDelay/SPEED_UP;
        }
      } else {
        if(timeDelay < MAX_TIME_DELAY){
          timeDelay *= SPEED_UP;
        }
      }
      
      s2 = second % 10;
      s3 = second/10;
      lc.setDigit(0,2,s2,true);
      lc.setDigit(0,3,s3,false);
      for(int subSecond = NUMBER_OF_SUBSECONDS - 1; subSecond >= 0; subSecond--){
          s0 = subseconds[subSecond] % 10;
          s1 =  subseconds[subSecond]/10;
          if(DEBUG){
            Serial.print(s1); Serial.print(s0);
            Serial.println();
          }
          lc.setDigit(0,0,s0,false);
          lc.setDigit(0,1,s1,false);
          if(s3 == codeSecond1 && s2 == codeSecond2 ){
            showSecret();
            delay(timeDelay * SECRET_CODE_OFFSET);
            resetDisplay(s5, s4, s3, s2, s1, s0); 
            break;
          } else{
            delay(timeDelay);
          }
      } 
    }
  }
  
  if(DEBUG){
  Serial.println("Button Pressed");
  }
}
