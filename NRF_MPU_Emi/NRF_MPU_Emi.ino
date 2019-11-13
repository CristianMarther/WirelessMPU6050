#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

/// uno ///
#define OFFSETS1  -2002,     -66,    1556,     234,      40,      -8  
/// DOS ///
#define OFFSETS2  -1329,   -2449,    1938,    -136,     226,    -124  
/// TRES ///
#define OFFSETS3  -3387,   -1754,     931,     144,      43,      42  
/// CUATRO ///
#define OFFSETS4  -1791,    -871,    1297,      65,       1,      64 
/// CINCO /// 
#define OFFSETS5  -1303,    -847,    1250,     -24,      19,     -64 
/// SEIS  ///
#define OFFSETS6   2279,      60,     954,     103,      24,     -50 
/// SIETE ///
#define OFFSETS7  -4359,    -159,    1169,     -57,    -104,    -229 

// llave de canal de cominicacion
const uint64_t pipe = 0xE8E8F0F0E1LL;

//----------- pines de entrada o salida


int mpu1 = 2;   //Pie Derecho
int mpu2 = 3;  //Pierna Derecha
int mpu3 = 4;  //Femur Derecho
int mpu4 = 5;  //Pie Izquierdo
int mpu5 = 6;  //Pierna Izquierda
int mpu6 = 9;  //Femur Izquierdo
int mpu7 = 10;  //Cadera

//----- Pines para el transmisor
const int pinCE = 7;
const int pinCSN = 8;

// pines no declarados pero usados
//const int pinD11 = 11;
//const int pinD12 = 12;
//const int pinD13 = 13;

//---------- Objetos de Clases

MPU6050 sensor1;  //Pie Derecho
MPU6050 sensor2;  //Pierna Derecha
MPU6050 sensor3;  //Femur Derecho
MPU6050 sensor4;  //Pie Izquierdo
MPU6050 sensor5;  //Pierna Izquierda
MPU6050 sensor6;  //Femur Izquierdo
MPU6050 sensor7;  //Cadera

RF24 radio(pinCE, pinCSN);

// ---------------- Variables a usar

int datos[14];

int ax1, ay1, az1;
int gx1, gy1, gz1;
long tiempo_prev1;
float dt1;
float ang_x1, ang_y1;
float ang_x_prev1, ang_y_prev1;

int ax2, ay2, az2;
int gx2, gy2, gz2;
long tiempo_prev2;
float dt2;
float ang_x2, ang_y2;
float ang_x_prev2, ang_y_prev2;

int ax3, ay3, az3;
int gx3, gy3, gz3;
long tiempo_prev3;
float dt3;
float ang_x3, ang_y3;
float ang_x_prev3, ang_y_prev3;

int ax4, ay4, az4;
int gx4, gy4, gz4;
long tiempo_prev4;
float dt4;
float ang_x4, ang_y4;
float ang_x_prev4, ang_y_prev4;

int ax5, ay5, az5;
int gx5, gy5, gz5;
long tiempo_prev5;
float dt5;
float ang_x5, ang_y5;
float ang_x_prev5, ang_y_prev5;

int ax6, ay6, az6;
int gx6, gy6, gz6;
long tiempo_prev6;
float dt6;
float ang_x6, ang_y6;
float ang_x_prev6, ang_y_prev6;

int ax7, ay7, az7;
int gx7, gy7, gz7;
long tiempo_prev7;
float dt7;
float ang_x7, ang_y7;
float ang_x_prev7, ang_y_prev7;




