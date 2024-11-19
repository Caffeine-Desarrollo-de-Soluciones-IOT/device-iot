#include "MotionSensor.h"

MotionSensor::MotionSensor(uint8_t pirPin) : pirPin(pirPin), lastMotionDetected(false) {}

void MotionSensor::begin() {
    pinMode(pirPin, INPUT);
}

void MotionSensor::update() {
    bool motionDetected = digitalRead(pirPin);
    if (motionDetected != lastMotionDetected) {
        lastMotionDetected = motionDetected;
        Serial.println(motionDetected ? "Motion detected!" : "No motion.");
    }
}

void MotionSensor::checkMotionAndSend(const String &endpoint) {
    bool motionDetected = digitalRead(pirPin);
    if (motionDetected && !lastMotionDetected) {
        HTTPClient http;
        http.begin(endpoint + "/motion");
        http.addHeader("Content-Type", "application/json");
        String payload = "{\"motion\": true}";
        int httpResponseCode = http.POST(payload);
        Serial.print("Motion Sensor HTTP Response code: ");
        Serial.println(httpResponseCode);
        http.end();
    }
    lastMotionDetected = motionDetected;
}
