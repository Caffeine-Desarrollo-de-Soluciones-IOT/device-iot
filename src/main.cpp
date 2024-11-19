#include <Arduino.h>
#include <SPI.h>
#include "ProximitySensor.h"
#include "MotionSensor.h"

// Pines del botón BOOT y control
#define BOOT_BUTTON 0 // GPIO 0 conectado al botón BOOT
#define PIR_PIN 34    // Pin del sensor PIR

// Instancias de sensores
MotionSensor motionSensor(PIR_PIN);

void setup() {
    Serial.begin(115200);
    pinMode(BOOT_BUTTON, INPUT_PULLUP);

    ProximitySensorHandler::setupProximitySensor();
    motionSensor.begin();
}

void loop() {
    static bool lastButtonState = HIGH;
    bool currentButtonState = digitalRead(BOOT_BUTTON);

    static bool useProximitySensor = true;

    if (currentButtonState == LOW && lastButtonState == HIGH) {
        useProximitySensor = !useProximitySensor;
        Serial.print("Usando sensor: ");
        Serial.println(useProximitySensor ? "Proximidad" : "Movimiento");
        delay(500); // Antirrebote
    }
    lastButtonState = currentButtonState;

    if (useProximitySensor) {
        ProximitySensorHandler::readProximitySensor();
    } else {
        motionSensor.update();
        motionSensor.checkMotionAndSend("https://edge-caffeine.free.beeceptor.com");
    }
}
