ESP8266 Bomb Clock

A decorative ESP8266 desk clock inspired by the visual design of a fictional time bomb.

The project uses an ESP8266 NodeMCU Amica, DS1307 RTC, TM1637 4-digit display and a passive buzzer to create a functional desk clock with a countdown-style alarm effect and a built-in web interface.

---

🇮🇷 فارسی

معرفی پروژه

ESP8266 Bomb Clock یک ساعت رومیزی دکوراتیو با طراحی الهام‌گرفته از بمب ساعتی است که با استفاده از برد NodeMCU Amica ESP8266 ساخته شده است.

هدف این پروژه، ایجاد یک وسیله الکترونیکی سرگرم‌کننده و دکوراتیو برای قرار دادن روی میز کار است.

زمان توسط ماژول DS1307 RTC نگهداری می‌شود و ساعت روی نمایشگر TM1637 چهاررقمی نمایش داده می‌شود.

برای ایجاد افکت صوتی آلارم نیز از یک Passive Buzzer استفاده شده است. صدای آلارم به‌صورت یک افکت هشدار و شمارش معکوس طراحی شده تا ظاهر و فضای بمب ساعتی پروژه را کامل کند.

این پروژه صرفاً یک پروژه DIY، سرگرمی و دکوراتیو است و هیچ کاربرد واقعی مرتبط با مواد منفجره یا سلاح ندارد.

---

✨ امکانات

- NodeMCU Amica ESP8266
- DS1307 RTC برای نگهداری زمان
- نمایش ساعت با TM1637 چهاررقمی
- Passive Buzzer برای آلارم
- کلید فیزیکی برای قطع آلارم
- Web Server داخلی
- ایجاد شبکه Wi-Fi توسط خود ESP8266
- تنظیم ساعت از طریق مرورگر
- تنظیم آلارم از طریق مرورگر
- ذخیره تنظیمات در حافظه ESP8266
- طراحی دکوراتیو با ظاهر بمب ساعتی
- Firmware آماده برای ESP8266
- امکان نصب Firmware با گوشی Android بدون نیاز به کامپیوتر

---

🧩 قطعات استفاده‌شده

قطعه| توضیح
NodeMCU Amica ESP8266| کنترلر اصلی
DS1307 RTC| نگهداری زمان
TM1637 4-Digit Display| نمایش ساعت
Passive Buzzer| تولید صدای آلارم
Push Button| قطع آلارم

---

🔌 اتصالات

TM1637

TM1637| ESP8266
CLK| D2
DIO| D1
VCC| تغذیه مناسب ماژول
GND| GND

DS1307

DS1307| ESP8266
SCL| D1
SDA| D2
VCC| تغذیه مناسب ماژول
GND| GND

Passive Buzzer

Buzzer| ESP8266
I/O| D4
GND| GND
VCC| تغذیه مناسب ماژول

Alarm Stop Button

کلید قطع آلارم بین D5 و GND متصل شده است.

D5 ───── Push Button ───── GND

---

⚠️ نکته درباره اتصالات

در نسخه فعلی پروژه از این GPIOها استفاده شده است:

D1 → TM1637 DIO
D1 → DS1307 SCL

D2 → TM1637 CLK
D2 → DS1307 SDA

D4 → Passive Buzzer

D5 → Alarm Stop Button

این Repository مستندکننده نسخه فعلی پروژه است.

در صورت طراحی نسخه سخت‌افزاری جدید، بهتر است اتصال TM1637 و DS1307 مجدداً بررسی شود و در صورت نیاز GPIOهای مستقل برای آن‌ها در نظر گرفته شود.

---

⏰ سیستم ساعت

ماژول DS1307 RTC وظیفه نگهداری زمان را بر عهده دارد.

ESP8266 زمان را از DS1307 دریافت کرده و آن را روی نمایشگر TM1637 نمایش می‌دهد.

ساختار کلی سیستم:

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
              ┌────────┴────────┐
              │                 │
              ▼                 ▼
       ┌──────────────┐  ┌──────────────┐
       │    TM1637    │  │    Buzzer    │
       │   Display    │  │    Alarm     │
       └──────────────┘  └──────┬───────┘
                                │
                                │
                           ┌────▼─────┐
                           │    D5    │
                           │   STOP   │
                           └──────────┘

