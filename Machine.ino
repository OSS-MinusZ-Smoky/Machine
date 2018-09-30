#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPClient.h>

#define FREQUENCY 5000 // send post frequency 1=1ms
#define ALALOGPIN A0 // MQ-7 Sensor 

const char* SSID = "wifi ssid"; // input your wifi ssid
const char* PASSWORD = "wifi password"; // input your password

const String URL = "http://192.168.43.225:3000/"; // input your server address


ESP8266WebServer server(80);

void pingCheck(){
  server.send(200,"text/plain","im on!!!");
}

void setup(void){
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connecting to Wifi....\n");
  }

  //Connection success
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(SSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/",pingCheck);
  server.begin();
}

void loop(void){
  int Sensor = analogRead(A0); // Read sensor value

  //Send data
  HTTPClient http;
  http.begin(URL);
  http.addHeader("Content-Type", "application/json");
  String data = String ("{\"state\":\"")+String(Sensor)+String("\"}");   // input your data
  int httpCode = http.POST(data);
  http.end();

   
  if (httpCode == 200){
    Serial.print("Sended Data to ");
    Serial.print(URL);
    Serial.print(" ");
    Serial.println(data);
  }
  else{
    Serial.println("Failed to send");
  }
  delay(FREQUENCY);
  server.handleClient();
}
