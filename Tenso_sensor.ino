#include <Q2HX711.h>

const byte hx711_data_pin = A2;
const byte hx711_clock_pin = A3;
const int probe_pin = 7;
const bool DEBUG = false;


long trigger = 12000; //Weight difference trigger. Lower is better
int tolerance = 3000; //
long weight, prev_weight, trigger_weight = 0;
bool is_pressed = false;


long timest = millis();

Q2HX711 hx711(hx711_data_pin, hx711_clock_pin);

void setup() {
  pinMode(probe_pin, OUTPUT);
  digitalWrite(probe_pin, LOW);
  
  Serial.begin(9600);
  delay(3000);

  prev_weight = weight = hx711.read();
  Serial.println(prev_weight);
}

void loop() {
  weight = hx711.read();
  if (DEBUG) {
    if (timest+500 <= millis()) {
      Serial.println(weight);
      timest = millis();    
    }  
  }
  


  if (is_pressed) {
    if (DEBUG) {
       char buffer [50];
       sprintf (buffer, "Current [%li] trigger [%li]", weight, trigger_weight);

       Serial.println(buffer);  
    }
    
    if ((trigger_weight + tolerance) >= weight) {
      if (DEBUG) {
        char buffer [50];
        sprintf (buffer, "Trigger released! [%li]", weight);
        Serial.println(buffer);  
      }
      
      digitalWrite(probe_pin, LOW);
      is_pressed = false;
    } 
  } else {
    if ((weight - prev_weight) >= trigger) {
      if (DEBUG) {
        char buffer [50];
        sprintf (buffer, "Trigger fired! [%li]", weight);
        Serial.println(buffer);  
      }
      
      digitalWrite(probe_pin, HIGH);
      is_pressed = true;
      trigger_weight = weight;
    }
    
    prev_weight = weight;  
  }
}
