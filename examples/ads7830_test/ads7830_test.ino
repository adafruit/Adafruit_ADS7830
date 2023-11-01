#include <Wire.h>
#include <Adafruit_ADS7830.h>

Adafruit_ADS7830 ad7830;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10); // Wait for console to open
  
  Serial.println("Adafruit ADS7830 Test by Limor Fried/Ladyada");

  // Possible arguments to begin():
  // begin(); // Uses default I2C address 0x48 and Wire
  // begin(0x49); // Uses I2C address 0x49 and Wire
  // begin(0x48, &Wire1); // Uses I2C address 0x48 and Wire1

  if (!ad7830.begin()) {
    Serial.println("Failed to initialize ADS7830!");
    while (1);
  }
}

void loop() {
  for (uint8_t ch = 0; ch <= 7; ch++) {
    uint8_t value = ad7830.readADCsingle(ch);
    Serial.print(value);
    if (ch < 7) {
      Serial.print(",\t");
    }
  }
  Serial.println();
  delay(100);
}
