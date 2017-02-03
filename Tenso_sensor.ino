#include <Q2HX711.h>

const byte hx711_data_pin = A2;
const byte hx711_clock_pin = A3;
const int probe_pin = 7;

long trigger = 200;
int tolerance = 5;
long weight = 0;
long prev_weight = 0;
long trigger_weight = 0;
bool is_pressed = false;
long act_weight = 0;

Q2HX711 hx711(hx711_data_pin, hx711_clock_pin);

void setup() {
  Serial.begin(9600);
  delay(3000);
  prev_weight = weight = hx711.read() >> 8;
  Serial.println(prev_weight);
  pinMode(probe_pin, OUTPUT);
  digitalWrite(probe_pin, LOW);
}

void loop() {
  weight = hx711.read() >> 8;
//  Serial.println(weight);

  if (is_pressed) {
//    char buffer [50];
//    sprintf (buffer, "Current [%li] trigger [%li]", weight, trigger_weight);

//    Serial.println(buffer);
    if ((trigger_weight - tolerance) <= weight) {
//      sprintf (buffer, "Trigger released! [%li]", weight);
//      Serial.println(buffer);
    
      digitalWrite(probe_pin, LOW);
      is_pressed = false;
//      delay(100);
    } 
  } else {
//    if (weight > prev_weight) weight = prev_weight;
    if ((prev_weight - weight) >= trigger) {
//      char buffer [50];
//      sprintf (buffer, "Trigger fired! [%li]", weight);
//      
//      Serial.println(buffer);
    
      digitalWrite(probe_pin, HIGH);
      is_pressed = true;
      trigger_weight = prev_weight;
    }
    
    prev_weight = weight;  
  }
//  delay(500);
}
