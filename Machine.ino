#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPClient.h>

#define FREQUENCY 500 // send post frequency
#define LED 13

const char* ssid = "Happy_House"; // input your wifi ssid
const char* password = "ab12345678"; // input your password

const String url = "http://192.168.0.2:3000/"; // input your server address
const String data = String ("{\"hello\" : \"hello\"}"); // input your data

void setup(void){
  pinMode(LED, OUTPUT);
  digitalWrite(LED, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connecting to Wifi....\n");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop(void){
  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.POST(data);
  http.end();
  if (httpCode = 200){
    Serial.print("Sended Data to ");
    Serial.print(url);
    Serial.println(data);
  }
  else{
    Serial.println("Failed to send");
  }
  delay(FREQUENCY);
}
