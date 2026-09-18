#include <ESP8266WiFi.h>
#include <Wire.h>
#include <RTClib.h>
#include <TM1637Display.h>
#include <EEPROM.h>

#define TM1637_CLK 4
#define TM1637_DIO 5
#define BUZZER_PIN 2

#define ALARM_STOP_BUTTON 14
#define RELAY_PIN 12

#define RELAY_ON  LOW
#define RELAY_OFF HIGH

const char* AP_SSID = "ESP8266-Clock-v1.1";
const char* AP_PASSWORD = "sain6308";

WiFiServer server(80);

RTC_DS1307 rtc;
TM1637Display display(TM1637_CLK, TM1637_DIO);

int alarmHour = -1;
int alarmMinute = -1;

bool alarmActive = false;
bool alarmTriggered = false;

unsigned long alarmStartMillis = 0;

// ALARM BUZZER SETTINGS

const unsigned long ALARM_DURATION_MS = 40000UL;

const unsigned long BEEP_DURATION_MS = 160UL;

const unsigned long CONTINUOUS_START_MS = 35000UL;

const unsigned long CONTINUOUS_DURATION_MS = 5000UL;

const unsigned int BUZZER_FREQUENCY = 1000;

unsigned long lastBeepStartMillis = 0;

bool buzzerSequenceStarted = false;

// RELAY SETTINGS

const unsigned long RELAY_DELAY_MS = 35000UL;

const unsigned long RELAY_DURATION_MS = 30000UL;

bool relayActive = false;
unsigned long relayStartMillis = 0;

bool relayManual = false;

#define EEPROM_SIZE 3
#define EEPROM_ALARM_H_ADDR     0
#define EEPROM_ALARM_M_ADDR     1
#define EEPROM_ALARM_STATE_ADDR 2

// TM1637 DISPLAY BLINK

bool alarmDisplayOn = true;

unsigned long lastDisplayUpdate = 0;

bool lastDisplayState = true;

// SETUP

void setup() {

  Serial.begin(115200);

  pinMode(BUZZER_PIN, OUTPUT);
  noTone(BUZZER_PIN);

  // D5 / GPIO14 
  pinMode(ALARM_STOP_BUTTON, INPUT_PULLUP);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, RELAY_OFF);

  Wire.begin(
    TM1637_CLK,
    TM1637_DIO
  );

  if (!rtc.begin()) {
    Serial.println(F("Couldn't find RTC"));
  }

  if (!rtc.isrunning()) {
    Serial.println(F("RTC is NOT running!"));
  }

  display.setBrightness(0x0f);

  EEPROM.begin(EEPROM_SIZE);

  byte savedState =
    EEPROM.read(EEPROM_ALARM_STATE_ADDR);

  if (savedState == 1) {

    byte savedHour =
      EEPROM.read(EEPROM_ALARM_H_ADDR);

    byte savedMinute =
      EEPROM.read(EEPROM_ALARM_M_ADDR);

    if (savedHour <= 23 &&
        savedMinute <= 59) {

      alarmHour = savedHour;
      alarmMinute = savedMinute;

    } else {

      alarmHour = -1;
      alarmMinute = -1;
    }

  } else {

    alarmHour = -1;
    alarmMinute = -1;
  }

  WiFi.mode(WIFI_AP);

  WiFi.softAP(
    AP_SSID,
    AP_PASSWORD
  );

  Serial.print(F("AP IP: "));
  Serial.println(WiFi.softAPIP());

  server.begin();
}

// LOOP

void loop() {

  updateDisplay();

  checkAlarm();

  checkRelay();

  handleClient();
}

// UPDATE DISPLAY

