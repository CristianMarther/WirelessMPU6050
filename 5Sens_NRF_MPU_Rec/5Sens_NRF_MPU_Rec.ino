#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

typedef union
{
 float number;
 uint16_t bytes[2];
} FLOATUNION_t;

FLOATUNION_t datofloat;

const uint64_t pipe = 0xE8E8F0F0E1LL;

const int pinCE = 7;
const int pinCSN = 8;

 uint16_t datos[10];

RF24 radio(pinCE, pinCSN);

long timer = 0;

void setup() {
  
  Serial.begin(230400);

  radio.begin();
  radio.setPayloadSize(30);
  radio.openReadingPipe(1, pipe);
  radio.startListening();

}

void loop() {


  /* code */

  //if(millis() - timer < 2000){ 
	if(radio.available()){

		radio.read(datos, 20);

		Serial.print((int)datos[0]);
		Serial.print(",");
		Serial.print((int)datos[1]);
		Serial.print(",");
		Serial.print((int)datos[2]);
		Serial.print(",");
		Serial.print((int)datos[3]);
		Serial.print(",");
		Serial.print((int)datos[4]);
		Serial.print(",");
		Serial.print((int)datos[5]);
		Serial.print(",");
		Serial.print((int)datos[6]);
		Serial.print(",");
		Serial.print((int)datos[7]);
		Serial.print(",");
    datofloat.bytes[0] = datos[8];
    datofloat.bytes[1] = datos[9];
		
//		Serial.print(datos[8]);
//		Serial.print(",");
//		Serial.print(datos[9]);
//		Serial.print(",");
//		Serial.print(datos[10]);
//		Serial.print(",");
//		Serial.print(datos[11]);
//		Serial.print(",");
//		Serial.print(datos[12]);
//		Serial.print(",");
		Serial.println(datofloat.number);

	//}
	}
}