void setup() {
  
  Serial.begin(230400);    //Iniciando puerto serial
  Wire.begin();

  radio.begin();
  radio.setPayloadSize(50);
  radio.openWritingPipe(pipe);

  pinMode(mpu1, OUTPUT);
  pinMode(mpu2, OUTPUT);
  pinMode(mpu3, OUTPUT);
  pinMode(mpu4, OUTPUT);
  pinMode(mpu5, OUTPUT);
  pinMode(mpu6, OUTPUT);
  pinMode(mpu7, OUTPUT);
  // put your setup code here, to run once:

  digitalWrite(mpu1, LOW);
  digitalWrite(mpu2, HIGH);
  digitalWrite(mpu3, HIGH);
  digitalWrite(mpu4, HIGH);
  digitalWrite(mpu5, HIGH);
  digitalWrite(mpu6, HIGH);
  digitalWrite(mpu7, HIGH);
  sensor1.initialize();
  setOffset(OFFSETS1, sensor1);

  digitalWrite(mpu1, HIGH);
  digitalWrite(mpu2, LOW);
  digitalWrite(mpu3, HIGH);
  digitalWrite(mpu4, HIGH);
  digitalWrite(mpu5, HIGH);
  digitalWrite(mpu6, HIGH);
  digitalWrite(mpu7, HIGH);
  sensor2.initialize();
  setOffset(OFFSETS2, sensor2);

  digitalWrite(mpu1, HIGH);
  digitalWrite(mpu2, HIGH);
  digitalWrite(mpu3, LOW);
  digitalWrite(mpu4, HIGH);
  digitalWrite(mpu5, HIGH);
  digitalWrite(mpu6, HIGH);
  digitalWrite(mpu7, HIGH);
  sensor3.initialize();
  setOffset(OFFSETS3, sensor3);

  digitalWrite(mpu1, HIGH);
  digitalWrite(mpu2, HIGH);
  digitalWrite(mpu3, HIGH);
  digitalWrite(mpu4, LOW);
  digitalWrite(mpu5, HIGH);
  digitalWrite(mpu6, HIGH);
  digitalWrite(mpu7, HIGH);
  sensor4.initialize();
  setOffset(OFFSETS4, sensor4);

  digitalWrite(mpu1, HIGH);
  digitalWrite(mpu2, HIGH);
  digitalWrite(mpu3, HIGH);
  digitalWrite(mpu4, HIGH);
  digitalWrite(mpu5, LOW);
  digitalWrite(mpu6, HIGH);
  digitalWrite(mpu7, HIGH);
  sensor5.initialize();
  setOffset(OFFSETS5, sensor5);

  digitalWrite(mpu1, HIGH);
  digitalWrite(mpu2, HIGH);
  digitalWrite(mpu3, HIGH);
  digitalWrite(mpu4, HIGH);
  digitalWrite(mpu5, HIGH);
  digitalWrite(mpu6, LOW);
  digitalWrite(mpu7, HIGH);
  sensor6.initialize();
  setOffset(OFFSETS6, sensor6);

  digitalWrite(mpu1, HIGH);
  digitalWrite(mpu2, HIGH);
  digitalWrite(mpu3, HIGH);
  digitalWrite(mpu4, HIGH);
  digitalWrite(mpu5, HIGH);
  digitalWrite(mpu6, HIGH);
  digitalWrite(mpu7, LOW);
  sensor7.initialize();
  setOffset(OFFSETS7, sensor7);

}

