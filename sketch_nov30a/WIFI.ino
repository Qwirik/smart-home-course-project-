void WIFIinit() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(_ssid, _password);

  const int maxTries = 30;  // Максимальное количество попыток подключения
  for (int tries = 0; tries < maxTries; ++tries) {
    if (WiFi.status() == WL_CONNECTED) {
      break;
    }
    Serial.print(".");
    delay(1000);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFailed to connect to WiFi. Starting AP mode...");
    // StartapMode();  // Если нужна точка доступа, создайте эту функцию
  }
}