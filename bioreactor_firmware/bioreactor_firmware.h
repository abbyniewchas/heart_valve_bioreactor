//
// Created by lutkus on 2/19/20.
//

/*
 * This header file collects all the necessary classes and functions for the bioreactor. This is done
 * instead of separating into multiple cpp and hpp files because there were dependency issues when trying to compile
 * code outside of the arduino IDE and in individual files
 *
 * Current classes in bioreactor_firmware:
 *      Controllers:
 *          PID
 *          LQR
 *      StateMachine
 *      DataLogger
 */

#ifndef HEART_VALVE_BIOREACTOR_BIOREACTOR_FIRMWARE_H
#define HEART_VALVE_BIOREACTOR_BIOREACTOR_FIRMWARE_H

//#include "Arduino.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

// Define state machine states
#define STARTUP 0
#define CALIBRATION 1
#define RUNNING 2
#define PAUSED 3
#define MEDIA_EXCHANGE 4
#define EXPERIMENT_TERMINATION 5

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
    // Parametrized constructor
    //Controller(std::string id, int num_control, int num_states);

    // Tune the controller
    virtual void tune_controller(float tuning_values[]) = 0;

    // Getters for protected members
    std::string get_id() const;
    int get_num_control() const;
    int get_num_states() const;
    ~Controller();
};

// PID, inherits from Controller
class PID : public Controller {
private:
    // P I D values for controller
    int P;
    int I;
    int D;

    // Running integral for PID
    float integral;

public:
    PID(std::string id);

    // Tune the controller
    void tune_controller(float tuning_values[3]);

    // PID control action
    float control_action(float state_estimation, float prev_estimation, float dt);

    // Reset the PID integral to prevent wind-up
    void reset_integral();
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

    // LQR control action
    float control_action(float *state_estimations);
};

/*
 * State Machine
 */
// for controllers need to handle (dt) being zero
class StateMachine {
private:
    int state;
    int** s;
public:
    // Initialize state machine
    StateMachine();

    // Print state
    std::string print_state();

    /*
     * States:
     *  System:
     *      Startup
     *      Compliance Calibration
     *      Running
     *      Paused
     *      Media Exchange
     *      Terminating Experiment
     *
     *  While Running:
     *      Forward_pressure
     *      Back_pressure
     *      Rest
     *
     */

    void state_transition(int new_state);

    // Destruct state machine
    ~StateMachine();

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
