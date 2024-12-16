#include <avr/io.h>
#include <util/delay.h>

#define DIGIT0 0b11111100
#define DIGIT1 0b01100000
#define DIGIT2 0b11011010
#define DIGIT3 0b11110010
#define DIGIT4 0b01100110
#define DIGIT5 0b10110110
#define DIGIT6 0b10111110
#define DIGIT7 0b11100000
#define DIGIT8 0b11111110
#define DIGIT9 0b11110110

const char DIGITS[10] = {
  DIGIT0,
  DIGIT1,
  DIGIT2,
  DIGIT3,
  DIGIT4,
  DIGIT5,
  DIGIT6,
  DIGIT7,
  DIGIT8,
  DIGIT9
};

void display(char digit) {

  char bit;
  for (char bit_select = 0; bit_select < 8; bit_select++) {
    bit = ((1 << bit_select) & digit) == 0 ? 0 : 1;
    
    PORTB |= (bit << PB0);
    _delay_ms(1);
    PORTB |= (1 << PB2);
    _delay_ms(1);
    PORTB &= ~(1 << PB2);
    _delay_ms(1);
    PORTB &= ~(1 << PB0);
    _delay_ms(1);
  }

  _delay_ms(1);
  PORTB |= (1 << PB1);
  _delay_ms(1);
  PORTB &= ~(1 << PB1);
  _delay_ms(1);
  PORTB &= ~(1 << PB0);
  _delay_ms(1);

  return;
}

int main() {

  // Circuit notes:
  // PB0 SER
  // PB1 RCLK
  // PB2 SRCLK

  // Set relevent outputs
  DDRB |= 0b00000111;
  
  while(1) {
    for (char digit = 0; digit < 10; digit++) {
      _delay_ms(1000);
      display(DIGITS[digit]);
    }
  }

  return 0;
}
