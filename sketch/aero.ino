#include "DHT.h"

#define DHTPIN_IN 8
#define DHTPIN_OUT 9

//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht_in(DHTPIN_IN, DHTTYPE);
DHT dht_out(DHTPIN_OUT, DHTTYPE);

uint8_t leggiCorrente();

void setup() {
  // put your setup code here, to run once:
  dht_in.begin();
  dht_out.begin();

  pinMode(A0,INPUT);
  
}

float h_in = 0;
float t_in = 0;
float h_out = 0;
float t_out = 0;

uint8_t cCottura = 0; //0: spento - 1: bassa - 2: media - 3: alta

bool appenaSpento = 0;
long tSpegnimento = 0;

void loop() {


  h_in = dht_in.readHumidity();
  t_in = dht_in.readTemperature();
  h_out = dht_out.readHumidity();
  t_out = dht_out.readTemperature();

  cCottura = leggiCorrente();

  if (cCottura > 0) {
    appenaSpento = true;
    
    switch (cCottura) {
      case 1:
        valvola2(true);
        ventola2(0);
        break;
      case 2:
        valvola2(true);
        ventola2(1);
        break;
      case 3:
        valvola2(true);
        ventola2(2);
        break;
    }
  }
  else {
    if (appenaSpento) {
      tSpegimento = millis();
      appenaSpento = false;
    }

    if ((millis() - tSpegimento) > 300000) { //DA 5 MINUTI
      if ()
    }
  }
  

  
  
  
  delay(2000);
}

uint8_t leggiCorrente() {
  if (analogRead(A0) < 10) {
    return 0;
  }
  else if (analogRead(A0) < 50) {
    return 1;
  }
  else if (analogRead(A0) < 200) {
    return 2;
  }
  else {
    return 3;
  }
}
