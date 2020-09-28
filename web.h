#ifndef WEB_H
#define WEB_H

#include "blinder.hpp"
#include "hardware.hpp"
#include "html.h"

#include <ESP8266WebServer.h>

namespace web {

ESP8266WebServer server(80);

String button_title1[] = {"CCW", "CW"};
String button_title2[] = {"CCW", "CW"};
String arg_id[] = {"ccw", "cw"};

String get_blinder_html() {
    std::string html;
    html += std::string("<h2><span style=\"background-color: #FFFF00\">Current blinder state: ") +
            blinder::get_state_str(blinder::state) + "</span></h2>";

    if (blinder::state == blinder::State::IS_UP) {
        html += std::string("<div class=\"btn\">		<a class=\"angleButton\" ") +
                "style=\"background-color:#90ee90\"  href=\"/go_down\">Go down</a></div>";
    }
    if (blinder::state == blinder::State::IS_DOWN) {
        html += std::string("<div class=\"btn\">		<a class=\"angleButton\" ") +
                "style=\"background-color:#90ee90\"  href=\"/go_up\">Go up</a></div>";
    }

    html += std::string("<h2><span style=\"background-color: #FFFF00\">Emergency stop:") +
            "</span></h2>";
    html += std::string("<div class=\"btn\">		<a class=\"angleButton\" ") +
            "style=\"background-color:#f56464\"  href=\"/emergency_stop\">Stop</a></div>";
    return html.c_str();
}

void handleRoot() {
    String HTML = INDEX_HTML;

    HTML += get_blinder_html();

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

void handler_go_up() {
    blinder::go_up();
    handleRoot();
}
void handler_go_down() {
    blinder::go_down();
    handleRoot();
}

void handler_set_steps() {
    blinder::set_steps_to_side(std::atoi(server.arg(arg_id[0]).c_str()));
    handleRoot();
}

void handler_emergency_stop() {
    blinder::emergency_stop();
    handleRoot();
}

void setup_server() {
    server.on("/", handleRoot);
    server.on("/motor", HTTP_GET, handler_driver_control);
    server.on("/go_up", HTTP_GET, handler_go_up);
    server.on("/go_down", HTTP_GET, handler_go_down);
    server.on("/emergency_stop", HTTP_GET, handler_emergency_stop);
    server.on("/set_steps", HTTP_GET, handler_set_steps);
    server.onNotFound(handleNotFound);
    server.begin();
    Serial.println("HTTP server started");
}

void server_loop() {
    server.handleClient();
}

} // namespace web
#endif /* WEB_H */
