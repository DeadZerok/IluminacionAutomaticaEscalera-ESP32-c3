#ifndef OTA_H
#define OTA_H


// Puedes pasar el nombre del host si quieres personalizarlo
void setupOTA(const char* hostname = "esp32-c3",const char* password = nullptr) {
  
  ArduinoOTA.setHostname(hostname);
  if (password != nullptr) {
    ArduinoOTA.setPassword(password);
  }

  ArduinoOTA.onStart([]() {
    Serial.println("Inicio de actualización OTA");
  });

  ArduinoOTA.onEnd([]() {
    Serial.println("\nActualización completada");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progreso: %u%%\r", (progress / (total / 100)));
  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Fallo de autenticación");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Fallo al comenzar");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Fallo de conexión");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Fallo de recepción");
    else if (error == OTA_END_ERROR) Serial.println("Fallo al finalizar");
  });

  ArduinoOTA.begin();
  Serial.println("OTA listo.");
}

#endif