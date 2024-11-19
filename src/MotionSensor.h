#ifndef MOTION_SENSOR_H
#define MOTION_SENSOR_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

class MotionSensor {
public:
    MotionSensor(uint8_t pirPin);
    void begin();
    void update();
    void checkMotionAndSend(const String &endpoint);

private:
    uint8_t pirPin;
    bool lastMotionDetected;
};

#endif
