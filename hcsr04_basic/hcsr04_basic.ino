/*
 * Chapter 11 · Digital Sensors
 * HC-SR04 ultrasonic distance — basic read
 *
 * Wiring:
 *   HC-SR04 VCC  -> 5V / VIN
 *   HC-SR04 TRIG -> GPIO 16
 *   HC-SR04 ECHO -> GPIO 17   (ECHO is 5V! use a 1k+2k divider to 3.3V)
 *   HC-SR04 GND  -> GND
 */

#define TRIG 16
#define ECHO 17

void setup() {
  Serial.begin(115200);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  digitalWrite(TRIG, LOW);
}

// Returns distance in cm, or -1 on timeout / out of range
long readDistanceCm() {
  digitalWrite(TRIG, LOW);  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH); delayMicroseconds(10);   // 10 us trigger
  digitalWrite(TRIG, LOW);

  long us = pulseIn(ECHO, HIGH, 30000);              // timeout 30 ms
  if (us == 0) return -1;                            // no echo
  return us * 0.0343 / 2;                            // cm
}

void loop() {
  long d = readDistanceCm();
  if (d < 0) Serial.println("Distance: out of range");
  else       Serial.printf("Distance: %ld cm\n", d);
  delay(200);
}
