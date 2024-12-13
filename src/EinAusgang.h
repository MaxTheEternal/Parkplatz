#include <Servo.h>

namespace EinAusGang
{

  const int eingangServo = 10;
  const int ausgangServo = 11;

  Servo EingangServo;
  Servo AusgangServo;

  unsigned long eingangGEoeffnetZeit = 0; // Tracks the last time the servo moved
  unsigned long ausgangGeoggnetZeit = 0;  // Tracks the last time the servo moved

  bool eingangOffen = false;
  bool ausgangOffen = false;

  unsigned long delayTime = 5000; // Time to wait in milliseconds (5 seconds)
  int bewegungsGrad = 20;
  int geschlossenGrad = 0;

  void setup()
  {
    EingangServo.attach(eingangServo);
    AusgangServo.attach(ausgangServo);
    EingangServo.write(geschlossenGrad);
    AusgangServo.write(geschlossenGrad);
  }

  void EingangOeffnen()
  {
    EingangServo.write(bewegungsGrad);
    eingangGEoeffnetZeit = millis();
    eingangOffen = true;
  }

  void AusgangOeffnen()
  {
    AusgangServo.write(bewegungsGrad);
    ausgangGeoggnetZeit = millis();
    eingangOffen = true;
  }

  void checkSchrankeSchliessen()
  {
    if (eingangOffen && millis() >= eingangGEoeffnetZeit + delayTime)
    {
      EingangServo.write(geschlossenGrad);
      eingangOffen = false;
    }
    if (ausgangOffen && millis() >= ausgangGeoggnetZeit + delayTime)
    {
      AusgangServo.write(geschlossenGrad);
      ausgangOffen = false;
    }
  }

};