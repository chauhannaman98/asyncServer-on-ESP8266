#include "ESP8266WiFi.h"
#include "ESPAsyncTCP.h"
#include "ESPAsyncWebServer.h"
#include "ArduinoJson.h"
#include "AsyncJson.h"
 
const char* ssid = "SSID";
const char* password =  "PASSWORD";

char* iot_kit_key;
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
    //nothing and dont remove it
  }, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)  {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject((const char*)data);
    if (root.success()) {
      if (root.containsKey("iot_kit_key")) {
        Serial.print("iot_kit_key: ");
        Serial.println(root["iot_kit_key"].asString());
      }
      if (root.containsKey("device_key")) {
        Serial.print("device_key: ");
        Serial.println(root["device_key"].asString());
      }
      if (root.containsKey("run_time_mins")) {
        Serial.print("run_time_mins: ");
        Serial.println(root["run_time_mins"].asString());
      }
      
      /*JSON Response Stream*/
      AsyncResponseStream *response = request->beginResponseStream("application/json");
      DynamicJsonBuffer jsonBuffer;
      JsonObject &root = jsonBuffer.createObject();
      root["command_executed"] = true;
      root["message"] = "Command executed successfully";
      root.printTo(*response);
      request->send(response);
    } else {
      request->send(404, "text/plain", "");
    }
  });

  server.begin();
}
 
void loop(){}
