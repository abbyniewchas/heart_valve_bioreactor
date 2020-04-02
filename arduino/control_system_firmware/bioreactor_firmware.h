//
// Created by lutkus on 2/19/20.
//

#ifndef HEART_VALVE_BIOREACTOR_BIOREACTOR_FIRMWARE_H
#define HEART_VALVE_BIOREACTOR_BIOREACTOR_FIRMWARE_H

//#include "Arduino.h"
#include <string>
#include <fstream>

/*
 * Controllers
 */
// Parent controller class for all controllers
class Controller {
protected:
    // String id for the controller
    std::string id;

    // Number of control inputs
    int num_control;

    // Number of states
    int num_states;
public:
    // Tune the controller
    virtual void tune_controller(float tuning_values[]) = 0;

    // Perform control action
    virtual float control_action(float current_state, float desired_state, float dt) = 0;

    // Getters for protected members
    std::string get_id() const;
    int get_num_control() const;
    int get_num_states() const;
    ~Controller();
};

// PID, inherits from Controller
class PID : public Controller {
private:
    // P I D gains for controller
    int P;
    int I;
    int D;

    // Running integral for PID
    float integral;

    //Previous value of error
    float prev_error;

    // Bool to prevent PID D and I terms blowing up on first control_action() call
    bool first_pass;

public:
    PID(std::string id);

    // Tune the controller
    void tune_controller(float tuning_values[3]);

    // PID control action
    float control_action(float current_state, float desired_state, float dt);

    // Reset the PID integral to prevent wind-up
    void reset_integral();

    // Reset previous error
    void reset_error();
};

// LQR, inherits from Controller
class LQR : public Controller {
private:
    // K matrix for LQR controller
    float *K;

public:
    LQR(std::string id);

    // Tune the controller
    void tune_controller(float tuning_values[]);

    // LQR control action (assumed to have 1 output control action)
    float control_action(float current_state, float desired_state, float dt);

    // Destructor
    ~LQR();
};

/*
 * Data Logger
 */
class DataLogger {
private:
    // File that will be written to
    std::ofstream file;

    // Number of sensors
    int num_sensors;
public:
    // DataLogger constructor
    DataLogger();

    // Parametrized constructor
    DataLogger(std::string filename, int num_sensors);

    // Open file to write data to
    void open_file(std::string filename);

    // Save data to the opened file
    void save_data(float *data);

    // Destruct DataLogger and close file
    ~DataLogger();
};

#endif //HEART_VALVE_BIOREACTOR_BIOREACTOR_FIRMWARE_H
