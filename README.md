<h1 align="center">🌡️ Chapter 11 · Digital Sensors</h1>
<p align="center"><em>How Sensors Speak in Bits</em></p>

<p align="center">
  <img alt="Platform" src="https://img.shields.io/badge/Platform-ESP32-000000?logo=espressif&logoColor=white">
  <img alt="Framework" src="https://img.shields.io/badge/Framework-Arduino-00979D?logo=arduino&logoColor=white">
  <img alt="Language" src="https://img.shields.io/badge/Language-C%2B%2B-00599C?logo=cplusplus&logoColor=white">
  <img alt="Course" src="https://img.shields.io/badge/Course-Full%20Stack%20IoT%20Bootcamp-0066CC">
  <img alt="License" src="https://img.shields.io/badge/License-MIT-green">
</p>

<p align="center">
  Part of the <strong>Full Stack IoT Engineer Bootcamp</strong> · IoT Bhai
</p>

---

## 📖 About this chapter

Your ESP32 has no eyes, no nose, no thermometer — so how does it know the room is 26 °C?
A **sensor is a translator**: it turns something physical into something the ESP32 can read.

This chapter covers **digital sensors** — the ones that do the thinking for you and send back
a *coded pattern of bits* instead of a raw voltage. You'll wire up two of the most common ones
and read them both in a single, responsive, non-blocking loop.

| | |
|---|---|
| 🎯 **You'll learn** | How digital sensors communicate, protocol vs raw voltage |
| 🌡️ **DHT22** | Temperature + humidity over a single-wire protocol |
| 📏 **HC-SR04** | Distance from ultrasonic echo timing |
| ⏱️ **Non-blocking reads** | Poll both sensors with `millis()` — zero `delay()` |
| 🎯 **Data quality** | Averaging, timeouts, spike & `NaN` filtering |

---

## 🧰 Hardware

| Component | Notes |
|-----------|-------|
| ESP32 DevKit | Any ESP32 dev board |
| DHT22 (AM2302) | Temperature + humidity — DHT11 also works |
| HC-SR04 | Ultrasonic distance sensor |
| Resistors | 10 kΩ (DHT pull-up), 1 kΩ + 2 kΩ (ECHO divider) |
| Breadboard + jumpers | |

### 🔌 Wiring

**DHT22**

| DHT22 pin | → | ESP32 |
|-----------|---|-------|
| VCC | → | 3V3 |
| DATA | → | **GPIO 15** *(10 kΩ pull-up to 3V3)* |
| GND | → | GND |

**HC-SR04**

| HC-SR04 pin | → | ESP32 |
|-------------|---|-------|
| VCC | → | 5V / VIN |
| TRIG | → | **GPIO 16** |
| ECHO | → | **GPIO 17** ⚠️ *(5 V — use a 1 kΩ + 2 kΩ divider to 3.3 V)* |
| GND | → | GND |

> ⚠️ **The ECHO pin outputs 5 V.** Feeding that straight into a 3.3 V ESP32 GPIO can damage it.
> Use a simple resistor divider (1 kΩ from ECHO, 2 kΩ to GND, tap to GPIO 17).

---

## 📂 Sketches

Each sketch is a self-contained Arduino project in its own folder.

| Folder | What it does |
|--------|--------------|
| [`dht22_basic/`](dht22_basic) | Read temperature + humidity from the DHT22 |
| [`hcsr04_basic/`](hcsr04_basic) | Measure distance with the HC-SR04 |
| [`both_sensors_nonblocking/`](both_sensors_nonblocking) | **Both sensors in one `millis()` loop — no `delay()`** ⭐ |

---

## 🚀 Getting started

1. **Install the Arduino IDE** and the **ESP32 board package**
   (Boards Manager → search *esp32* by Espressif Systems).
2. **Install the library** (Library Manager):
   - `DHT sensor library` by Adafruit
   - `Adafruit Unified Sensor` (installed alongside it)
3. **Wire it up** as in the table above.
4. Open a sketch folder (e.g. `both_sensors_nonblocking/both_sensors_nonblocking.ino`).
5. Select your ESP32 board + port, then **Upload**.
6. Open the **Serial Monitor** at **115200 baud**.

### Expected output

```text
Temp: 26.4 C   Hum: 68.0 %   Dist: 24 cm
Temp: 26.4 C   Hum: 68.0 %   Dist: 23 cm
Temp: 26.5 C   Hum: 67.0 %   Dist: 41 cm
```

---

## 💡 Key takeaways

- Digital sensors **speak a protocol** — timed HIGH/LOW patterns, not raw voltage.
- **DHT22** streams 40 bits over one wire; a library decodes temp & humidity.
- **HC-SR04** measures distance from echo timing — always use a `pulseIn` timeout.
- **`millis()`** lets both sensors share one responsive loop with **zero delays**.
- Average, filter, and validate — a reading you can't trust is worse than none.

---

## 🗺️ Course context

| | Chapter | Focus |
|---|---------|-------|
| ← | 10 · Time Management | Non-blocking code, `millis()`, interrupts |
| 🟦 | **11 · Digital Sensors** | **DHT22, HC-SR04, non-blocking reads** |
| → | 12 · Analog Sensors | LM35, soil moisture, MQ gas, ADC filtering |

---

<p align="center">
  <sub>Full Stack IoT Engineer Bootcamp · IoT Bhai · Released under the MIT License</sub>
</p>
