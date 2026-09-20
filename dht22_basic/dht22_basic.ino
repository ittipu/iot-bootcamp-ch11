/*
 * Chapter 11 · Digital Sensors
 * DHT22 temperature + humidity — basic read
 *
 * Wiring:
 *   DHT22 VCC  -> 3V3
 *   DHT22 DATA -> GPIO 15   (10k pull-up to 3V3; usually on the module)
 *   DHT22 GND  -> GND
 *
 * Library: "DHT sensor library" by Adafruit (+ "Adafruit Unified Sensor")
 */

#include <DHT.h>

#define DHTPIN  15        // data pin (D15)
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  float t = dht.readTemperature();   // °C
  float h = dht.readHumidity();      // %

  if (isnan(t) || isnan(h)) {        // read failed -> skip
    Serial.println("DHT read failed");
    delay(2000);
    return;
  }

  Serial.printf("Temp: %.1f C   Hum: %.1f %%\n", t, h);
  delay(2000);                       // DHT22 minimum interval
}