void updateDisplay() {

  if (alarmActive) {

    if (millis() - lastDisplayUpdate < 20)
      return;

    lastDisplayUpdate = millis();

    unsigned long elapsed =
      millis() - alarmStartMillis;

    bool displayShouldBeOn = false;

    if (elapsed >= CONTINUOUS_START_MS &&
        elapsed < ALARM_DURATION_MS) {

      displayShouldBeOn = true;
    }

    else if (elapsed < CONTINUOUS_START_MS) {

      if (buzzerSequenceStarted) {

        unsigned long timeSinceLastBeep =
          millis() - lastBeepStartMillis;

        if (timeSinceLastBeep < BEEP_DURATION_MS) {

          displayShouldBeOn = false;

        } else {

          float elapsedSeconds =
            elapsed / 1000.0;

          float silenceSeconds =
            1.8 - (0.05 * elapsedSeconds);

          if (silenceSeconds < 0.0)
            silenceSeconds = 0.0;

          unsigned long silenceMillis =
            (unsigned long)(
              silenceSeconds * 1000.0
            );

          if (timeSinceLastBeep <
              BEEP_DURATION_MS + silenceMillis) {

            displayShouldBeOn = true;

          } else {

            displayShouldBeOn = false;
          }
        }
      }
    }

    if (displayShouldBeOn != lastDisplayState) {

      if (displayShouldBeOn) {

        DateTime now = rtc.now();

        display.showNumberDecEx(
          now.hour() * 100 + now.minute(),
          0b01000000,
          true
        );

      } else {

        display.clear();
      }

      lastDisplayState = displayShouldBeOn;
    }

    return;
  }

  if (millis() - lastDisplayUpdate < 200)
    return;

  lastDisplayUpdate = millis();

  DateTime now = rtc.now();

  static int lastSecond = -1;

  if (now.second() != lastSecond ||
      lastDisplayState == false) {

    lastSecond = now.second();

    display.showNumberDecEx(
      now.hour() * 100 + now.minute(),
      0b01000000,
      true
    );

    lastDisplayState = true;
  }
}

void checkAlarm() {

  if (digitalRead(ALARM_STOP_BUTTON) == LOW) {

    if (alarmActive || relayActive) {

      stopAlarmAndRelay();

      Serial.println(
        F("Alarm and Relay STOPPED by D5")
      );
    }

    return;
  }

  DateTime now = rtc.now();

  long nowSeconds =
    (long)now.hour() * 3600L +
    (long)now.minute() * 60L +
    (long)now.second();

  long alarmSeconds =
    (long)alarmHour * 3600L +
    (long)alarmMinute * 60L;

  long alarmStartSeconds =
    alarmSeconds - 40L;

  if (alarmStartSeconds < 0)
    alarmStartSeconds += 86400L;

  if (alarmTriggered &&
      nowSeconds > alarmSeconds) {

    alarmTriggered = false;
  }

  if (alarmHour >= 0 &&
      !alarmActive &&
      !alarmTriggered) {

    bool startAlarmNow = false;

    if (alarmStartSeconds <= alarmSeconds) {

      if (nowSeconds >= alarmStartSeconds &&
          nowSeconds < alarmSeconds) {

        startAlarmNow = true;
      }

    }

    else {

      if (nowSeconds >= alarmStartSeconds ||
          nowSeconds < alarmSeconds) {

        startAlarmNow = true;
      }
    }

    if (startAlarmNow) {

      alarmActive = true;

      alarmTriggered = true;

      alarmStartMillis = millis();

      lastBeepStartMillis = alarmStartMillis;

      buzzerSequenceStarted = true;

      tone(
        BUZZER_PIN,
        BUZZER_FREQUENCY
      );

      Serial.println(
        F("Alarm STARTED 40 seconds before set time")
      );
    }
  }

  if (alarmActive) {

    unsigned long elapsed =
      millis() - alarmStartMillis;

    if (elapsed >= CONTINUOUS_START_MS &&
        elapsed < ALARM_DURATION_MS) {

      tone(
        BUZZER_PIN,
        BUZZER_FREQUENCY
      );

      return;
    }

    if (elapsed >= ALARM_DURATION_MS) {

      stopAlarm();

      return;
    }

    if (buzzerSequenceStarted) {

      unsigned long timeSinceLastBeep =
        millis() - lastBeepStartMillis;

      if (timeSinceLastBeep < BEEP_DURATION_MS) {

        tone(
          BUZZER_PIN,
          BUZZER_FREQUENCY
        );

        return;
      }

      float elapsedSeconds =
        elapsed / 1000.0;

      float silenceSeconds =
        1.8 - (0.05 * elapsedSeconds);

      if (silenceSeconds < 0.0)
        silenceSeconds = 0.0;

      unsigned long silenceMillis =
        (unsigned long)(
          silenceSeconds * 1000.0
        );

      if (timeSinceLastBeep <
          BEEP_DURATION_MS + silenceMillis) {

        noTone(BUZZER_PIN);

        return;
      }

      tone(
        BUZZER_PIN,
        BUZZER_FREQUENCY
      );

      lastBeepStartMillis = millis();
    }
  }
}

