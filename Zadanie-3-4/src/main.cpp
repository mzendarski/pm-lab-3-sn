#include <avr/io.h>
#include <avr/interrupt.h>

int main(void) {
  DDRD &= ~(1 << DD5);
  PORTD |= (1 << PORTD5);
  TIMSK1 |= (1 << TOIE1);
  TCCR1B |= (1 << CS12) | (1 << CS11) | (1 << CS10);
  sei();

  while(1) {

  }
}

ISR(TIMER1_OVF_vect) {

}   // Chciałbym to zrobić ale potrafię tylko przpisywać kod.