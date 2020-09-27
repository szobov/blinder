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

int poleStep = 0;
int dirStatus = 3; // stores direction status 3= stop (do not change)

void setup_driver() {
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

void driveStepper(int c) {
    digitalWrite(stepper_driver_pins.pin_1, pole1[c]);
    digitalWrite(stepper_driver_pins.pin_2, pole2[c]);
    digitalWrite(stepper_driver_pins.pin_3, pole3[c]);
    digitalWrite(stepper_driver_pins.pin_4, pole4[c]);
}

void driver_loop() {
    if (dirStatus == 1) {
        poleStep++;
        driveStepper(poleStep);
    } else if (dirStatus == 2) {
        poleStep--;
        driveStepper(poleStep);
    } else {
        driveStepper(8);
    }
    if (poleStep > 7) {
        poleStep = 0;
    }
    if (poleStep < 0) {
        poleStep = 7;
    }
}

void motorControl(const String arg1, const String arg2) {
    if (arg1 == "on") {
        dirStatus = 1; // CCW
    } else if (arg1 == "off") {
        dirStatus = 3; // motor OFF
    } else if (arg2 == "on") {
        dirStatus = 2; // CW
    } else if (arg2 == "off") {
        dirStatus = 3; // motor OFF
    }
}

} // namespace hardware
#endif /* PRIVATE_DRIVER_H */