// RELAY

void checkRelay() {

  if (relayManual)
    return;

  if (alarmActive &&
      !relayActive &&
      millis() - alarmStartMillis >=
      RELAY_DELAY_MS) {

    relayActive = true;

    relayStartMillis = millis();

    digitalWrite(
      RELAY_PIN,
      RELAY_ON
    );

    Serial.println(F("Relay ON"));
  }

  if (relayActive) {

    if (millis() - relayStartMillis >=
        RELAY_DURATION_MS) {

      relayActive = false;

      digitalWrite(
        RELAY_PIN,
        RELAY_OFF
      );

      Serial.println(F("Relay OFF"));
    }
  }
}

// STOP ALARM

void stopAlarm() {

  alarmActive = false;

  noTone(BUZZER_PIN);

  buzzerSequenceStarted = false;
  lastBeepStartMillis = 0;

  display.clear();
  lastDisplayState = false;
}

// STOP ALARM + RELAY BY D5

void stopAlarmAndRelay() {

  alarmActive = false;

  noTone(BUZZER_PIN);

  buzzerSequenceStarted = false;
  lastBeepStartMillis = 0;

  alarmTriggered = true;

  relayActive = false;
  relayManual = false;

  digitalWrite(
    RELAY_PIN,
    RELAY_OFF
  );

  display.clear();
  lastDisplayState = false;
}

// MANUAL RELAY

void manualRelayOn() {

  relayManual = true;
  relayActive = true;

  digitalWrite(
    RELAY_PIN,
    RELAY_ON
  );
}

void manualRelayOff() {

  relayManual = false;
  relayActive = false;

  digitalWrite(
    RELAY_PIN,
    RELAY_OFF
  );
}

// WEB SERVER

void handleClient() {

  WiFiClient client =
    server.available();

  if (!client)
    return;

  client.setTimeout(1000);

  String requestLine =
    client.readStringUntil('\n');

  while (client.connected() &&
         client.available()) {

    String line =
      client.readStringUntil('\n');

    if (line == "\r")
      break;
  }

  int firstSpace =
    requestLine.indexOf(' ');

  int secondSpace =
    requestLine.indexOf(
      ' ',
      firstSpace + 1
    );

  if (firstSpace == -1 ||
      secondSpace == -1) {

    client.stop();
    return;
  }

  String path =
    requestLine.substring(
      firstSpace + 1,
      secondSpace
    );

  String route = path;
  String query = "";

  int qIndex =
    path.indexOf('?');

  if (qIndex != -1) {

    route =
      path.substring(0, qIndex);

    query =
      path.substring(qIndex + 1);
  }

  if (route == "/") {

    sendMainPage(client);

  } else if (route == "/settings") {

    sendSettingsPage(client);

  } else if (route == "/getTime") {

    sendTimeJson(client);

  } else if (route == "/setTime") {

    handleSetTime(query);

    sendTextResponse(
      client,
      F("Time set")
    );

  } else if (route == "/setAlarm") {

    handleSetAlarm(query);

    sendTextResponse(
      client,
      F("Alarm set")
    );

  } else if (route == "/resetAlarm") {

    handleResetAlarm();

    sendTextResponse(
      client,
      F("Alarm reset")
    );

  } else if (route == "/relayOn") {

    manualRelayOn();

    sendTextResponse(
      client,
      F("Relay ON")
    );

  } else if (route == "/relayOff") {

    manualRelayOff();

    sendTextResponse(
      client,
      F("Relay OFF")
    );

  } else {

    send404(client);
  }

  client.stop();
}


// QUERY PARAMETER


int getQueryParamInt(
  const String& query,
  const char* key,
  int defaultValue
) {

  String searchKey =
    String(key) + "=";

  int idx =
    query.indexOf(searchKey);

  if (idx == -1)
    return defaultValue;

  int start =
    idx + searchKey.length();

  int end =
    query.indexOf('&', start);

  if (end == -1)
    end = query.length();

  if (end <= start)
    return defaultValue;

  return query.substring(
    start,
    end
  ).toInt();
}

// SET TIME

void handleSetTime(
  const String& query
) {

  int hour =
    getQueryParamInt(
      query,
      "hour",
      -1
    );

  int minute =
    getQueryParamInt(
      query,
      "minute",
      -1
    );

  int second =
    getQueryParamInt(
      query,
      "second",
      -1
    );

  if (hour >= 0 &&
      hour <= 23 &&
      minute >= 0 &&
      minute <= 59 &&
      second >= 0 &&
      second <= 59) {

    DateTime now = rtc.now();

    rtc.adjust(
      DateTime(
        now.year(),
        now.month(),
        now.day(),
        hour,
        minute,
        second
      )
    );
  }
}

