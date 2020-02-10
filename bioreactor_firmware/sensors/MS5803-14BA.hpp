//
// Created by lutkus on 2/8/20.
//

#ifndef HEART_VALVE_BIOREACTOR_MS5803_14BA_HPP
#define HEART_VALVE_BIOREACTOR_MS5803_14BA_HPP

#include "bioreactor_sensor.hpp"
#include "../external_lib/SparkFun_MS5803-14BA_Breakout_Arduino_Library-master/src/SparkFun_MS5803_I2C.h"


/*
 * This class is a wrapper for Sparkfun's external lib of the MS5803.
 * this is done to get their sensor code to fit in our defined architecture.
 */
class MS5803_14BA : public Sensor{
private:
    // Constructor will create an object of sparkfun's sensor class
    MS5803* sparkfun_MS5803;

public:
    // Overload Sensor constructor
    MS5803_14BA();

    // Overload Sensor constructor with initialization
    MS5803_14BA(std::string id, int num_inputs, std::vector<std::string> input_pins, int max_sampling_freq);

    // Define get values function
    int* get_values();

    // Sensor begin from Sensor parent class
    void sensor_begin();

    ~MS5803_14BA();
};

#endif //HEART_VALVE_BIOREACTOR_MS5803_14BA_HPP
