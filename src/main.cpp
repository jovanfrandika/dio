#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUDP.h>
#include <NTPClient.h>
#include <TimeLib.h>
#include <LiquidCrystal_I2C.h>

#define _SSID "ssid"
#define _PASSWORD "password"

#define LCD_COL 16
#define LCD_ROW 2

String updateClockTime(unsigned long unix_epoch);
String updateDateTime(unsigned long unix_epoch);
void updateTime();

LiquidCrystal_I2C lcd(0x27, LCD_COL, LCD_ROW);

WiFiUDP ntpUDP;
NTPClient timeClient(
  ntpUDP,
  "time.nist.gov",
  25200, // 25200 = GMT+7 (3600 = GMT+1)
  60000
);

void setup() {
  lcd.init();
  lcd.backlight();
  
  WiFi.begin(_SSID, _PASSWORD);

  lcd.setCursor(0, 0);
  lcd.print("Connecting");

  lcd.setCursor(0, 1);
  while (WiFi.status() != WL_CONNECTED){
    delay(100);
    lcd.print(".");
  }
  lcd.print("\n WiFi Connected");

  timeClient.begin();
  lcd.clear();
}

void loop() {
  updateTime();
}

String updateClockTime(unsigned long epochTime) {
  String clockTime= "TIME:";
  byte _second, _minute, _hour;

  _second = second(epochTime);
  _minute = minute(epochTime);
  _hour = hour(epochTime);

  clockTime.concat(_hour);
  clockTime.concat(":");
  clockTime.concat(_minute);
  clockTime.concat(":");
  clockTime.concat(_second);

  return clockTime;
}

String updateDateTime(unsigned long epochTime) {
  String dateTime = "DATE:";
  byte  _day, _month, _year;

  _day = day(epochTime);
  _month = month(epochTime);
  _year = year(epochTime);

  dateTime.concat(_day);
  dateTime.concat("/");
  dateTime.concat(_month);
  dateTime.concat("/");
  dateTime.concat(_year);

  return dateTime;
}

void updateTime(){
  timeClient.update();

  // Get Unix epoch time from NTP server
  unsigned long epochTime = timeClient.getEpochTime();

  String clockTime = updateClockTime(epochTime);
  lcd.setCursor(0, 0);
  lcd.print(clockTime);

  String dateTime = updateDateTime(epochTime);
  lcd.setCursor(0, 1);
  lcd.print(dateTime);

  delay(200);
}
