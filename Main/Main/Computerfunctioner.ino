void TilstandSkift() {
  accelmeter.getAcceleration(&xAxis, &yAxis, &zAxis); // Tager memory address som input

  if (zAxis <= 0.2 && tilt) {
    if (yAxis > 0.2) {
      screenNumber -= 1;
      if (screenNumber == 255) {
        screenNumber = 0;
      }
    } else {
      screenNumber += 1;
      if (screenNumber == 6) {
        screenNumber = 5;
      }
    }
    lcd.setRGB(farver[screenNumber][0], farver[screenNumber][1], farver[screenNumber][2]);
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

char RandomElev[31][9] = { "Anders", "Emil", "Fahmi", "Freja", "Gustav W", "Gustav E", "Haris", "Ismail", "Jabriil", "Jacob", "Ludvig", "Jeppe", "Jonatan", "Kasper", "Lovro", "Mathias", "Mie", "Mohammad", "Nelisa", "Nicolai", "Pernille", "Rasmus", "Robert", "Sarah", "Silas", "Simon", "Thoeger", "Tobias", "Taaha", "William", "Tryk"};
void getName(void) {
  lcd.print(RandomElev[navnNr]);
  if (digitalRead(A1) && tryk){
    navnNr = random(0, 30);
    tryk = false;
  }else if (!digitalRead(A1)) {
    tryk = true;
  }
}

void StopUr() {
  if (digitalRead(A1) && trykFoer == false) {
    if (urStop == false) {
      urStop = true;
    } else {
      urStop = false;
      tidFoer = millis();
      lcd.clear();
    } 
  }
  trykFoer = digitalRead(A1);
  
  if (urStop == false) {
    count = millis() - tidFoer;
  }
  
  
  lcd.setCursor(0, 0);
  lcd.print(count / 1000);
}


void Christsmas() {
  lcd.setCursor(0, 0);
  lcd.print(24 - clock.dayOfMonth);
  lcd.print(" dage til jul");
  lcd.setCursor(0, 1);
  lcd.print(12 - clock.month);
  lcd.print(" maaned t. jul");
}

void morse() {
  lcd.print(check[map(analogRead(A2), 0, 1023, 0, 25)]);
  if (digitalRead(A1) && tryk){
    int tal = res[map(analogRead(A2), 0, 1023, 0, 25)];
    uint8_t i = 0;
    while (int(tal) > 0) {
//      lcd.print((tal));
      digitalWrite(2, 1);
      delay(100);
      digitalWrite(2, 0);
      delay(100);
      
      i ++;
    }
    tryk = false;
  }else if (!digitalRead(A1)) {
    tryk = true;
  }
}
