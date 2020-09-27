#ifndef PRIVATE_NETWORK_H
#define PRIVATE_NETWORK_H

#include "secrets.h"

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>

namespace network {
const char* ssid = STASSID;
const char* password = STAPSK;

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

} // namespace network

#endif /* PRIVATE_NETWORK_H */
