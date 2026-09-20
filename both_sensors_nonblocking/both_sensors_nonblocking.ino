/*
 * Chapter 11 · Digital Sensors
 * Both sensors in ONE non-blocking loop (the Chapter 10 millis() payoff)
 *
 * Reads a DHT22 every 2 s and an HC-SR04 ten times a second,
 * with no delay() anywhere, so buttons / WiFi / other tasks stay responsive.
 *
 * Wiring:
 *   DHT22   VCC->3V3   DATA->GPIO15 (10k pull-up)   GND->GND
 *   HC-SR04 VCC->5V    TRIG->GPIO16  ECHO->GPIO17 (5V! divider)  GND->GND
 *
 * Library: "DHT sensor library" by Adafruit (+ "Adafruit Unified Sensor")
 */

#include <DHT.h>

// ---------- Pins ----------
#define DHTPIN  15         // DHT22 data (D15)
#define DHTTYPE DHT22
#define TRIG    16         // HC-SR04 trigger
#define ECHO    17         // HC-SR04 echo

DHT dht(DHTPIN, DHTTYPE);

// ---------- Timers (millis pattern) ----------
unsigned long lastDHT = 0, lastPing = 0, lastPrint = 0;
const unsigned long DHT_EVERY  = 2000;   // DHT22 needs >= 2 s
const unsigned long PING_EVERY = 100;    // distance 10x/sec
const unsigned long PRINT_EVERY = 1000;  // report once a second

// ---------- Latest good readings ----------
float tempC = NAN, humid = NAN;
long  distCm = -1;

// Read HC-SR04 once; returns cm, or -1 on timeout / out of range
long readDistanceCm() {
  digitalWrite(TRIG, LOW);  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long us = pulseIn(ECHO, HIGH, 30000);    // 30 ms timeout
  if (us == 0) return -1;                  // no echo
  return us * 0.0343 / 2;                  // cm
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  digitalWrite(TRIG, LOW);
}

void loop() {
  unsigned long now = millis();

  // --- DHT22: every 2 s ---
  if (now - lastDHT >= DHT_EVERY) {
    lastDHT = now;
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    if (!isnan(t) && !isnan(h)) {           // keep valid reads only
      tempC = t;
      humid = h;
    }
  }

  // --- HC-SR04: 10x per second ---
  if (now - lastPing >= PING_EVERY) {
    lastPing = now;
    long d = readDistanceCm();
    if (d > 0 && d < 400) distCm = d;        // reject out-of-range spikes
  }

  // --- Report together: no delay() anywhere ---
  if (now - lastPrint >= PRINT_EVERY) {
    lastPrint = now;
    Serial.printf("Temp: %.1f C   Hum: %.1f %%   Dist: %ld cm\n",
                  tempC, humid, distCm);
  }
}
