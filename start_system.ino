void start_system(){
  lcd.init();
  lcd.backlight();
  lcd.print(F("memulai sistem"));
  delay(2000);
  lcd.clear();
  finger.begin(57600);
  lcd.clear();
  lcd.print(F("Mencari Module"));
  lcd.setCursor(0,1);
  delay(2000);
  finger.getParameters();
  finger.getTemplateCount();
  if (finger.verifyPassword()){
    Serial.println(F("Found fingerprint sensor!"));
    lcd.clear();
    lcd.print(F("Module ditemukan"));
    delay(2000);
  }else{
    Serial.println(F("Did not find fingerprint sensor :("));
    lcd.clear();
    lcd.print(F("Modul Tidak ditemukan"));
    lcd.setCursor(0,1);
    lcd.print(F("Cek koneksi"));
    while (1);
  }
}
