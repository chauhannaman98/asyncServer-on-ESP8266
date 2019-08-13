#include "ESP8266WiFi.h"
#include "ESPAsyncTCP.h"
#include "ESPAsyncWebServer.h"
#include "ArduinoJson.h"
#include "AsyncJson.h"
 
const char* ssid = "ArGee";
const char* password =  "i6et72qnt6";

char* iot_kit_key=" ";
int device_key;
int run_time_mins;
 
AsyncWebServer server(80);
 
void setup(){
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println(WiFi.localIP());
 
  server.on("/trigger_command", HTTP_PUT, [](AsyncWebServerRequest *request){
    Serial.println("Request received!");

    /*JSON body handling as a request*/
    AsyncCallbackJsonWebHandler* handler = 
        new AsyncCallbackJsonWebHandler("/trigger_command", [](AsyncWebServerRequest *request, JsonVariant &json) {
      JsonObject& jsonObj = json.as<JsonObject>();
      // ...
    });
    server.addHandler(handler);

    /*JSON Response Stream*/
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    DynamicJsonBuffer jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["command_executed"] = true;
    root["message"] = "Command executed successfully";
    root.printTo(*response);
    request->send(response);
  });
 
  server.begin();
}
 
void loop(){}
