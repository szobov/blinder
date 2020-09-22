#ifndef WEB_H
#define WEB_H

#include "data.h"

#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

void handleRoot() {
    // Robojax.com ESP32 Relay Motor Control
    String HTML = "<!DOCTYPE html>"
                  "<html>"
                  "<head>"

                  "<title>Robojax 28BYJ-48 Motor Control</title>"

                  "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"

                  "<style>"

                  "html,body{"
                  "width:100%;"
                  "height:100%;"
                  "margin:0}"
                  "*{box-sizing:border-box}"
                  ".colorAll{"
                  "background-color:#90ee90}"
                  ".colorBtn{"
                  "background-color:#add8e6}"
                  ".angleButtdon,a{"
                  " font-size:30px;"
                  "border:1px solid #ccc;"
                  "display:table-caption;"
                  "padding:7px 10px;"
                  "text-decoration:none;"
                  "cursor:pointer;"
                  "padding:5px 6px 7px 10px}a{"
                  "display:block}"
                  ".btn{"
                  "margin:5px;"
                  "border:none;"
                  "display:inline-block;"
                  "vertical-align:middle;"
                  "text-align:center;"
                  "white-space:nowrap}";

    HTML += "</style>"
            "</head>"
            "<body>"
            "<h1>Robojax 28BYJ-48 Stepper Motor Control </h1>"
            ";";

    if (dirStatus == 2) {
        HTML += "<h2><span style=\"background-color: #FFFF00\">Motor Running in CW</span></h2>";
    } else if (dirStatus == 1) {
        HTML += "<h2><span style=\"background-color: #FFFF00\">Motor Running in CCW</span></h2>";
    } else {
        HTML += "<h2><span style=\"background-color: #FFFF00\">Motor OFF</span></h2>";
    }
    if (dirStatus == 1) {
        HTML += "<div class=\"btn\"><a class=\"angleButton\" style=\"background-color:#f56464\"  "
                "href=\"/motor?";
        HTML += argId[0];
        HTML += "=off\">";
        HTML += buttonTitle1[0]; // motor ON title
    } else {
        HTML += "	<div class=\"btn\"><a class=\"angleButton \" "
                "style=\"background-color:#90ee90\"  href=\"/motor?";
        HTML += argId[0];
        HTML += "=on\">";
        HTML += buttonTitle2[0]; // motor OFF title
    }
    HTML += "</a>	</div>";
    if (dirStatus == 2) {
        HTML += "	<div class=\"btn\">		<a class=\"angleButton\" "
                "style=\"background-color:#f56464\"  href=\"/motor?";
        HTML += argId[1];
        HTML += "=off\">";
        HTML += buttonTitle1[1]; // motor ON title
    } else {
        HTML += "	<div class=\"btn\"> <a class=\"angleButton \" "
                "style=\"background-color:#90ee90\"  href=\"/motor?";
        HTML += argId[1];
        HTML += "=on\">";
        HTML += buttonTitle2[1]; // motor OFF title
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

#endif /* WEB_H */
