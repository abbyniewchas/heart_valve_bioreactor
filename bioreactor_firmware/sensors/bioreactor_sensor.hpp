//
// Created by lutkus on 2/7/20.
//

#ifndef HEART_VALVE_BIOREACTOR_BIOREACTOR_SENSOR_HPP
#define HEART_VALVE_BIOREACTOR_BIOREACTOR_SENSOR_HPP

#define DEFAULT_SAMPLING_FREQUENCY = 1000;

// Overarching parent sensor class for all sensors to be derived from
class Sensor {
private:
    // Sensor id
    std::string id;

    // Number of input values from sensor
    int num_inputs;

    // Input pins for sensor (eg. {'A0', 'A1', 'A2', ...})
    std::vector<std::string> input_pins;

    // Sensor max sampling frequency [Hz]
    int max_sampling_freq;

public:
    // Getters - each function returns one of the private members of a Sensor parent object
    std::string get_id();

    int get_num_inputs();

    std::vector<std::string> get_input_pins();

    int get_max_sampling_freq();

    // Setters - each function sets one of the private members of a Sensor parent object
    std::string set_id();

    int set_num_inputs();

    std::vector<std::string> set_input_pins();

    int set_max_sampling_freq();

    // Main Sensor functions
    // Get sensor's current value
    virtual int get_values() = 0;
};

#endif //HEART_VALVE_BIOREACTOR_BIOREACTOR_SENSOR_HPP
