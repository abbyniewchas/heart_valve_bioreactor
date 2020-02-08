//
// Created by lutkus on 2/8/20.
//

#ifndef HEART_VALVE_BIOREACTOR_MS5803_14BA_HPP
#define HEART_VALVE_BIOREACTOR_MS5803_14BA_HPP

#include "bioreactor_sensor.hpp"
#include "../external_lib/SparkFun_MS5803-14BA_Breakout_Arduino_Library-master/src/SparkFun_MS5803_I2C.h"

class MS5803_14BA : public Sensor, public MS5803 {
private:


public:
    // Override constructor
    //MS5803_14BA();

    // Define get values function
    int[] get_values();
};

#endif //HEART_VALVE_BIOREACTOR_MS5803_14BA_HPP
