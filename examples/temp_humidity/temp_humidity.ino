#include "Adafruit_SHTC3.h"

#define I2C_SDA    47
#define I2C_SCL    48

Adafruit_SHTC3 shtc3 = Adafruit_SHTC3();
sensors_event_t humidity, temp;

void setup() {
  Serial.begin(115200);

  // important! this device does not use the default I2C pins! 
  Wire.begin(I2C_SDA, I2C_SCL);

  shtc3.begin();
}

void loop() {
  shtc3.getEvent(&humidity, &temp);
    
  Serial.print("Temperature: "); 
  Serial.print(temp.temperature); 
  Serial.println(" degrees C");

  Serial.print("Humidity: "); 
  Serial.print(humidity.relative_humidity); 
  Serial.println("% rH");

  delay(1000);
}
