#include <Arduino.h>
#include <stdint.h>

#define FOSC 16000000
#define BAUD 9600
#define MY_UBRR (FOSC / 16 / BAUD - 1)
#define USE_UART_RX_IRQ 0
char ReceivedChar;
char Message[] = "Hello";
char * pMessage = Message;
void setup(){
  /* Konfiguracja szybkości pracy */
  UBRR0H = (MY_UBRR >> 8);
  UBRR0L = MY_UBRR;
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0); // Włączenie nadajnika i odbiornika
  UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // Format ramki: 8 data, 1 stop1

while(*pMessage){ //Wysyłanie wiadomości
  while ( !( UCSR0A & (1<<UDRE0)) );
  UDR0 = *pMessage;
  pMessage++;
}
  /* Wait for empty transmit buffer */
#if (USE_UART_RX_IRQ == 1)
  UCSR0B |= (1 << RXCIE0); // Włączenie przerwania od odbiornika
#endif
}
void loop(){
#if (USE_UART_RX_IRQ == 0)
  while (!(UCSR0A & (1 << RXC0)))
    ;                  // Czekaj na odbieranie danych
  ReceivedChar = UDR0; // Odebranie znaku z bufora RX
  while (!(UCSR0A & (1 << UDRE0)))
    ;                  // Czekaj na pusty bufor nadawczy
  UDR0 = ReceivedChar; // Wysyłanie znaku do bufora TX
#endif
}
#if (USE_UART_RX_IRQ == 1)
ISR (USAR_RX_vect){
    ReceivedChar = UDR0          // Odebranie znaku z bufora RX
    UDR0 = ReceivedChar;         // Wysłanie znaku do bufora TX
}
#endif