# MCU-Programming-AVR-ADC-Sensor-Monitoring
This project implements a smart environmental monitoring node using an AVR microcontroller. It uses **three analog sensors**—for **temperature**, **humidity**, and **soil moisture**—connected to ADC channels and read via an **interrupt-driven ADC routine**. Based on sensor readings, three output pins (PORTB0–PORTB2) control actuators or indicator LEDs.

---

## Project Overview

- **Microcontroller**: AVR (ATmega2560)
- **Clock Frequency**: 8 MHz
- **Sensors**:
  - Analog Temperature Sensor (e.g., LM35)
  - Analog Humidity Sensor (using a potentiometer)
  - Soil Moisture Sensor (using a potentiometer)
- **Outputs**:
  - PORTB0: High temperature indicator (LED)
  - PORTB1: High humidity indicator
  - PORTB2: Low moisture indicator
- **Features**:
  - ADC interrupt-based sampling
  - Channel multiplexing (3 channels)
  - Real-time condition checking and response

---

## How It Works

- ADC uses **interrupt mode** to sequentially sample channels 0, 1, and 2.
- A **circular buffer** via `channel++` switches inputs on each ISR trigger.
- The `main()` loop converts raw ADC values to:
  - Temperature (°C)
  - Humidity (%)
  - Moisture (%)
- Conditions:
  - If **Temp > 30°C**, PB0 goes HIGH.
  - If **Humidity > 60%**, PB1 goes HIGH.
  - If **Moisture < 40%**, PB2 goes HIGH.

---

## Circuit Setup

| Signal      | AVR Pin | Component            |
|-------------|---------|----------------------|
| ADC0        | PC0     | LM35 (Temperature)   |
| ADC1        | PC1     | Humidity Sensor      |
| ADC2        | PC2     | Soil Moisture Sensor |
| PB0–PB2     | Output  | LEDs or Relays       |

You can simulate this system in **Proteus** or deploy on hardware using **breadboard + sensors**.

---
## Circuit Setup in Proteus
<img width="955" height="643" alt="image" src="https://github.com/user-attachments/assets/880fc2af-94fb-4f9e-809d-454df1d5ecc5" />
