// for the 74HC595
#define clockpin 4
#define latchpin 3
#define datapin 2

// to control each Digits  
#define D1 5
#define D2 6
#define D3 7
#define D4 12
// needed for calculations
int y = 0;
int i = 0;
int number = 10;
long n = 0;
int count = 0;

//What kind of Numbers or Letters it should represent in each Digit.
byte digit[] = {
  0xFC, // 0
  0x60, // 1
  0xDA, // 2
  0xF2, // 3
  0x66, // 4
  0xB6, // 5
  0xBE, // 6
  0xE0, // 7
  0xFE, // 8
  0xF6, // 9
  0x00, //clear
};

byte digitdot[] = {  // The last digit represents the dot
  B11111101, // 0
  B01100001, // 1
  B11011011, // 2
  B11110011, // 3
  B01100111, // 4
  B10110111, // 5
  B10111111, // 6
  B11100001, // 7
  B11111111, // 8
  B11110111, // 9
  B00000000, //clear
};

void setup() {
  
  // Timer 
  // explanation: https://deepbluembedded.com/arduino-timerone-library/
  cli(); // disable interrupts

  // reset
  TCCR1A = 0; // set TCCR1A register to 0
  TCCR1B = 0; // set TCCR1B register to 0
  TCNT1  = 0; // reset counter value

  OCR1A = 15624; // compare match register

  // set prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);

  TCCR1B |= (1 << WGM12); // turn on CTC mode
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt

  sei(); // allow interrupts

  // end Timer
  
  
  pinMode(datapin, OUTPUT);
  pinMode(latchpin, OUTPUT);
  pinMode(clockpin, OUTPUT);

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  //Serial.begin(9600); // debugging in the Seriell Monitor

}

void loop() {
  digitnumber(10);     //This clears the digit (more precies numbers)
  pickDigit(3);        // Picks whitch digit is used 
  digitnumber(y % 10); //only the first digit of y is given out
  
  digitnumber(10);
  pickDigit(2);
  digitnumber((y % 100) / 10); //only the second digit is given out
  
  digitnumber(10);
  pickDigit(1);
  digitnumber((y % 1000) / 100); //only the third digit is given out
  
  digitnumber(10);
  pickDigit(0);
  digitnumber((y % 10000) / 1000); //only the fourth digit is given out



}


ISR(TIMER1_COMPA_vect) { // function which will be called when an interrupt occurs at timer 1
  y++;

   // count +1 everytime this interrupt is called
}



void pickDigit(int x) //light up a 7-segment display
{
  //The 7-segment LED display is a common-cathode one. So also use digitalWrite to  set d1 as high and the LED will go out
  // https://www.arduino.cc/reference/de/language/structure/control-structure/switchcase/
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);

  switch (x)
  {
    case 0:
      digitalWrite(D1, LOW);//Light d1 up
      break;
    case 1:
      digitalWrite(D2, LOW); //Light d2 up
      break;
    case 2:
      digitalWrite(D3, LOW); //Light d3 up
      break;
    case 3:
      digitalWrite(D4, LOW); //Light d4 up
      break;
  }
}

void digitnumber(int i) { // can be written as a function
  switch (i) {
    case 0:
      digitalWrite(latchpin, LOW);                     // makes sure the shiftregistry doesn't gives out anything
      shiftOut(datapin, clockpin, LSBFIRST, digit[0]); // gives out the byte to the shiftregistery
      digitalWrite(latchpin, HIGH);                    // gives out what is stored in the registry
      break;

    case 1:
      digitalWrite(latchpin, LOW);
      shiftOut(datapin, clockpin, LSBFIRST, digit[1]);
      digitalWrite(latchpin, HIGH);
      break;

    case 2:
      digitalWrite(latchpin, LOW);
      shiftOut(datapin, clockpin, LSBFIRST, digit[2]);
      digitalWrite(latchpin, HIGH);
      break;

    case 3:
      digitalWrite(latchpin, LOW);
      shiftOut(datapin, clockpin, LSBFIRST, digit[3]);
      digitalWrite(latchpin, HIGH);
      break;

    case 4:
      digitalWrite(latchpin, LOW);
      shiftOut(datapin, clockpin, LSBFIRST, digit[4]);
      digitalWrite(latchpin, HIGH);
      break;

    case 5:
      digitalWrite(latchpin, LOW);
      shiftOut(datapin, clockpin, LSBFIRST, digit[5]);
      digitalWrite(latchpin, HIGH);
      break;

    case 6:
      digitalWrite(latchpin, LOW);
      shiftOut(datapin, clockpin, LSBFIRST, digit[6]);
      digitalWrite(latchpin, HIGH);
      break;

    case 7:
      digitalWrite(latchpin, LOW);
      shiftOut(datapin, clockpin, LSBFIRST, digit[7]);
      digitalWrite(latchpin, HIGH);
      break;

    case 8:
      digitalWrite(latchpin, LOW);
      shiftOut(datapin, clockpin, LSBFIRST, digit[8]);
      digitalWrite(latchpin, HIGH);
      break;

    case 9:
      digitalWrite(latchpin, LOW);
      shiftOut(datapin, clockpin, LSBFIRST, digit[9]);
      digitalWrite(latchpin, HIGH);
      break;

    case 10:
      digitalWrite(latchpin, LOW);
      shiftOut(datapin, clockpin, LSBFIRST, digit[10]);
      digitalWrite(latchpin, HIGH);
      break;




  }

}
