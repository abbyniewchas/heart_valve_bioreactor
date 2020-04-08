//
// Created by lutkus on 2/7/20.
//
#include "bioreactor_firmware.h"
#include <iostream>

int main() {

    // Initialize PID controller and tune it
    PID pid("PID Example");
    float PID_values[3] = {1, 0.2, 0.2};
    pid.tune_controller(PID_values);

    // Setup data logger
    std::string filename = "my_file_test.csv";
    int num_outputs = 3;
    DataLogger datalogger(filename, num_outputs);

    // Create test data of "system state"
    float test_data[5] = {1, 2, 3, 4, 5};

    // Reset integral and error of PID
    pid.reset_integral();
    pid.reset_error();

    // Loop over data, performing control action and saving output
    for (int i = 0; i < 5; i++) {
        float pid_output = pid.control_action(test_data[i], 3, 0.1);
        std::cout << "Desired State: " << 5 << " Current State: " << test_data[i] << " PID Output: " << pid_output << std::endl;
        float data[3] = {5, test_data[i], pid_output};

        datalogger.save_data(data);
    }
    return 0;
}