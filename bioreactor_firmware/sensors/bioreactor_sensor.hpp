//
// Created by lutkus on 2/7/20.
//

#ifndef HEART_VALVE_BIOREACTOR_BIOREACTOR_SENSOR_HPP
#define HEART_VALVE_BIOREACTOR_BIOREACTOR_SENSOR_HPP

#include <string>
#include <vector>

#define DEFAULT_SAMPLING_FREQUENCY 1000

// Overarching parent sensor class for all sensors to be derived from
class Sensor {
protected:
    // Sensor id
    std::string id;

    // Number of input values from sensor
    int num_inputs;

    // Input pins for sensor (eg. {'A0', 'A1', 'A2', ...})
    std::string input_pins[];

    // Sensor max sampling frequency [Hz]
    int max_sampling_freq;

public:
    // Constructors
    Sensor();

    Sensor(std::string id, int num_inputs, std::string input_pins, int max_sampling_freq);

    // Copy Constructor
    Sensor(const Sensor& other);
/*
    // Getters - each function returns one of the private members of a Sensor parent object
    std::string get_id() const;

    int get_num_inputs() const;

    std::string get_input_pins() const;

    int get_max_sampling_freq() const;

    // Setters - each function sets one of the private members of a Sensor parent object
    void set_id(std::string id);

    void set_num_inputs(int num_inputs);

    void set_input_pins(std::string input_pins);

    void set_max_sampling_freq(int max_sampling_freq);
*/
    // Main Sensor functions
    // Get sensor's current value
    virtual int* get_values() = 0;

    // Start sensor with any initializations needed
    virtual void sensor_begin() = 0;

    // Print sensor parameters
    void sensor_param() const;

    // Destructor
    ~Sensor();
};

#endif //HEART_VALVE_BIOREACTOR_BIOREACTOR_SENSOR_HPP
