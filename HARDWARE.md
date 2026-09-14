# ESP8266 Bomb Clock — Hardware Documentation

Complete hardware documentation for the ESP8266 Bomb Clock project.

This document describes the hardware components, pin assignments, wiring and electrical connections used in the current project version.

---

## 1. Project Hardware

The current hardware version is built around the following components:

| Component | Description |
|---|---|
| NodeMCU Amica ESP8266 | Main controller |
| DS1307 RTC | Real-Time Clock module |
| TM1637 | 4-digit 7-segment display |
| Passive Buzzer | Alarm sound output |
| Push Button | Physical alarm stop button |

The current version does not use a relay.

---

## 2. Main Controller

### NodeMCU Amica ESP8266

The NodeMCU Amica ESP8266 is the main controller of the project.

It is responsible for:

- Reading the DS1307 RTC
- Controlling the TM1637 display
- Generating the alarm sound
- Reading the physical alarm stop button
- Running the Wi-Fi Access Point
- Running the built-in Web Server
- Managing clock and alarm settings

---

## 3. TM1637 Display

The project uses a 4-digit TM1637 7-segment display to show the clock time.

### Connections

| TM1637 Pin | ESP8266 |
|---|---|
| CLK | D2 |
| DIO | D1 |
| VCC | 3.3V |
| GND | GND |

### Pin Assignment

```text
TM1637 CLK  → ESP8266 D2
TM1637 DIO  → ESP8266 D1
TM1637 VCC  → ESP8266 3.3V
TM1637 GND  → ESP8266 GND
4. DS1307 RTC
The DS1307 Real-Time Clock module is used to keep the current time.
The RTC maintains the clock time independently and provides the time information to the ESP8266.
Connections
DS1307 Pin
ESP8266
SCL
D1
SDA
D2
VCC
3.3V
GND
GND
Pin Assignment
DS1307 SCL  → ESP8266 D1
DS1307 SDA  → ESP8266 D2
DS1307 VCC  → ESP8266 3.3V
DS1307 GND  → ESP8266 GND
5. Passive Buzzer
A passive buzzer is used to generate the alarm sound effect.
The buzzer provides the audible warning/countdown-style effect used by the project.
Connections
Buzzer Pin
ESP8266
I/O
D4
VCC
3.3V
GND
GND
Pin Assignment
Buzzer I/O  → ESP8266 D4
Buzzer VCC  → ESP8266 3.3V
Buzzer GND  → ESP8266 GND
6. Alarm Stop Button
A physical push button is provided to stop the alarm.
The button is connected between ESP8266 D5 and GND.
Connection
ESP8266 D5 ───── Push Button ───── GND
Pin Assignment
Button Connection
ESP8266
Signal
D5
Other side
GND
7. Complete GPIO Assignment
The current firmware uses the following GPIO assignments:
Function
ESP8266 Pin
GPIO
TM1637 CLK
D2
GPIO4
TM1637 DIO
D1
GPIO5
DS1307 SCL
D1
GPIO5
DS1307 SDA
D2
GPIO4
Passive Buzzer
D4
GPIO2
Alarm Stop Button
D5
GPIO14
Summary
D1 / GPIO5
 ├── TM1637 DIO
 └── DS1307 SCL

D2 / GPIO4
 ├── TM1637 CLK
 └── DS1307 SDA

D4 / GPIO2
 └── Passive Buzzer

D5 / GPIO14
 └── Alarm Stop Button
8. Important Wiring Note
The current project version uses the same ESP8266 GPIO pins for the TM1637 and DS1307:
D1 / GPIO5 → TM1637 DIO + DS1307 SCL

D2 / GPIO4 → TM1637 CLK + DS1307 SDA
This is the actual pin arrangement used by the current firmware and hardware version.
It is documented here for compatibility and reproduction of the existing project.
For future hardware revisions, separate GPIO assignments for the TM1637 and DS1307 may be preferable.
9. Power Connections
The current documented connections use:
ESP8266 3.3V
      │
      ├── TM1637 VCC
      ├── DS1307 VCC
      └── Buzzer VCC

ESP8266 GND
      │
      ├── TM1637 GND
      ├── DS1307 GND
      ├── Buzzer GND
      └── Alarm Button GND
All connected modules must share a common ground.
10. Hardware Block Diagram
                    ┌─────────────────┐
                    │   DS1307 RTC    │
                    │                 │
                    │ SCL ───── D1    │
                    │ SDA ───── D2    │
                    └────────┬────────┘
                             │
                             │ Time
                             ▼
                    ┌─────────────────┐
                    │    ESP8266      │
                    │  NodeMCU Amica  │
                    └───────┬─────────┘
                            │
             ┌──────────────┼──────────────┐
             │              │              │
             ▼              ▼              ▼
       ┌──────────┐   ┌──────────┐   ┌──────────┐
       │  TM1637  │   │  Buzzer  │   │  Button  │
       │ Display  │   │  Alarm   │   │   STOP   │
       │ D1 / D2  │   │   D4     │   │   D5     │
       └──────────┘   └──────────┘   └────┬─────┘
                                           │
                                          GND
11. Hardware Features
The current hardware provides:
ESP8266-based clock controller
Battery-powered portable project capability
Real-Time Clock using DS1307
4-digit digital time display
Passive buzzer alarm
Physical alarm stop control
Wi-Fi connectivity through the ESP8266
Built-in Web Server
No external Wi-Fi router required for the local Web Server
12. Current Hardware Version
Hardware Revision
Hardware Version: Current / V1
Controller: NodeMCU Amica ESP8266
RTC: DS1307
Display: TM1637 4-Digit
Alarm: Passive Buzzer
Alarm Stop: Push Button
Relay: Not used
13. Future Hardware Improvements
Possible future hardware revisions may include:
Separate GPIO assignments for TM1637 and DS1307
Improved power management
Dedicated PCB
Improved wiring layout
More compact enclosure
Improved cable management
Status LED
Additional control buttons
Improved display arrangement
Battery monitoring
These are future possibilities and are not part of the current hardware version.
14. Reproduction Notes
To reproduce the current hardware configuration, use the exact GPIO assignments documented in this file.
The compiled firmware in this repository is intended for the documented ESP8266 hardware configuration.
Before modifying the wiring, verify the firmware pin assignments and module voltage requirements.
Different ESP8266 boards or module versions may have different hardware characteristics.
15. Safety and Usage
This project is a decorative and educational DIY electronics project.
The visual design is inspired by fictional time-bomb props used in entertainment.
The device contains:
No explosive material
No weapon functionality
No destructive mechanism
It is intended for:
DIY electronics
Learning
Experimentation
Decoration
Entertainment
Author
HUSAIN
Designed, assembled and developed as a personal DIY electronics project.
