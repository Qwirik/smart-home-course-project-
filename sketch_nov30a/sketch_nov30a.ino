#include <ESP8266WiFi.h>


const char* _ssid = "Paranoia";
const char* _password = "Paranoia_Sarmat" ;
// Определение пинов кнопок и светодиодов
const int btn_pin1 = 3;
const int btn_pin2 = 5;
const int btn_pin3 = 4;
const int btn_pin4 = 2;

const int led_pin1 = 14;
const int led_pin2 = 12;
const int led_pin3 = 13;
const int led_pin4 = 15;

bool btn_state1 = false;
bool btn_state2 = false;
bool btn_state3 = false;
bool btn_state4 = false;

void setup() {
  WIFIinit();

  Serial.begin(9600);   // Инициализация последовательного порта
  pinMode(btn_pin1, INPUT_PULLUP); 
  pinMode(btn_pin2, INPUT_PULLUP);  
  pinMode(btn_pin3, INPUT_PULLUP);  
  pinMode(btn_pin4, INPUT_PULLUP);  

  pinMode(led_pin1, OUTPUT);        
  pinMode(led_pin2, OUTPUT);        
  pinMode(led_pin3, OUTPUT);        
  pinMode(led_pin4, OUTPUT);        
}

void loop() {
  // Проверка состояния каждой кнопки
  checkButton(btn_pin1, &btn_state1, led_pin1);
  checkButton(btn_pin2, &btn_state2, led_pin2);
  checkButton(btn_pin3, &btn_state3, led_pin3);
  checkButton(btn_pin4, &btn_state4, led_pin4);
}

void checkButton(int btn_pin, bool *btn_state, int led_pin) {
  int currentBtnState = digitalRead(btn_pin);

  if (currentBtnState == LOW && *btn_state == true) {
    delay(50);
    *btn_state = false;
    digitalWrite(led_pin, !digitalRead(led_pin));
  } else if (currentBtnState == HIGH && *btn_state == false) {
    *btn_state = true;
  }
}
