//
// Created by lutkus on 2/8/20.
//

// Implementation of get_values()

#include "MS5803-14BA.hpp"
#include "bioreactor_sensor.hpp"

// Constructors (should be called at arduino setup)
// Constructor for MS5803_14BA
MS5803_14BA::MS5803_14BA() {
    this->sparkfun_MS5803 = new MS5803(ADDRESS_HIGH);
}

// Constructor with initialization
MS5803_14BA(std::string id, int num_inputs, std::vector<std::string> input_pins, int max_sampling_freq)
    : Sensor(id, num_inputs, input_pins, max_sampling_freq) {
    this->sparkfun_MS5803 = new MS5803(ADDRESS_HIGH);
}

int* MS5803_14BA::get_values() {

}

MS5803_14BA::~MS5803_14BA() {
    delete this->sparkfun_MS5803;
}