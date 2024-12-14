#include <Arduino.h>
#include <FastLED.h>
#include <parkingLights.h>
#include <Display.h>
#include <EinAusgang.h>
#include <List.hpp>

#define NUM_LEDS 51
#define LED_PIN 12 // Pin connected to the LED strip
#define CHIPSET WS2812B
#define COLOR_ORDER GRB

#define PARKPLATZ_FREI 0
#define PARKPLATZ_BELEGT 1
#define PARKPLATZ_RESERVIERT 2
#define PARKPLATZ_VERLASSEN 3

#define DATA_PIN 4
#define CLOCK_PIN 17
#define LATCH_PIN 16
#define AUSGANG_SENSOR 39
#define EINGANG_SENSOR 36

CRGB leds[NUM_LEDS];

const int numBits = 40; /* Set to 8 * number of shift registers */
const int numParkplaetze = 30;

// int sensorToLedMapping[numBits] = {11, 9, 0, 1, 21, 22, 10, 12, 2, 3, 4, 6, 15, 14, 17, 13, 20, 19, 18, 27, 31, 32, 33, 24, 34, 41, 30, 29, 48, 45, 46, 36, 40, 39, 38, 37, 49, 42, 50, 47};

List<Parkplatz::Parkplatz> carsGoingRound;
int freeSpaces = numParkplaetze;

int zustandParkplaetze[numParkplaetze] = {0};

void turnRedParkingSpaces(int i, bool taken);
int findParkplatz();
void readSensors();
void turnOffLedsAfterCar(int sensorIndex);
void turnOnLedsToParkplatz(int autoIndex);
void SchrankenSchliessen();
void ParkplatzZustandSetzen(int i, bool sensorAn);
int FreiePlaetze();
void PlatzFreiMachen();

  

  unsigned long eingangGEoeffnetZeit = 0; // Tracks the last time the servo moved
  unsigned long ausgangGeoggnetZeit = 0;  // Tracks the last time the servo moved

  bool eingangOffen = false;
  bool ausgangOffen = false;

  unsigned long delayTime = 5000; // Time to wait in milliseconds (5 seconds)

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

  pinMode(DATA_PIN, INPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);

  pinMode(EINGANG_SENSOR, INPUT);
  pinMode(AUSGANG_SENSOR, INPUT);
  EinAusGang::setup();
}

void loop()
{
  if(digitalRead(EINGANG_SENSOR) == LOW){
    Serial.println("Eingang Sensor ");
  }
  if(digitalRead(AUSGANG_SENSOR) == LOW){
    Serial.println("Ausgang Sensor");
  }

  if (digitalRead(EINGANG_SENSOR) == LOW && !eingangOffen)
  {
    // Check freie plaetze
    if (FreiePlaetze() > 0)
    {
      //  finde Parkplatz
      int platz = findParkplatz();
      if (platz != -1) {

          //  Schranke hoch
        Serial.println("Eingang Öffnen");
        EinAusGang::EingangOeffnen();
        eingangGEoeffnetZeit = millis();
        eingangOffen = true;

        //  Auto zu liste an Autos hinzufügen
        carsGoingRound.add(Parkplatz::allePlaetze[platz]);
        turnOnLedsToParkplatz(platz);
      }
    }
  }

  if (digitalRead(AUSGANG_SENSOR) == LOW && !ausgangOffen)
  {
    ausgangGeoggnetZeit = millis();
    ausgangOffen = true;
    Serial.println("Ausgang Öffnen");
    EinAusGang::AusgangOeffnen();
  }


  readSensors();
  display::displayNumber(FreiePlaetze());
  SchrankenSchliessen();
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
  digitalWrite(LATCH_PIN, LOW);
  delay(50);
  digitalWrite(LATCH_PIN, HIGH);
  delay(50);

  // Shift
  // Serial.print("Bits: ");
  for (int i = 0; i < numBits; i++)
  {
    digitalWrite(CLOCK_PIN, LOW);
    delayMicroseconds(5);
    int bit = digitalRead(DATA_PIN);

    // Sensor false
    if (bit == HIGH)
    {
      ParkplatzZustandSetzen(i, false);
    }
    // Sensor true
    else
    {
      turnOffLedsAfterCar(i);
      ParkplatzZustandSetzen(i, true);
    }
    // Serial.print(" ");
    digitalWrite(CLOCK_PIN, HIGH); // Shift out the next bit
    delayMicroseconds(5);
  }

  FastLED.show();
  // Serial.print(" Count: ");
  // Serial.print(count);
  // Serial.print("\n");
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


void SchrankenSchliessen(){
  if (eingangOffen && millis() >= eingangGEoeffnetZeit + delayTime) {
    eingangOffen = false;
    EinAusGang::EingangSchliessen();
  }

  if (ausgangOffen && millis() >= ausgangGeoggnetZeit + delayTime) {
    ausgangOffen = false;
    EinAusGang::AusgangSchliessen();
  }
}


  void ParkplatzZustandSetzen(int i, bool sensorAn) {
  int platz = Parkplatz::SensorToParkplatz[i];
  if (platz == -1) {
    return;
  }
  if (sensorAn) {
      if (zustandParkplaetze[platz] == PARKPLATZ_RESERVIERT)
      {
        zustandParkplaetze[platz] = PARKPLATZ_BELEGT;
        leds[Parkplatz::ParkplatzToLed[platz]] == CRGB::Red;
      } else if (zustandParkplaetze[platz] == PARKPLATZ_VERLASSEN){
        zustandParkplaetze[platz] = PARKPLATZ_BELEGT;
        leds[Parkplatz::ParkplatzToLed[platz]] == CRGB::Red;
      }
 } else {
      if (zustandParkplaetze[platz] == PARKPLATZ_BELEGT)
      {
        zustandParkplaetze[platz] = PARKPLATZ_VERLASSEN;
        leds[Parkplatz::ParkplatzToLed[platz]] == CRGB::Black;
      }
  }

 }

 int FreiePlaetze() {
  int count = 0;
  for(int i = 0; i < numParkplaetze; i++){
    if (zustandParkplaetze[i] == PARKPLATZ_FREI) {
      count++;
    }
  }
  return count;
 }

 void PlatzFreiMachen(){
   for(int i = 0; i < numParkplaetze; i++){
    if (zustandParkplaetze[i] == PARKPLATZ_VERLASSEN) {
      zustandParkplaetze[i] = PARKPLATZ_FREI;
    }
  } 
 }