---

🌐 Web Server

این نسخه دارای Web Server داخلی ESP8266 است.

ESP8266 پس از راه‌اندازی، یک شبکه Wi-Fi ایجاد می‌کند و برای دسترسی به پنل تنظیمات نیازی به مودم یا اینترنت ندارد.

Wi-Fi Access Point

SSID: ESP8266-Clock
Password: 12345678

ورود به Web Server

ابتدا با گوشی یا دستگاه دیگر به شبکه زیر متصل شوید:

ESP8266-Clock

سپس مرورگر را باز کرده و آدرس زیر را وارد کنید:

http://192.168.4.1

پس از باز شدن صفحه، پنل وب ساعت نمایش داده می‌شود.

---

⚙️ تنظیم ساعت و آلارم

از طریق Web Server می‌توان تنظیمات مربوط به ساعت و آلارم را انجام داد.

امکانات اصلی پنل:

- تنظیم ساعت
- تنظیم زمان آلارم
- مدیریت تنظیمات آلارم
- ذخیره تنظیمات
- مشاهده اطلاعات مربوط به ساعت و آلارم

تنظیمات در حافظه ESP8266 ذخیره می‌شوند تا پس از خاموش و روشن شدن دستگاه نیز حفظ شوند.

---

🚨 سیستم آلارم

برای آلارم از یک Passive Buzzer استفاده شده است.

صدای آلارم به‌صورت یک افکت هشدار و شمارش معکوس طراحی شده که با ظاهر بمب ساعتی پروژه هماهنگ است.

آلارم را می‌توان با کلید فیزیکی متصل به D5 متوقف کرد.

D5 ───── Push Button ───── GND

---

📱 نصب Firmware با گوشی Android

یکی از ویژگی‌های مهم این پروژه این است که Firmware آن را می‌توان بدون کامپیوتر و مستقیماً با گوشی Android روی ESP8266 نصب کرد.

برای این کار از برنامه:

ESPFlash-ESP32/ESP8266Flasher

استفاده شده است.

برنامه از فلش کردن Firmware روی ESP8266 از طریق USB OTG پشتیبانی می‌کند.

برنامه مورد استفاده

Google Play:

https://play.google.com/store/apps/details?id=io.serialflow.espflash

---

📲 روش نصب Firmware

1. آماده‌سازی

موارد مورد نیاز:

- گوشی Android
- برد NodeMCU Amica ESP8266
- کابل USB مناسب
- در صورت نیاز مبدل USB OTG
- فایل Firmware پروژه:

esp8266-bomb-clock-v1.0.bin

گوشی را از طریق USB به ESP8266 متصل کنید.

---

2. اجرای برنامه

برنامه ESPFlash-ESP32/ESP8266Flasher را باز کنید.

در قسمت Firmware File روی علامت:

+

بزنید.

---

3. اضافه کردن Firmware

صفحه‌ای با عنوان:

Add Firmware

باز می‌شود.

فایل زیر را از حافظه گوشی انتخاب کنید:

esp8266-bomb-clock-v1.0.bin

---

4. تنظیم Address

پس از اضافه کردن فایل، مقدار Address را روی:

0x0000

قرار دهید.

تنظیمات مورد استفاده در نسخه فعلی:

Firmware File:
esp8266-bomb-clock-v1.0.bin

Address:
0x0000

---

5. High-Speed Mode

در این پروژه گزینه زیر فعال بوده است:

High-Speed Mode (Stub)

این گزینه برای افزایش سرعت انتقال Firmware استفاده می‌شود.

---

6. Firmware Compress

در نسخه‌ای که برای این پروژه استفاده شده، گزینه زیر نیز فعال بوده است:

Firmware Compress

این گزینه به حالت High-Speed Mode وابسته است و برای کاهش زمان انتقال Firmware استفاده می‌شود.

---

7. Baudrate

مقدار Baudrate را روی:

