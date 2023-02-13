//BasicHTTP Edit

#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#define USE_SERIAL Serial

WiFiMulti wifiMulti;

String payload;

void setup() {

    USE_SERIAL.begin(115200);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    wifiMulti.addAP("ChosenUndead", "LordOfCinders");

}

void loop() {
    // wait for WiFi connection
    if((wifiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
        http.begin("https://api-v3.mbta.com/predictions?filter[stop]=place-balsq&sort[arrival_time]"); //HTTP. -----------FIX THIS


        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println("payload would be here");
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
						//----------PRINT ERROR TO MATRIX
        }

        http.end();
    }

    // Stream& input;

    StaticJsonDocument<0> filter;
    filter.set(true);

    StaticJsonDocument<4096> doc;

    DeserializationError error = deserializeJson(doc, payload, DeserializationOption::Filter(filter));

    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }

    for (JsonObject data_item : doc["data"].as<JsonArray>()) { //---------What is this loop condition 

      const char* data_item_attributes_departure_time = data_item["attributes"]["departure_time"];
      // data_item["attributes"]["status"] is null

      const char* data_item_id = data_item["id"]; // "prediction-54541192-70509-700", ...

      for (JsonPair data_item_relationship : data_item["relationships"].as<JsonObject>()) {
        const char* data_item_relationship_key = data_item_relationship.key().c_str(); // "route", "stop", ...

        const char* data_item_relationship_value_data_id = data_item_relationship.value()["data"]["id"];
        const char* data_item_relationship_value_data_type = data_item_relationship.value()["data"]["type"];

      }

      const char* data_item_type = data_item["type"]; // "prediction", "prediction"

    }

    const char* jsonapi_version = doc["jsonapi"]["version"]; // "1.0"

    JsonObject links = doc["links"];
    const char* links_first = links["first"];
    const char* links_last = links["last"];
    const char* links_next = links["next"];

    
    //USE_SERIAL.println(data_item_); //Fix this shit - do I need to define these ahead of time?
    delay(6000);
}