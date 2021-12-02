void TilstandSkift() {
  accelmeter.getAcceleration(&xAxis, &yAxis, &zAxis); // Tager memory address som input
  //tjekker om axisen blivet tiltet og hvis den gør tager eller ligger til screenNumber
  if (zAxis <= 0.2 && tilt) {
    if (xAxis > 0.2) {
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
    //sætter farven ud fra hvad skærm det er.
    lcd.setRGB(farver[screenNumber][0], farver[screenNumber][1], farver[screenNumber][2]);
    tilt = false;
    //Giver Lyd feedback når man skifter
    digitalWrite(2,1);
    delay(100);
    digitalWrite(2,0);
  } else if (zAxis >= 0.8) {
    tilt = true;
  }
}


void DitUr() {
  //Tager tid fra Ur komponenten 
  clock.getTime();
  //Printer Tid på Lcd Skærm
  lcd.print(clock.hour, DEC);
  lcd.print(":");
  lcd.print(clock.minute, DEC);
  lcd.print(":");
  //tjekker om tid har nummer over 10 hvis ikke læg en 0 string foran
  if (clock.second < 10) {
    lcd.print("0" + String(clock.second, DEC));
    lcd.print("  ");
  } else {
    lcd.print(clock.second, DEC);
    lcd.print("  ");
  }
//printer dato 
  lcd.setCursor(0,1);
  lcd.print(clock.month, DEC);
  lcd.print("/");
  lcd.print(clock.dayOfMonth, DEC);
  lcd.print("/");
  lcd.print(clock.year + 2000, DEC);
  lcd.print(" ");
  
  if (clock.second == 0) {
    for (i = 0; i < 6; i ++) {
      if (clock.hour == tid[i][0] && clock.minute == tid[i][2]) {
        digitalWrite(2, 1);
        delay(1000);
        digitalWrite(2, 0);
//        break;
      }else if (clock.hour == tid[i][1] && clock.minute == tid[i][2]) {
        digitalWrite(2, 1);
        delay(400);
        digitalWrite(2, 0);
        delay(200);
        digitalWrite(2, 1);
        delay(400);
        digitalWrite(2, 0);
//        break;
      }
    }
  }
}

//laver array med alle mennesker i klassen
char RandomElev[31][9] = { "Anders", "Emil", "Fahmi", "Freja", "Gustav W", "Gustav E", "Haris", "Ismail", "Jabriil", "Jacob", "Ludvig", "Jeppe", "Jonatan", "Kasper", "Lovro", "Mathias", "Mie", "Mohammad", "Nelisa", "Nicolai", "Pernille", "Rasmus", "Robert", "Sarah", "Silas", "Simon", "Thoeger", "Tobias", "Taaha", "William", "Tryk"};
void getName(void) {
  lcd.print(RandomElev[navnNr]);
  if (digitalRead(A1) && tryk){
    clock.getTime();
    for (i = 0; i < clock.second; i ++) {
      navnNr = random(0, 30);
    }
    tryk = false;
  }else if (!digitalRead(A1)) {
    tryk = true;
  }
}

void StopUr() {
 //Tjekker hvis knappen blivertrykker og den ikke er blevet trykket før 
  if (digitalRead(A1) && trykFoer == false) {
    //tjekker om uret er stopper
    if (urStop == false) {
      urStop = true;
    } else {
      urStop = false;
      //Definere tid 
      tidFoer = millis();
      lcd.clear();
    } 
  }
  //Ser om den er holdt nede 
  trykFoer = digitalRead(A1);
  //hvis uret stopper så så vis tiden
  if (urStop == false) {
    count = millis() - tidFoer;
  }
  
  //print count
  lcd.setCursor(0, 0);
  lcd.print(count / 1000);
}


void Christmas() {
  lcd.setCursor(0, 0);
 //tjekker hvad måned det er og printer det
  lcd.print(12 - clock.month);
  lcd.print(" maaned(er) og");
  lcd.setCursor(0, 1);
  lcd.print(24 - clock.dayOfMonth);
  lcd.print(" dage til jul");
}

void morse() {
  lcd.print(check[map(analogRead(A2), 0, 1023, 0, 25)]);
  if (digitalRead(A1) && tryk){
    int tal = res[map(analogRead(A2), 0, 1023, 0, 25)];
    uint8_t i = 0;
    while (tal > 0) {
      digitalWrite(2, 1);
      delay(100 * floor(tal / pow(10, 4 - i)));
      tal -= floor(tal / pow(10, 4 - i)) * pow(10, 4 - i);
      digitalWrite(2, 0);
      delay(100);
      
      i ++;
    }
    tryk = false;
  }else if (!digitalRead(A1)) {
    tryk = true;
  }
}
