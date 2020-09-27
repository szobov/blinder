#include "data.h"
#include "hardware.hpp"
#include "memory.h"
#include "web.h"

void setup(void) {
    Serial.begin(115200);

    setup_wifi();
    setup_driver();
    setup_eeprom();
    setup_server();
}

void loop(void) {
    server_loop();
    driver_loop();
    delay(1);
}
