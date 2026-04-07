#define PIN_BTN_KEY     4
#define PIN_BTN_BOOT    0

void setup() {
    Serial.begin(115200);
   
    pinMode(PIN_BTN_KEY, INPUT_PULLUP);
    pinMode(PIN_BTN_BOOT, INPUT_PULLUP);
}

void loop() {
    if(digitalRead(PIN_BTN_KEY) == LOW) {
      Serial.println("button: key");
    }
    
    if(digitalRead(PIN_BTN_BOOT) == LOW) {
      Serial.println("button: boot");
    }

    delay(100);
}