void loop() {

  digitalWrite(mpu1, LOW);
  digitalWrite(mpu2, HIGH);
  digitalWrite(mpu3, HIGH);
  digitalWrite(mpu4, HIGH);
  digitalWrite(mpu5, HIGH);
  digitalWrite(mpu6, HIGH);
  digitalWrite(mpu7, HIGH);
  sensor1.getAcceleration(&ax1, &ay1, &az1);
  sensor1.getRotation(&gx1, &gy1, &gz1);
  
  dt1 = (millis()-tiempo_prev1)/1000.0;
  tiempo_prev1=millis();
  
  //Calcular los ángulos con acelerometro
  float accel_ang_x1=atan(ay1/sqrt(pow(ax1,2) + pow(az1,2)))*(180.0/3.14);
  float accel_ang_y1=atan(-ax1/sqrt(pow(ay1,2) + pow(az1,2)))*(180.0/3.14);
  
  //Calcular angulo de rotación con giroscopio y filtro complemento  
  ang_x1 = 0.98*(ang_x_prev1+(gx1/131)*dt1) + 0.02*accel_ang_x1;
  ang_y1 = 0.98*(ang_y_prev1+(gy1/131)*dt1) + 0.02*accel_ang_y1;
  
  
  //ang_x_prev1=ang_x1;
  //ang_y_prev1=ang_y1;

  datos[0] = (int) ang_x1;
  datos[1] = (int) ang_y1;


  digitalWrite(mpu1, HIGH);
  digitalWrite(mpu2, LOW);
  digitalWrite(mpu3, HIGH);
  digitalWrite(mpu4, HIGH);
  digitalWrite(mpu5, HIGH);
  digitalWrite(mpu6, HIGH);
  digitalWrite(mpu7, HIGH);
  sensor2.getAcceleration(&ax2, &ay2, &az2);
  sensor2.getRotation(&gx2, &gy2, &gz2);
  
  dt2 = (millis()-tiempo_prev2)/1000.0;
  tiempo_prev2=millis();
  
  //Calcular los ángulos con acelerometro
  float accel_ang_x2=atan(ay2/sqrt(pow(ax2,2) + pow(az2,2)))*(180.0/3.14);
  float accel_ang_y2=atan(-ax2/sqrt(pow(ay2,2) + pow(az2,2)))*(180.0/3.14);
  
  //Calcular angulo de rotación con giroscopio y filtro complemento  
  ang_x2 = 0.98*(ang_x_prev2+(gx2/131)*dt2) + 0.02*accel_ang_x2;
  ang_y2 = 0.98*(ang_y_prev2+(gy2/131)*dt2) + 0.02*accel_ang_y2;
  
  
  //ang_x_prev2=ang_x2;
  //ang_y_prev2=ang_y2;

  datos[2] = (int) ang_x2;
  datos[3] = (int) ang_y2;

  digitalWrite(mpu1, HIGH);
  digitalWrite(mpu2, HIGH);
  digitalWrite(mpu3, LOW);
  digitalWrite(mpu4, HIGH);
  digitalWrite(mpu5, HIGH);
  digitalWrite(mpu6, HIGH);
  digitalWrite(mpu7, HIGH);
  sensor3.getAcceleration(&ax3, &ay3, &az3);
  sensor3.getRotation(&gx3, &gy3, &gz3);
  
  dt3 = (millis()-tiempo_prev3)/1000.0;
  tiempo_prev3=millis();
  
  //Calcular los ángulos con acelerometro
  float accel_ang_x3=atan(ay3/sqrt(pow(ax3,2) + pow(az3,2)))*(180.0/3.14);
  float accel_ang_y3=atan(-ax3/sqrt(pow(ay3,2) + pow(az3,2)))*(180.0/3.14);
  
  //Calcular angulo de rotación con giroscopio y filtro complemento  
  ang_x3 = 0.98*(ang_x_prev3+(gx3/131)*dt3) + 0.02*accel_ang_x3;
  ang_y3 = 0.98*(ang_y_prev3+(gy3/131)*dt3) + 0.02*accel_ang_y3;
  
  
  //ang_x_prev3=ang_x3;
  //ang_y_prev3=ang_y3;

  datos[4] = (int) ang_x3;
  datos[5] = (int) ang_y3;

  digitalWrite(mpu1, HIGH);
  digitalWrite(mpu2, HIGH);
  digitalWrite(mpu3, HIGH);
  digitalWrite(mpu4, LOW);
  digitalWrite(mpu5, HIGH);
  digitalWrite(mpu6, HIGH);
  digitalWrite(mpu7, HIGH);
  sensor4.getAcceleration(&ax4, &ay4, &az4);
  sensor4.getRotation(&gx4, &gy4, &gz4);
  
  dt4 = (millis()-tiempo_prev4)/1000.0;
  tiempo_prev4=millis();
  
  //Calcular los ángulos con acelerometro
  float accel_ang_x4=atan(ay4/sqrt(pow(ax4,2) + pow(az4,2)))*(180.0/3.14);
  float accel_ang_y4=atan(-ax4/sqrt(pow(ay4,2) + pow(az4,2)))*(180.0/3.14);
  
  //Calcular angulo de rotación con giroscopio y filtro complemento  
  ang_x4 = 0.98*(ang_x_prev4+(gx4/131)*dt4) + 0.02*accel_ang_x4;
  ang_y4 = 0.98*(ang_y_prev4+(gy4/131)*dt4) + 0.02*accel_ang_y4;
  
  
  //ang_x_prev4=ang_x4;
  //ang_y_prev4=ang_y4;

  datos[6] = (int) ang_x4;
  datos[7] = (int) ang_y4;

  digitalWrite(mpu1, HIGH);
  digitalWrite(mpu2, HIGH);
  digitalWrite(mpu3, HIGH);
  digitalWrite(mpu4, HIGH);
  digitalWrite(mpu5, LOW);
  digitalWrite(mpu6, HIGH);
  digitalWrite(mpu7, HIGH);
  sensor5.getAcceleration(&ax5, &ay5, &az5);
  sensor5.getRotation(&gx5, &gy5, &gz5);
  
  dt5 = (millis()-tiempo_prev5)/1000.0;
  tiempo_prev5=millis();
  
  //Calcular los ángulos con acelerometro
  float accel_ang_x5=atan(ay5/sqrt(pow(ax5,2) + pow(az5,2)))*(180.0/3.14);
  float accel_ang_y5=atan(-ax5/sqrt(pow(ay5,2) + pow(az5,2)))*(180.0/3.14);
  
  //Calcular angulo de rotación con giroscopio y filtro complemento  
  ang_x5 = 0.98*(ang_x_prev5+(gx5/131)*dt5) + 0.02*accel_ang_x5;
  ang_y5 = 0.98*(ang_y_prev5+(gy5/131)*dt5) + 0.02*accel_ang_y5;
  
  
  //ang_x_prev5=ang_x5;
  //ang_y_prev5=ang_y5;

  datos[8] = (int) ang_x5;
  datos[9] = (int) ang_y5;

  digitalWrite(mpu1, HIGH);
  digitalWrite(mpu2, HIGH);
  digitalWrite(mpu3, HIGH);
  digitalWrite(mpu4, HIGH);
  digitalWrite(mpu5, HIGH);
  digitalWrite(mpu6, LOW);
  digitalWrite(mpu7, HIGH);
  sensor6.getAcceleration(&ax6, &ay6, &az6);
  sensor6.getRotation(&gx6, &gy6, &gz6);
  
  dt6 = (millis()-tiempo_prev6)/1000.0;
  tiempo_prev6=millis();
  
  //Calcular los ángulos con acelerometro
  float accel_ang_x6=atan(ay6/sqrt(pow(ax6,2) + pow(az6,2)))*(180.0/3.14);
  float accel_ang_y6=atan(-ax6/sqrt(pow(ay6,2) + pow(az6,2)))*(180.0/3.14);
  
  //Calcular angulo de rotación con giroscopio y filtro complemento  
  ang_x6 = 0.98*(ang_x_prev6+(gx6/131)*dt6) + 0.02*accel_ang_x6;
  ang_y6 = 0.98*(ang_y_prev6+(gy6/131)*dt6) + 0.02*accel_ang_y6;
  
  
  //ang_x_prev6=ang_x6;
  //ang_y_prev6=ang_y6;

  datos[10] = (int) ang_x6;
  datos[11] = (int) ang_y6;


  digitalWrite(mpu1, HIGH);
  digitalWrite(mpu2, HIGH);
  digitalWrite(mpu3, HIGH);
  digitalWrite(mpu4, HIGH);
  digitalWrite(mpu5, HIGH);
  digitalWrite(mpu6, HIGH);
  digitalWrite(mpu7, LOW);
  sensor7.getAcceleration(&ax7, &ay7, &az7);
  sensor7.getRotation(&gx7, &gy7, &gz7);
  
  dt7 = (millis()-tiempo_prev7)/1000.0;
  tiempo_prev7=millis();
  
  //Calcular los ángulos con acelerometro
  float accel_ang_x7=atan(ay7/sqrt(pow(ax7,2) + pow(az7,2)))*(180.0/3.14);
  float accel_ang_y7=atan(-ax7/sqrt(pow(ay7,2) + pow(az7,2)))*(180.0/3.14);
  
  //Calcular angulo de rotación con giroscopio y filtro complemento  
  ang_x7 = 0.98*(ang_x_prev7+(gx7/131)*dt7) + 0.02*accel_ang_x7;
  ang_y7 = 0.98*(ang_y_prev7+(gy7/131)*dt7) + 0.02*accel_ang_y7;
  
  
  //ang_x_prev7=ang_x7;
  //ang_y_prev7=ang_y7;
  datos[12] = (int) ang_x7;
  datos[13] = (int) ang_y7;

  Serial.print("X1: ");
  Serial.print(datos[0]); 
  Serial.print(" Y1: ");
  Serial.print(datos[1]);
  Serial.print(" X2: ");
  Serial.print(datos[2]); 
  Serial.print(" Y2: ");
  Serial.print(datos[3]);
  Serial.print(" X3: ");
  Serial.print(datos[4]); 
  Serial.print(" Y3: ");
  Serial.print(datos[5]);
  Serial.print(" X4: ");
  Serial.print(datos[6]); 
  Serial.print(" Y4: ");
  Serial.print(datos[7]);
  Serial.print(" X5: ");
  Serial.print(datos[8]); 
  Serial.print(" Y5: ");
  Serial.print(datos[9]);
  Serial.print(" X6: ");
  Serial.print(datos[10]); 
  Serial.print(" Y6: ");
  Serial.print(datos[11]);
  Serial.print(" X7: ");
  Serial.print(datos[12]); 
  Serial.print(" Y7: ");
  Serial.println(datos[13]);

  radio.write(datos, 28);

  delay(1);

}

//funcion de variables

void setOffset(int ax_, int ay_, int az_, int gx_, int gy_, int gz_, MPU6050 h) {
  h.setXAccelOffset(ax_);
  h.setYAccelOffset(ay_);
  h.setZAccelOffset(az_);
  h.setXGyroOffset(gx_);
  h.setYGyroOffset(gy_);
  h.setZGyroOffset(gz_);
}
