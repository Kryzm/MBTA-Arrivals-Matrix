//---------------------------------------Screen setup
#include <PxMatrix.h>
#define P_LAT 16
#define P_A 5
#define P_B 4
#define P_C 15
#define P_D 12
#define P_E 0
#define P_OE 2
#define PxMATRIX_COLOR_DEPTH 3
#define matrix_width 64
#define matrix_height 32
#include <Ticker.h>
Ticker display_ticker;
uint8_t display_draw_time=60;
PxMATRIX display(64,32,P_LAT,P_OE,P_A,P_B,P_C,P_D);
uint16_t myColor = display.color565(255,40,0); //--Orange

void display_updater() //----------------------------Need to look up how these two voids work
{
  display.display(display_draw_time);
}

void display_update_enable(bool is_enable)
{
if (is_enable)
  display_ticker.attach(0.004, display_updater);
else
  display_ticker.detach();
}

//-----------------------------------Wifi setup
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
ESP8266WiFiMulti WifiMulti;
int httpCode;

#include <ArduinoJson.h>
StaticJsonDocument<768> doc; //-----------------------------JSON doc

void setup() {
  Serial.begin(115200);
  Serial.println();
  display.begin(16);
  Serial.println("Display starting...");
  display.setColorOrder(BBRRGG);
  display.setBrightness(200);
  display.clearDisplay();
  display.setTextSize(4);
  display.setTextColor(myColor);
  display.setCursor(23,2);
  display.print("T"); // -------------------------------------------Replace this with actual logo
  Serial.println("Display test...");
  display_update_enable(true);
  delay(5000);
  display.clearDisplay();

  WiFi.mode(WIFI_STA);
  WifiMulti.addAP("ChosenUndead", "LordOfCinders");
}



void loop() {
  display.setTextWrap(false);
  display.setTextSize(1);
  display.setCursor(3,3);
  
  if((WifiMulti.run() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;
    Serial.println("HTTP Begin");
    if (http.begin(client, "http://worldtimeapi.org/api/timezone/America/New_York")) {
      Serial.println("HTTP Get");
      httpCode = http.GET();
      if(httpCode > 0) {
        Serial.println(httpCode);
          if(httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            Serial.println(payload);
            DeserializationError error = deserializeJson(doc, payload);
            if (error) {
              Serial.print(F("deserializeJson() failed: "));
              Serial.println(error.f_str());
              return;
            }
            String datetime = doc["datetime"]; // "2023-05-12T00:34:57.949761-04:00"

            String Clock = datetime.substring(11,19);
            display.clearDisplay();
            display.print(Clock);
            delay(1000);
            }
      }
    }
    else {
      Serial.println(http.errorToString(httpCode).c_str());
    }
    http.end();
  }
}
/*
  Serial.println("Displaying arrival");
  
  display.print("E Train  8");
  display.setCursor(3,20);
  display.print("D Train  4");
  delay(10000);
}*/
