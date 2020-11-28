#include "DHT.h"
#include "RunningAverage.h"
#include<ADS1115_WE.h> 
#include<Wire.h>

#define I2C_ADDRESS 0x48

#define R1_1 8
#define R1_2 7
#define R1_3 6
#define R1_4 5

#define R2_1 12
#define R2_2 11
#define R2_3 10
#define R2_4 9

#define DHTPIN_1 4
#define DHTPIN_2 3

#define DHTTYPE DHT22

ADS1115_WE adc(I2C_ADDRESS);
RunningAverage myRA(5);

DHT dht1(DHTPIN_1, DHTTYPE);
DHT dht2(DHTPIN_2, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  pinMode(R1_1,OUTPUT);
  pinMode(R1_2,OUTPUT);
  pinMode(R1_3,OUTPUT);
  pinMode(R1_4,OUTPUT);

  pinMode(R2_2,OUTPUT);
  pinMode(R2_3,OUTPUT);
  pinMode(R2_4,OUTPUT);
  pinMode(R2_1,OUTPUT);

  pinMode(A0,INPUT_PULLUP);
  pinMode(A1,INPUT_PULLUP);

  myRA.clear();
  Wire.begin();

  Serial.begin(9600);

  dht1.begin();
  dht2.begin();

  adc.setVoltageRange_mV(ADS1115_RANGE_2048);
  adc.setCompareChannels(ADS1115_COMP_0_1);
  adc.setMeasureMode(ADS1115_CONTINUOUS);

  digitalWrite(R1_1,HIGH);
  digitalWrite(R1_2,HIGH);
  digitalWrite(R1_3,HIGH);
  digitalWrite(R1_4,HIGH);

  digitalWrite(R2_2,HIGH);
  digitalWrite(R2_3,HIGH);
  digitalWrite(R2_4,HIGH);
  digitalWrite(R2_1,HIGH);

  
}

void loop() {

  float h1 = dht1.readHumidity();
  float t1 = dht1.readTemperature();
  float h2 = dht2.readHumidity();
  float t2 = dht2.readTemperature();

  Serial.print(F("Humidity: "));
  Serial.print(h1);
  Serial.print(F("%  Temperature: "));
  Serial.print(t1);
  Serial.println(F("°C "));
  Serial.print(F("Humidity2: "));
  Serial.print(h2);
  Serial.print(F("%  Temperature2: "));
  Serial.print(t2);
  Serial.println(F("°C "));

  float voltage = 0.0;
  voltage = adc.getResult_mV();
  myRA.addValue(abs(voltage));
  Serial.println(myRA.getAverage());
  
  delay(1000);

}
