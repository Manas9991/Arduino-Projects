#include <Wire.h>
#include "RTClib.h"
#include "SevenSegmentTM1637.h"
#include "SevenSegmentExtended.h"

const byte PIN_CLK = 4;   // define CLK pin (any digital pin)
const byte PIN_DIO = 5;   // define DIO pin (any digital pin)
SevenSegmentExtended display(PIN_CLK, PIN_DIO);

RTC_DS1307 RTC;

void setup () {
    Serial.begin(9600);
    Wire.begin();
    RTC.begin();
  // Check to see if the RTC is keeping time.  If it is, load the time from your computer.
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // This will reflect the time that your sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  display.begin();            // initializes the display
  display.setBacklight(30);  // set the brightness to 100 %
}
void loop () {
    DateTime now = RTC.now(); 
    int hours = now.hour();
    int minutes = now.minute();
    int sec = now.second();
    int mnth = now.month();
    int date = now.day(); 
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print('/');
    Serial.print(now.year(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    if((sec>=29)and(sec<=31))
    {
      display.printTime(date, mnth, true);
    }
    else
    {
      display.printTime(hours, minutes, true);    
    }
    delay(1000);
}
