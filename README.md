# Escalera Inteligente con ESP32
---

## 💡 Descripción del Proyecto

Este proyecto implementa un sistema de **iluminación inteligente y automatizada para escaleras**, diseñado para mejorar la seguridad y la comodidad. Utilizando un microcontrolador **ESP32** (compatible con ESP32-C3 mini) en conjunto con un **sensor ultrasónico HC-SR04**, el sistema detecta la presencia de personas que se acercan a la escalera. Al detectar movimiento, las luces se encienden por un tiempo predefinido y se apagan automáticamente después.

Para una mayor flexibilidad y facilidad de uso, el sistema incorpora una **interfaz web** que permite configurar parámetros de forma remota y monitorear el estado del dispositivo. Además, soporta **Actualizaciones Over-The-Air (OTA)**, lo que facilita la actualización del firmware de forma inalámbrica, sin necesidad de conectar físicamente el ESP32.

## ✨ Características Principales

* **Detección de Presencia:** Activa automáticamente las luces al detectar personas cerca de la escalera.
* **Ahorro Energético:** Las luces se apagan automáticamente después de un tiempo configurable, reduciendo el consumo.
* **Interfaz Web:** Permite una configuración sencilla y monitoreo del sistema desde cualquier navegador web.
* **Actualizaciones OTA:** Actualiza el firmware del ESP32 de forma inalámbrica vía WiFi.
* **Compatibilidad:** Diseñado para ESP32, incluyendo el mini-C3, facilitando su integración.

---

## 📦 Estructura de Archivos

* `EscaleraInteligente.ino`: El **código principal** del firmware del ESP32.
* `ota.h`: Contiene la lógica para la configuración y manejo de las **Actualizaciones OTA** vía WiFi.
* `page.h`, `style.h`, `script.h`: Archivos que definen la **interfaz web** (HTML, CSS y JavaScript).
* `Token.h`: **¡Importante!** Este archivo contiene tu **configuración WiFi y credenciales OTA**. **NO se incluye en el repositorio público por seguridad.**
* `.gitignore`: Define los archivos y directorios que Git debe ignorar, asegurando que `Token.h` no se suba accidentalmente.

---


## 🚀 Cómo Usar

Sigue estos pasos para poner en marcha tu sistema de escalera inteligente:

1.  **Clona el Repositorio:** Descarga el código a tu máquina local.
2.  **Abre en Arduino IDE:** Abre el archivo `EscaleraInteligente.ino` con el Arduino IDE.
3.  **Instala Librerías:** Asegúrate de tener instaladas las siguientes librerías  y gestor de placas en el IDE de arduino.

**Gestor de Placas** del Arduino IDE:
    
    esp32 de Espressif`

    
**Gestor de Librerías** del Arduino IDE:
   
    Arduinojson
    
4.  **modifica `Token.h`:** En la **misma carpeta** que `EscaleraInteligente.ino`, modifica el archivo llamado `Token.h`. Este archivo debe contener tus credenciales de red y OTA, siguiendo el formato del ejemplo a continuación.
5.  **Compila y Sube:** Selecciona tu placa ESP32 (por ejemplo, "ESP32C3 Dev Module") y el puerto COM correcto, luego compila y sube el código a tu ESP32.

---

## 🔐 Ejemplo de `Token.h`

**¡Atención!** Crea este archivo en tu entorno local. **Nunca lo subas a un repositorio público para proteger tus credenciales.**

```cpp


const char* ssid = "casajuan";        // Reemplaza con el SSID de tu red WiFi
const char* password = "12345"; // Reemplaza con la contraseña de tu red WiFi

// Configuración para Actualizaciones OTA
const char* ota_name = "esp32-c3-Escalera"; // Nombre para identificar el dispositivo en la red para OTA
const char* ota_password = "123456"; // Contraseña para acceder a las actualizaciones OTA






