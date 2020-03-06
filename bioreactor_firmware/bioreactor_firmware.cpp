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

// Initialize state machine, should be done once at beginning of bioreactor experiment
StateMachine::StateMachine() {
    this->state = STARTUP;

    const int num_states = 6;

    // Initialize transition matrix as a 2D matrix using a pointer to array of pointers
    this->s = new int*[num_states];
    for (int i = 0; i < num_states; i++) {
        this->s[i] = new int[num_states];
    }

    // Setup transition matrix with unique value for each (state -> new_state) transition
    int unique_val = 0;
    for (int i = 0; i < num_states; i++){
        for (int j = 0; j < num_states; j++) {
            this->s[i][j] = unique_val;
            unique_val += 1;
        }
    }
}

std::string StateMachine::print_state() {
    std::cout << "Current state: " << this->state;
}

void StateMachine::state_transition(int new_state) {

    // Get transition from current state to new state
    int trans = this->s[this->state][new_state];

    // Run code depending on transition being made
    // Startup -> new_state
    if (trans == this->s[STARTUP][CALIBR
    ATION]) {
        std::cout << "test_startup->calib\n";
    }
    else if (trans == this->s[STARTUP][RUNNING]) {
        std::cout << "test_startup->running\n";
    }

    // Calibration -> new_state
    else if (trans == this->s[CALIBRATION][RUNNING]) {

    }

    /*
     * TODO : finish transitions
     */
}

StateMachine::~StateMachine() {
    delete this->s;
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