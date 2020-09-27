#include "data.h"
#include "memory.h"
#include "secrets.h"
#include "web.h"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = STASSID;
const char* password = STAPSK;

void setup(void) {
    pinMode(stepper_driver_pins.pin_1, OUTPUT); // define pin for ULN2003 in1
    pinMode(stepper_driver_pins.pin_2, OUTPUT); // define pin for ULN2003 in2
    pinMode(stepper_driver_pins.pin_3, OUTPUT); // define pin for ULN2003 in3
    pinMode(stepper_driver_pins.pin_4, OUTPUT); // define pin for ULN2003 in4

    setup_eeprom();
    Serial.begin(115200); // initialize the serial monitor

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

    server.on("/", handleRoot);
    server.on("/motor", HTTP_GET, motorControl);
    server.onNotFound(handleNotFound);
    server.begin();
    Serial.println("HTTP server started");
}

void loop(void) {
    server.handleClient();
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

    delay(1);
}

void motorControl() {
    if (server.arg(argId[0]) == "on") {
        dirStatus = 1; // CCW
    } else if (server.arg(argId[0]) == "off") {
        dirStatus = 3; // motor OFF
    } else if (server.arg(argId[1]) == "on") {
        dirStatus = 2; // CW
    } else if (server.arg(argId[1]) == "off") {
        dirStatus = 3; // motor OFF
    }
    handleRoot();
} // motorControl end

void driveStepper(int c) {
    digitalWrite(stepper_driver_pins.pin_1, pole1[c]);
    digitalWrite(stepper_driver_pins.pin_2, pole2[c]);
    digitalWrite(stepper_driver_pins.pin_3, pole3[c]);
    digitalWrite(stepper_driver_pins.pin_4, pole4[c]);
} // driveStepper end here
