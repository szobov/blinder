#include "blinder.hpp"
#include "hardware.hpp"
#include "memory.h"
#include "network.h"
#include "web.h"

void setup(void) {
    Serial.begin(115200);

    hardware::setup_reed();
    network::setup_wifi();
    hardware::setup_driver();
    memory::setup_eeprom();
    web::setup_server();
    blinder::setup_blinder();
    Serial.println("Setup is finished. Entering loop...");
}

void loop(void) {
    hardware::reed_loop();
    web::server_loop();
    hardware::driver_loop();

    blinder::blinder_loop();

    delay(1);
}