// SET ALARM

void handleSetAlarm(
  const String& query
) {

  int newAlarmHour =
    getQueryParamInt(
      query,
      "alarmHour",
      -1
    );

  int newAlarmMinute =
    getQueryParamInt(
      query,
      "alarmMinute",
      -1
    );

  if (newAlarmHour >= 0 &&
      newAlarmHour <= 23 &&
      newAlarmMinute >= 0 &&
      newAlarmMinute <= 59) {

    alarmHour = newAlarmHour;
    alarmMinute = newAlarmMinute;

    alarmTriggered = false;

    EEPROM.write(
      EEPROM_ALARM_H_ADDR,
      (byte)alarmHour
    );

    EEPROM.write(
      EEPROM_ALARM_M_ADDR,
      (byte)alarmMinute
    );

    EEPROM.write(
      EEPROM_ALARM_STATE_ADDR,
      1
    );

    EEPROM.commit();

    stopAlarmAndRelay();

    alarmTriggered = false;
  }
}

// RESET ALARM

void handleResetAlarm() {

  alarmHour = -1;
  alarmMinute = -1;

  alarmTriggered = false;

  EEPROM.write(
    EEPROM_ALARM_H_ADDR,
    0
  );

  EEPROM.write(
    EEPROM_ALARM_M_ADDR,
    0
  );

  EEPROM.write(
    EEPROM_ALARM_STATE_ADDR,
    0
  );

  EEPROM.commit();

  stopAlarmAndRelay();

  alarmTriggered = false;
}

// TEXT RESPONSE

void sendTextResponse(
  WiFiClient& client,
  const __FlashStringHelper* text
) {

  client.println(F("HTTP/1.1 200 OK"));
  client.println(F("Content-Type: text/plain"));
  client.println(F("Connection: close"));
  client.println();
  client.println(text);
}

// 404

void send404(
  WiFiClient& client
) {

  client.println(F("HTTP/1.1 404 Not Found"));
  client.println(F("Content-Type: text/plain"));
  client.println(F("Connection: close"));
  client.println();
  client.println(F("Not found"));
}

// TIME JSON

void sendTimeJson(
  WiFiClient& client
) {

  DateTime now = rtc.now();

  char buf[9];

  snprintf(
    buf,
    sizeof(buf),
    "%02d:%02d:%02d",
    now.hour(),
    now.minute(),
    now.second()
  );

  client.println(F("HTTP/1.1 200 OK"));
  client.println(F("Content-Type: application/json"));
  client.println(F("Connection: close"));
  client.println();

  client.print(F("{\"time\":\""));
  client.print(buf);
  client.println(F("\"}"));
}

// MAIN PAGE

void sendMainPage(
  WiFiClient& client
) {

  client.println(F("HTTP/1.1 200 OK"));
  client.println(F("Content-Type: text/html; charset=utf-8"));
  client.println(F("Connection: close"));
  client.println();

  client.println(
    F("<!DOCTYPE html>"
      "<html><head>"
      "<meta name='viewport' "
      "content='width=device-width, initial-scale=1.0'>"
      "<style>"
      "body{"
      "font-family:Arial,sans-serif;"
      "background:linear-gradient(to right,#ffcccb,#ff69b4);"
      "text-align:center;"
      "margin:0;"
      "padding:0;"
      "}"
      "h1{color:#c71585;}"
      ".clock{"
      "font-size:72px;"
      "margin:20px;"
      "color:#ffffff;"
      "}"
      ".button{"
      "padding:15px 30px;"
      "font-size:18px;"
      "margin:20px;"
      "cursor:pointer;"
      "background-color:#ff1493;"
      "color:white;"
      "border:none;"
      "border-radius:5px;"
      "}"
      ".footer{"
      "margin-top:20px;"
      "font-size:14px;"
      "color:#ffffff;"
      "}"
      "</style>"
      "<script>"
      "function updateClock(){"
      "fetch('/getTime')"
      ".then(r=>r.json())"
      ".then(data=>{"
      "document.getElementById('clock').innerText=data.time;"
      "});"
      "}"
      "setInterval(updateClock,1000);"
      "window.onload=updateClock;"
      "</script>"
      "</head><body>"
      "<h1>Sain Clock</h1>"
      "<div class='clock' id='clock'>"
      "--:--:--"
      "</div>"
      "<button class='button' "
      "onclick=\"window.location.href='/settings'\">"
      "Settings"
      "</button>"
      "<div class='footer'>"
      "This code was written and coordinated by \"Husain\" and is dedicated to you."
      "</div>"
      "</body></html>")
  );
}

