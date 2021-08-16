#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
  const char* ssid = "";
  const char* password = "";
const int drop = 150;   
#define BOTtoken ""  // Ваш Токен
#define CHAT_ID ""                                      

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

const int gasSensor = 12;  
const int motionSensor = 13;                                      // PIR датчик
bool motionDetected = false;
bool gasDetected = false;

void ICACHE_RAM_ATTR detectsMovement() {
  //Serial.println("Обнаружено движение!!!");
  motionDetected = true;
}
  void ICACHE_RAM_ATTR detectsGas() {
  //Serial.println("Обнаружено газ!!!");
  gasDetected = true;
}
void setup() {
  Serial.begin(115200);
  client.setInsecure();
 pinMode(gasSensor, INPUT_PULLUP);                            
  pinMode(motionSensor, INPUT_PULLUP);   
  // Внутренняя подтяжка PIR  INPUT_PULLUP
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);
  attachInterrupt(digitalPinToInterrupt(gasSensor), detectsGas, RISING);
  // Attempt to connect to Wifi network:
  Serial.print("Соединение с Wifi: ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi соединение установлено");
  Serial.print("IP адрес: ");
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID, "Бот стартовал", "");
}
void loop() {
   if(gasDetected){
    bot.sendMessage(CHAT_ID, "Кожаный ублюдки забыли выключить газ!", "");
    Serial.println("Обнаружен газ");
    gasDetected = false;
  }
   if(motionDetected){
    bot.sendMessage(CHAT_ID, "Кожаный ублюдки зашли в дом!", "");
    Serial.println("Обнаружено движение");
    motionDetected = false;
  }
}
