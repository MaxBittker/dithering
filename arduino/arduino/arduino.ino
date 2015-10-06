

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


int incomingByte = 0;   // for incoming serial data
int i = 0;

void setup() {
  randomSeed(analogRead(0));

  Serial.begin(9600);
  // This line is for compatibility with the Adafruit IotP project pack,
  // which uses pin 7 as a spare grounding point.  You only need this if
  // wired up the same way (w/3-pin header into pins 5/6/7):
  pinMode(7, OUTPUT); digitalWrite(7, LOW);

  mySerial.begin(19200);  // Initialize SoftwareSerial

  printer.begin();        // Init printer (same regardless of serial type)
 printer.setDefault();
  printer.setCodePage(CODEPAGE_KATAKANA);
   // Restore printer to defaults
  printer.justify('C');
}

// Print charset map to printer, similar to test page but
// without the baud rate, etc.


void loop() {
  //          int r = rand()%2;
  //          if(r==1)
  //          {
  //            printer.write(92);
  //          }
  //          else{
  //            printer.write(47);
  //          }
//  printer.write(i);
  i++;
  //          if (Serial.available() > 0) {
  //                // read the incoming byte:
  //                incomingByte = Serial.read();
  //                printer.write(incomingByte);
  //
  //
  //                // say what you got:
  //                Serial.print("I received: ");
  //                Serial.println(incomingByte, DEC);
  //        }

}
