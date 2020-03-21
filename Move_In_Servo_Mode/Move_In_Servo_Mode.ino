#include "Dynamixel_Serial.h"       // Library needed to control Dynamixal servo
#include "SparkFun_MS5803_I2C.h"
#include <Wire.h>

// ID of Dynamixel Servo
#define SERVO_ID 0x01

// Create MS5803 pressure sensor objects (sensors before and after heart valve)
MS5803 sensor_p1(ADDRESS_HIGH);
MS5803 sensor_p2(ADDRESS_LOW);

// Use Arduino's setup() function to run code before continous loop
void setup(){
    // Give time for Dynamixel servo motor to start on power-up
    delay(1000);

    // Begin Dynamixel servo motor with specified baudrate and control pin on hardware
    Dynamixel.begin(1000000,0x02);

    // Visually show that Dynamixel servo is communicating with Arduino via its LED light
    Dynamixel.ledState(SERVO_ID, ON);
    delay(5);

    // Set Dynamixel servo motor's mode to SERVO (ie. control angular position and not rotational velocity)
    Dynamixel.setMode(SERVO_ID, SERVO,0x000,0xFFF);
    delay(5);

    // Start the I2C communication ports on the Arduino (used by the MS5803 sensors)
    Wire.begin();

    // Reset and begin each sensor
    sensor_p1.reset();
    sensor_p2.reset();
    sensor_p1.begin();
    sensor_p2.begin();

    // Begin Arduino serial port at chosen baud rate
    Serial.begin(1000000);
}

// Infinite loop that will run continuously on the Arduino after setup() runs once
int start_time = 0;
void loop(){
    // Digital pin used for toggle switch
    int digitalIn = 4;

    // Value for writing the servo's position
    int servo_write = 0;

    // Value for storing time in milliseconds
    int time_ms = 0;

    // Record sensor pressure at highest resolution
    double pressure_abs_p1 = sensor_p1.getPressure(ADC_4096);
    double pressure_abs_p2 = sensor_p2.getPressure(ADC_4096);

    // Using toggle switch to allow servo to actuate or stay in rest position
    if (digitalRead(digitalIn) == LOW) {
        // If toggle switch is off, set servo to rest position and hold
        Dynamixel.servo(SERVO_ID,1200,0x3FF);

        // Continuously updating start time so that when toggle switch is flipped
        // the time elapsed since the servo command was first issued is accurate
        start_time = (int) millis();

    } else {
        // Servo movement is a time-dependent linear function following the generic (y = mx + b) equation
        // Start and stop positions for linear movement
        int start_pos = 1200;
        int stop_pos = 700;

        // Slope of curve determines duration of movement (slope=1000 means 1200->700 in 0.5sec)
        int slope = 1000;
        time_ms = ((int) millis()) - start_time;
        servo_write = (-slope * (time_ms / 1000.0)) + start_pos;

        // Saturate servo movement between start and stop positions
        servo_write = max(min(servo_write, start_pos), stop_pos);

        // Move the servo motor with speed set to max servo speed
        Dynamixel.servo(SERVO_ID,servo_write,0x3FF);
    
        // Move servo back once goal position reached hit to create sinusoidal movement in and out
        if (servo_write == stop_pos) {

            // Restart timers
            time_ms = 0;
            start_time = (int) millis();

            // Move the servo linearly back to the start position
            while (servo_write < start_pos) {
                // Get current time
                time_ms = ((int) millis()) - start_time;

                // Command servo following same equation as before but with positive slope
                servo_write = (slope * (time_ms / 1000.0)) + stop_pos;
                servo_write = max(min(servo_write, start_pos), stop_pos);
                Dynamixel.servo(SERVO_ID,servo_write,0x3FF);

                // Record data during this while loop and print to serial port
                pressure_abs_p1 = sensor_p1.getPressure(ADC_4096);
                pressure_abs_p2 = sensor_p2.getPressure(ADC_4096);
                Serial.print(time_ms);
                Serial.print(", ");
                Serial.print(servo_write);
                Serial.print(", ");
                Serial.print(pressure_abs_p1);
                Serial.print(", ");
                Serial.print(pressure_abs_p2);
                Serial.print(", ");
                Serial.print("\n");
            }

            // Restart start timer after start position is reached
            start_time = (int) millis();
        }
    }

    // Record data and print to serial port for data acquisition
    // technically there is latency between these variable measurements but for the time resolution needed
    // for this project this is okay
    Serial.print(time_ms);
    Serial.print(", ");
    Serial.print(servo_write);
    Serial.print(", ");
    Serial.print(pressure_abs_p1);
    Serial.print(", ");
    Serial.print(pressure_abs_p2);
    Serial.print(", ");
    Serial.print("\n");
}
