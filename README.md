ESP8266 Bomb Clock

🇮🇷 بخش فارسی

⏰ معرفی پروژه

ESP8266 Bomb Clock یک ساعت رومیزی دست‌ساز و دکوراتیو است که با استفاده از NodeMCU Amica ESP8266 ساخته شده و ظاهر آن عمداً شبیه یک بمب ساعتی طراحی شده است.

هدف این پروژه سرگرمی، ساخت یک وسیله دکوراتیو و تجربه عملی در زمینه الکترونیک و برنامه‌نویسی بوده است.

این پروژه از ابتدا توسط سازنده طراحی و ساخته شده و شامل یک ساعت دیجیتال، سیستم آلارم، ماژول RTC و یک بازر Passive است.

«⚠️ این پروژه صرفاً یک وسیله الکترونیکی دکوراتیو و نمایشی است و کاربرد واقعی یا خطرناک ندارد.»

---

📸 تصاویر پروژه

نمای روبه‌رو

نمای بالا

---

✨ امکانات

- استفاده از NodeMCU Amica ESP8266
- نمایش ساعت با نمایشگر TM1637 چهاررقمی
- ساعت ۲۴ ساعته
- استفاده از DS1307 برای نگهداری زمان
- تنظیم ساعت از طریق Web Server
- عملکرد کاملاً آفلاین
- سیستم آلارم حدود ۴۰ ثانیه‌ای
- بازر Passive
- دکمه فیزیکی برای قطع آلارم
- تغییر تدریجی سرعت بوق‌ها
- تبدیل بوق‌های متناوب به صدای ممتد در پایان آلارم
- تغذیه با باتری 18650
- طراحی ظاهری شبیه بمب ساعتی
- مناسب برای استفاده به عنوان ساعت و وسیله دکوراتیو

---

🔧 قطعات استفاده‌شده

قطعه| توضیحات
NodeMCU Amica ESP8266| برد اصلی پروژه
TM1637| نمایشگر ۴ رقمی
DS1307| ماژول ساعت واقعی
Passive Buzzer| تولید صدای آلارم
Push Button| دکمه قطع آلارم
18650| باتری ۳.۷ ولتی

---

🔌 اتصالات

TM1637

TM1637| ESP8266
CLK| D2
DIO| D1

DS1307

DS1307| ESP8266
SCL| D1
SDA| D2

Passive Buzzer

Buzzer| ESP8266
Signal| D4

دکمه قطع آلارم

دکمه بین پایه D5 و GND قرار گرفته است.

Button| ESP8266
یک پایه| D5
پایه دیگر| GND

---

🕐 عملکرد ساعت

نمایشگر TM1637 ساعت را به شکل زیر نمایش می‌دهد:

HH:MM

ساعت به صورت ۲۴ ساعته کار می‌کند.

در این نسخه تاریخ نمایش داده نمی‌شود.

تنظیم ساعت از طریق Web Server داخلی ESP8266 انجام می‌شود.

---

🚨 سیستم آلارم

مدت زمان کل آلارم تقریباً ۴۰ ثانیه است.

آلارم ابتدا با بوق‌های کوتاه و فاصله زیاد شروع می‌شود و سپس فاصله بین بوق‌ها به صورت تدریجی کاهش پیدا می‌کند.

مشخصات آلارم

- مدت روشن بودن هر بوق: تقریباً ۱۵۰ میلی‌ثانیه
- فاصله اولیه بین بوق‌ها: تقریباً ۱۸۰۰ تا ۲۰۰۰ میلی‌ثانیه
- کاهش فاصله بین بوق‌ها: تقریباً ۴۰ تا ۵۰ میلی‌ثانیه در هر مرحله
- تعداد مراحل شتاب‌گیری: حدود ۴۵ بوق
- کمترین فاصله نهایی: تقریباً ۶۰ تا ۷۰ میلی‌ثانیه
- مدت مرحله شتاب‌گیری: حدود ۳۵ ثانیه

در پایان، بوق‌های متناوب متوقف شده و بازر وارد حالت صدای ممتد می‌شود.

صدای نهایی

در مرحله پایانی، بازر یک تون ممتد تقریباً:

5000 Hz

را برای حدود:

5 seconds

