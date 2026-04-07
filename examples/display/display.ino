#include <GxEPD2_7C.h>
#include <Fonts/FreeMonoBold9pt7b.h>

#include <Wire.h>
#include <SPI.h>

// EPD SPI
#define PIN_DC     8
#define PIN_CS     9
#define PIN_SCK    10
#define PIN_MOSI   11
#define PIN_MISO   -1
#define PIN_RST    12
#define PIN_BUSY   13

GxEPD2_7C<GxEPD2_730c_GDEP073E01, GxEPD2_730c_GDEP073E01::HEIGHT> display(
  GxEPD2_730c_GDEP073E01(PIN_CS, PIN_DC, PIN_RST, PIN_BUSY)
);

const char HelloWorld[] = "Hello World!";

void setup() {
    Serial.begin(115200);

    SPI.begin(PIN_SCK, PIN_MISO, PIN_MOSI, PIN_CS);

    display.init(115200, true, 2, false);

    display.setRotation(1);
    display.fillScreen(GxEPD_WHITE);

    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(10, 10);
    display.print(HelloWorld);

    display.display();

    display.hibernate();
}

void loop() {
  delay(1000);
}
