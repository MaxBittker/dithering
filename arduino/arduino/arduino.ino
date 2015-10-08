/*------------------------------------------------------------------------
  Example sketch for Adafruit Thermal Printer library for Arduino.
  Demonstrates some of the available alternate characters.
  See 'A_printertest' sketch for a more generalized printing example.

  THESE FEATURES ARE NOT AVAILABLE ON ALL PRINTERS.  Older firmware
  does not support the alternate characters used here.
  ------------------------------------------------------------------------*/

#include "Adafruit_Thermal.h"

// Here's the syntax when using SoftwareSerial (e.g. Arduino Uno) --------
// If using hardware serial instead, comment out or remove these lines:



#include "stdlib.h"



#include "SoftwareSerial.h"
#define TX_PIN 6 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor
// Then see setup() function regarding serial & printer begin() calls.

// Here's the syntax for hardware serial (e.g. Arduino Due) --------------
// Un-comment the following line if using hardware serial:

//Adafruit_Thermal printer(&Serial1);      // Or Serial2, Serial3, etc.

// -----------------------------------------------------------------------

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))
#define COLUMNS 32

uint8_t c = ( 2 << 4 ) | 0;
uint8_t b = ( rand() % 16 << 4 ) | rand() % 16;

int row[COLUMNS + 2] = { 0 };
int rules[] = {
  30,
  90,
  94,

  18,
  22,
  26,
  28,
  30,
  45,
  47,
  50,
  54,
  57,
  60,
  62,
  69,
  73,
  75,
  77,
  89
};

uint8_t rule = rand() % 255; //26;

void setup() {
  randomSeed(analogRead(0));

  Serial.begin(9600);
  // This line is for compatibility with the Adafruit IotP project pack,
  // which uses pin 7 as a spare grounding point.  You only need this if
  // wired up the same way (w/3-pin header into pins 5/6/7):
  pinMode(7, OUTPUT); digitalWrite(7, LOW);

  mySerial.begin(19200);  // Initialize SoftwareSerial

  printer.begin();        // Init printer (same regardless of serial type)
  //  printer.setDefault();
  //  printer.setCodePage(CODEPAGE_KATAKANA);
  // Restore printer to defaults
  //  printer.justify('C');
  printer.setLineHeight(0);
  //printer.setCodePage(CODEPAGE_KATAKANA);

  //  printer.setCodePage(CODEPAGE_WCP1253);

  row[15] = 1;
}

// Print charset map to printer, similar to test page but
// without the baud rate, etc.

int iteration = 0, index = 5;

void reset(int rule) {
  memset(row, 0, sizeof(row));
  row[15] = 1;
  //    printer.print(F("---------- "));
  //    printer.println(F(sprintf(str, "%d", rule);));

  Serial.print("---------- ");
  Serial.print(rule);
  Serial.println();
}

int next(uint8_t rule, int left, int middle, int right) {
  int control = (left << 2) + (middle << 1) + right;

  return !!(rule & (1 << control));
}

void print_row() {

  b++;
  //  uint8_t c = ( rand()%16 << 4 ) | rand()%16;

  int i;
  for (i = 1; i < COLUMNS ; i++) {

    if (row[i] == 0) {
      //      printer.print(F(" "));

      printer.write(c);
      Serial.print(" ");
    } else {
      printer.write(b);

      //      printer.print(F("@"));
      Serial.print("#");
    }
  }
  printer.println(F(" "));
  Serial.println();
}

void loop() {
  if (++iteration > 16) {
    iteration = 0;
    index++;
    rule = rand() % 255; //rules[index];
    b = ( rand() % 16 << 4 ) | rand() % 16;
    printer.setCodePage(rand() % 45);

    reset(rule);
    return;

  }

  index = index % ARRAY_LENGTH(rules);

  print_row();

  //  delay(1000);

  int newrow[COLUMNS + 2] = { 0 };
  int changed = 0;
  for (int i = 1; i < 33; i++) {
    newrow[i] = next(rule, row[i - 1], row[i], row[i + 1]);
    if (newrow[i] != row[i])
    { changed ++;
    }

  }

  memcpy(row, newrow, sizeof(newrow));

  for (int i = 0; i < COLUMNS + 2; i++) {
    row[i] = newrow[i];
  }
  if (changed == 0)
  {
    iteration = 100;
  }
  if (Serial.available()) {
    uint8_t incomingByte = Serial.read();
    while (true) {
      delay(10000000000);
    }
  }
}


