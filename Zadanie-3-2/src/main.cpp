#include <Arduino.h>
#include <SPI.h>

#define SPI_CS_PIN 10

typedef int32_t  BMP280_S32_t;
typedef uint32_t BMP280_U32_t;

uint8_t configReg = 0, ctrlReg = 0;

uint8_t device_id = 0;
uint8_t rawdata[32];
uint32_t rawVal = 0;
uint32_t degC = 0, press = 0;
double ddegC = 0, dpress = 0;

// Parametry kompensacji wartości:
uint16_t dig_T1 = 0;
int16_t dig_T2 = 0, dig_T3 = 0;
uint16_t dig_P1 = 0; 
int16_t dig_P2 = 0, dig_P3 = 0, dig_P4 = 0, dig_P5 = 0;
int16_t dig_P6 = 0, dig_P7 = 0, dig_P8 = 0, dig_P9 = 0;

BMP280_S32_t t_fine;

BMP280_S32_t bmp280_compensate_T_int32(BMP280_S32_t adc_T);
BMP280_S32_t bmp280_compensate_P_int32(BMP280_S32_t adc_P);

void setup() {
  Serial.begin(9600);
 Serial.setTimeout(4000);

 SPI.begin();
 pinMode(SPI_CS_PIN, OUTPUT);
 digitalWrite(SPI_CS_PIN, HIGH);

 digitalWrite(SPI_CS_PIN, LOW);
 SPI.transfer(0xD0);                     //adres rejestru (Device ID)
 device_id = SPI. transfer(0x00);        //dane
 digitalWrite(SPI_CS_PIN, HIGH);
 Serial.print("Device ID:  "); Serial.println(device_id, HEX);

 digitalWrite(SPI_CS_PIN, LOW);
 SPI.transfer(0x88);                     //Parametry kompensacji
 for(int i = 0; i < 24; i++); {
   rawdata[i] = SPI.transfer(0x00);  
  }
 digitalWrite(SPI_CS_PIN, HIGH);

 dig_T1 = (((uint16_t)rawdata[1]) << 8) | ((uint16_t)rawdata[0]);
 dig_T2 = (((int16_t)rawdata[3]) << 8) | ((int16_t)rawdata[2]);
 dig_T3 = (((int16_t)rawdata[5]) << 8) | ((int16_t)rawdata[4]);
 dig_P1 = (((uint16_t)rawdata[7]) << 8) | ((uint16_t)rawdata[6]);
 dig_P2 = (((int16_t)rawdata[9]) << 8) | ((int16_t)rawdata[8]);
 dig_P3 = (((int16_t)rawdata[11]) << 8) | ((int16_t)rawdata[10]);
 dig_P4 = (((int16_t)rawdata[13]) << 8) | ((int16_t)rawdata[12]);
 dig_P5 = (((int16_t)rawdata[15]) << 8) | ((int16_t)rawdata[14]);
 dig_P6 = (((int16_t)rawdata[17]) << 8) | ((int16_t)rawdata[16]);
 dig_P7 = (((int16_t)rawdata[19]) << 8) | ((int16_t)rawdata[18]);
 dig_P8 = (((int16_t)rawdata[21]) << 8) | ((int16_t)rawdata[20]);
 dig_P9 = (((int16_t)rawdata[23]) << 8) | ((int16_t)rawdata[22]);

 //t_sb = 0x04 | filter = 0x04 | spi3w_en = 0x00;
 configReg = (0x04 << 5) | (0x04 << 2) | 0x00;
 //osrs_t = 0x02 | osrs_p = 0x05 | mode = 0x03
 ctrlReg = (0x02 << 5) | (0x05 << 2) | 0x03;

 digitalWrite(SPI_CS_PIN, LOW);
 SPI.transfer(0x75);             //Rejestr config
 SPI.transfer(configReg);        //dane
 SPI.transfer(0x74);             //Rejestr ctrl
 SPI.transfer(ctrlReg);          //dane
 digitalWrite(SPI_CS_PIN, HIGH);
}

void loop() {
  //Odczyt seryjny wartości raw:
 digitalWrite(SPI_CS_PIN, LOW);
 SPI.transfer(0xF7);
 for(int i= 0; i < 6; i++)  {
   rawdata[i] = SPI.transfer (0x00);
  }
 digitalWrite(SPI_CS_PIN, HIGH);

 rawVal = (((uint32_t)rawdata[3]) << 12) | (((uint32_t)rawdata[4]) << 4) | (((uint32_t)rawdata[5]) >> 4);
 degC = bmp280_compensate_T_int32(rawVal);
 ddegC = degC / 100.0;
 Serial.print("Temperatura: "); Serial.print(ddegC); Serial.println("stC");

 rawVal = (((uint32_t)rawdata[0]) << 12) | (((uint32_t)rawdata[1]) << 4) | (((uint32_t)rawdata[2]) >> 4);
 press = bmp280_compensate_P_int32(rawVal);
 dpress = press / 100.0;
 Serial.print("Cisnienie:   "); Serial.print(dpress); Serial.println("hPa");

 delay(3000);
}

BMP280_S32_t bmp280_compensate_T_int32(BMP280_S32_t adc_T) { 
}
BMP280_S32_t bmp280_compensate_P_int32(BMP280_S32_t adc_P) { 
}
