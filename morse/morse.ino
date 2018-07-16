// Defined led pin
#define PIN_BUZZER 13
#define PIN_BUTTON 12
#define BUZZER_FREQUENCY 1900

// All morse delays
#define MORSE_DELAY 200
#define MORSE_DELAY_DOT (MORSE_DELAY * 1)
#define MORSE_DELAY_DASH (MORSE_DELAY * 3)
#define MORSE_DELAY_SPACE (MORSE_DELAY * 7)

// All morse characters
#define MORSE_DOT '.'
#define MORSE_DASH '-'



/**
 * All morse letters
 * @var *char[]
 */
char* MORSE_LETTERS[] = {
  ".-",     // A
  "-...",   // B
  "-.-.",   // C
  "-..",    // D
  ".",      // E
  "..-.",   // F
  "--.",    // G
  "....",   // H
  "..",     // I
  ".---",   // J
  "-.-",    // K
  ".-..",   // L
  "--",     // M
  "-.",     // N
  "---",    // O
  ".--.",   // P
  "--.-",   // Q
  ".-.",    // R
  "...",    // S
  "-",      // T
  "..-",    // U
  "...-",   // V
  ".--",    // W
  "-..-",   // X
  "-.--",   // Y
  "--.."    // Z
};



/**
 * All morse numbers
 * @var *char[]
 */
char* MORSE_NUMBERS[] = {
  "-----",   // 0
  ".----",   // 1
  "..---",   // 2
  "...--",   // 3
  "....-",   // 4
  ".....",   // 5
  "-....",   // 6
  "--...",   // 7
  "---..",   // 8
  "----."    // 9
};



/**
 * Setup function
 * Initialize communication with the serial monitor
 * @returns void
 */
void setup() {
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  // Serial.begin(9600);
}



/**
 * Loop function
 * Code runs forever until the arduino dies
 *
 * How the code figures out the position of the character:
 *
 * If you send: "Hello" it starts with "H"
 * H = 0x48 (decimal: 72)
 * A = 0x41 (decimal: 65)
 *
 * 72 - 65 = 7
 *
 * 7th in the alphabet = H
 * MORSE_LETTERS[7] = H = ....
 *
 * @returns void
 */
void loop() {

  // Current character sent from the serial
  char current;


  // Is there anything to be read from USB?
  if (Serial.available()) {

    // Read a single letter
    current = Serial.read();


    // Lower case letters
    if (current >= 'a' && current <= 'z') {
      flashSequence(MORSE_LETTERS[current - 'a']);
    }

    // Capital case letters
    else if (current >= 'A' && current <= 'Z') {
      flashSequence(MORSE_LETTERS[current - 'A']);
    }

    // Numbers
    else if (current >= '0' && current <= '9') {
      flashSequence(MORSE_NUMBERS[current - '0']);
    }

    // Space character (3500  ms)
    else if (current == ' ') {
      delay(MORSE_DELAY_SPACE);
    }


    // Print output back
    if (current == '\0') {
      Serial.println("");
    } else {
      Serial.print(current);
    }
  }
}



/**
 * Flash a sequence of characters
 * @param char* sequence
 * @returns void
 */
void buzzSequence (char* sequence) {

  // Counter
  int i = 0;

  // Loop through every character until an 'end-of-line' (null) character is found
  while (sequence[i] != '\0') {
    buzzDotOrDash(sequence[i]);
    i++;
  }

  // Delay between every sequence
  delay(MORSE_DELAY_SPACE);
}



/**
 * Flash a single character
 * @param char
 * @returns void
 */
void buzzDotOrDash (char unit) {

  // Turn led on
  tone(PIN_BUZZER, BUZZER_FREQUENCY);

  // Unit is a dot (500 ms)
  if (unit == MORSE_DOT) {
    delay(MORSE_DELAY_DOT);
  }

  // Unit is a dash (1500 ms)
  if (unit == MORSE_DASH) {
    delay(MORSE_DELAY_DASH);
  }

  // Turn led off and add a delay between a dot and dash (500)
  // Inter-element gap
  noTone(PIN_BUZZER);
  delay(MORSE_DELAY);
}


char readFromButton(){
	double t1, t2;
	char res;
	while (digitalRead(PIN_BUTTON) == HIGH) {};
	t1 = millis();
	tone(PIN_BUZZER, BUZZER_FREQUENCY);
	while (digitalRead(PIN_BUTTON) == LOW) {};
	t2 = millis() - t1;
	noTone(PIN_BUZZER);
	if (t2 < MORSE_DELAY_DOT){
		res = '.';
	} elif (t2 > MORSE_DELAY_DOT && t2 < MORSE_DELAY_DASH) {
		res = '-';
	} else {
		res = ' ';
	}
	return res;
}

char decode(char *morse){
	for(int i=0; i < sizeof(MORSE_LETTERS); i++){
		for(int j=0; j < sizeof(morse) - 1; j++){
			if(MORSE_LETTERS[i][j] != morse[j]){
				break;
			}
			if (j == (sizeof(morse) -1)){
				return MORSE_LETTERS[i]
			}
	}
}
