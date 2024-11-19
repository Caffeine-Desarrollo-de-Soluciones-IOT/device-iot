#ifndef PROXIMITY_SENSOR_H
#define PROXIMITY_SENSOR_H

#include <Arduino.h>

// Pines del sensor de proximidad
#define TRIG_PIN 23
#define ECHO_PIN 22
#define LED_PIN 21

namespace ProximitySensorHandler {
    void setupProximitySensor();  // Configuración inicial
    void readProximitySensor();  // Leer valores del sensor de proximidad
}

#endif // PROXIMITY_SENSOR_H
