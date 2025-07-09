//librerias para componetes
#include <WiFi.h>
#include <WebServer.h>

//llamado a pagina
#include "token.h"
#include "page.h"
#include "style.h"
#include "script.h"

//habilitar actualizacion ota
#include <ArduinoJson.h>
#include <ArduinoOTA.h>
#include "ota.h"

// ----- Configuración del servidor web -----
WebServer server(80);

// ----- Pines y parámetros -----
#define TRIG_ABAJO 20
#define ECHO_ABAJO 21
#define LED_ABAJO 8

#define TRIG_ARRIBA 10
#define ECHO_ARRIBA 9
#define LED_ARRIBA 0

int umbralArriba = 50;
int umbralAbajo  = 45;
#define TIEMPO_DELAY_ENTRE_LEDS 1300
#define TIEMPO_LED_ENCENDIDO 7000

unsigned long timerLEDAbajo = 0;
unsigned long timerLEDArriba = 0;
bool ledAbajoOn = false;
bool ledArribaOn = false;

bool sensorTriggered = false;
unsigned long chainStartTime = 0;
unsigned long secondLEDTime = 0;
int chainOrigin = 0;

long distanciaAbajo = 0;
long distanciaArriba = 0;

// NUEVAS VARIABLES para modo manual
bool modoManualAbajo = false;
bool modoManualArriba = false;

long medirDistancia(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin, LOW);
  long duracion = pulseIn(echoPin, HIGH, 30000);
  long distancia = duracion * 0.034 / 2;
  return distancia;
}

void turnOnLEDAbajo() {
  digitalWrite(LED_ABAJO, HIGH);
  ledAbajoOn = true;
  timerLEDAbajo = millis() + TIEMPO_LED_ENCENDIDO;
}

void turnOnLEDArriba() {
  digitalWrite(LED_ARRIBA, HIGH);
  ledArribaOn = true;
  timerLEDArriba = millis() + TIEMPO_LED_ENCENDIDO;
}

void turnOffLEDAbajo() {
  digitalWrite(LED_ABAJO, LOW);
  ledAbajoOn = false;
}

void turnOffLEDArriba() {
  digitalWrite(LED_ARRIBA, LOW);
  ledArribaOn = false;
}

void handleRoot() {
  server.send_P(200, "text/html", index_html);
}

void handleCSS() {
  server.send_P(200, "text/css", style_css);
}

void handleJavaScript() {
  server.send_P(200, "application/javascript", script_js);  // <<< corregido
}

void handleToggle() {
  if (!server.hasArg("led")) {
    server.send(400, "text/plain", "Falta parámetro 'led'");
    return;
  }
  String led = server.arg("led");
  String mensaje = "";

  if (led == "abajo") {
    if (ledAbajoOn) {
      turnOffLEDAbajo();
      modoManualAbajo = false;
      mensaje = "LED Abajo apagado manualmente.";
    } else {
      turnOnLEDAbajo();
      modoManualAbajo = true;
      mensaje = "LED Abajo encendido manualmente.";
    }
  } else if (led == "arriba") {
    if (ledArribaOn) {
      turnOffLEDArriba();
      modoManualArriba = false;
      mensaje = "LED Arriba apagado manualmente.";
    } else {
      turnOnLEDArriba();
      modoManualArriba = true;
      mensaje = "LED Arriba encendido manualmente.";
    }
  } else {
    server.send(400, "text/plain", "Parámetro inválido");
    return;
  }

  sensorTriggered = false;
  server.send(200, "text/plain", mensaje);
}

void handleSetThreshold() {
  if (!server.hasArg("sensor") || !server.hasArg("value")) {
    server.send(400, "text/plain", "Faltan parámetros");
    return;
  }
  String sensor = server.arg("sensor");
  int    val    = server.arg("value").toInt();

  if (sensor == "arriba") {
    umbralArriba = val;
    server.send(200, "text/plain", "Umbral ARRIBA = " + String(val));
  }
  else if (sensor == "abajo") {
    umbralAbajo = val;
    server.send(200, "text/plain", "Umbral ABAJO = " + String(val));
  }
  else {
    server.send(400, "text/plain", "Sensor inválido");
  }
}

void handleStatus() {
  String json = "{";
  json += "\"distAbajo\":" + String(distanciaAbajo) + ",";
  json += "\"distArriba\":" + String(distanciaArriba) + ",";
  json += "\"ledAbajo\":" + String(ledAbajoOn ? "true" : "false") + ",";
  json += "\"ledArriba\":" + String(ledArribaOn ? "true" : "false");
  json += "}";
  server.send(200, "application/json", json);
}

void setupWiFi() {
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Conectado.");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
 // Configura tus pines 
  pinMode(TRIG_ABAJO, OUTPUT);
  pinMode(ECHO_ABAJO, INPUT);
  pinMode(LED_ABAJO, OUTPUT);
  digitalWrite(LED_ABAJO, LOW);

  pinMode(TRIG_ARRIBA, OUTPUT);
  pinMode(ECHO_ARRIBA, INPUT);
  pinMode(LED_ARRIBA, OUTPUT);
  digitalWrite(LED_ARRIBA, LOW);

  // Conecta WiFi
  setupWiFi();

  // Configura OTA
setupOTA(ota_name, ota_password);
  


  server.on("/", handleRoot);
  server.on("/style.css", handleCSS);
  server.on("/toggle", handleToggle);
  server.on("/status", handleStatus);
  server.on("/script.js", handleJavaScript); 
  server.on("/setThreshold", HTTP_GET, handleSetThreshold); 
  server.begin();
  Serial.println("Servidor web iniciado.");
}

void loop() {
  ArduinoOTA.handle();  // Escucha por actualizaciones OTA
  server.handleClient();
  unsigned long now = millis();

  distanciaAbajo = medirDistancia(TRIG_ABAJO, ECHO_ABAJO);
  distanciaArriba = medirDistancia(TRIG_ARRIBA, ECHO_ARRIBA);

  // Verifica si sensores están habilitados antes de activar la lógica automática
  if (!sensorTriggered && !modoManualAbajo && !modoManualArriba) {
    if (distanciaAbajo > 0 && distanciaAbajo < umbralAbajo) {
      turnOnLEDAbajo();
      chainOrigin = 1;
      sensorTriggered = true;
      chainStartTime = now;
      secondLEDTime = now + TIEMPO_DELAY_ENTRE_LEDS;
    } else if (distanciaArriba > 0 && distanciaArriba < umbralArriba) {
      turnOnLEDArriba();
      chainOrigin = 2;
      sensorTriggered = true;
      chainStartTime = now;
      secondLEDTime = now + TIEMPO_DELAY_ENTRE_LEDS;
    }
  }

  if (sensorTriggered && now >= secondLEDTime) {
    if (chainOrigin == 1 && !ledArribaOn) {
      turnOnLEDArriba();
    } else if (chainOrigin == 2 && !ledAbajoOn) {
      turnOnLEDAbajo();
    }
    sensorTriggered = false;
  }

  // Apagado de LEDs (solo si no están en modo manual)
  if (ledAbajoOn && !modoManualAbajo && now >= timerLEDAbajo) {
    turnOffLEDAbajo();
  }
  if (ledArribaOn && !modoManualArriba && now >= timerLEDArriba) {
    turnOffLEDArriba();
  }

  delay(50);
}