پخش می‌کند.

پس از پایان این تون، آلارم متوقف شده و سیستم وارد حالت سکوت می‌شود.

روند کلی آلارم

بوق‌های آرام و با فاصله زیاد
          ↓
کاهش تدریجی فاصله بوق‌ها
          ↓
بوق‌های بسیار سریع
          ↓
صدای ممتد 1000Hz
          ↓
پایان آلارم

دکمه متصل به D5 برای قطع کردن آلارم استفاده می‌شود.

---

🌐 Web Server

این پروژه دارای یک Web Server داخلی است.

از Web Server برای تنظیم ساعت و تنظیمات مربوط به آلارم استفاده می‌شود.

پروژه برای کارکرد اصلی خود به اینترنت نیاز ندارد و به صورت Offline طراحی شده است.

یعنی ESP8266 می‌تواند بدون اتصال به اینترنت، Web Server خود را اجرا کند و کاربر از طریق شبکه محلی ایجادشده توسط دستگاه به آن متصل شود.

---

🔋 منبع تغذیه

در این پروژه از یک باتری قابل شارژ:

3.7V 18650 Li-ion

استفاده شده است.

⚠️ باتری 18650 در حالت شارژ کامل می‌تواند تا حدود 4.2V برسد. بنابراین نباید آن را بدون مدار مناسب مستقیماً به پایه 3.3V ESP8266 متصل کرد.

برای تغذیه NodeMCU از روش مناسب و پایدار استفاده کنید.

---

🏗️ ساخت بدنه

بدنه پروژه با استفاده از لوله ساخته شده است.

هر قسمت لوله حدود:

20 cm

برش داده شده و با کاغذ رنگی قرمز پوشانده شده است.

بردها و سیم‌کشی‌ها نیز به صورت قابل مشاهده روی بدنه نصب شده‌اند تا ظاهر پروژه بیشتر شبیه یک بمب ساعتی تخیلی باشد.

این طراحی صرفاً برای ایجاد ظاهر دکوراتیو و نمایشی پروژه انجام شده است.

---

🎨 کاربرد پروژه

این پروژه را می‌توان هم به عنوان:

- ساعت رومیزی
- وسیله دکوراتیو
- پروژه آموزشی الکترونیک
- پروژه سرگرمی و ساخت‌وساز

استفاده کرد.

---

💻 نرم‌افزار

پروژه با استفاده از Arduino IDE توسعه داده شده است.

برد مورد استفاده:

NodeMCU Amica ESP8266

فایل سورس اصلی ".ino" در حال حاضر در Repository موجود نیست و نسخه منتشرشده شامل فایل Firmware کامپایل‌شده است.

---

📦 Firmware

نسخه منتشرشده پروژه:

esp8266-bomb-clock-v1.0.bin

این فایل Firmware کامپایل‌شده برای ESP8266 است.

نسخه

v1.0

برد هدف

ESP8266
NodeMCU Amica

---

📁 ساختار Repository

esp8266-bomb-clock/
│
├── README.md
├── esp8266-bomb-clock-v1.0.bin
├── clock.jpg
└── clock2.jpg

---

📜 مجوز

این پروژه تحت MIT License منتشر می‌شود.

استفاده، مطالعه، تغییر و انتشار مجدد پروژه طبق شرایط این مجوز آزاد است.

---

👤 سازنده

SAIN

یک پروژه DIY در زمینه الکترونیک، میکروکنترلر و ساخت وسایل دست‌ساز.

---

🇬🇧 English Section

⏰ About the Project

ESP8266 Bomb Clock is a DIY decorative desk clock built around a NodeMCU Amica ESP8266.

The device was intentionally designed with a fictional bomb-clock-inspired appearance for entertainment, decoration and hands-on electronics experimentation.

The project was designed and built from scratch by the author and combines a digital clock, RTC module, alarm system and passive buzzer.

«⚠️ This is a decorative and fictional electronic project. It is not intended for any dangerous or harmful purpose.»

---

📸 Project Photos

Front View

Top View

---

✨ Features

