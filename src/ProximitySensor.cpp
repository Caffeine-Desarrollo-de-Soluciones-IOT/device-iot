#include "ProximitySensor.h"
#include <WiFi.h>
#include <HTTPClient.h>

// Configuración del WiFi
const char* ssid = "Gaby";
const char* password = "Gaby2608";

void ProximitySensorHandler::setupProximitySensor() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    // Conectar a WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando a WiFi...");
    }
    Serial.println("Conectado a WiFi");
}

void ProximitySensorHandler::readProximitySensor() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Leer distancia
    long duration = pulseIn(ECHO_PIN, HIGH);
    float distance = duration * 0.034 / 2;

    // Ajustar brillo del LED según la distancia
    int brightness = map(distance, 0, 100, 255, 0); // Mapea distancia a brillo (entre 0 y 255)
    brightness = constrain(brightness, 0, 255);    // Asegura valores válidos
    analogWrite(LED_PIN, brightness);              // Cambia la intensidad del LED

    // Enviar datos si está dentro de rango
    if (distance < 100) {
        HTTPClient http;
        http.begin("https://edge-caffeine.free.beeceptor.com/sensor/data");
        http.addHeader("Content-Type", "application/json");
        String payload = "{\"sensor\":\"proximity\",\"distance\":" + String(distance) + "}";
        int httpResponseCode = http.POST(payload);

        Serial.print("Proximity Data Response: ");
        Serial.println(httpResponseCode);
        http.end();
    }

    // Mostrar datos en el monitor serial
    Serial.print("Distancia: ");
    Serial.println(distance);
    Serial.print("Brillo LED: ");
    Serial.println(brightness);
    delay(1000); // Esperar un segundo antes de la siguiente lectura
}
