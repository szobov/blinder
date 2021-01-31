#ifndef PRIVATE_DRIVER_H
#define PRIVATE_DRIVER_H

#include <AccelStepper.h>
#include <Arduino.h>

namespace hardware {

#define HALFSTEP 8

int STEPS_TO_SIDE = 150000;


struct StepperDriverPins {
    int pin_1 = D1; // IN1 is connected
    int pin_2 = D2; // IN2 is connected
    int pin_3 = D3; // IN3 is connected
    int pin_4 = D4; // IN4 is connected
} stepper_driver_pins;

AccelStepper stepper(HALFSTEP, stepper_driver_pins.pin_1, stepper_driver_pins.pin_3, stepper_driver_pins.pin_2, stepper_driver_pins.pin_4);


int REED_SWITCH_PIN = D6;
enum class ReedState { CLOSED, OPEN } reed_state;
int reed_hystersis_counter = 0;
const int REED_HYSTERESIS_STEPS = 1000;

int pole_step = 0;

enum class RotationDirection { CCW = 1, CW, OFF } dir_status;

void setup_driver() {
    dir_status = RotationDirection::OFF;
    stepper.setMaxSpeed(1000);
    stepper.setSpeed(1000);
}

void setup_reed() {
    pinMode(REED_SWITCH_PIN, INPUT_PULLUP);
    reed_hystersis_counter = 0;
}

bool is_reed_in_hysteresis() {
    if (reed_hystersis_counter > 0) {
        reed_hystersis_counter--;
        return true;
    };
    return false;
}

void reed_loop() {
    if (is_reed_in_hysteresis()) {
        return;
    }
    auto current_state = digitalRead(REED_SWITCH_PIN);
    if ((current_state == LOW) && (reed_state != ReedState::OPEN)) {
        reed_state = ReedState::OPEN;
        reed_hystersis_counter = REED_HYSTERESIS_STEPS;
        Serial.print("Reed is open now");
        Serial.println();
    };
    if ((current_state == HIGH) && (reed_state != ReedState::CLOSED)) {
        reed_state = ReedState::CLOSED;
        reed_hystersis_counter = REED_HYSTERESIS_STEPS;
        Serial.print("Reed is closed now");
        Serial.println();
    };
}

void drive_stepper(int c) {
}


void drive_stop() {
    stepper.stop();
    stepper.move(0);
    stepper.setSpeed(0);
}

void drive_go_down() {
    stepper.move(STEPS_TO_SIDE);
    stepper.setSpeed(1000);
}

void drive_go_up() {
    stepper.move(-(STEPS_TO_SIDE + 1000));
    stepper.setSpeed(1000);
}

void driver_loop() {
    stepper.runSpeedToPosition();
}

void motorControl(const String ccw_status, const String cw_status) {
    if (ccw_status == "on") {
        dir_status = RotationDirection::CCW;
    } else if (ccw_status == "off") {
        dir_status = RotationDirection::OFF; // motor OFF
    } else if (cw_status == "on") {
        dir_status = RotationDirection::CW; // CW
    } else if (cw_status == "off") {
        dir_status = RotationDirection::OFF; // motor OFF
    }
}

} // namespace hardware
#endif /* PRIVATE_DRIVER_H */
