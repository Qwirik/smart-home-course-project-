#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* _ssid = "Paranoia";
const char* _password = "Paranoia_Sarmat";

ESP8266WebServer server(80);

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

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
  Serial.begin(9600);   // Инициализация последовательного порта
  // Настройка статического IP-адреса
  IPAddress local_IP(192, 168, 1, 34);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);

  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }

  WiFi.begin(_ssid, _password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(btn_pin1, INPUT_PULLUP); 
  pinMode(btn_pin2, INPUT_PULLUP);  
  pinMode(btn_pin3, INPUT_PULLUP);  
  pinMode(btn_pin4, INPUT_PULLUP);  

  pinMode(led_pin1, OUTPUT);        
  pinMode(led_pin2, OUTPUT);        
  pinMode(led_pin3, OUTPUT);        
  pinMode(led_pin4, OUTPUT);        

  server.on("/led", HTTP_GET, handleLed);
  server.on("/status", HTTP_GET, handleStatus);
  server.on("/ping", HTTP_GET, handlePing); // Регистрация обработчика для /ping
  server.begin();
}

void loop() {
  server.handleClient();

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

void handleLed() {
  if (server.hasArg("pin") && server.hasArg("state")) {
    int pin = server.arg("pin").toInt();
    int state = server.arg("state").toInt();

    // Проверка, что пин является одним из допустимых
    if (pin == led_pin1 || pin == led_pin2 || pin == led_pin3 || pin == led_pin4) {
      digitalWrite(pin, state);
      server.send(200, "text/plain", "OK");
    } else {
      server.send(400, "text/plain", "Invalid pin");
    }
  } else {
    server.send(400, "text/plain", "Missing arguments");
  }
}

void handleStatus() {
  String response = "\n";
  response += "led_1:" + String(digitalRead(led_pin1) ? "\x1b[32m on \x1b[0m" : "\x1b[31m off \x1b[0m") + "\n";
  response += "led_2:" + String(digitalRead(led_pin2) ? "\x1b[32m on \x1b[0m" : "\x1b[31m off \x1b[0m") + "\n";
  response += "led_3:" + String(digitalRead(led_pin3) ? "\x1b[32m on \x1b[0m" : "\x1b[31m off \x1b[0m") + "\n";
  response += "led_4:" + String(digitalRead(led_pin4) ? "\x1b[32m on \x1b[0m" : "\x1b[31m off \x1b[0m");
  response += "";
  server.send(200, "application/json", response);
}

void handlePing() {
  String ipAddress = WiFi.localIP().toString();
  server.send(200, "text/plain", ipAddress);
}