115200

قرار دهید.

تنظیمات نهایی مورد استفاده:

High-Speed Mode (Stub): ON
Firmware Compress: ON
Baudrate: 115200

---

8. شروع Flash

پس از انجام تنظیمات، روی دکمه Upload / Flash که با علامت فلش رو به پایین نمایش داده می‌شود بزنید.

برنامه شروع به انتقال Firmware به ESP8266 می‌کند.

منتظر بمانید تا عملیات کامل شود.

---

9. پایان عملیات

پس از پایان موفقیت‌آمیز عملیات، برنامه پیام مربوط به کامل شدن عملیات Flash را نمایش می‌دهد.

پس از اتمام Flash، ESP8266 را راه‌اندازی مجدد کنید.

در صورت اجرای صحیح Firmware، دستگاه باید به حالت ساعت و Web Server پروژه وارد شود.

---

📌 تنظیمات Flash استفاده‌شده در این پروژه

برای بازسازی همین نسخه Firmware، تنظیمات ثبت‌شده در این پروژه عبارت‌اند از:

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

«این تنظیمات بر اساس روش واقعی استفاده‌شده برای نصب Firmware این پروژه ثبت شده‌اند. در صورت استفاده از Firmware یا برد متفاوت، ممکن است تنظیمات Flash متفاوت باشند.»

---

📷 تصویر برنامه Android

"Android ESPFlash Firmware Upload" (App.update.file.android.jpg)

این تصویر محیط برنامه Android مورد استفاده برای نصب Firmware پروژه را نشان می‌دهد.

---

📷 تصاویر پروژه

نمای ظاهری

"ESP8266 Bomb Clock" (clock.jpg)

"ESP8266 Bomb Clock" (clock2.jpg)

Web Server

"ESP8266 Bomb Clock Web Server" (Web.clock.jpg)

"ESP8266 Bomb Clock Web Server" (Web.clock2.jpg)

---

📦 Firmware

نسخه فعلی Firmware پروژه:

esp8266-bomb-clock-v1.0.bin

این فایل نسخه کامپایل‌شده Firmware برای ESP8266 است.

Source Code

در حال حاضر نسخه اصلی Arduino با پسوند ".ino" در دسترس نیست.

بنابراین Repository فعلی شامل:

- Firmware کامپایل‌شده
- مستندات پروژه
- تصاویر سخت‌افزار
- تصاویر Web Server
- آموزش نصب Firmware

است.

فایل ".bin" یک Firmware کامپایل‌شده است و مانند فایل ".ino" قابل ویرایش مستقیم نیست.

در صورت پیدا شدن سورس کد اصلی در آینده، می‌توان آن را به Repository اضافه کرد.

---

🛠️ وضعیت پروژه

Project Status: Completed / Archived Firmware

این Repository برای نگهداری، پشتیبان‌گیری و مستندسازی نسخه فعلی پروژه ایجاد شده است.

موارد موجود:

- Firmware کامپایل‌شده ESP8266
- اطلاعات سخت‌افزار
- شماتیک اتصالات
- تصاویر پروژه
- تصاویر Web Server
- آموزش نصب Firmware با Android
- اطلاعات Web Server

---

🔧 ایده‌های توسعه آینده

در صورت ادامه توسعه پروژه، امکانات زیر می‌توانند اضافه شوند:

- انتشار سورس کد اصلی ".ino"
- بهبود طراحی سخت‌افزار
- استفاده از GPIOهای مستقل برای TM1637 و DS1307
- تنظیم خودکار زمان از طریق Wi-Fi
- امکانات بیشتر برای Web Server
- تنظیم شدت نور نمایشگر
- نمایش ثانیه
- الگوهای مختلف صدای آلارم
- LED وضعیت
- طراحی PCB اختصاصی
- بهبود قاب و ظاهر پروژه
- ذخیره تنظیمات بیشتر در حافظه

---

⚠️ هشدار

این پروژه یک وسیله دکوراتیو، سرگرمی و آموزشی است.

