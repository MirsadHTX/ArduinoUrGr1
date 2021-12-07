#include <MMA7660.h>
#include <rgb_lcd.h>
#include <Wire.h>
#include "DS1307.h"

//giver alle værdier der bliver brugt
rgb_lcd lcd;
MMA7660 accelmeter;
uint8_t farver[5][3] = {{0, 255, 0}, {255, 0, 255}, {0, 180, 255}, {255, 0, 0}, {42, 42, 42}};
uint8_t tid[6][3] = {{8, 9, 15}, {9, 10, 35}, {10, 11, 45}, {12, 13, 15}, {13, 14, 25}, {14, 15, 30}};
char check[27]= "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int res[26] = {1300, 3111, 3131, 3110, 1000, 1131, 3310, 1111, 1100, 1333, 3130, 1311, 3300, 3100, 3330, 1331, 3313, 1310, 1110, 3000, 1130, 1113, 1330, 3113, 3133, 3311};
uint8_t screenNumber = 255;
bool tilt = true;
bool tryk = true;
float xAxis, yAxis, zAxis;
uint8_t navnNr;
uint8_t i;
unsigned long tidNu;
unsigned long tidFoer;
float count;
bool trykFoer;
bool trykNu;
bool urStop = true;
bool lock = false;
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
  //kalder tilstandskift for at se hvad screenNumber vi er på
  TilstandSkift();
  //clear skærmen så man ikke printer tekst oven i hindanden
  lcd.clear();
  if (lock) {
    lcd.setCursor(15, 0);
    lcd.print("L");
    lcd.setCursor(0, 0);
  }
  if (screenNumber == 0) {
    DitUr();
  } else if (screenNumber == 1) {
    getName();
  } else if (screenNumber == 2) {
    lcd.print(String(1.0 / (log(1023.0 / analogRead(A0) - 1.0) / 4275 + 1 / 298.15) - 273.15) + " Celsius");
    laas();
  } else if (screenNumber == 3) {
    StopUr();
  } else if (screenNumber == 4) {
    Christmas();
  } else if (screenNumber == 5) {
    morse();
  }
  //delay så skærmen den kan følge med
  delay(100);
}
