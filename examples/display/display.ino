#include <GxEPD2_7C.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <XPowersLib.h>

#include <Wire.h>
#include <SPI.h>

#define I2C_SDA    47
#define I2C_SCL    48

#define PIN_DC     8
#define PIN_CS     9
#define PIN_SCK    10
#define PIN_MOSI   11
#define PIN_MISO   -1
#define PIN_RST    12
#define PIN_BUSY   13

#define DISPLAY_WIDTH   800
#define DISPLAY_HEIGHT  480

XPowersAXP2101 pmu;

GxEPD2_7C<GxEPD2_730c_GDEP073E01, GxEPD2_730c_GDEP073E01::HEIGHT> display(
  GxEPD2_730c_GDEP073E01(PIN_CS, PIN_DC, PIN_RST, PIN_BUSY)
);

const uint16_t supported_colours[] = { GxEPD_BLACK, GxEPD_WHITE, GxEPD_YELLOW, GxEPD_RED, GxEPD_BLUE, GxEPD_GREEN };

void setup() {
    Serial.begin(115200);

    // enable power to the display
    Wire.begin(I2C_SDA, I2C_SCL);
    pmu.begin(Wire, AXP2101_SLAVE_ADDRESS, I2C_SDA, I2C_SCL);
    pmu.setALDO4Voltage(3300);
    pmu.enableALDO4();

    // init display
    SPI.begin(PIN_SCK, PIN_MISO, PIN_MOSI, PIN_CS);
    display.init(115200, true, 2, false);

    display.setRotation(2);
    display.fillScreen(GxEPD_WHITE);

    // loop over the 6 colours supported by the display
    int bar_w = DISPLAY_WIDTH / 6;
    for (int i = 0; i < 6; i++) {
      display.fillRect(i * bar_w, 0, bar_w, DISPLAY_HEIGHT, supported_colours[i]);
    }

    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLUE);
    display.setCursor(bar_w, 100);
    display.print("Hello World!");

    display.display();
    display.hibernate();
}

void loop() {
  delay(1000);
}
