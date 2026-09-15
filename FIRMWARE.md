#1. Firmware Overview

The ESP8266 Bomb Clock firmware controls the main functions of the project, including:

- Real-Time Clock communication
- TM1637 4-digit display
- Passive buzzer alarm
- Physical alarm stop button
- Wi-Fi Access Point
- Built-in Web Server
- Clock configuration
- Alarm configuration
- Persistent settings

The firmware is provided as a compiled `.bin` file.

---

## 2. Current Firmware

| Item | Information |
|---|---|
| Firmware | ESP8266 Bomb Clock |
| Version | v1.0.0 |
| Firmware File | `esp8266-bomb-clock-v1.0.bin` |
| Target Board | NodeMCU Amica ESP8266 |
| Firmware Format | Compiled Binary (`.bin`) |
| Flash Address | `0x0000` |
| Status | Stable / Archived |

---

## 3. Firmware File

The current firmware image is:

```text
esp8266-bomb-clock-v1.0.bin

This file is the compiled firmware used to run the current version of the project.

The firmware can be found in the root of this repository.


---

4. Supported Hardware

The firmware is intended for the following hardware configuration:

Controller:
NodeMCU Amica ESP8266

RTC:
DS1307

Display:
TM1637 4-Digit Display

Alarm:
Passive Buzzer

Alarm Stop:
Push Button

For the complete hardware connections, see:

HARDWARE.md


---

5. GPIO Configuration

The current firmware uses the following pin assignments:

Function	ESP8266 Pin	GPIO

TM1637 CLK	D2	GPIO4
TM1637 DIO	D1	GPIO5
DS1307 SCL	D1	GPIO5
DS1307 SDA	D2	GPIO4
Passive Buzzer	D4	GPIO2
Alarm Stop Button	D5	GPIO14


Pin Summary

D1 / GPIO5 → TM1637 DIO
D1 / GPIO5 → DS1307 SCL

D2 / GPIO4 → TM1637 CLK
D2 / GPIO4 → DS1307 SDA

D4 / GPIO2 → Passive Buzzer

D5 / GPIO14 → Alarm Stop Button


---

6. Wi-Fi Access Point

The firmware creates its own Wi-Fi Access Point.

No external router or Internet connection is required to access the local Web Server.

Wi-Fi Configuration

SSID:
ESP8266-Clock

Password:
12345678

Web Server Address

After connecting to the ESP8266 Wi-Fi network, open:

http://192.168.4.1

The Web Server provides access to the clock and alarm configuration.


---

7. Web Interface

The firmware includes a built-in Web Server.

The Web Interface can be used for functions such as:

Clock configuration

Alarm configuration

Alarm management

Saving settings

Viewing clock and alarm information


The Web Server operates locally through the ESP8266 Access Point.

An Internet connection is not required for local configuration.


---

8. Alarm System

The firmware uses a passive buzzer to generate the alarm sound effect.

The alarm is designed as a fictional warning/countdown-style effect matching the decorative theme of the project.

The physical alarm stop button is connected to:

D5 / GPIO14

Button connection:

D5 ───── Push Button ───── GND


---

9. Persistent Settings

The firmware stores project settings in the ESP8266's internal memory.

This allows supported settings to remain available after the device is restarted or powered off.

The exact internal storage implementation depends on the compiled firmware and is not intended to be modified without the original source code.


---

10. Android Firmware Installation

The firmware can be installed directly from an Android phone.

The tested application is:

ESPFlash-ESP32/ESP8266Flasher

The application is used with the ESP8266 through USB and USB OTG.

Requirements

Android phone

NodeMCU Amica ESP8266

USB cable

USB OTG adapter, if required

esp8266-bomb-clock-v1.0.bin



---

11. Tested Flash Configuration

The following configuration was successfully used to install the firmware:

Firmware:
esp8266-bomb-clock-v1.0.bin

Address:
0x0000

High-Speed Mode (Stub):
ON

Firmware Compress:
ON

Baudrate:
115200

These settings document the tested installation procedure for this specific firmware.

Different firmware builds or ESP8266 hardware configurations may require different flashing settings.


---

12. Android Flashing Procedure

Step 1 — Connect the ESP8266

Connect the NodeMCU Amica ESP8266 to the Android phone using USB and OTG.


---

Step 2 — Open ESPFlash

Launch:

ESPFlash-ESP32/ESP8266Flasher


---

Step 3 — Add Firmware

In the Firmware File section, press:

+

Select:

esp8266-bomb-clock-v1.0.bin


---

Step 4 — Set Address

Set:

0x0000


---

Step 5 — Enable High-Speed Mode

Enable:

High-Speed Mode (Stub)


---

Step 6 — Enable Firmware Compression

Enable:

Firmware Compress


---

Step 7 — Set Baudrate

Set:

115200


---

Step 8 — Start Flashing

Press the Flash / Upload button.

The application will transfer the firmware to the ESP8266.

Wait until the flashing process has completed successfully.


---

Step 9 — Restart

After successful flashing, restart the ESP8266.

The Bomb Clock firmware should then start.


---

13. Firmware Verification

After installation, the following basic functions should be checked:

TM1637 displays the clock

DS1307 provides the clock time

ESP8266 creates the ESP8266-Clock Wi-Fi network

The Web Server is accessible at 192.168.4.1

Clock configuration works

Alarm configuration works

Passive buzzer operates during the alarm

D5 button stops the alarm



---

14. Firmware Recovery

If the firmware needs to be reinstalled, the same .bin file can be flashed again using the documented Android procedure.

Use:

Address: 0x0000
Baudrate: 115200
High-Speed Mode (Stub): ON
Firmware Compress: ON

The ESP8266 should be connected directly to the Android device through a suitable USB OTG connection.


---

15. Source Code Availability

The original Arduino .ino source code for this firmware is currently unavailable.

The repository therefore provides the compiled firmware rather than the original editable source code.

The .bin file is a compiled firmware image and cannot be edited directly like an Arduino .ino source file.

If the original source code is recovered in the future, it can be added to the repository.


---

16. Firmware Limitations

Because the original .ino source code is currently unavailable:

The firmware cannot be directly modified from the .bin file.

New features cannot be reliably added to the original firmware without recovering or recreating the source.

Internal implementation details cannot be guaranteed beyond the documented behavior.

Future hardware modifications may require different firmware.


The current firmware should therefore be considered a preserved and archived build.


---

17. Compatibility

The firmware is intended for:

NodeMCU Amica ESP8266

Using a different ESP8266 board may require different hardware connections or firmware configuration.

Before flashing the firmware to another board, verify:

Board compatibility

GPIO mapping

Power requirements

USB/serial interface

Connected peripherals



---

18. Release Information

Current release:

ESP8266 Bomb Clock v1.0.0

Release tag:

v1.0.0

This is the initial stable firmware release documented in this repository.


---

19. Related Documentation

For additional project information, see:

README.md — Project overview and complete documentation

HARDWARE.md — Hardware components and wiring

CHANGELOG.md — Version history and changes

LICENSE — Project license



---

20. Project Status

Firmware Status: Stable / Archived
Version: v1.0.0
Source Code: Currently unavailable

This firmware is preserved as part of the ESP8266 Bomb Clock project for documentation, backup and reproduction purposes.


---

Author

HUSAIN

Designed, assembled and developed as a personal DIY electronics project.
