// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 2 
#define DHTTYPE DHT11

uint8_t second;
RTC_DS1307 rtc;
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
DHT dht(DHTPIN, DHTTYPE);

void setup () {
  while (!Serial); // for Leonardo/Micro/Zero
  lcd.begin();
  lcd.backlight();
  dht.begin();
  Serial.println("DHTxx test!");
  Serial.begin(9600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    //following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void loop () {
    DateTime now = rtc.now();
    lcd.setCursor(1,0);
    // lcd.print(now.day(), DEC);
    // lcd.print('/');
    // lcd.print(now.month(), DEC);
    // lcd.print('/');
    // lcd.print(now.year(), DEC);
    lcd.print(" (");
    lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
    lcd.print(") ");
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    lcd.print(':');
    second = now.second();
    if(second < 10)
    {
      lcd.print("0");
    }
    lcd.print(now.second(), DEC);
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    int h = dht.readHumidity();
    int t = dht.readTemperature();

    // check if returns are valid, if they are NaN (not a number) then something went wrong!
    if (isnan(t) || isnan(h)) {
      Serial.println("Failed to read from DHT");
    } else {
      Serial.print("Humidity: "); 
      Serial.print(h);
      Serial.print(" %\t");
      Serial.print("Temperature: "); 
      Serial.print(t);
      Serial.println(" *C");
    }
    lcd.setCursor(0,1);
    lcd.print(t);
    lcd.print("oC");
    lcd.print("/");
    lcd.print("Do am:");
    lcd.print(h);
    lcd.print("%");


}