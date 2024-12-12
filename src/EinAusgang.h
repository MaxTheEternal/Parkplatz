#include <Arduino.h>
#include <Servo.h>


namespace EinAusGang {

const int eingangSensor = 0;
const int ausgangSensor = 1;
const int eingangServo = 10;
const int ausgangServo = 11;

Servo EingangServo;
Servo AusgangServo;

void setup() {
  EingangServo.attach(eingangServo);
  AusgangServo.attach(ausgangServo);

  pinMode(eingangSensor, INPUT);
  pinMode(ausgangSensor, OUTPUT);
}

void EingangOeffnen() {
    
}

void AusgangOeffnen() {

}

};