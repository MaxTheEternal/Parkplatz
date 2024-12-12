#include <Arduino.h>

#define DISPLAY_RCLK A4 // RCLK Pin
#define DISPLAY_SRCLK A5 // SRCLK Pin
#define DISPLAY_SER A3 // SER Pin
namespace display {

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
};

}