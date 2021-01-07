void Enroll(){
  int admin = getFingerprintAdmin();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("MOHON KONFIRMASI"));
  lcd.setCursor(4,1);
  lcd.print(F("ADMIN!!!"));
  delay(2000);
  if(admin== 1){
    int count=0;
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print(F("WELCOME"));
    lcd.setCursor(4,1);
    lcd.print(F("ADMIN ^_^"));
    delay(2000);
    lcd.clear();
    lcd.print(F("SILAHKAN DAFTAR!!! "));
    lcd.setCursor(4,1);
    lcd.print(F("ID :"));
    Serial.println(F("Silahkan daftarkan jari"));
    while(1){
      lcd.setCursor(9,1);
      lcd.print(count);
      Serial.print(count);
      if(digitalRead(up) == 0){
        count++;
        if(count>25)
        count=0;
        delay(1000);
      }else if(digitalRead(down) == 0){
        count--;
        if(count<0)
        count=25;
        delay(1000);
      }else if(digitalRead(del) == 0){
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print(F("Pendaftaran"));
        lcd.setCursor(2,1);
        lcd.print(F("DiBatalkan"));
        delay(1000);
        return;
      }else if(digitalRead(enroll) == 0){
        id=count;
        getFingerprintEnroll();  
        return;
      }
    }
  }else{
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print(F("SIDIK JARI"));
    lcd.setCursor(2,1);
    lcd.print(F("SALAH!!!"));
    delay(1000);
    Enroll();
  }
}
// for Admin
int getFingerprintAdmin(){
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)
    return -1;
    p = finger.image2Tz();
  if (p != FINGERPRINT_OK)
    return -1;
 
  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK){
    return -1;
    }
  // found a match!
    Serial.print("Ditemukan ID #");
    Serial.println(finger.fingerID);
    return finger.fingerID;
} 

uint8_t getFingerprintEnroll(){
  int p = -1;
  lcd.clear();
  lcd.print("ID Jari:");
  lcd.print(id);
  lcd.setCursor(1,1);
  lcd.print("Tempelkan Jari");
  delay(1000);
  while (p != FINGERPRINT_OK){
    p = finger.getImage();
    switch (p){
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      lcd.clear();
      lcd.print("Gambar Diambil");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No Finger");
      lcd.clear();
      lcd.print("Tidak Ada Jari");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      lcd.clear();
      lcd.print("Comm Error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      lcd.clear();
      lcd.print("Gambar Error");
      break;
    default:
      Serial.println("Unknown error");
      lcd.clear();
      lcd.print("Unknown Error");
      break;
    }
  }
 
  // OK success!
 
  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      lcd.clear();
      lcd.print("Gambar diconvertsi");
    break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      lcd.clear();
      lcd.print("Gambar Berantakan");
    return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      lcd.clear();
      lcd.print("Comm Error");
    return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      lcd.clear();
      lcd.print("Feature Not Found");
    return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      lcd.clear();
      lcd.print("Feature Not Found");
    return p;
    default:
      Serial.println("Unknown error");
      lcd.clear();
      lcd.print("Error");
      return p;
  }
  Serial.println("Remove finger");
  lcd.clear();
  lcd.print(" Lepas Jari ");
  delay(1000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
  p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
  lcd.clear();
  lcd.print(" Tempelkan Lagi ");
  lcd.setCursor(0,1);
  lcd.print(" Jari Yang Sama ");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
      break;
      case FINGERPRINT_NOFINGER:
        Serial.print(".");
      break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
      break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
      break;
      default:
        Serial.println("Unknown error");
        return p;
    }
  }
 
  // OK success!
 
  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
    break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
    return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
    return p;
case FINGERPRINT_FEATUREFAIL:
Serial.println("Could not find fingerprint features");
return p;
case FINGERPRINT_INVALIDIMAGE:
Serial.println("Could not find fingerprint features");
return p;
default:
Serial.println("Unknown error");
return p;
}
 
// OK converted!
Serial.print("Creating model for #"); 
Serial.println(id);
 
p = finger.createModel();
if (p == FINGERPRINT_OK) {
Serial.println("Prints matched!");
} else if (p == FINGERPRINT_PACKETRECIEVEERR) {
Serial.println("Communication error");
return p;
} else if (p == FINGERPRINT_ENROLLMISMATCH) {
Serial.println("Fingerprints did not match");
return p;
} else {
Serial.println("Unknown error");
return p;
}
 
Serial.print("ID "); Serial.println(id);
p = finger.storeModel(id);
if (p == FINGERPRINT_OK) {
Serial.println("Stored!");
lcd.clear();
lcd.print("ID Tersimpan!");
delay(2000);
} else if (p == FINGERPRINT_PACKETRECIEVEERR) {
Serial.println("Communication error");
return p;
} else if (p == FINGERPRINT_BADLOCATION) {
Serial.println("Could not store in that location");
return p;
} else if (p == FINGERPRINT_FLASHERR) {
Serial.println("Error writing to flash");
return p;
}
else {
Serial.println("Unknown error");
return p;
}
}

  
