/*
 * marcador
 * 
 * Sketch to control a scoring board. 
 * 
 * Inputs are 3 momentary buttons (left, right, and reset). 
 * Outputs are 2 digits in a 4-digit 7-segment display. 
 * 
 * At the start, and when pressing resetm the score is 0-0. 
 * Pressing the left button increases the left score. 
 * Pressing the right button increases the right score. 
 */

/*
 * Constants
 */

// Number of digits
const int NDIGITS = 10;

// Number of segments
const int NSEGMENTS = 7; 

// Default delay in milliseconds
const int DELAY = 200; 

/*
   These arrays will define how the digits 0-9 are
   represented in terms setting each of the 7 segments
   HIGH and LOW. 
   In this 7-segment display, each segment is controlled 
   as follows:

                         seg11

                   seg10       seg7

                         seg5

                   seg1        seg4

                         seg2
*/

const int digits[NDIGITS][NSEGMENTS] = {
  {HIGH, HIGH, HIGH,  LOW, HIGH, HIGH, HIGH},
  {LOW,  LOW,  HIGH,  LOW, HIGH, LOW,  LOW},
  {HIGH, HIGH, LOW,  HIGH, HIGH, LOW,  HIGH},
  {LOW,  HIGH, HIGH, HIGH, HIGH, LOW,  HIGH},
  {LOW,  LOW,  HIGH, HIGH, HIGH, HIGH,  LOW},
  {LOW,  HIGH, HIGH, HIGH, LOW, HIGH,  HIGH},
  {HIGH, HIGH, HIGH, HIGH, LOW, HIGH,  HIGH},
  {LOW,  LOW,  HIGH,  LOW, HIGH, LOW,  HIGH},
  {HIGH, HIGH, HIGH,  HIGH, HIGH, HIGH, HIGH},
  {LOW,  HIGH, HIGH,  HIGH, HIGH, HIGH, HIGH},
};


// We also need a symbol to clear all segments:
const int EMPTY[NSEGMENTS] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW};

/*
 * Variables
 */

// Pins  control the 7-segment digits
int seg1;
int seg2;
int seg4;
int seg5;
int seg7;
int seg10;
int seg11;

// Pins to control the "channel" 
// I.e. if the displayed digit is the one at the left or right 
int selectLeft; 
int selectRight; 

// Pins to control the buttons
int btnLeft;
int btnRight;
int btnReset;

// Buttons and digit states

int buttonLeftState; 
int buttonLeftLastState; 
int currentDigitLeft; 

int buttonRightState; 
int buttonRightLastState; 
int currentDigitRight; 

int buttonResetState; 
int buttonResetLastState; 


/*
 * ************************
 * START AND LOOP FUNCTIONS
 * ************************
 */

/*
 * setup: Specifies what to do at startup. 
 */
void setup() {

  // Assign 7 segments to pins
  seg1  = 2;
  seg2  = 3;
  seg4  = 4;
  seg5  = 5;
  seg7  = 6;
  seg10 = 7;
  seg11 = 8;

  // Assign channels to pins
  selectLeft  = 11; 
  selectRight = 12; 

  // Assign buttons to pins
  btnLeft  = 10;
  btnRight = 13;
  btnReset  = 9;  

  // Init button states
  buttonLeftState = 0; 
  buttonLeftLastState = 0; 
  currentDigitLeft = 0; 

  buttonRightState = 0; 
  buttonRightLastState = 0; 
  currentDigitRight = 0; 
  
  buttonResetState = 0; 
  buttonResetLastState = 0; 

  // Set pin modes.
  // These are the 7 segment pins, thus --> output.  
  pinMode (seg1,  OUTPUT); 
  pinMode (seg2,  OUTPUT); 
  pinMode (seg4,  OUTPUT); 
  pinMode (seg5,  OUTPUT); 
  pinMode (seg7,  OUTPUT); 
  pinMode (seg10, OUTPUT); 
  pinMode (seg11, OUTPUT);

  // 4-digit controller
  pinMode(selectLeft,  OUTPUT);
  pinMode(selectRight, OUTPUT);
  
  // Buttons
  pinMode (btnLeft, INPUT);
  pinMode (btnRight, INPUT);
  pinMode (btnReset, INPUT);

   // Init
   digitalWrite(selectLeft,  HIGH); 
   digitalWrite(selectRight, HIGH); 

   // Demo (so that user sees all numbers are displayed correctly)
   fulldemo(DELAY); 
}

