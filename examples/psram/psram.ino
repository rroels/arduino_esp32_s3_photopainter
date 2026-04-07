byte* img_buffer;

void setup() {
  Serial.begin(115200);

  psramInit();
 
  Serial.printf("Total PSRAM: %d \n", ESP.getPsramSize());
  Serial.printf("Free PSRAM: %d \n", ESP.getFreePsram());

  // allocate 1MB in PSRAM (note: this wouldn't fit in regular RAM)
  img_buffer = (byte*)ps_malloc(1024 * 1024);

  Serial.printf("Free PSRAM after ps_malloc: %d \n", ESP.getFreePsram());

  // clean up
  free(img_buffer);

  Serial.printf("Free PSRAM after cleanup: %d \n", ESP.getFreePsram());
}

void loop() {
  delay(2000);
}
