# Arduino LPG Gas Leakage Detector

> **Undergraduate Engineering Project (2018)**  
> **Institution:** Daffodil International University  
> **Department:** Department of Electronics and Telecommunication Engineering (ETE / ICE)  
> **Author:** Mohammad Motasim Fuad ([ORCID: 0009-0007-1823-0620](https://orcid.org/0009-0007-1823-0620))

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-Arduino%20Pro%20Mini-blue)](https://www.arduino.cc/)
[![Sensor](https://img.shields.io/badge/Sensor-MQ--Series-green)](https://www.sparkfun.com/)
[![Status](https://img.shields.io/badge/Status-Completed%20(2018)-lightgrey)]()

---

## Abstract
Liquefied Petroleum Gas (LPG) is a primary fuel in residential and industrial environments across South Asia. Unnoticed gas leaks present severe safety risks, including asphyxiation, catastrophic fires, and explosions. This project presents the design, fabrication, and experimental validation of an embedded, low-cost LPG leakage detection and alert system built around an Arduino Pro Mini microcontroller. 

The system utilizes an MQ-series electrochemical gas sensor module to monitor ambient gas concentrations. When leakage exceeds a calibrated safety threshold, the sensor comparator asserts a digital HIGH signal on pin A4 (D18). The Arduino firmware detects this event, triggers an audible alarm through a BC547 NPN transistor-switched buzzer on pin 13, and prints real-time status alerts on an HD44780 16×2 LCD module operating in 4-bit mode. Under normal atmospheric conditions, the display reports passive safe-state monitoring.

---

## Hardware Components

| Component | Specification / Rating | Quantity |
| :--- | :--- | :---: |
| **Microcontroller** | Arduino Pro Mini (ATmega328P, 5V, 16MHz) | 1 |
| **Gas Sensor** | MQ-Series Gas Sensor Module (MQ-2 / MQ-6 with onboard comparator) | 1 |
| **Display** | 16×2 Character LCD (HD44780 compatible) | 1 |
| **Driver Transistor** | BC547 NPN Transistor (TO-92 package) | 1 |
| **Acoustic Alert** | 5V Active Piezoelectric Buzzer | 1 |
| **Resistor** | 1 kΩ (Base current limiting for BC547) | 1 |
| **Power Supply** | 9V DC Battery / Regulated 5V rail | 1 |
| **Prototyping** | 830-point Solderless Breadboard & Jumper Wires | 1 |

---

## Circuit Architecture & Pin Mapping

```text
                       +5V (VCC)
                           |
             +-------------+-------------+
             |                           |
       [MQ Sensor VCC]              [LCD VDD, A]
             |
       DOUT (Comparator)
             |
         Pin A4 (D18)
      [Arduino Pro Mini]
             |
          Pin D13 ───[ 1kΩ ]─── Base (BC547)
                                   |
                               Collector ──── [ Buzzer (+) ]
                                   |
                                Emitter ───── GND (Common Ground)
                                                |
                                            [ Buzzer (-) ]
```

### Arduino Pro Mini Pinout:
* **Pin A4 (D18) [INPUT]:** MQ Sensor Digital Output (DOUT).
* **Pin D13 [OUTPUT]:** Buzzer Trigger via BC547 Base.
* **Pin D7 [OUTPUT]:** LCD Register Select (RS).
* **Pin D8 [OUTPUT]:** LCD Enable (EN).
* **Pin D9 [OUTPUT]:** LCD Data Bit 4 (D4).
* **Pin D10 [OUTPUT]:** LCD Data Bit 5 (D5).
* **Pin D11 [OUTPUT]:** LCD Data Bit 6 (D6).
* **Pin D12 [OUTPUT]:** LCD Data Bit 7 (D7).

---

## Firmware Logic Flow

```text
   [ SYSTEM START / POWER-ON ]
                |
                v
   [ 10s Sensor Warm-up Delay ]
                |
                v
   [ LCD: "System Ready / Monitoring..." ]
                |
                +<--------------------------------------+
                |                                       |
                v                                       |
   [ Read Pin A4 (MQ DOUT) ]                            |
                |                                       |
        Is Gas Detected?                                |
          /          \                                  |
       (YES)         (NO)                               |
        /              \                                |
       v                v                               |
 [ LCD: "LPG LEAKAGE   [ LCD: "System Ready             |
        ALERT!" ]             No LPG Leakage" ]         |
       |                |                               |
 [ Pulsed Buzzer ON ]  [ Buzzer OFF ]                   |
       |                |                               |
       +-------> [ Delay 500ms ] -----------------------+
```

---

## Project Structure
```text
arduino-lpg-gas-leakage-detector/
├── README.md               # System specification and documentation
├── LICENSE                 # MIT License
└── src/
    └── lpg_detector.ino    # Arduino C++ production sketch
```

---

## Citation & Academic Record
If referencing or utilizing this project structure for academic or technical study, cite as:
```bibtex
@misc{fuad2018lpg,
  author       = {Mohammad Motasim Fuad},
  title        = {Design and Implementation of an Arduino-Based LPG Gas Leakage Detection and Alert System},
  year         = {2018},
  institution  = {Daffodil International University},
  howpublished = {Undergraduate Project, Department of Electronics and Telecommunication Engineering},
  url          = {https://orcid.org/0009-0007-1823-0620}
}
```

## License
This project is open-source and licensed under the [MIT License](LICENSE).
