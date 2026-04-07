#include <SPI.h>
#include <SD.h>

#define PIN_SD_CS   38
#define PIN_SD_CLK  39
#define PIN_SD_MISO 40
#define PIN_SD_MOSI 41

SPIClass spi_sd(HSPI);

void setup() {
  Serial.begin(115200);

  spi_sd.begin(PIN_SD_CLK, PIN_SD_MISO, PIN_SD_MOSI, PIN_SD_CS);
  SD.begin(PIN_SD_CS, spi_sd, 4000000);

  ...
}