- NodeMCU Amica ESP8266
- TM1637 4-digit display
- 24-hour clock
- DS1307 real-time clock
- Local Web Server for clock configuration
- Offline operation
- Passive buzzer alarm
- Physical alarm stop button
- Approximately 40-second alarm sequence
- Progressive alarm acceleration
- Final continuous tone
- 18650 rechargeable battery
- Bomb-clock-inspired decorative design
- Can be used as both a desk clock and a decorative object

---

🔧 Hardware

Component| Description
NodeMCU Amica ESP8266| Main controller
TM1637| 4-digit display
DS1307| Real-time clock module
Passive Buzzer| Alarm sound
Push Button| Alarm stop button
18650| 3.7 V Li-ion battery

Components not used in v1.0

- Relay
- LED
- Sensors
- Date display

---

🔌 Wiring

TM1637

TM1637| ESP8266
CLK| D2
DIO| D1

DS1307

DS1307| ESP8266
SCL| D1
SDA| D2

Passive Buzzer

Buzzer| ESP8266
Signal| D4

Alarm Stop Button

The button is connected between D5 and GND.

Button| ESP8266
One side| D5
Other side| GND

---

🕐 Clock

The TM1637 display shows the time in:

HH:MM

format.

The clock uses a 24-hour format.

Date display is not included in v1.0.

The clock can be configured through the ESP8266's local Web Server.

---

🚨 Alarm System

The complete alarm sequence lasts approximately 40 seconds.

The alarm starts with short beeps separated by relatively long intervals. The interval gradually decreases, making the alarm progressively faster.

Alarm characteristics

- Beep duration: approximately 150 ms
- Initial silent interval: approximately 1800–2000 ms
- Interval reduction: approximately 40–50 ms per stage
- Approximately 45 acceleration stages
- Final interval: approximately 60–70 ms
- Acceleration phase: approximately 35 seconds

At the end of the acceleration sequence, the buzzer changes from individual beeps to a continuous tone.

Final tone

The final stage produces a continuous tone of approximately:

5000 Hz

for approximately:

5 seconds

After the final tone, the alarm stops and the buzzer becomes silent.

Alarm sequence

Slow beeps
     ↓
Progressively faster beeps
     ↓
Very short intervals
     ↓
Continuous 5000 Hz tone
     ↓
Alarm stops

The physical button connected to D5 can be used to stop the alarm.

---

🌐 Web Server

The project includes a built-in local Web Server.

The Web Server is used to configure the clock and alarm settings.

The project is designed to operate offline and does not require an internet connection for its main functions.

The ESP8266 can provide its own local network access so the user can connect to the Web Server and configure the device.

---

🔋 Power

The prototype uses a rechargeable:

3.7 V 18650 Li-ion battery

⚠️ A fully charged 18650 cell can reach approximately 4.2 V. Do not connect an unregulated Li-ion cell directly to the ESP8266 3.3 V pin.

Use an appropriate and stable power method for the NodeMCU board.

---

🏗️ Physical Design

The body was built using tubes.

Each tube section is approximately:

20 cm

long and covered with red-colored paper.

The electronic boards and wiring are intentionally mounted visibly on the body to enhance the fictional bomb-clock appearance.

This design is purely decorative and intended to create the visual style of a fictional bomb-clock prop.

---

🎨 Intended Use

The project can be used as:

- A desk clock
- A decorative object
- An electronics learning project
- A DIY maker project
- An entertainment project

---

💻 Software

The project was developed using:

- Arduino IDE
- ESP8266 Arduino platform

Target board:

NodeMCU Amica ESP8266

The original Arduino ".ino" source code is not currently included in the repository.

The currently released firmware is the compiled binary version.

---

📦 Firmware

Released firmware:

esp8266-bomb-clock-v1.0.bin

Version

v1.0

Target

ESP8266
NodeMCU Amica

---

📁 Repository Structure

esp8266-bomb-clock/
│
├── README.md
├── esp8266-bomb-clock-v1.0.bin
├── clock.jpg
└── clock2.jpg

---

📜 License

This project is released under the MIT License.

You are free to use, modify and redistribute the project according to the terms of the license.

---

👤 Author

SAIN

A DIY project focused on electronics, microcontrollers and hands-on hardware building.

---

⭐ ESP8266 Bomb Clock

Version 1.0

Built for learning, experimentation, entertainment and decoration.
