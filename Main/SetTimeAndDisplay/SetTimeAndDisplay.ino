#include <rgb_lcd.h>
#include <Wire.h>
#include "DS1307.h"

rgb_lcd lcd;

DS1307 clock;//define a object of DS1307 class
void setup() 
{
    lcd.begin(16,2);
    clock.begin();
    clock.fillByYMD(2021, 11, 18); //Jan 19,2013
    clock.fillByHMS(9, 10,10 ); //15:28 30"
    clock.fillDayOfWeek(THU);//Saturday
    clock.setTime();//write time to the RTC chip
    lcd.setRGB(0,0,255);
}
void loop() {
    printTime();
}
/*Function: Display time on the serial monitor*/
void printTime() {
     lcd.clear();
     clock.getTime();
     lcd.print(clock.hour, DEC);
     lcd.print(":");
     lcd.print(clock.minute, DEC);
     lcd.print(":");
     lcd.print(clock.second, DEC);
     lcd.print("	");
     lcd.setCursor(0,1);
     lcd.print(clock.month, DEC);
     lcd.print("/");
     lcd.print(clock.dayOfMonth, DEC);
     lcd.print("/");
     lcd.print(clock.year + 2000, DEC);
     lcd.print(" ");
     lcd.print(clock.dayOfMonth);
     lcd.print("*");
     delay(100);
            
    }
     
