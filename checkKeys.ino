void checkKeys(){
  if(digitalRead(enroll) == 0){
    while(digitalRead(enroll) == 0);
    Enroll();
  }else if(digitalRead(del) == 0){
    lcd.clear();
    lcd.print(F("Mohon Tunggu"));
    delay(2000);
    deleted();
  }
}
