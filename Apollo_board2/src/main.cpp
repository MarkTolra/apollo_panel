#include <Arduino.h>
#include <Wire.h>

void receiveEvent(int howMany);

// Leds (charlieplexed)
const int PIN_A = 2;
const int PIN_B = 3;
const int PIN_C = 4;
// int led_array[3][2][2] = {
//   {{PIN_A, PIN_B}, {PIN_A, PIN_C}},
//   {{PIN_B, PIN_A}, {PIN_B, PIN_C}},
//   {{PIN_C, PIN_A}, {PIN_C, PIN_B}}
// };

void led_init();
void led_control(int high_pin, int low_pin);
void reset_pins();

void setup() {
  Wire.begin(8);
  led_init();
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println("Working");

  // led_control(PIN_A, PIN_B);
  // Serial.println("A");
  // delay(1000);

  // led_control(PIN_B, PIN_C);
  // Serial.println("B");
  // delay(1000);

  // led_control(PIN_C, PIN_A);
  // Serial.println("C");
  // delay(1000);

  // led_control(PIN_A, PIN_C);
  // Serial.println("D");
  // delay(1000);
}

// function that executes whenever data is received from master
  // this function is registered as an event, see setup()
void receiveEvent(int howMany) 
{
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}

void led_init()
{
  pinMode(PIN_A, INPUT);
  pinMode(PIN_B, INPUT);
  pinMode(PIN_C, INPUT);
}

void led_control(int high_pin, int low_pin)
{
  reset_pins();

  pinMode(high_pin, OUTPUT);
  pinMode(low_pin, OUTPUT);

  digitalWrite(high_pin, HIGH);
  digitalWrite(low_pin, LOW);
}

void reset_pins()
{
  pinMode(PIN_A, INPUT);
  pinMode(PIN_B, INPUT);
  pinMode(PIN_C, INPUT);

  digitalWrite(PIN_A, LOW);
  digitalWrite(PIN_B, LOW);
  digitalWrite(PIN_C, LOW);
}