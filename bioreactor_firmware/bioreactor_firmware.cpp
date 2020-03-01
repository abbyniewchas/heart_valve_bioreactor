//
// Created by lutkus on 2/19/20
//

#include "bioreactor_firmware.h"

/*
 * Controllers
 */

//Controller::Controller(std::string id, int num_control, int num_states) {
//    this->id = id;
//    this->num_control = num_control;
//    this->num_states = num_states;
//}

std::string Controller::get_id() const {
    return this->id;
}

int Controller::get_num_control() const {
    return this->num_control;
}

int Controller::get_num_states() const {
    return this->num_states;
}

Controller::~Controller() {};

/*
 * Controller : PID
 */
PID::PID(std::string id) {
    // Initialize controller parameters
    this->id = id;
    this->num_control = 1;
    this->num_states = 1;

    // Initialize PID parameters
    this->P = 0;
    this->I = 0;
    this->D = 0;
    this->integral = 0;
}

void PID::tune_controller(float tuning_values[3]) {
    // Store the tuning values in the PID object
    this->P = tuning_values[0];
    this->I = tuning_values[1];
    this->D = tuning_values[2];
}

float PID::control_action(float state_estimation, float prev_estimation, float dt) {
    // Multiply state estimation by weighted P, I, and D terms
    float P_term = this->P * state_estimation;
    float I_term = this->I * this->integral;
    float D_term = this->D * (state_estimation - prev_estimation) / dt;

    // Update integral using trapezoidal integration method
    this->integral += dt * (state_estimation + prev_estimation) / 2;

    // Return the sum of all PID components
    return P_term + I_term + D_term;
}

void PID::reset_integral() {
    // Reset integral term
    this->integral = 0;
}

/*
 * Controller : LQR
 */

/*
 * State Machine
 */


/*
 * Data Logger
 */

// DataLogger constructor
DataLogger::DataLogger() {
    this->num_sensors = 0;
}

// Parametrized constructor
DataLogger::DataLogger(std::string filename, int num_sensors) {
    this->file.open(filename.c_str());
    this->num_sensors = num_sensors;
}

// Open file to write data to
void DataLogger::open_file(std::string filename) {
    this->file.open(filename.c_str());
}

// Save data to the opened file
void DataLogger::save_data(float *data) {
    for (int i = 0; i < this->num_sensors; i++){
        this->file << data[i] << ", ";
    }
    this->file << "\n";
}

// Destruct DataLogger and close file
DataLogger::~DataLogger() {
    this->file.close();
}