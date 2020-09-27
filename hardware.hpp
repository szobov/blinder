#ifndef PRIVATE_DRIVER_H
#define PRIVATE_DRIVER_H

#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include "secrets.h"

namespace hardware {

const char* ssid = STASSID;
const char* password = STAPSK;

struct StepperDriverPins {
    int pin_1 = D1; // IN1 is connected
    int pin_2 = D2; // IN2 is connected
    int pin_3 = D3; // IN3 is connected
    int pin_4 = D4; // IN4 is connected
} stepper_driver_pins;

int pole1[] = {0, 0, 0, 0, 0, 1, 1, 1, 0}; // pole1, 8 step values
int pole2[] = {0, 0, 0, 1, 1, 1, 0, 0, 0}; // pole2, 8 step values
int pole3[] = {0, 1, 1, 1, 0, 0, 0, 0, 0}; // pole3, 8 step values
int pole4[] = {1, 1, 0, 0, 0, 0, 0, 1, 0}; // pole4, 8 step values

int pole_step = 0;

enum class RotationDirection { CCW = 1, CW, OFF } dir_status;

void setup_driver() {
    dir_status = RotationDirection::OFF;

    pinMode(stepper_driver_pins.pin_1, OUTPUT); // define pin for ULN2003 in1
    pinMode(stepper_driver_pins.pin_2, OUTPUT); // define pin for ULN2003 in2
    pinMode(stepper_driver_pins.pin_3, OUTPUT); // define pin for ULN2003 in3
    pinMode(stepper_driver_pins.pin_4, OUTPUT); // define pin for ULN2003 in4
}

void setup_wifi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: http://");
    Serial.println(WiFi.localIP());
}

void drive_stepper(int c) {
    digitalWrite(stepper_driver_pins.pin_1, pole1[c]);
    digitalWrite(stepper_driver_pins.pin_2, pole2[c]);
    digitalWrite(stepper_driver_pins.pin_3, pole3[c]);
    digitalWrite(stepper_driver_pins.pin_4, pole4[c]);
}

void driver_loop() {
    if (dir_status == RotationDirection::CCW) {
        pole_step++;
        drive_stepper(pole_step);
    } else if (dir_status == RotationDirection::CW) {
        pole_step--;
        drive_stepper(pole_step);
    } else {
        drive_stepper(8);
    }
    if (pole_step > 7) {
        pole_step = 0;
    }
    if (pole_step < 0) {
        pole_step = 7;
    }
}

void motorControl(const String ccw_status, const String cw_status) {
    if (ccw_status == "on") {
        dir_status = RotationDirection::CCW;
    } else if (ccw_status == "off") {
        dir_status = RotationDirection::OFF; // motor OFF
    } else if (cw_status == "on") {
        dir_status = RotationDirection::CW; // CW
    } else if (cw_status == "off") {
        dir_status = RotationDirection::OFF; // motor OFF
    }
}

} // namespace hardware
#endif /* PRIVATE_DRIVER_H */
