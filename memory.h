#ifndef MEMORY_H
#define MEMORY_H

#include <EEPROM.h>

struct __attribute__((packed)) TestStruct {
    char test_1;
    char test_2;
    char test_3;
    char test_4;
} test_struct;

void setup_eeprom() {
    EEPROM.begin(4096);
}

bool write_to_eeprom(const char data, const uint16_t addr) {
    EEPROM.write(addr, data);
    return EEPROM.commit();
}

char read_from_eeprom(const uint16_t addr) {
    return EEPROM.read(addr);
}

template <typename T>
bool put_data_to_eeprom(const int address, const T& t) {
    EEPROM.put(t);
    return EEPROM.commit();
}

template <typename T>
void get_data_from_eeprom(T& t) {
    EEPROM.get(0, t);
}

#endif /* MEMORY_H */
