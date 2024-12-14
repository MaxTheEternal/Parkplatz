#include <ESP32Servo.h>
#define EINGANG_SERVO_PIN 34
#define AUSGANG_SERVO_PIN 35
namespace EinAusGang
{
  Servo EingangServo;
  Servo AusgangServo;

  const int bewegungsGrad = 20;
  const int geschlossenGrad = 0;

  void setup()
  {
    	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	EingangServo.setPeriodHertz(50);    // standard 50 hz servo
	EingangServo.attach(EINGANG_SERVO_PIN, 500, 2400); // attaches the servo on pin 18 to the servo object
	EingangServo.setPeriodHertz(50);    // standard 50 hz servo
	EingangServo.attach(AUSGANG_SERVO_PIN, 500, 2400); // attaches the servo on pin 18 to the servo object
    // EingangServo.attach(eingangServo);
    // AusgangServo.attach(ausgangServo);
    EingangServo.write(geschlossenGrad);
    AusgangServo.write(geschlossenGrad);
  }

  void EingangOeffnen()
  {
    EingangServo.write(bewegungsGrad);
  }

  void AusgangOeffnen()
  {
    AusgangServo.write(bewegungsGrad);
  }

  void EingangSchliessen(){
    EingangServo.write(geschlossenGrad);

  }

  void AusgangSchliessen(){
    AusgangServo.write(geschlossenGrad);
  }

};

// void setup() {
// 	// using default min/max of 1000us and 2000us
// 	// different servos may require different min/max settings
// 	// for an accurate 0 to 180 sweep
// }
 
// void loop() {
 
// 	for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
// 		// in steps of 1 degree
// 		myservo.write(pos);    // tell servo to go to position in variable 'pos'
// 		delay(15);             // waits 15ms for the servo to reach the position
// 	}
// 	for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
// 		myservo.write(pos);    // tell servo to go to position in variable 'pos'
// 		delay(15);             // waits 15ms for the servo to reach the position
// 	}
