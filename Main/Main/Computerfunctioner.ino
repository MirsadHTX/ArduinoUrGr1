void TilstandSkift() {
  accelmeter.getAcceleration(&xAxis, &yAxis, &zAxis); // Tager memory address som input

  if (zAxis <= 0.2 && tilt) {
    if (yAxis > 0.2) {
      screenNumber += 1;
    } else {
      screenNumber -= 1;
    }
    lcd.setRGB(random(0, 256), random(0, 256), random(0, 256));
    tilt = false;
    digitalWrite(2,1);
    delay(100);
    digitalWrite(2,0);
  } else if (zAxis >= 0.8) {
    tilt = true;
  }
}


void DitUr() {
  clock.getTime();
  lcd.print(clock.hour, DEC);
  lcd.print(":");
  lcd.print(clock.minute, DEC);
  lcd.print(":");
  if (clock.second < 10) {
    lcd.print("0" + String(clock.second, DEC));
    lcd.print("  ");
  } else {
    lcd.print(clock.second, DEC);
    lcd.print("  ");
  }

  lcd.setCursor(0,1);
  lcd.print(clock.month, DEC);
  lcd.print("/");
  lcd.print(clock.dayOfMonth, DEC);
  lcd.print("/");
  lcd.print(clock.year + 2000, DEC);
  lcd.print(" ");
}



char RandomElev[31][10] = { "Anders", "Emil", "Fahmi", "Freja", "Gustav W.", "Gustav E.", "Haris", "Ismail", "Jabriil", "Jacob", "Ludvig", "Jeppe", "Jonatan", "Kasper", "Lovro", "Mathias", "Mie", "Mohammad", "Nelisa", "Nicolai", "Pernille", "Rasmus", "Robert", "Sarah", "Silas", "Simon", "Thoeger", "Tobias", "Taaha", "William", "Tryk knap"};
void getName(void) {
  lcd.print(RandomElev[navnNr]);
  if (digitalRead(A1) && tryk){
    navnNr = random(0, 31);
    tryk = false;
  }else if (!digitalRead(A1)) {
    tryk = true;
  }
}




void StopUr()
{
  trykNu= digitalRead(A1);
  if (trykNu == true && trykFoer ==false)
  {
    if (urStop==false)
    {
       urStop=true;
   }
    else 
    {
      urStop=false;

      
     tidFoer = tidNu;
     lcd.clear();
    
    } 
 
  }


  
  if (urStop==false)
  {
    tidNu = millis();

    count = tidNu-tidFoer;
  }

  trykFoer=trykNu;
  
  lcd.setCursor(0,0);
  lcd.print(count/1000);
}
