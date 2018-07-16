// constants won't change. They're used here to set pin numbers:
const int button1 = A0;     // the number of the pushbutton pin
const int button2 = A1;     // the number of the pushbutton pin
const int button3 = A2;     // the number of the pushbutton pin
const int button4 = A3;     // the number of the pushbutton pin
const int button5 = A4;     // the number of the pushbutton pin
//const int buttonT3 = A5;     // the number of the pushbutton pin

// variables will change:
int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;         // variable for reading the pushbutton status
int buttonState3 = 0;         // variable for reading the pushbutton status
int buttonState4 = 0;         // variable for reading the pushbutton status
int buttonState5 = 0;         // variable for reading the pushbutton status
//int buttonStateT3 = 0;         // variable for reading the pushbutton status

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  pinMode(button5, INPUT_PULLUP);
//  pinMode(buttonT3, INPUT_PULLUP);
  lcd.begin(16, 2);
	// Serial.begin(9600);
}

int readButtons() {
  int value = 0;
  buttonState1 = digitalRead(button1);
  buttonState2 = digitalRead(button2);
  buttonState3 = digitalRead(button3);
  buttonState4 = digitalRead(button4);
  buttonState5 = digitalRead(button5);
//  buttonStateT3 = digitalRead(buttonT3);
  // Serial.println("---");
  // Serial.print(buttonState1);
  // Serial.print(buttonState2);
  // Serial.print(buttonState3);
  // Serial.print(buttonStateT1);
  // Serial.print(buttonStateT2);
  // Serial.print(buttonStateT3);
  // Serial.println("---");
  if (buttonState1 == HIGH) {
    value = value | 1;
  }
  if (buttonState2 == HIGH) {
    value = value | (1 << 1);
  }
  if (buttonState3 == HIGH) {
    value = value | (1 << 2);
  }
  if (buttonState4 == HIGH) {
    value = value | (1 << 3);
  }
  if (buttonState5 == HIGH) {
    value = value | (1 << 4);
  }
  return value;
}

String valueToHint(int val){
  String res = "";
  switch(val) {
    case 0:
      res = "No points";
      break;
    case 1:
      res = "One and only";
      break;
    case 2:
      res = "Two low";
      break;
    case 3:
      res = "Three-zy";
      break;
    case 4:
      res = "I can do that four sure";
      break;
    case 5:
      res = "Fiver";
      break;
    case 6:
      res = "Six";
      break;
    case 7:
      res = "seven ate nine";
      break;
    case 8:
      res = "ate nine";
      break;
    case 9:
      res = "Nine";
      break;
    case 10:
      res = "no-pun-in-ten-did";
      break;
    case 11:
      res = "Eleven";
      break;
    case 12:
      res = "Twelve";
      break;
    case 13:
      res = "Jippie! 1234";
      break;
    case 14:
      res = "Ten-four";
      break;
    case 15:
      res = "Fifteen";
      break;
    case 16:
      res = "Sixteen";
      break;
    case 17:
      res = "Seventeen";
      break;
    case 18:
      res = "Eighteen";
      break;
    case 19:
      res = "Nineteen";
      break;
    case 20:
      res = "Twenty";
      break;
    case 21:
      res = "Twentyone";
      break;
    case 22:
      res = "Twentytwo";
      break;
    case 23:
      res = "Twentythree";
      break;
    case 24:
      res = "Twentyfour";
      break;
    case 25:
      res = "Twentyfive";
      break;
    case 26:
      res = "Twentysix";
      break;
    case 27:
      res = "Twentyseven";
      break;
    case 28:
      res = "Twentyeight";
      break;
    case 29:
      res = "Twentynine";
      break;
    case 30:
      res = "Thirty";
      break;
    case 31:
      res = "Thirtyone";
      break;
    default:
      res = "No Answer";
      break;
  }
  return res;
}

int value;
int oldValue;
String answer;

void loop() {
  // read the state of the pushbutton value:
  value = readButtons();
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (value != oldValue) {
    lcd.clear();
    answer = valueToHint(value);
    if ( answer.length() > 16){
      lcd.setCursor(0, 0);
      lcd.print(answer.substring(0,15));
      lcd.setCursor(0, 1);
      lcd.print(answer.substring(16,answer.length() - 1));
    } else {
      lcd.setCursor(0, 0);
      lcd.print(answer);
    }
    oldValue = value;
  }
  // Serial.println(value);
	delay(10);
}
