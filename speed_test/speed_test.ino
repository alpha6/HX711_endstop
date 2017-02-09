#include <Q2HX711.h>

const byte hx711_data_pin = A2;
const byte hx711_clock_pin = A3;
const int probe_pin = 7;

const int readCount = 100;

Q2HX711 hx711(hx711_data_pin, hx711_clock_pin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:

  long startTime = millis();
  for (int i = 0; i<readCount; i++) {
    hx711.read();
  }
  long endTime = millis();
  long timeDiff = endTime-startTime;
  div_t rps = div(timeDiff, readCount);
  
  char buffer [50];
  sprintf(buffer, "Time per %d reads - %li. %i ms per request", readCount, timeDiff, rps.quot);
  
  Serial.println(buffer);

}
