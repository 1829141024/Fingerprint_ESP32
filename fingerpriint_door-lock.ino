// Library Fingerprint
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#include <Adafruit_Fingerprint.h>
#define fingerPrint Serial2
//SoftwareSerial dataESP(0,1);
LiquidCrystal_I2C lcd(0x27, 16, 2);
uint8_t id;
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerPrint);


//Library Firebase
#include <WiFi.h>
#include <FirebaseESP32.h>
#define FIREBASE_HOST "https://lab-tekom-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "SanC2XF0CgRaHsK8kDmEQmzmXYpvuHdbOfoBkcoM"
#define WIFI_SSID "INDIHOME2020"
#define WIFI_PASSWORD "inipasswordnya"
FirebaseData firebasedata;
FirebaseJson json;


#define enroll 27
#define del 26
#define up 14
#define down 12
#define Relay 4
#define closeLight 2
#define buzzer 19
 
void setup(){
  Serial.begin(115200);
  wifi_conn();
  pin_mode();
  //dataESP.begin(115200);
  start_system();
  
}
 
void loop(){
  digitalWrite(closeLight, HIGH);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("LAB ELEKTRONIKA"));
  lcd.setCursor(5,1);
  lcd.print(F("TEKOM"));
  delay(50);
  
  Open_door();
  checkKeys();
  delay(100);
}

 
