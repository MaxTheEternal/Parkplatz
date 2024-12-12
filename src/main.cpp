#include <Arduino.h>
#include <FastLED.h> 
#include <parkingLights.h>
#include <Display.h>
#include <EinAusgang.h>

#define NUM_LEDS 51
#define LED_PIN     13  // Pin connected to the LED strip
#define CHIPSET     WS2812B
#define COLOR_ORDER GRB



CRGB leds[NUM_LEDS];

const int dataPin = A0;   /* Q7 */
const int clockPin = A2;  /* CP */
const int latchPin = A1;  /* PL */
const int clockInhibit = A5;


 
const int numBits = 40;   /* Set to 8 * number of shift registers */

int sensorToLedMapping[numBits] = {12, 10, 1, 2, 22, 23, 11, 13, 3, 4, 5, 7, 16, 15, 18, 14, 21, 20, 19, 28, 32, 33, 34, 25, 35, 42, 31, 30, 49, 46, 47, 37, 41, 40, 39, 38, 50, 43, 51, 48};

int freeSpaces = 30;

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

  EinAusGang::setup();

}
 
void loop() {
  // Step 1: Sample
  digitalWrite(latchPin, LOW);
  delay(50);
  digitalWrite(latchPin, HIGH);
  delay(50);

  int count = 0;
 
  // Step 2: Shift
  Serial.print("Bits: ");
  for (int i = 0; i < numBits; i++) {
    digitalWrite(clockPin, LOW);
    delayMicroseconds(5);
    int bit = digitalRead(dataPin);
    // Serial.print(i);
    // Serial.print(":");
    if (bit == HIGH) {
      leds[sensorToLedMapping[i]-1] = CRGB::Black;
      // Serial.print("0");
    } else {

      // Serial.print("1");
      leds[sensorToLedMapping[i]-1] = CRGB::Green;

      count++;
    }
    Serial.print(" ");
    digitalWrite(clockPin, HIGH); // Shift out the next bit
    delayMicroseconds(5);
  }

  // greenPath(count);
  display::displayNumber(count);
  FastLED.show();
  Serial.print(" Count: ");
  Serial.print(count);
  Serial.print("\n");

}
