void Open_door(){
  int a;
  int result = getFingerprintIDez();
  if(result>=0 ){
    json.set("/pintu",1);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(500);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print(F("PINTU TERBUKA"));
    lcd.setCursor(4,1);
    lcd.print(F("WELCOME"));
    digitalWrite(Relay, HIGH);
    digitalWrite(closeLight, LOW);
    delay(2000);
    digitalWrite(Relay, LOW);
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print(F("PINTU"));
    lcd.setCursor(1,1);
    lcd.print(F("TERKUNCI !!"));
    delay(1000);
    return;
  }
  //else if(Firebase.updateNode(firebasedata,"/pintu",json)){
    //if(firebasedata.intData() >=0){
    //lcd.clear();
    //lcd.setCursor(1,0);
    //lcd.print(F("PINTU TERBUKA"));
    //lcd.setCursor(4,1);
    //lcd.print(F("WELCOME"));
    //digitalWrite(Relay, HIGH);
    //digitalWrite(closeLight, LOW);
    //delay(2000);
    //digitalWrite(Relay, LOW);
    //lcd.clear();
    //lcd.setCursor(3,0);
    //lcd.print(F("PINTU"));
    //lcd.setCursor(1,1);
    //lcd.print(F("TERKUNCI !!"));
    //delay(1000);
    //return;
    //}else{
      //Firebase.setInt(firebasedata, "/pintu",0);
      //digitalWrite(closeLight, HIGH);
    //}
  else{
    //Firebase.setInt("/pintu",0);
    digitalWrite(closeLight, HIGH);
  }
}

int getFingerprintIDez(){
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)
    return -1;
    p = finger.image2Tz();
  if (p != FINGERPRINT_OK)
    return -1;
 
  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK){
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    lcd.clear();
    lcd.print(F("Tidak Terdaftar!!!"));
    lcd.setCursor(0,1);
    lcd.print(F("Coba Lagi"));
    delay(1000);
    return -1;
    }
  // found a match!
    Serial.print(F("Ditemukan ID #"));
    Serial.println(finger.fingerID);
    return finger.fingerID;
}
