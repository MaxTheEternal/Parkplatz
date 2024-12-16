#include <ESP32Servo.h>
#include <parkingLights.h>
#include <FastLED.h>
#include <List.hpp>

#define NUM_LEDS 51
#define LED_PIN 23// Pin connected to the LED strip
#define CHIPSET WS2812B
#define COLOR_ORDER GRB

int ledPins[14] = { 2, 4, 16, 17, 5, 18, 19, 21, 3, 1, 22, 27, 25, 26};

#define PARKPLATZ_FREI 0
#define PARKPLATZ_BELEGT 1
#define PARKPLATZ_RESERVIERT 2
#define PARKPLATZ_VERLASSEN 3

#define DATA_PIN 14
#define CLOCK_PIN 13
#define LATCH_PIN 12

#define EINGANG_SENSOR 34
#define AUSGANG_SENSOR 35

#define EINGANG_SERVO 33
#define AUSGANG_SERVO 32

#define SCHRANKE_AUF 25
#define SCHRANKE_ZU 0
#define SCHRANKE_RAUS_OFFSET 7

Servo eingangServo;
Servo ausgangServo;

unsigned long eingangGEoeffnetZeit = 0; // Tracks the last time the servo moved
unsigned long ausgangGeoggnetZeit = 0;  // Tracks the last time the servo moved
unsigned long delayTime = 5000; // Time to wait in milliseconds (5 seconds)


bool eingangOffen = false;
bool ausgangOffen = false;

const int numBits = 40; /* Set to 8 * number of shift registers */
const int numParkplaetze = 30;

CRGB leds[NUM_LEDS];

List<Parkplatz::Parkplatz> carsGoingRound;
int freeSpaces = numParkplaetze;
int neunZehnCounter = 0;

int zustandParkplaetze[numParkplaetze] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  
  0, 0, 0, 0, 0, 0, 0, 0, 0, 9,  
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
};

void turnRedParkingSpaces(int i, bool taken);
int findParkplatz();
void readSensors();
void turnOffLedsAfterCar(int sensorIndex);
void turnOnLedsToParkplatz(int autoIndex);
void SchrankenSchliessen();
void ParkplatzZustandSetzen(int i, bool sensorAn);
int FreiePlaetze();
void PlatzFreiMachen();
void TurnOnParkingLeds();
void LedCarousel();
void displayNumber(byte number);

void setup() {
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(50);

  eingangServo.attach(EINGANG_SERVO);
  ausgangServo.attach(AUSGANG_SERVO);
  
  eingangServo.write(SCHRANKE_ZU);
  ausgangServo.write(SCHRANKE_ZU+SCHRANKE_RAUS_OFFSET);

  pinMode(DATA_PIN, INPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);

  pinMode(EINGANG_SENSOR, INPUT);
  pinMode(AUSGANG_SENSOR, INPUT);

  

  for(int i = 0; i < 14; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
//  LedCarousel();

if (digitalRead(EINGANG_SENSOR) == LOW && !eingangOffen)
  {
    if (FreiePlaetze() > 0)
    {
      int platz = findParkplatz();
      if (platz != -1) {

          //  Schranke hoch
        eingangServo.write(SCHRANKE_AUF);
        eingangGEoeffnetZeit = millis();
        eingangOffen = true;

        //  Auto zu liste an Autos hinzufügen
        if(carsGoingRound.getSize() >= 2) {
          carsGoingRound.removeFirst();
        }
        carsGoingRound.add(Parkplatz::allePlaetze[platz]);
        turnOnLedsToParkplatz(platz);
      }
    }
  }

  if (digitalRead(AUSGANG_SENSOR) == LOW && !ausgangOffen)
  {
    ausgangGeoggnetZeit = millis();
    ausgangOffen = true;
    ausgangServo.write(SCHRANKE_AUF+SCHRANKE_RAUS_OFFSET);
    PlatzFreiMachen();
  }


  readSensors();
  int freie = FreiePlaetze();
  // Hier Display Freie Plätze
  displayNumber(freie);
  SchrankenSchliessen();
  FastLED.show();

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

  TurnOnParkingLeds();
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
    eingangServo.write(SCHRANKE_ZU);
  }

  if (ausgangOffen && millis() >= ausgangGeoggnetZeit + delayTime) {
    ausgangOffen = false;
  ausgangServo.write(SCHRANKE_ZU+SCHRANKE_RAUS_OFFSET);
  }
}

  void ParkplatzZustandSetzen(int i, bool sensorAn) {
  int platz = Parkplatz::SensorToParkplatz[i];
  if (platz == -1) {
    return;
  }

  // Keine Ahnung warum aber 19 startet als 3 also mache ich mal das
  if (platz == 19 && neunZehnCounter < 5) {
    neunZehnCounter++;
    zustandParkplaetze[19] = 0;
    return;
  }
  if (sensorAn) {
        zustandParkplaetze[platz] = PARKPLATZ_BELEGT;
  } else {
      if (zustandParkplaetze[platz] == PARKPLATZ_BELEGT)
      {
        zustandParkplaetze[platz] = PARKPLATZ_VERLASSEN;
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


void TurnOnParkingLeds() {
  for(int i = 0; i < numParkplaetze; i++) {
    int zustand = zustandParkplaetze[i];
    if(zustand == PARKPLATZ_BELEGT){
      leds[Parkplatz::ParkplatzToLed[i]] = CRGB::Red;
    } else if(zustand == PARKPLATZ_RESERVIERT){
      leds[Parkplatz::ParkplatzToLed[i]] = CRGB::Green;
    } else {
      leds[Parkplatz::ParkplatzToLed[i]] = CRGB::Black;
    }
  }
}

void LedCarousel() {
  delay(5000);
  for(int i = 0; i < 14; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
  for(int i = 0; i < 14; i++) {
    digitalWrite(ledPins[i], LOW);
    delay(1000);
    digitalWrite(ledPins[i], HIGH);
  }
}

void displayNumber (byte number){
  long firstDigitEncoding[] = 
  {
    0b01101100100111,//0
    0b01101111111111,//1
    0b01111100010111, //2
    0b01101110010111//3
  };
  long lastDigitEncoding[] =  
  {
    0b11010011111000,//0
    0b11111011111110,//1
    0b10110011111001,//2
    0b10110011111010,//3
    0b10011011111110,//4
    0b10010111111010,//5
    0b10010111111000,//6
    0b11110011111110,//7
    0b10010011111000,//8
    0b10010011111010//9
  };
  byte lastDigit = number%10;
  byte firstDigit = (number/10)%10;

  long data = firstDigitEncoding[firstDigit] & lastDigitEncoding[lastDigit];
   
  for (int i = 0; i < 14; i++){
    digitalWrite(ledPins[i], (data & (0b10000000000000 >> i )) != 0);
  }
}