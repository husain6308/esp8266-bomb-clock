[![Release](https://img.shields.io/github/v/release/husain6308/esp8266-bomb-clock?label=Release)](https://github.com/husain6308/esp8266-bomb-clock/releases)
[![License](https://img.shields.io/github/license/husain6308/esp8266-bomb-clock)](LICENSE)
[![GitHub repo](https://img.shields.io/badge/GitHub-Repository-black?logo=github)](https://github.com/husain6308/esp8266-bomb-clock)

# ESP8266 Bomb Clock

<div dir="rtl">

## معرفی پروژه

**ESP8266 Bomb Clock** یک ساعت رومیزی دکوراتیو با طراحی الهام‌گرفته از بمب ساعتی خیالی است که با استفاده از برد **NodeMCU Amica ESP8266** ساخته شده است.

هدف پروژه، ساخت یک وسیله الکترونیکی سرگرم‌کننده و دکوراتیو برای قرار دادن روی میز کار است.

این پروژه از ماژول **DS1307 RTC** برای نگهداری زمان، نمایشگر **TM1637 چهاررقمی** برای نمایش ساعت و **Passive Buzzer** برای ایجاد افکت صوتی آلارم استفاده می‌کند.

در نسخه **v1.1.0** قابلیت‌های جدیدی از جمله کنترل رله، کنترل رله از طریق Web Server، سیستم آلارم بهبودیافته و سورس کامل Arduino به پروژه اضافه شده است.

این پروژه صرفاً یک پروژه DIY، سرگرمی، آموزشی و دکوراتیو است.

</div>

---

<div dir="ltr">

## 📚 Documentation

- [Hardware Documentation](HARDWARE.md)
- [Firmware Documentation](FIRMWARE.md)
- [Changelog](CHANGELOG.md)
- [Contributing](CONTRIBUTING.md)
- [Security Policy](SECURITY.md)
- [License](LICENSE)

</div>

---

<div dir="rtl">

## 🆕 تغییرات نسخه v1.1.0

نسخه `v1.1.0` نسبت به نسخه `v1.0.0` شامل تغییرات و قابلیت‌های جدید زیر است:

- اضافه شدن پشتیبانی از رله روی `D6 / GPIO12`
- اضافه شدن کنترل دستی رله از طریق Web Server
- اضافه شدن کلید روشن/خاموش رله در صفحه Settings
- اضافه شدن کنترل خودکار رله در زمان اجرای آلارم
- امکان خاموش کردن هم‌زمان آلارم و رله با دکمه فیزیکی `D5`
- بهبود الگوی صدای آلارم
- کوتاه‌تر شدن فاصله بین Beepها با نزدیک شدن به پایان آلارم
- فعال شدن صدای پیوسته در ۵ ثانیه پایانی آلارم
- تغییر رفتار نمایشگر در زمان آلارم
- امکان تنظیم ثانیه هنگام تنظیم ساعت از Web Server
- تغییر نام شبکه Wi-Fi به `ESP8266-Clock-v1.1`
- اضافه شدن سورس کامل Arduino به Repository

### سیستم آلارم نسخه v1.1.0

- شروع آلارم: ۴۰ ثانیه قبل از زمان تعیین‌شده
- مدت کل آلارم: ۴۰ ثانیه
- فرکانس Buzzer: `1000 Hz`
- مدت هر Beep: `160 ms`
- فاصله بین Beepها با گذشت زمان کمتر می‌شود.
- در ۵ ثانیه پایانی، Buzzer به‌صورت پیوسته فعال است.

### سیستم رله

- پایه رله: `D6 / GPIO12`
- تأخیر فعال شدن رله: ۳۵ ثانیه بعد از شروع آلارم
- مدت روشن بودن رله: ۳۰ ثانیه
- کنترل دستی رله از Web Server
- دکمه `D5` می‌تواند آلارم و رله را متوقف کند.

### Web Server

- نام Wi-Fi: `ESP8266-Clock-v1.1`
- رمز Wi-Fi: `sain6308`
- آدرس Web Server: `http://192.168.4.1`
- تنظیم ساعت
- تنظیم ثانیه
- تنظیم آلارم
- Reset Alarm
- کنترل دستی Relay

### سورس کد

سورس کامل نسخه `v1.1.0` در Repository قرار گرفته است:

`firmware/esp8266-bomb-clock-v1.1.ino`

</div>

---

<div dir="ltr">

## ✨ Features

### Hardware

- NodeMCU Amica ESP8266
- DS1307 Real-Time Clock
- TM1637 4-digit display
- Passive buzzer
- Physical alarm stop button
- Relay module on D6 / GPIO12

### Clock System

- DS1307-based timekeeping
- 24-hour clock display
- Clock configuration through the Web Server
- Hour, minute and second selection
- Persistent alarm settings using EEPROM

### Alarm System

- Alarm starts 40 seconds before the configured alarm time
- 40-second alarm sequence
- 1000 Hz buzzer frequency
- 160 ms beep duration
- Decreasing beep intervals during the countdown
- Continuous buzzer during the final 5 seconds
- Physical alarm stop button

### Relay System

- Relay output on D6 / GPIO12
- Automatic relay activation 35 seconds after alarm start
- Automatic relay duration of 30 seconds
- Manual relay ON/OFF control through the Web Server
- Physical stop button can turn the relay OFF

### Web Server

- Built-in ESP8266 Web Server
- Standalone Wi-Fi Access Point
- No external router or Internet connection required
- Clock configuration
- Alarm configuration
- Alarm reset
- Relay control
- Clock seconds selection
- Live clock display

### Source Code

- Complete Arduino `.ino` source code available
- Source file:
  `firmware/esp8266-bomb-clock-v1.1.ino`

</div>

---

<div dir="rtl">

## 📦 نسخه‌های پروژه

### نسخه فعلی

**v1.1.0 — Source Code Release**

نسخه فعلی به‌صورت سورس کامل Arduino در Repository قرار دارد.

فایل:

`firmware/esp8266-bomb-clock-v1.1.ino`

### نسخه قبلی

**v1.0.0 — Compiled Firmware**

فایل کامپایل‌شده نسخه قبلی همچنان در Repository و Release مربوط به `v1.0.0` نگهداری می‌شود.

</div>

---

<div dir="ltr">

## 🔌 Wiring Diagram

| Component | Component Pin | ESP8266 Pin |
|---|---|---|
| TM1637 | CLK | D2 |
| TM1637 | DIO | D1 |
| TM1637 | VCC | 3.3V |
| TM1637 | GND | GND |
| DS1307 | SCL | D1 |
| DS1307 | SDA | D2 |
| DS1307 | VCC | 3.3V |
| DS1307 | GND | GND |
| Passive Buzzer | I/O | D4 |
| Passive Buzzer | VCC | 3.3V |
| Passive Buzzer | GND | GND |
| Push Button (Stop) | Pin 1 | D5 |
| Push Button (Stop) | Pin 2 | GND |
| Relay Module | Control / IN | D6 |
| Relay Module | VCC | According to module |
| Relay Module | GND | GND |

</div>

---

<div dir="rtl">

## ⚠️ نکته درباره اتصالات

در نسخه `v1.1.0` از پایه‌های زیر استفاده می‌شود:

`D1` → TM1637 DIO

`D1` → DS1307 SCL

`D2` → TM1637 CLK

`D2` → DS1307 SDA

`D4` → Passive Buzzer

`D5` → Alarm Stop Button

`D6 / GPIO12` → Relay Control

در این پروژه پایه‌های `D1` و `D2` به‌صورت مشترک برای TM1637 و DS1307 استفاده شده‌اند.

قبل از ساخت سخت‌افزار، اتصال واقعی و نوع ماژول‌های مورد استفاده را بررسی کنید.

رله این پروژه برای کاربردهای الکترونیکی عمومی و دکوراتیو در نظر گرفته شده است.

</div>

---

<div dir="ltr">

## ⏰ Clock System

The DS1307 RTC is responsible for keeping the current time.

The ESP8266 reads the time from the RTC and displays it on the TM1637 4-digit display.

```text
                ┌──────────────┐
                │    DS1307    │
                │     RTC      │
                └──────┬───────┘
                       │
                       │ Time
                       ▼
                ┌──────────────┐
                │   ESP8266    │
                │  Controller  │
                └──────┬───────┘
                       │
              ┌────────┼─────────┐
              │        │         │
              ▼        ▼         ▼
       ┌──────────┐ ┌────────┐ ┌────────┐
       │  TM1637  │ │ Buzzer │ │ Relay  │
       │ Display  │ │ Alarm  │ │ D6/GPIO12
       └──────────┘ └───┬────┘ └────────┘
                        │
                   ┌────▼─────┐
                   │    D5    │
                   │   STOP   │
                   └──────────┘
