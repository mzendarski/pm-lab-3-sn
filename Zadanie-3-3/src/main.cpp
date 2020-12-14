#include <Arduino.h>
#define ADC_RESOLUTION_DEFAULT (5.0f / 1024.0f)

uint16_t digital;
float voltage;

uint16_t ADCsingleREAD(uint8_t adcToUse){
  uint16_t ADCval;

  ADMUX = adcToUse;                                    //Konfiguracja numeru wejścia
  ADMUX |= (1 << REFS0);                               //Konfiguracja napięcia odniesienia - zewnętrzne 5v
  ADMUX &= ~(1 << ADLAR);                              //Rozdzielczość 10 bitów
  ADCSRA|= (1 << ADPS2) | (1 << ADPS1) | (1 >> ADPS0); //Konfiguracja presklara na 125Khz
  ADCSRA |= (1 << ADEN);                               //Włączeniue ADC
  ADCSRA |= (1 <<ADSC);                                //Uruchomienie konwersji
  while (ADCSRA & (1 << ADSC))
    ;                           //Oczekiwanie na zakończenie konwersji
  ADCval = ADCL;                //Odczyt młodszych bitów wyniku konwersji
  ADCval = (ADCH << 8) +ADCval; //odczyt starszych bitów wyniku kowersji
  
  return ADCval;                //Zwrócenie wyniku konwersji
}

void setup(){
  Serial.begin(9600);
}

void loop(){
  digital = ADCsingleREAD(0);
  voltage =ADC_RESOLUTION_DEFAULT * digital;
  Serial.print("A0 = ");
  Serial.print(digital);
  Serial.print(" \t V(0) = ");
  Serial.print(voltage);
  Serial.println(" [V]");
  delay(1000);
}