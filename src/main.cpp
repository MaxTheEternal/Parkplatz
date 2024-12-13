#include <Arduino.h>
#include <FastLED.h>
#include <parkingLights.h>
#include <Display.h>
#include <EinAusgang.h>
#include <List.hpp>

#define NUM_LEDS 51
#define LED_PIN 13 // Pin connected to the LED strip
#define CHIPSET WS2812B
#define COLOR_ORDER GRB

#define PARKPLATZ_FREI 0
#define PARKPLATZ_BELEGT 1
#define PARKPLATZ_RESERVIERT

CRGB leds[NUM_LEDS];

const int dataPin = A0;  /* Q7 */
const int clockPin = A2; /* CP */
const int latchPin = A1; /* PL */
const int clockInhibit = A5;

const int eingangSensor = 0;
const int ausgangSensor = 1;

const int numBits = 40; /* Set to 8 * number of shift registers */
const int numParkplaetze = 30;

int sensorToLedMapping[numBits] = {11, 9, 0, 1, 21, 22, 10, 12, 2, 3, 4, 6, 15, 14, 17, 13, 20, 19, 18, 27, 31, 32, 33, 24, 34, 41, 30, 29, 48, 45, 46, 36, 40, 39, 38, 37, 49, 42, 50, 47};

List<Parkplatz::Parkplatz> carsGoingRound;
int freeSpaces = numParkplaetze;

// 0 = Frei; 1 == besetzt; 2 = reserviert
int zustandParkplaetze[numParkplaetze] = {0};

void turnRedParkingSpaces(int i, bool taken);
int findParkplatz();
void readSensors();
void turnOffLedsAfterCar(int sensorIndex);
void turnOnLedsToParkplatz(int autoIndex);

void setup()
{
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

  pinMode(eingangSensor, INPUT);
  pinMode(ausgangSensor, OUTPUT);
  EinAusGang::setup();
}

void loop()
{

  if (digitalRead(eingangSensor))
  {
    // Check freie plätze
    if (freeSpaces > 0)
    {
      freeSpaces--;
      //  Schranke hoch
      EinAusGang::EingangOeffnen();

      //  finde Parkplatz
      int platz = findParkplatz();
      carsGoingRound.add(Parkplatz::allePlaetze[platz]);
      turnOnLedsToParkplatz(platz);
    }
  }

  if (digitalRead(ausgangSensor))
  {
    freeSpaces++;
    if (freeSpaces > 30)
    {
      freeSpaces = 30;
    }
    EinAusGang::AusgangOeffnen();
  }

  //  Auto zu liste an Autos hinzufügen

  readSensors();
  display::displayNumber(freeSpaces);
  EinAusGang::checkSchrankeSchliessen();
}

void turnRedParkingSpaces(int i, bool taken)
{
  // Achtung hier wird 0 basiert gezählt
  switch (i)
  {
  case 1:
  case 6:
  case 11:
  case 13:
  case 24:
  case 29:
  case 27:
  case 25:
  case 19:
  case 14:
    break;
  default:
    if (taken)
    {
      leds[sensorToLedMapping[i]] = CRGB::Red;
    }
    else
    {
      leds[sensorToLedMapping[i]] = CRGB::Black;
    };
    break;
  }
}

int findParkplatz()
{
  for (int i = 0; i < numParkplaetze; i++)
  {
    if (zustandParkplaetze[i] == PARKPLATZ_FREI)
    {
      zustandParkplaetze[i] = PARKPLATZ_RESERVIERT;
      return i;
    }
  }
  return -1;
}

void readSensors()
{
  digitalWrite(latchPin, LOW);
  delay(50);
  digitalWrite(latchPin, HIGH);
  delay(50);

  int count = 0;

  // Shift
  Serial.print("Bits: ");
  for (int i = 0; i < numBits; i++)
  {
    digitalWrite(clockPin, LOW);
    delayMicroseconds(5);
    int bit = digitalRead(dataPin);
    // Sensor false
    if (bit == HIGH)
    {
      if (zustandParkplaetze[i] == PARKPLATZ_BELEGT)
      {
        turnRedParkingSpaces(i, false);
      }
    }
    // Sensor true
    else
    {

      if (zustandParkplaetze[i] == PARKPLATZ_RESERVIERT)
      {
        zustandParkplaetze[i] == PARKPLATZ_BELEGT;
        turnRedParkingSpaces(i, false);
      }
      turnOffLedsAfterCar(i);
      turnRedParkingSpaces(i, true);
      count++;
    }
    Serial.print(" ");
    digitalWrite(clockPin, HIGH); // Shift out the next bit
    delayMicroseconds(5);
  }

  FastLED.show();
  Serial.print(" Count: ");
  Serial.print(count);
  Serial.print("\n");
}

void turnOffLedsAfterCar(int sensorIndex)
{
  for (int i = 0; i < carsGoingRound.getSize(); i++)
  {
    Parkplatz::Parkplatz curCar = carsGoingRound.get(i);
    for (int j = 0; j < curCar.length; j++)
    {
      if (sensorIndex == curCar.sensorPfad[j])
      {
        leds[curCar.ledPfad[j]] = CRGB::Black;
      }
    }
  }
}

void turnOnLedsToParkplatz(int autoIndex)
{
  Parkplatz::Parkplatz target = Parkplatz::allePlaetze[autoIndex];
  for (int i = 0; i < target.length; i++)
  {

    leds[target.ledPfad[i]] = CRGB::Green;
  }
}