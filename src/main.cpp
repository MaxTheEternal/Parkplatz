#include <Arduino.h>
#include <FastLED.h> 
#include <List.hpp>
#include "ParkingNode.h"

using namespace std;

#define NUM_LEDS 51
#define LED_PIN     13  // Pin connected to the LED strip
#define CHIPSET     WS2812B
#define COLOR_ORDER GRB

#define DISPLAY_RCLK A4 // RCLK Pin
#define DISPLAY_SRCLK A5 // SRCLK Pin
#define DISPLAY_SER A3 // SER Pin

CRGB leds[NUM_LEDS];

const int dataPin = A0;   /* Q7 */
const int clockPin = A2;  /* CP */
const int latchPin = A1;  /* PL */
const int clockInhibit = A5;
 
const int numBits = 40;   /* Set to 8 * number of shift registers */


void displayNumber (int number){
  uint16_t firstDigitEncoding[] = 
  {0b1000111100011111,//0
  0b1110111111011111,//1
  0b0100111100111111,//2
  0b0100111110011111,//3
  0b0010111111011111//4
  };
  uint16_t lastDigitEncoding[] =  
  {0b1111100011101001,//0
  0b1111111011111101,//1
  0b1111010011101011,//2
  0b1111010011111001,//3
  0b1111001011111101,//4
  0b1111000111111001,//5
  0b1111000111101001,//6
  0b1111110011111101,//7
  0b1111000011101001,//8
  0b1111000011111001//9
  };
  byte lastDigit = number%10;
  byte firstDigit = (number/10)%10;

  int data = firstDigitEncoding[firstDigit] & lastDigitEncoding[lastDigit];

  digitalWrite(DISPLAY_RCLK, LOW);
  shiftOut(DISPLAY_SER, DISPLAY_SRCLK, LSBFIRST, (data >> 8) & 0xff);
  shiftOut(DISPLAY_SER, DISPLAY_SRCLK, LSBFIRST, data  & 0xff);
  digitalWrite(DISPLAY_RCLK, HIGH);
}

// byte toByte(int value) {
//     return (value >= 0 && value <= 255) ? static_cast<byte>(value) : 0;
// }

void setup() {
  // LED Setup
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(50);

  pinMode(DISPLAY_RCLK, OUTPUT);
  pinMode(DISPLAY_SRCLK, OUTPUT);
  pinMode(DISPLAY_SER, OUTPUT);
  // Sensor Setup
  Serial.begin(115200);

  pinMode(dataPin, INPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockInhibit, OUTPUT);

  

}
 
void loop() {
  // Step 1: Sample
  digitalWrite(latchPin, LOW);
  delay(50);
  digitalWrite(latchPin, HIGH);
  delay(50);

  bool sensorArray[numBits] = {false};
  int count = 0;
 
  // Step 2: Shift
  Serial.print("Bits: ");
  for (int i = 0; i < numBits; i++) {
    digitalWrite(clockPin, LOW);
    delayMicroseconds(5);
    int bit = digitalRead(dataPin);
    Serial.print(i);
    Serial.print(":");
    if (bit == HIGH) {
      sensorArray[i] = false;
      leds[i] = CRGB::Black;
      Serial.print("0");
    } else {

      sensorArray[i] = true;
      Serial.print("1");
      leds[i] = CRGB::Green;

      count++;
    }
    Serial.print(" ");
    digitalWrite(clockPin, HIGH); // Shift out the next bit
    delayMicroseconds(5);
  }

   displayNumber(count);
  FastLED.show();
  Serial.print(" Count: ");
  Serial.print(count);
  Serial.print("\n");

}

