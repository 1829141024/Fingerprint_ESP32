void deleted(){
  int count=0;
  lcd.clear();
  lcd.print(F("Menghapus Sidik Jari"));
  lcd.setCursor(4,1);
  lcd.print(F("(Lokasi:"));
  while(1){
    lcd.setCursor(9,1);
    lcd.print(count);
    if(digitalRead(up) == 0){
      count++;
      if(count>25)
      count=00;
      delay(1000);
    }else if(digitalRead(down) == 0){
      count--;
      if(count<0)
      count=25;
      delay(1000);
    }else if(digitalRead(del) == 0){
      id=count;
      deleteFingerprint(id);
      return;
    }else if(digitalRead(enroll) == 0){
      return;
    }
  }
}

uint8_t deleteFingerprint(uint8_t id){
  uint8_t p = -1;
  lcd.clear();
  lcd.print(F("Silahkan Tunggu..."));
  p = finger.deleteModel(id);
  if (p == FINGERPRINT_OK){
    Serial.println(F("Menghapus..!"));
    lcd.clear();
    lcd.print(F("Sidik jari Dihapus"));
    lcd.setCursor(0,1);
    lcd.print(F("Berhasil"));
    delay(2000);
  }else{
    Serial.print(F("Terjadi Kesalahan"));
    lcd.clear();
    lcd.print(F("Kesalahan Berulang"));
    lcd.setCursor(0,1);
    lcd.print(F("Coba Lagi"));
    delay(2000);
    return p;
  }
}
