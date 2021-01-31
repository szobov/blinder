#ifndef PRIVATE_BLINDER_H
#define PRIVATE_BLINDER_H

#include "hardware.hpp"

namespace blinder {

int current_step_counter = 0;

const auto ROTATION_DOWN = hardware::RotationDirection::CCW;
const auto ROTATION_UP = hardware::RotationDirection::CW;

enum class State { NOT_INITIALIZED, IS_DOWN, IS_UP, IN_PROGRESS_UP, IN_PROGRESS_DOWN } state;

std::string get_state_str(State state) {
    switch (state) {
    case State::NOT_INITIALIZED:
        return "NOT_INITIALIZED";
    case State::IS_DOWN:
        return "IS_DOWN";
    case State::IS_UP:
        return "IS_UP";
    case State::IN_PROGRESS_DOWN:
        return "IN_PROGRESS_DOWN";
    case State::IN_PROGRESS_UP:
        return "IN_PROGRESS_UP";
    }
}

void setup_blinder() {
    current_step_counter = 0;
    state = State::NOT_INITIALIZED;
}

void go_down() {
    Serial.println("Try to go down");
    if (state != State::IS_UP) {
        Serial.println("Can't go down if we're not in up position");
    };
    hardware::drive_go_down();
    state = State::IN_PROGRESS_DOWN;
};

void go_up() {
    Serial.println("Try to go up");
    if (state != State::IS_DOWN) {
        Serial.println("Can't go up if we're not in down position");
    }
    hardware::drive_go_up();
    state = State::IN_PROGRESS_UP;
}

void emergency_stop() {
    Serial.println("Cover steps before finish: ");
    Serial.print(hardware::STEPS_TO_SIDE - std::abs(hardware::stepper.distanceToGo()));
    Serial.println("");
    hardware::drive_stop();
    state = State::IS_DOWN;
}

void blinder_loop() {
    if (state == State::NOT_INITIALIZED) {
        if (hardware::reed_state == hardware::ReedState::OPEN) {
            state = State::IS_UP;
        } else {
            state = State::IS_DOWN;
            go_up();
        }
    }

    if (state == State::IN_PROGRESS_DOWN) {
        if (hardware::stepper.distanceToGo() == 0) {
            state = State::IS_DOWN;
            Serial.println("Reach down position");
        }
    };

    if (state == State::IN_PROGRESS_UP) {
        if (hardware::reed_state == hardware::ReedState::CLOSED) {
        } else {
            state = State::IS_UP;
            hardware::drive_stop();
            Serial.println("Reach up position");
        }
    };
}

void set_steps_to_side(int steps) {
    Serial.println("Set steps to side: ");
    Serial.print(steps);
    Serial.println(" number of steps");
    hardware::STEPS_TO_SIDE = steps;
}

} // namespace blinder

#endif /* PRIVATE_BLINDER_H */
