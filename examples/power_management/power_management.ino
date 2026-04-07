#include <XPowersLib.h>

#define I2C_SDA    47
#define I2C_SCL    48

XPowersAXP2101 pmu;

void setup() {
  Serial.begin(115200);

  // important! this device does not use the default I2C pins! 
  Wire.begin(I2C_SDA, I2C_SCL);
 
  pmu.begin(Wire, AXP2101_SLAVE_ADDRESS, I2C_SDA, I2C_SCL);
  pmu.enableSystemVoltageMeasure();
  pmu.setALDO4Voltage(3300);
  pmu.enableALDO4(); // enables power to the epaper circuitry

  delay(100);
}

void loop() {
  float vbat = pmu.getBattVoltage();
  float vsys = pmu.getSystemVoltage();
  float valdo4 = pmu.getALDO4Voltage();
  if (vbat > 100.0f) vbat /= 1000.0f;
  if (vsys > 100.0f) vsys /= 1000.0f;
  if (valdo4 > 100.0f) valdo4 /= 1000.0f;

  Serial.printf("V_BAT=%.3f, V_SYS=%.3f, V_ALDO4=%.3f, CHARGING=%s \n", vbat, vsys, valdo4, pmu.isCharging() ? "yes" : "no");

  if (pmu.isBatteryConnect()) {
    Serial.printf("Estimated Battery Percentage: %d%% \n", pmu.getBatteryPercent()); 
  }

  delay(2000);
}
