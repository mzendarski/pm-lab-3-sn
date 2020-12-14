#include <Arduino.h>

#define BUTTON 2

int stanPrzycisku;
int poprzedniStanPrzycisku = LOW;
unsigned long poprzedniCzas = 0;
unsigned int liczba_nacisniec = 0;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON, INPUT);
}

void loop() {
  int odczyt = digitalRead(BUTTON);

  if (odczyt != poprzedniStanPrzycisku) {
    poprzedniCzas = millis();
  }

   if((millis() - poprzedniCzas) >50) {
    if (odczyt != stanPrzycisku) {
       stanPrzycisku = odczyt;
       if (stanPrzycisku == HIGH) {
       liczba_nacisniec++;

       Serial.print("Liczba nacisniec przycisku: ");
       Serial.println(liczba_nacisniec);
       }   
    }    
  }

  poprzedniStanPrzycisku = odczyt;
}