اگرچه ظاهر پروژه از بمب ساعتی تخیلی الهام گرفته شده است، این وسیله هیچ ماده منفجره، سلاح یا عملکرد مخربی ندارد.

---

👤 سازنده

HUSAIN

Designed, assembled and developed as a personal DIY electronics project.

---

🇬🇧 English

Project Overview

ESP8266 Bomb Clock is a decorative desk clock inspired by the visual design of a fictional time bomb.

The project was built using an ESP8266 NodeMCU Amica, a DS1307 Real-Time Clock, a TM1637 4-digit display, and a passive buzzer.

The DS1307 is responsible for keeping the time, while the TM1637 displays the current time.

A passive buzzer provides a fictional countdown-style alarm effect that matches the visual theme of the project.

The project is intended for decoration, entertainment, DIY electronics and experimentation only.

It has no real explosive, weapon or destructive functionality.

---

✨ Features

- NodeMCU Amica ESP8266
- DS1307 Real-Time Clock
- TM1637 4-digit display
- Passive buzzer alarm
- Physical alarm stop button
- Built-in ESP8266 Web Server
- Standalone Wi-Fi Access Point
- Clock configuration through a web browser
- Alarm configuration through a web browser
- Settings stored in ESP8266 memory
- Decorative time-bomb-inspired design
- Ready-to-use compiled firmware
- Android-based firmware flashing without a PC

---

🔌 Wiring

TM1637

TM1637| ESP8266
CLK| D2
DIO| D1
VCC| Appropriate module supply
GND| GND

DS1307

DS1307| ESP8266
SCL| D1
SDA| D2
VCC| Appropriate module supply
GND| GND

Passive Buzzer

Buzzer| ESP8266
I/O| D4
GND| GND
VCC| Appropriate module supply

Alarm Stop Button

The alarm stop button is connected between D5 and GND.

D5 ───── Push Button ───── GND

---

⚠️ Wiring Note

The current version uses:

D1 → TM1637 DIO
D1 → DS1307 SCL

D2 → TM1637 CLK
D2 → DS1307 SDA

D4 → Passive Buzzer

D5 → Alarm Stop Button

These are the connections used by the current version.

For future hardware revisions, the TM1637 and DS1307 connections should be reviewed and separate GPIO assignments may be preferable.

---

⏰ Clock System

The DS1307 RTC keeps the current time.

The ESP8266 reads the time from the RTC and drives the TM1637 display.

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
              ┌────────┴────────┐
              │                 │
              ▼                 ▼
       ┌──────────────┐  ┌──────────────┐
       │    TM1637    │  │    Buzzer    │
       │   Display    │  │    Alarm     │
       └──────────────┘  └──────┬───────┘
                                │
                           ┌────▼─────┐
                           │    D5    │
                           │   STOP   │
                           └──────────┘

---

🌐 Web Server

This version includes a built-in ESP8266 Web Server.

The ESP8266 creates its own Wi-Fi Access Point, so the configuration page can be accessed directly from a phone without requiring an external router or Internet connection.

Wi-Fi Access Point

SSID: ESP8266-Clock
Password: 12345678

Accessing the Web Interface

Connect your phone to:

ESP8266-Clock

Then open:

http://192.168.4.1

The project web interface should then be displayed.

---

⚙️ Clock and Alarm Configuration

The Web Server allows the user to configure the clock and alarm.

Main functions include:

- Setting the clock
- Setting the alarm time
- Managing alarm settings
- Saving settings
- Viewing clock and alarm information

The settings are stored in ESP8266 memory and can remain available after restarting the device.

---

🚨 Alarm

A passive buzzer is used for the alarm system.

The alarm sound is designed as a fictional warning and countdown-style effect inspired by movie-style time-bomb props.

The physical button connected to D5 can be used to stop the alarm.

D5 ───── Push Button ───── GND

---

📱 Flashing the Firmware from Android

The firmware can be installed on the ESP8266 directly from an Android phone without using a computer.

The application used to flash this project is:

ESPFlash-ESP32/ESP8266Flasher

Google Play:

https://play.google.com/store/apps/details?id=io.serialflow.espflash

---

Requirements

