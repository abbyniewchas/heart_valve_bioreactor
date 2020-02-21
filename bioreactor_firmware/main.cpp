//
// Created by lutkus on 2/7/20.
//

#include "bioreactor_firmware.h"
#include <iostream>

int main() {

    PID pid("pid1");
    float PID_values[5] = {5.3, 5.21, 5.15, 1};
    float PID_values2[3] = {5, 4, 3};
    pid.tune_controller(PID_values);

    std::cout << pid.control_action(41.2, 41.0, 0.02) << std::endl;

    return 0;
}