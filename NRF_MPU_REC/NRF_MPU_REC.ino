#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>


const uint64_t pipe = 0xE8E8F0F0E1LL;

const int pinCE = 7;
const int pinCSN = 8;

int datos[14];

RF24 radio(pinCE, pinCSN);


void setup() {
  
  Serial.begin(230400);

  radio.begin();
  radio.setPayloadSize(50);
  radio.openReadingPipe(1, pipe);
  radio.startListening();

}

void loop() {
  /* code */
	if(radio.available()){

		radio.read(datos, 28);

		Serial.print(datos[0]);
		Serial.print(",");
		Serial.print(datos[1]);
		Serial.print(",");
		Serial.print(datos[2]);
		Serial.print(",");
		Serial.print(datos[3]);
		Serial.print(",");
		Serial.print(datos[4]);
		Serial.print(",");
		Serial.print(datos[5]);
		Serial.print(",");
		Serial.print(datos[6]);
		Serial.print(",");
		Serial.print(datos[7]);
		Serial.print(",");
		Serial.print(datos[8]);
		Serial.print(",");
		Serial.print(datos[9]);
		Serial.print(",");
		Serial.print(datos[10]);
		Serial.print(",");
		Serial.print(datos[11]);
		Serial.print(",");
		Serial.print(datos[12]);
		Serial.print(",");
		Serial.println(datos[13]);

	}
}