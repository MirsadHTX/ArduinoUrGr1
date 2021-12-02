#include <MMA7660.h>
#include <rgb_lcd.h>
#include <Wire.h>
#include "DS1307.h"

rgb_lcd lcd;
MMA7660 accelmeter;
uint8_t farver[5][3] = {{0, 255, 0}, {255, 0, 255}, {0, 180, 255}, {255, 0, 0}, {42, 42, 42}};
char check[27]= "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int res[26] = {1300, 3111, 3131, 3110, 1000, 1131, 3310, 1111, 1100, 1333, 3130, 1311, 3300, 3100, 3330, 1331, 3313, 1310, 1110, 3000, 1130, 1113, 1330, 3113, 3133, 3311};
uint8_t screenNumber = 255;
bool tilt = true;
bool tryk = true;
float xAxis, yAxis, zAxis;
uint8_t navnNr;
unsigned long tidNu;
unsigned long tidFoer;
float count;
bool trykFoer;
bool trykNu;
bool urStop = true;
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
//  lcd.print(screenNumber);

  if (screenNumber == 0) {
    DitUr();
  } else if (screenNumber == 1) {
    getName();
  } else if (screenNumber == 2) {
    lcd.print(1.0 / (log(1023.0 / analogRead(A0) - 1.0) / 4275 + 1 / 298.15) - 273.15);
  } else if (screenNumber == 3) {
    StopUr();
  } else if (screenNumber == 4) {
    Christsmas();
  } else if (screenNumber == 5) {
    morse();
  }
  
  delay(100);
}