- Android phone
- NodeMCU Amica ESP8266
- USB cable
- USB OTG adapter if required
- Project firmware:

esp8266-bomb-clock-v1.0.bin

---

Flashing Procedure

1. Connect the ESP8266

Connect the NodeMCU ESP8266 to the Android phone using USB and OTG.

Open the ESPFlash-ESP32/ESP8266Flasher application.

---

2. Add the Firmware

In the Firmware File section, press:

+

Select:

esp8266-bomb-clock-v1.0.bin

The firmware should then appear under the Add Firmware section.

---

3. Set the Address

Set the firmware address to:

0x0000

The configuration used for this project is:

Firmware File:
esp8266-bomb-clock-v1.0.bin

Address:
0x0000

---

4. Enable High-Speed Mode

Enable:

High-Speed Mode (Stub)

This option is used in the tested flashing procedure for this project.

---

5. Enable Firmware Compress

Enable:

Firmware Compress

The tested configuration uses both High-Speed Mode and Firmware Compress.

---

6. Set Baudrate

Set:

Baudrate: 115200

Final tested settings:

High-Speed Mode (Stub): ON
Firmware Compress: ON
Baudrate: 115200

---

7. Start Flashing

Press the Flash / Upload button represented by the downward arrow.

The application will begin transferring the firmware to the ESP8266.

Wait until the operation has completed.

---

8. Flash Complete

After the firmware has been successfully written, the application displays a completion message indicating that the flash operation has finished.

Restart the ESP8266 if necessary.

After successful installation, the ESP8266 should start the Bomb Clock firmware.

---

📌 Tested Flash Configuration

The following configuration was used successfully with the firmware in this repository:

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

«These settings document the flashing procedure used for this specific firmware. Different ESP8266 boards or different firmware builds may require different flashing settings.»

---

📷 Android Flashing App

"Android ESPFlash Firmware Upload" (App.update.file.android.jpg)

The image above shows the Android application used to install the firmware.

---

📷 Project Photos

Hardware

"ESP8266 Bomb Clock" (clock.jpg)

"ESP8266 Bomb Clock" (clock2.jpg)

Web Interface

"ESP8266 Bomb Clock Web Server" (Web.clock.jpg)

"ESP8266 Bomb Clock Web Server" (Web.clock2.jpg)

---

📦 Firmware

Current firmware:

esp8266-bomb-clock-v1.0.bin

This is the compiled firmware image for the ESP8266.

Source Code

The original Arduino ".ino" source code is currently unavailable.

Therefore, this repository currently contains:

- Compiled firmware
- Hardware documentation
- Project photographs
- Web Server screenshots
- Android flashing instructions

The ".bin" file is a compiled firmware image and cannot be edited directly like the original ".ino" source code.

If the original source code is recovered in the future, it can be added to this repository.

---

🛠️ Project Status

Project Status: Completed / Archived Firmware

This repository was created to preserve, back up and document the current version of the project.

The repository contains:

- Compiled ESP8266 firmware
- Hardware information
- Wiring documentation
- Project photographs
- Web Server screenshots
- Android firmware flashing instructions

---

🔧 Future Improvements

Possible future improvements include:

- Recovering and publishing the original ".ino" source code
- Improved hardware design
- Separate GPIO assignments for TM1637 and DS1307
- Wi-Fi time synchronization
- More advanced Web Server controls
- Display brightness control
- Seconds display
- Multiple alarm sound patterns
- Status LED
- Custom PCB
- Improved enclosure
- Additional persistent settings

---

⚠️ Disclaimer

This is a decorative, entertainment and educational electronics project.

Although its appearance is inspired by a fictional time bomb, the device contains no explosive material, weapon functionality or destructive mechanism.

---

👤 Author

HUSAIN

Designed, assembled and developed as a personal DIY electronics project.

---

📄 Repository Contents

esp8266-bomb-clock
│
├── README.md
├── esp8266-bomb-clock-v1.0.bin
├── clock.jpg
├── clock2.jpg
├── Web.clock.jpg
├── Web.clock2.jpg
└── App.update.file.android.jpg
