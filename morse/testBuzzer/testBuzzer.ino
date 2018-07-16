#define BUZZER_PIN1 5
#define BUZZER_PIN2 9
#define BUZZER_PIN3 10
#define BUZZER_PIN4 11
#define LED_PIN 6
#define BUTTON_PIN 12
#define TIME 10
#define FREQ 440 * 2


int Buzzers[4] = {BUZZER_PIN1, BUZZER_PIN2, BUZZER_PIN3, BUZZER_PIN4};

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  for(int index = 0; index < 4; index++){
      pinMode(Buzzers[index], OUTPUT);
    }
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == LOW) {
    digitalWrite(LED_PIN, HIGH);
    for(int index = 0; index < 4; index++){
      tone(Buzzers[index], FREQ, TIME);
      delay(TIME);
      noTone(Buzzers[index]);
    }
    digitalWrite(LED_PIN, LOW);
  } 
}
