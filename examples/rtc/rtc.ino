#include <SensorPCF85063.hpp>

#define I2C_SDA    47
#define I2C_SCL    48
#define RTC_IRQ    6

SensorPCF85063 rtc;

RTC_DateTime datetime;
struct tm timeinfo;
char buf[64];

void setup() {
  Serial.begin(115200);

  // important! this device does not use the default I2C pins! 
  Wire.begin(I2C_SDA, I2C_SCL);
 
  rtc.begin(Wire, I2C_SDA, I2C_SCL);

  set_time();
}

void loop() {
  datetime = rtc.getDateTime();
  timeinfo = datetime.toUnixTime();

  strftime(buf, 64, "%A, %B %d %Y %H:%M:%S", &timeinfo);
  Serial.println(buf);
	
  delay(1000);
}
	
// extract the compilation time of the current firmware, and set that as current time in the RTC	
void set_time()
{
    char s_month[5];
    int year;
    tm t{};
    static constexpr char month_names[37] = "JanFebMarAprMayJunJulAugSepOctNovDec";
	
    // extract time values from compilation timestamp embedded in firmware
    sscanf(__DATE__, "%s %d %d", s_month, &t.tm_mday, &year);
    sscanf(__TIME__, "%2d %*c %2d %*c %2d", &t.tm_hour, &t.tm_min, &t.tm_sec);
	
    // find where s_month is in month_names, deduce month value.
    t.tm_mon = (strstr(month_names, s_month) - month_names) / 3;
    t.tm_year = year - 1900;
	
    // optional: add 30 seconds to compensate for compile/upload time
    time_t timestamp = mktime(&t);
    timestamp = timestamp + 30;
    localtime_r(&timestamp, &t);
	
    // Set the defined date and time on the RTC
    rtc.setDateTime(t);
}
