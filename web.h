#ifndef WEB_H
#define WEB_H

#include "hardware.hpp"
#include "html.h"

#include <ESP8266WebServer.h>

namespace web {

ESP8266WebServer server(80);

String button_title1[] = {"CCW", "CW"};
String button_title2[] = {"CCW", "CW"};
String arg_id[] = {"ccw", "cw"};

void handleRoot() {
    String HTML = INDEX_HTML;

    if (hardware::dir_status == hardware::RotationDirection::CW) {
        HTML += "<h2><span style=\"background-color: #FFFF00\">Motor Running in CW</span></h2>";
    } else if (hardware::dir_status == hardware::RotationDirection::CCW) {
        HTML += "<h2><span style=\"background-color: #FFFF00\">Motor Running in CCW</span></h2>";
    } else {
        HTML += "<h2><span style=\"background-color: #FFFF00\">Motor OFF</span></h2>";
    }
    if (hardware::dir_status == hardware::RotationDirection::CCW) {
        HTML += "<div class=\"btn\"><a class=\"angleButton\" style=\"background-color:#f56464\"  "
                "href=\"/motor?";
        HTML += arg_id[0];
        HTML += "=off\">";
        HTML += button_title1[0]; // motor ON title
    } else {
        HTML += "	<div class=\"btn\"><a class=\"angleButton \" "
                "style=\"background-color:#90ee90\"  href=\"/motor?";
        HTML += arg_id[0];
        HTML += "=on\">";
        HTML += button_title2[0]; // motor OFF title
    }
    HTML += "</a>	</div>";
    if (hardware::dir_status == hardware::RotationDirection::CW) {
        HTML += "	<div class=\"btn\">		<a class=\"angleButton\" "
                "style=\"background-color:#f56464\"  href=\"/motor?";
        HTML += arg_id[1];
        HTML += "=off\">";
        HTML += button_title1[1]; // motor ON title
    } else {
        HTML += "	<div class=\"btn\"> <a class=\"angleButton \" "
                "style=\"background-color:#90ee90\"  href=\"/motor?";
        HTML += arg_id[1];
        HTML += "=on\">";
        HTML += button_title2[1]; // motor OFF title
    }
    HTML += "</a>	</div>";

    server.send(200, "text/html", HTML);
}

void handleNotFound() {
    String message = "File Not Found";
    message += "URI: ";
    message += server.uri();
    message += "Method: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "Arguments: ";
    message += server.args();
    message += "";

    for (uint8_t i = 0; i < server.args(); i++) {
        message += " " + server.argName(i) + ": " + server.arg(i) + "";
    }

    server.send(404, "text/plain", message);
}

void handler_driver_control() {
    hardware::motorControl(server.arg(arg_id[0]), server.arg(arg_id[1]));
    handleRoot();
}

void setup_server() {
    server.on("/", handleRoot);
    server.on("/motor", HTTP_GET, handler_driver_control);
    server.onNotFound(handleNotFound);
    server.begin();
    Serial.println("HTTP server started");
}

void server_loop() {
    server.handleClient();
}

} // namespace web
#endif /* WEB_H */
