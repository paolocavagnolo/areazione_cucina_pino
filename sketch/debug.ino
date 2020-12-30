#include "DHT.h"
#include "RunningAverage.h"
#include<ADS1115_WE.h> 
#include<Wire.h>

#define I2C_ADDRESS 0x48

#define VE1_VE 8
#define VE1_EN 7
#define R1_3 6
#define VA1 5

#define VE2_VE 12
#define VE2_EN 11
#define R2_3 10
#define VA2 9

#define DHTPIN_1 4
#define DHTPIN_2 3

#define DHTTYPE DHT22

ADS1115_WE adc(I2C_ADDRESS);
RunningAverage myRA(5);

DHT dht1(DHTPIN_1, DHTTYPE);
DHT dht2(DHTPIN_2, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  pinMode(VE1_VE,OUTPUT);
  pinMode(VE1_EN,OUTPUT);
  pinMode(R1_3,OUTPUT);
  pinMode(VA1,OUTPUT);

  pinMode(VE2_VE,OUTPUT);
  pinMode(VE2_EN,OUTPUT);
  pinMode(R2_3,OUTPUT);
  pinMode(VA2,OUTPUT);

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

  digitalWrite(VE1_VE,HIGH);
  digitalWrite(VE1_EN,HIGH);
  digitalWrite(R1_3,HIGH);
  digitalWrite(VA1,HIGH);

  digitalWrite(VE2_VE,HIGH);
  digitalWrite(VE2_EN,HIGH);
  digitalWrite(R2_3,HIGH);
  digitalWrite(VA2,HIGH);

  
}

String inS;

void loop() {

  float hIN = dht1.readHumidity();
  float tIN = dht1.readTemperature();
  float hOUT = dht2.readHumidity();
  float tOUT = dht2.readTemperature();

  float voltage = 0.0;
  voltage = adc.getResult_mV();
  myRA.addValue(abs(voltage));
 

  while (Serial.available()) {
    inS = Serial.readString();
  }

    
  if (inS == "v1 on") {
  
    digitalWrite(VE1_EN,LOW);
    Serial.println(inS);
  
  }
    
  else if (inS == "v1 off") {
  
    digitalWrite(VE1_EN,HIGH);
    Serial.println(inS);
  
  }
    
  else if (inS == "v1 l") {
  
    digitalWrite(VE1_VE,HIGH);
    Serial.println(inS);
  
  }
  
  else if (inS == "v1 h") {
  
    digitalWrite(VE1_VE,LOW);
    Serial.println(inS);
  
  }
    
  else if (inS == "v2 on") {
  
    digitalWrite(VE2_EN,LOW);
    Serial.println(inS);
  
  }
    
  else if (inS == "v2 off") {
  
    digitalWrite(VE2_EN,HIGH);
    Serial.println(inS);
  
  }
    
  else if (inS == "v2 l") {
  
    digitalWrite(VE2_VE,HIGH);
    Serial.println(inS);
  
  }
  
  else if (inS == "v2 h") {
  
    digitalWrite(VE2_VE,LOW);
    Serial.println(inS);
  
  }
  
  else if (inS == "valv1 o") {
  
    digitalWrite(VA1,LOW);
    Serial.println(inS);
  
  }
  
  else if (inS == "valv1 c") {
  
    digitalWrite(VA1,HIGH);
    Serial.println(inS);
  
  }
    
  else if (inS == "valv2 o") {
  
    digitalWrite(VA2,LOW);
    Serial.println(inS);
  
  }
  
  else if (inS == "valv2 c") {
  
    digitalWrite(VA2,HIGH);
    Serial.println(inS);
  
  }
  
  else if (inS == "current") {
  
    Serial.println(myRA.getAverage());
  
  }
  
  else if (inS == "in") {
  
    Serial.print(hIN);
    Serial.print(" %\t");
    Serial.print(tIN);
    Serial.println(" °");
  
  }
  
  else if (inS == "out") {
  
    Serial.print(hOUT);
    Serial.print(" %\t");
    Serial.print(tOUT);
    Serial.println(" °");
  
  }
  
  else {
    Serial.println("Guida:");
    Serial.println("v1 off");
    Serial.println("v1 l");
    Serial.println("v1 h");
    Serial.println("v2 on");
    Serial.println("v2 off");
    Serial.println("v2 l");
    Serial.println("v2 h");
    Serial.println("valv1 o");
    Serial.println("valv1 c");
    Serial.println("valv2 o");
    Serial.println("valv2 c");
    Serial.println("current");
    Serial.println("in");
    Serial.println("out");
  }
  

  delay(500);

}