// HOUR OPTIONS

void sendHourOptions(
  WiFiClient& client,
  const char* id,
  int selectedValue
) {

  client.print(F("<select id='"));
  client.print(id);
  client.println(F("'>"));

  for (int i = 0; i < 24; i++) {

    client.print(F("<option value='"));
    client.print(i);
    client.print(F("'"));

    if (i == selectedValue)
      client.print(F(" selected"));

    client.print(F(">"));

    if (i < 10)
      client.print('0');

    client.print(i);
    client.println(F("</option>"));
  }

  client.println(F("</select>"));
}

// MINUTE OPTIONS

void sendMinuteOptions(
  WiFiClient& client,
  const char* id,
  int selectedValue
) {

  client.print(F("<select id='"));
  client.print(id);
  client.println(F("'>"));

  for (int i = 0; i < 60; i++) {

    client.print(F("<option value='"));
    client.print(i);
    client.print(F("'"));

    if (i == selectedValue)
      client.print(F(" selected"));

    client.print(F(">"));

    if (i < 10)
      client.print('0');

    client.print(i);
    client.println(F("</option>"));
  }

  client.println(F("</select>"));
}

// SECOND OPTIONS

void sendSecondOptions(
  WiFiClient& client,
  const char* id,
  int selectedValue
) {

  client.print(F("<select id='"));
  client.print(id);
  client.println(F("'>"));

  for (int i = 0; i < 60; i++) {

    client.print(F("<option value='"));
    client.print(i);
    client.print(F("'"));

    if (i == selectedValue)
      client.print(F(" selected"));

    client.print(F(">"));

    if (i < 10)
      client.print('0');

    client.print(i);
    client.println(F("</option>"));
  }

  client.println(F("</select>"));
}

// SETTINGS PAGE

