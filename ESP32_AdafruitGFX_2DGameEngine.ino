#include <Adafruit_GFX.h>    // Core graphics library
#include <XTronical_ST7735.h> // Hardware-specific library
#include <SPI.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "Graphics.h"

// set up pins we are going to use to talk to the screen
#define TFT_DC     2       // register select (stands for Data Control perhaps!)
#define TFT_RST   4         // Display reset pin, you can also connect this to the ESP32 reset
// in which case, set this #define pin to -1!
#define TFT_CS   5       // Display enable (Chip select), if not enabled will not talk on SPI bus

// initialise the routine to talk to this display with these pin connections (as we've missed off
// TFT_SCLK and TFT_MOSI the routine presumes we are using hardware SPI and internally uses 13 and 11
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
Graphics gfx = Graphics(&tft);

// WLAN sektion
char* ssid = "WLAN-C6QFYT";
const char* password = "4258803659978466";

// Webserver
WebServer server(80);

int arrowRotation = 0;

void setup(void) {
  Serial.begin(115200);
  tft.init();   // LCD init
  tft.setRotation(0);
  Serial.println("LCD init finished");
  DrawLoadingScreen(10);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); // WIFI connect
  DrawLoadingScreen(20);
  delay(500);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  DrawLoadingScreen(35);
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Signalstärke: ");
  Serial.print(GetWifiStrength(10));
  Serial.println("");

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }
  DrawLoadingScreen(50);
  server.on("/", handleRoot);
  server.on("/test", handleTest);
  server.on("/map", handleMap);
  server.begin();
  DrawLoadingScreen(75);
  btStop();
  DrawLoadingScreen(80);

  Serial.println("Start GUI task");
  xTaskCreate(
                    taskOne,          /* Task function. */
                    "GUI task",        /* String with name of task. */
                    10000,            /* Stack size in words. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);            /* Task handle. */
 
  Serial.println("Start webserver task");
  xTaskCreate(
                    taskTwo,          /* Task function. */
                    "Webserver task",        /* String with name of task. */
                    10000,            /* Stack size in words. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);            /* Task handle. */
  
}

///
///
/// Task One (Core 0)
///
///

void taskOne( void * parameter )
{
  while(1)
  {
    DrawTopThreeNetworks();
    //DrawRotatingArrow();
    delay(50); // delay wird hier benötigt um dem Watchdog zeit zu geben
  }
  vTaskDelete( NULL );
}

///
///
/// Task Two (Core 1)
///
///

void taskTwo( void * parameter)
{
  while(1)
  {
    server.handleClient();
  }
  vTaskDelete( NULL );
}

///
///
/// loop function
/// 
///

void loop() {
  delay(1000);
}

///
///
/// WebServer handling
///
///

void handleRoot() 
{
  char temp[400];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

  snprintf(temp, 400,
           "<html>\
              <head>\
                <meta http-equiv='refresh' content='5'/>\
                <title>ESP32 Demo</title>\
                <style>\
                  body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
                </style>\
              </head>\
              <body>\
                <h1>Hello from ESP32!</h1>\
                <p>Uptime: %02d:%02d:%02d</p>\
                <img src=\"/test.svg\" />\
              </body>\
            </html>",
           hr, min % 60, sec % 60
          );
  server.send(200, "text/html", temp);
}

void handleTest()
{
  String message = "Number of args received:";
  message += server.args();
  message += "\n";
  for (int i = 0; i < server.args(); i++) {
    message += "Arg nr " + String(i) + " -> ";
    message += server.argName(i) + ": ";
    message += server.arg(i) + "\n";
  } 
  server.send(200, "text/plain", message);
  Serial.println(message);
}

void handleMap()
{
  String password = "";

  for (int i = 0; i < server.args(); i++) {
    if (server.argName(i) == "password")
    {
      password = server.arg(i);
    }
  } 

  if (password == "test")
  {
    server.send(200, "text/plain", "yay");
  }
  else
  {
    server.send(402, "text/plain");
  }
}

///
///
/// Graphics calculation
///
///

void DrawRotatingArrow()
{
  uint16_t time = millis();
  tft.fillScreen(ST7735_BLACK);
  time = millis() - time;
  drawArrow(ST7735_WHITE, 48, 32, .5, arrowRotation);

  tft.displayBuffer();

  arrowRotation += 30;
  if (arrowRotation >= 360)
  {
    arrowRotation = 0;
  }
}

void drawArrow(uint16_t color, int x, int y, float factor, int rotation)
{
  int width = 32 * factor;
  int height = 64 * factor;
  int arrowHeight = 32 * factor;
  int constant = 10 * factor;

  //Spitze
  int ax = x + (width / 2);
  int ay = y + height + arrowHeight;

  int bx = x - constant;
  int by = y + height;

  int cx = x + width + constant - 1;
  int cy = y + height - 1;

  //Transformierung des Origin zu (0,0) für die rotation
  int transformedax = ax - x - width / 2;
  int transformeday = ay - y - height / 2;

  int transformedbx = bx - x - width / 2;
  int transformedby = by - y - height / 2;

  int transformedcx = cx - x - width / 2;
  int transformedcy = cy - y - height / 2;

  float rad = rotation * PI / 180;

  // Transformierung und rotation
  ax = transformedax * cos(rad) - transformeday * sin(rad) + x + width / 2;
  ay = transformeday * cos(rad) + transformedax * sin(rad) + y + height / 2;

  bx = transformedbx * cos(rad) - transformedby * sin(rad) + x + width / 2;
  by = transformedby * cos(rad) + transformedbx * sin(rad) + y + height / 2;

  cx = transformedcx * cos(rad) - transformedcy * sin(rad) + x + width / 2;
  cy = transformedcy * cos(rad) + transformedcx * sin(rad) + y + height / 2;

  gfx.drawRect(x, y, width, height, rotation, color);

  gfx.drawTriangle( ax,
                    ay,
                    bx,
                    by,
                    cx,
                    cy,
                    0,
                    color);
}

void DrawLoadingScreen(int percentage)
{
  tft.fillScreen(ST7735_BLACK);
  int margin = 5;
  int step = (128 - (2 * margin)) / 100;
  gfx.drawText(36, 54, "Loading", ST7735_GREEN);
  gfx.drawHLine(margin, margin + step * percentage, 64, ST7735_GREEN);
  gfx.drawText(52, 70, String(percentage), ST7735_GREEN);
  tft.displayBuffer();
}


///
///
/// Funcionality
///
///

void DrawTopThreeNetworks()
{
  tft.fillScreen(ST7735_BLACK);

  int numberOfNetworks = WiFi.scanNetworks();
  String ssidList[8];
  int ssidStrenghts[8];

  if (numberOfNetworks > 8)
  {
    numberOfNetworks = 8;
  }

  for(int i =0; i<numberOfNetworks; i++)
  {
    ssidList[i] = WiFi.SSID(i);
    ssidStrenghts[i] = GetWifiStrengthForSSID(5, i);
  }

  int best = 0;
  int secondBest = 1;
  int thirdBest = 2;

  // Sortiere Array



  String msg = ssidList[best] + " " + ssidStrenghts[best] + "\n\n" +
              ssidList[secondBest] + " " + ssidStrenghts[secondBest] + "\n\n" +
              ssidList[thirdBest] + " " + ssidStrenghts[thirdBest];

  gfx.drawText(msg, ST7735_BLUE);
  
  tft.displayBuffer();
  //free(cMsg);
}

///
///
/// Extension Methoden
///
///

int GetWifiStrength(int points){
  long rssi = 0;
  long averageRSSI=0;
  
  for (int i=0;i < points;i++){
      rssi += WiFi.RSSI();
      delay(20);
  }

  averageRSSI=rssi/points;
  return averageRSSI;
}

int GetWifiStrengthForSSID(int points, int number){
  long rssi = 0;
  long averageRSSI=0;
  
  for (int i=0;i < points;i++){
      rssi += WiFi.RSSI(number);
      delay(20);
  }

  averageRSSI=rssi/points;
  return averageRSSI;
}
