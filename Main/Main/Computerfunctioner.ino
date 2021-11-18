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

float Temperatur() {
  float t = 1.0 / (log(1023.0 / analogRead(A0) - 1.0) / 4275 + 1 / 298.15) - 273.15;
  return t;
}

void StopUr() {

}

char RandomElev[31][17] = { "Anders", "Emil", "Fahmi", "Freja", "Gustav W.", "Gustav E.", "Haris", "Ismail", "Jabriil", "Jacob", "Ludvig", "Jeppe", "Jonatan", "Kasper", "Lovro", "Mathias", "Mie", "Mohammad", "Nelisa", "Nicolai", "Pernille", "Rasmus", "Robert", "Sarah", "Silas", "Simon", "Thoeger", "Tobias", "Taaha", "William", "Du tryk den knap"};
void getName(void) {
  lcd.print(RandomElev[navnNr]);
  if (digitalRead(A1) == 1 && tryk){
    navnNr = random(0, 31);
    tryk = false;
  }else if (digitalRead(A1) == 0) {
    tryk = true;
  }
}