/*
 * loop: Specifies which action to repeat after startup  
 */

void loop() {

  const int deltaBtn = 50; // Delay for pushbutton event
  const int deltaMux = 10; // Delay for digit multiplexing

  // Read button states
  buttonLeftState  = digitalRead(btnLeft);
  buttonRightState = digitalRead(btnRight);
  buttonResetState = digitalRead(btnReset);

  // If left button changed state, i.e. pressed
  if (buttonLeftState != buttonLeftLastState) {
    if (buttonLeftState == HIGH) {
      currentDigitLeft++; // Increase left digit value
      if (currentDigitLeft == NDIGITS) {
        currentDigitLeft = 0; // Set back to 0 after9
      }
    }
    delay(deltaBtn); 
  }

  // If right button changed state, i.e. pressed
  if (buttonRightState != buttonRightLastState) {
    if (buttonRightState == HIGH) {
      currentDigitRight++; // Increase right value
      if (currentDigitRight == NDIGITS) {
        currentDigitRight = 0; // Set back to 0 after 9
      }
    }
    delay(deltaBtn); 
  }
  
  // Record last states 
  buttonLeftLastState  = buttonLeftState; 
  buttonRightLastState = buttonRightState; 

  // If reset button changed state (e.g. pressed)  
  if (buttonResetState != buttonResetLastState) {
    if (buttonResetState == HIGH) {
      currentDigitLeft  = 0; // Set everything to 0
      currentDigitRight = 0;       
    }
    delay(deltaBtn);
  }
  buttonResetLastState = buttonResetState; // Record state

  // Now write the digits which correspond to current values
  
  // Select left channel and print
  digitalWrite(selectRight, HIGH); 
  digitalWrite(selectLeft,  LOW); 
  print(currentDigitLeft);
  delay(deltaMux);  
  
  // Select right channel and print
  digitalWrite(selectLeft, HIGH);
  digitalWrite(selectRight, LOW); 
  print(currentDigitRight);
  delay(deltaMux);  

}

/*
 * *****************
 * Utility functions
 * *****************
 */

 
/*
 * print7
 * 
 * Print a 7-segment digit to the current channel. 
 * 
 *     arr: Array of int containing the HIGH/LOW values of each segment in 
 *     ascending order (seg1, ...seg 11). 
 */
void print7(int* arr) {
  digitalWrite(seg1,  arr[0]);
  digitalWrite(seg2,  arr[1]);
  digitalWrite(seg4,  arr[2]);
  digitalWrite(seg5,  arr[3]);
  digitalWrite(seg7,  arr[4]);
  digitalWrite(seg10, arr[5]);
  digitalWrite(seg11, arr[6]);
}

/*
 * print
 * 
 * Print digit to current channel. 
 *     n: Digit to print. 
 */
void print(int n) {
  print7(digits[n]);
}

/*
 * clear
 * 
 * Clear digit segments. 
 */
void clear() {
  print7(EMPTY);
} 

/*
 * demo
 * 
 * Show demo (sweep numbers from 0 to 9 in current channel). 
 * 
 *     delta: delay between numbers (milliseconds) 
 */
void demo(int delta) {

  for (int i=0; i<NDIGITS; i++) {
    print(i); 
    delay(delta); 
  }
  clear();
  delay(delta);
  
}

/*
 * fulldemo
 * 
 * Sweep between numbers 0-9 first in left channel and then 
 * in the right channel. 
 * 
 *     delta: delay between numbers (milliseconds)
 */
void fulldemo(int delta) {

  digitalWrite(selectRight, HIGH); 
  digitalWrite(selectLeft,  LOW); 

  demo(delta); 

  digitalWrite(selectRight, LOW); 
  digitalWrite(selectLeft,  HIGH);
  demo(delta);  
  
  digitalWrite(selectRight, HIGH); 
  digitalWrite(selectLeft,  HIGH); 

}
