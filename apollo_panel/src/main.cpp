/*
Apollo inspired "control panel" handling the LCD, battery monitor and keypad.

Created: 5/10/19
Last modified: 19/10/19
*/

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <Keypad.h>

// Battery monitoring
const int battPin = A0;
uint32_t battMonitor();

// Keypad
const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns
const int debouncetime = 20;

//define the cymbols on the buttons of the keypads
const char keymap[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

const int CODE_LENGTH = 3;

byte rowPins[ROWS] = {8, 7, 6, 5};   //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 3, 2};      //connect to the column pinouts of the keypad

// //initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(keymap), rowPins, colPins, ROWS, COLS); 
// char getKey();
char keypad_read();

void setup() {
  Serial.begin(9600);
  Serial.println("Serial start up"); 
  Wire.begin();
}

byte x = 0;

void loop() {
  char keypad_output = keypad_read();
  Wire.beginTransmission(8); // transmit to device #8
  // Wire.write("x is ");        // sends five bytes
  // Wire.write(x);              // sends one byte
  // Wire.endTransmission();    // stop transmitting
  Serial.println(&keypad_output);
  // x++;
  // delay(500);
  // Wire.beginTransmission(8); // transmit to device #9
  Wire.write(&keypad_output);              
  Wire.endTransmission();    // stop transmitting
  // Serial.println(keypad_output);
}

uint32_t battMonitor()
{
  // reads and returns the voltage for battery monitoring

  int sensorValue = analogRead(battPin);
  float voltage = sensorValue * (5.0 /1023.0) * 2;  // convert the value to a true value
  // Serial.println(voltage);

  return voltage;
}

char keypad_read()
{
  char c1,c2,c3,c4;
  char tot;

  // char customKey = customKeypad.getKey();
  char customKey = customKeypad.waitForKey();

  // int code[CODE_LENGTH] = {};

  if (customKey == '*')
  {
    Serial.println("Enter code: ");
    customKey = customKeypad.waitForKey();
    if (customKey != NO_KEY)
    {
      c1 = customKey;
      Serial.print(c1);
    }
    customKey = customKeypad.waitForKey();
    if (customKey != NO_KEY)
    {
      c2 = customKey;
      Serial.print(c2);
    }
    customKey = customKeypad.waitForKey();
    if (customKey != NO_KEY)
    {
      c3 = customKey;
      Serial.println(c3);
    }
    tot = 'string';
    // ((c1-48)*100)+((c2-48)*10)+(c3-48);
    //  c1+c2+c3
   
    return tot;
  }
}

