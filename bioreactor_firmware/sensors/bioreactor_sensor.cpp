//
// Created by lutkus on 2/7/20.
//

#include "bioreactor_sensor.hpp"
#include <iostream>

/*
 * Constructors
 */

// Default constructor
Sensor::Sensor() {
    this->id = "UNDEFINED SENSOR";
    this->num_inputs = 0;
    this->input_pins[0];
    this->max_sampling_freq = DEFAULT_SAMPLING_FREQUENCY;
}

// Constructor with initialization
Sensor::Sensor(std::string id, int num_inputs, std::string input_pins, int max_sampling_freq = DEFAULT_SAMPLING_FREQUENCY){
    this->id = id;
    this->num_inputs = num_inputs;
    this->input_pins[num_inputs] = input_pins;
    this->max_sampling_freq = max_sampling_freq;
}

// Copy Constructor
Sensor::Sensor(const Sensor& other) {
    this->id = other.id;
    this->num_inputs = other.num_inputs;
    for (int i = 0; i < num_inputs; i++) {
        this->input_pins[i] = other.input_pins[i];
    }
    this->max_sampling_freq = other.max_sampling_freq;
}

/*
 * Getters
 */
/*
// Get id of sensor
std::string Sensor::get_id() const {
    return this->id;
}

// Get number of sensor inputs
int Sensor::get_num_inputs() const {
    return this->num_inputs;
}

// Get input pins
std::vector<std::string> Sensor::get_input_pins() const {
    return this->input_pins;
}

// Get max sampling frequency
int Sensor::get_max_sampling_freq() const {
    return this->max_sampling_freq;
}
*/
/*
 * Setters
 */
/*
// Set id of sensor
void Sensor::set_id(std::string id) {
    this->id = id;
}

// Set number of input pins
void Sensor::set_num_inputs(int num_inputs) {
    this->num_inputs = num_inputs;
}

// Set input pins locations
void Sensor::set_input_pins(std::vector <string> input_pins) {
    this->input_pins = input_pins;
}

// Set max sampling frequency
void Sensor::set_max_sampling_freq(int max_sampling_freq) {
    this->max_sampling_freq = max_sampling_freq;
}
 */

void Sensor::sensor_param() const {
    std::cout << "Sensor id: " << this->id << "\n";
    std::cout << "  Number inputs: " << this->num_inputs << "\n";
    std::cout << "  Input pins: ";
    for (int i = 0; i < (this->num_inputs - 1); i++) {
        std::cout << this->input_pins[i] << ", ";
    }
    std::cout << input_pins[this->num_inputs-1] << "\n";
    std::cout << "  Max sampling frequency: " << this->max_sampling_freq << std::endl;
}

/*
 * Destructor
 */

Sensor::~Sensor(){
}