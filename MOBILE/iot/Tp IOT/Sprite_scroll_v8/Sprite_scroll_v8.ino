#include <TFT_eSPI.h>
#include <SPI.h>
TFT_eSPI tft = TFT_eSPI();

void showScrn1(String ipAddress) {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setCursor(0, 30);
  tft.setFreeFont(&Orbitron_Light_24);
  tft.println("Berkane-Begoug");
  tft.drawLine(0, 35, 250, 35, TFT_BLUE);
  tft.setCursor(80, 60);
  tft.print("TP IOT");
  tft.setCursor(10, 90);
  tft.print(ipAddress);
  tft.setCursor(10, 120);
  tft.print("2021/2022");
}
//==========================================================================================
void setup() {
   Serial.begin(115200);
  tft.begin();
  tft.setRotation(1); //Landscape
  showScrn1("192.168.75.12");
}

//==========================================================================================
void loop() {
  


} // Loop back and do it all again
//==========================================================================================
