#include "hardware.hpp"
#include "memory.h"
#include "web.h"

void setup(void) {
    Serial.begin(115200);

    hardware::setup_wifi();
    hardware::setup_driver();
    memory::setup_eeprom();
    web::setup_server();

    Serial.println("Setup is finished. Entering loop...");
}

void loop(void) {
    web::server_loop();
    hardware::driver_loop();
    delay(1);
}
