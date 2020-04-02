//
// Created by lutkus on 2/19/20
//

#include "bioreactor_firmware.h"

/*
 * Controllers
 */
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
    this->prev_error = 0;
}

void PID::tune_controller(float tuning_values[3]) {
    // Store the tuning values in the PID object
    this->P = tuning_values[0];
    this->I = tuning_values[1];
    this->D = tuning_values[2];
}

float PID::control_action(float current_state, float desired_state, float dt) {
    // Calculate error between current and desired state
    float error = desired_state - current_state;

    // If this is the first call to control_action, just use the P term so that the other terms do not
    // blow up going from zero initialized error to actual error
    float P_term = 0;
    float I_term = 0;
    float D_term = 0;
    if (this->first_pass) {
        P_term = this->P * error;
        this->first_pass = false;
    } else {
        // Multiply state estimation by weighted P, I, and D terms
        P_term = this->P * error;
        I_term = this->I * this->integral;
        D_term = this->D * (error - this->prev_error) / dt;
    }

    // Update integral using trapezoidal integration method
    this->integral += dt * (error + this->prev_error) / 2;

    // Update previous state estimation
    this->prev_error = error;

    // Return the sum of all PID components
    return P_term + I_term + D_term;
}

void PID::reset_integral() {
    // Reset integral term
    this->integral = 0;
}

void PID::reset_error() {
    // Reset previous error and set first pass flag to ON
    this->prev_error = 0;
    this->first_pass = true;
}

/*
 * Controller : LQR
 */
LQR::LQR(std::string id) {
    // Initialize controller parameters
    this->id = id;
    this->num_control = 1;
    this->num_states = 2;

    // Initialize LQR parameters
    this->K = new float[this->num_states * this->num_control];
}

void LQR::tune_controller(float *tuning_values) {
    // K matrix is defined as a (m x n) matrix where m is the system's states and n is the number of control inputs
    for (int i = 0; i < (this->num_states * this->num_control); i++) {
        this->K[i] = tuning_values[i];
    }
}

float LQR::control_action(float current_state, float desired_state, float dt) {
    // Calculate optimal control action with tuned LQR controller, given state vector x
    // optimal control u* = -K * x
    float u_star = 0;
    for (int i = 0; i < (this->num_states * this->num_control); i++) {
        u_star += -this->K[i] * current_state;
    }

    return u_star;
}

LQR::~LQR() {
    // Delete K matrix from heap
    delete[] this->K;
}

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