void sendSettingsPage(
  WiFiClient& client
) {

  DateTime now = rtc.now();

  int currentHour = now.hour();
  int currentMinute = now.minute();
  int currentSecond = now.second();

  client.println(F("HTTP/1.1 200 OK"));
  client.println(F("Content-Type: text/html; charset=utf-8"));
  client.println(F("Connection: close"));
  client.println();

  client.println(
    F("<!DOCTYPE html>"
      "<html><head>"
      "<meta name='viewport' "
      "content='width=device-width, initial-scale=1.0'>"
      "<style>"
      "body{"
      "font-family:Arial,sans-serif;"
      "background:linear-gradient(to right,#ffcccb,#ff69b4);"
      "text-align:center;"
      "margin:0;"
      "padding:0;"
      "}"
      "h1{color:#c71585;}"
      ".card{"
      "background:rgba(255,255,255,0.85);"
      "border-radius:10px;"
      "margin:20px auto;"
      "padding:15px;"
      "max-width:320px;"
      "}"
      "select{"
      "padding:10px;"
      "font-size:16px;"
      "margin:10px;"
      "border-radius:5px;"
      "border:1px solid #c71585;"
      "}"
      ".button{"
      "padding:10px 20px;"
      "font-size:16px;"
      "margin:10px;"
      "cursor:pointer;"
      "background-color:#ff1493;"
      "color:white;"
      "border:none;"
      "border-radius:5px;"
      "}"
      ".switch{"
      "position:relative;"
      "display:inline-block;"
      "width:58px;"
      "height:32px;"
      "}"
      ".switch input{"
      "opacity:0;"
      "width:0;"
      "height:0;"
      "}"
      ".slider{"
      "position:absolute;"
      "cursor:pointer;"
      "top:0;"
      "left:0;"
      "right:0;"
      "bottom:0;"
      "background:#777;"
      "border-radius:32px;"
      "transition:.25s;"
      "}"
      ".slider:before{"
      "content:'';"
      "position:absolute;"
      "height:26px;"
      "width:26px;"
      "left:3px;"
      "top:3px;"
      "background:white;"
      "border-radius:50%;"
      "transition:.25s;"
      "box-shadow:0 1px 3px rgba(0,0,0,.35);"
      "}"
      "input:checked + .slider{"
      "background:#2196F3;"
      "}"
      "input:checked + .slider:before{"
      "transform:translateX(26px);"
      "}"
      ".relayRow{"
      "display:flex;"
      "align-items:center;"
      "justify-content:space-between;"
      "padding:5px 10px;"
      "}"
      ".footer{"
      "margin-top:20px;"
      "font-size:14px;"
      "color:#ffffff;"
      "}"
      "</style>"
      "<script>"

      "function setTime(){"
      "const hour=document.getElementById('hour').value;"
      "const minute=document.getElementById('minute').value;"
      "const second=document.getElementById('second').value;"
      "fetch('/setTime?hour='+hour+'&minute='+minute+'&second='+second)"
      ".then(()=>{"
      "alert('Time set to '+hour+':'+minute+':'+second);"
      "window.location.href='/';"
      "});"
      "}"

      "function setAlarm(){"
      "const alarmHour=document.getElementById('alarmHour').value;"
      "const alarmMinute=document.getElementById('alarmMinute').value;"
      "fetch('/setAlarm?alarmHour='+alarmHour+'&alarmMinute='+alarmMinute)"
      ".then(()=>{"
      "alert('Alarm set for '+alarmHour+':'+alarmMinute);"
      "window.location.href='/';"
      "});"
      "}"

      "function resetAlarm(){"
      "fetch('/resetAlarm')"
      ".then(()=>{"
      "alert('Alarm reset!');"
      "window.location.href='/';"
      "});"
      "}"

      "function relaySwitch(){"
      "const sw=document.getElementById('relaySwitch');"
      "if(sw.checked){"
      "fetch('/relayOn');"
      "}else{"
      "fetch('/relayOff');"
      "}"
      "}"

      "</script>"
      "</head><body>"
      "<h1>Settings</h1>")
  );

  // CLOCK

  client.println(
    F("<div class='card'>"
      "<h2>Clock</h2>"
      "<form onsubmit=\"event.preventDefault();setTime();\">"
      "Hour: ")
  );

  sendHourOptions(
    client,
    "hour",
    currentHour
  );

  client.println(F("<br>Minute: "));

  sendMinuteOptions(
    client,
    "minute",
    currentMinute
  );

  client.println(F("<br>Second: "));

  sendSecondOptions(
    client,
    "second",
    currentSecond
  );

  client.println(
    F("<br>"
      "<input type='submit' "
      "value='Set Time' class='button'>"
      "</form>"
      "</div>")
  );

  // ALARM

  client.println(
    F("<div class='card'>"
      "<h2>Alarm</h2>"
      "<form onsubmit=\"event.preventDefault();setAlarm();\">"
      "Hour: ")
  );

  if (alarmHour >= 0) {

    sendHourOptions(
      client,
      "alarmHour",
      alarmHour
    );

  } else {

    sendHourOptions(
      client,
      "alarmHour",
      0
    );
  }

  client.println(F("<br>Minute: "));

  if (alarmMinute >= 0) {

    sendMinuteOptions(
      client,
      "alarmMinute",
      alarmMinute
    );

  } else {

    sendMinuteOptions(
      client,
      "alarmMinute",
      0
    );
  }

  client.println(
    F("<br>"
      "<input type='submit' "
      "value='Set Alarm' class='button'>"
      "</form>")
  );

  client.println(
    F("<button class='button' "
      "onclick=\"resetAlarm()\">"
      "Reset Alarm"
      "</button>"
      "</div>")
  );

  // RELAY

  client.println(
    F("<div class='card'>"
      "<div class='relayRow'>"
      "<h2 style='margin:0;'>Relay</h2>"
      "<label class='switch'>"
      "<input type='checkbox' "
      "id='relaySwitch' "
      "onchange='relaySwitch()'")
  );

  if (relayManual && relayActive)
    client.print(F(" checked"));

  client.println(
    F(">"
      "<span class='slider'></span>"
      "</label>"
      "</div>"
      "</div>")
  );

  // BACK

  client.println(
    F("<button class='button' "
      "onclick=\"window.location.href='/'\">"
      "Back"
      "</button>"
      "<div class='footer'>"
      "This code was written and coordinated by \"Husain\" and is dedicated to you."
      "</div>"
      "</body></html>")
  );
}
