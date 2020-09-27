#ifndef DRIVER_H
#define DRIVER_H

#include "data.h"
#include "secrets.h"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = STASSID;
const char* password = STAPSK;

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

#endif /* DRIVER_H */
