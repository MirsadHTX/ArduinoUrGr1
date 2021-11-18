#include <MMA7660.h>
#include <rgb_lcd.h>
#include <Wire.h>
#include "DS1307.h"

rgb_lcd lcd;
MMA7660 accelmeter;
uint8_t screenNumber = 1;
uint8_t tilt = 1;
uint8_t tryk = 1;
float xAxis, yAxis, zAxis;
uint8_t navnNr;
DS1307 clock;

void setup() {
  lcd.begin(16, 2);
  accelmeter.init();
  navnNr = 30;

/*  clock.begin(); 
  clock.fillByYMD(2021, 11, 18); //Jan 19,2013
  clock.fillByHMS(9, 50,10 ); //15:28 30"
  clock.fillDayOfWeek(THU);//Saturday
  clock.setTime();//write time to the RTC chip
  lcd.setRGB(0,0,255);*/
}

void loop() {
  TilstandSkift();
  lcd.clear();
//  lcd.print(navnNr);

  if (screenNumber == 0) {
    DitUr();
  } else if (screenNumber == 1) {
    getName();
  } else if (screenNumber == 2) {
    lcd.print(1.0 / (log(1023.0 / analogRead(A0) - 1.0) / 4275 + 1 / 298.15) - 273.15);
  }

  delay(100);
}
