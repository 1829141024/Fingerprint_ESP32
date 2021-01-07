void wifi_conn(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Menghubungkan Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("terhubung dengan IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setReadTimeout(firebasedata, 1000 * 60);
  Firebase.setwriteSizeLimit(firebasedata, "tiny");
  
  Serial.println("------------------------------------");
  Serial.println("Terhubung");
}
