#include <Q2HX711.h>

# HX711 Library source https://github.com/ConnectedHealthFoundry/Q2HX711

const bool DEBUG = false;

const byte hx711_data_pin = A2;
const byte hx711_clock_pin = A3;
const int probe_pin = 7;

long trigger = 13000; //Weight difference trigger. Lower is better

long weight, prev_weight, trigger_weight = 0;
bool is_pressed = false;



//Filter parameters
float FK = 0.9;
int tolerance = 3000; //
int values_count = 5; //HX711 speed is 80Hz or near this value. To get 10 values the sensor need around 120ms.

long timest = millis();

Q2HX711 hx711(hx711_data_pin, hx711_clock_pin);


//Get filtered values from HX711
long getSensorValue() { //
    long acc_x_raw, acc_x, acc_xf;
    
    for (int i = 0; i < values_count; i++) {
       acc_x_raw = hx711.read();
       acc_x = acc_x_raw - tolerance/1.0;
       acc_xf = (1-FK)*acc_xf + FK*acc_x; 
    }
    
    return acc_xf;
}

void setup() {
  pinMode(probe_pin, OUTPUT);
  digitalWrite(probe_pin, LOW);
  
  Serial.begin(115200);
  delay(1000);

  prev_weight = weight = getSensorValue();
  Serial.println(prev_weight);
}

void loop() {
  weight = getSensorValue();
  
  if (DEBUG) {
    if (timest+500 <= millis()) {
      char buffer [50];
      sprintf (buffer, "current weight! [%li] [%li]", weight, prev_weight);
      Serial.println(buffer);
      timest = millis();    
    }  
  }
  
  if (is_pressed) {
    if (DEBUG) {
       char buffer [50];
       sprintf (buffer, "Current [%li] trigger [%li]", weight, trigger_weight);

       Serial.println(buffer);  
    }
    
    if (trigger_weight >= weight) {
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
