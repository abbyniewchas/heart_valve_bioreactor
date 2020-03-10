

/*
#include <GSM3SoftSerial.h>
#include <GSM.h>
#include <GSM3MobileAccessProvider.h>
#include <GSM3MobileMockupProvider.h>
#include <GSM3MobileNetworkRegistry.h>
#include <GSM3ShieldV1CellManagement.h>
#include <GSM3ShieldV1ServerProvider.h>
#include <GSM3ShieldV1DataNetworkProvider.h>
#include <GSM3ShieldV1ModemVerification.h>
#include <GSM3ShieldV1PinManagement.h>
#include <GSM3MobileDataNetworkProvider.h>
#include <GSM3IO.h>
#include <GSM3CircularBuffer.h>
#include <GSM3MobileSMSProvider.h>
#include <GSM3VoiceCallService.h>
#include <GSM3MobileClientService.h>
#include <GSM3MobileVoiceProvider.h>
#include <GSM3ShieldV1MultiClientProvider.h>
#include <GSM3ShieldV1BandManagement.h>
#include <GSM3MobileServerProvider.h>
#include <GSM3ShieldV1ModemCore.h>
#include <GSM3ShieldV1VoiceProvider.h>
#include <GSM3ShieldV1AccessProvider.h>
#include <GSM3MobileClientProvider.h>
#include <GSM3MobileServerService.h>
#include <GSM3MobileNetworkProvider.h>
#include <GSM3ShieldV1MultiServerProvider.h>
#include <GSM3MobileCellManagement.h>
#include <GSM3ShieldV1.h>
#include <GSM3ShieldV1SMSProvider.h>
#include <GSM3ShieldV1BaseProvider.h>
#include <GSM3SMSService.h>
#include <GSM3ShieldV1DirectModemProvider.h>
#include <GSM3ShieldV1ClientProvider.h>
#include <GSM3ShieldV1ScanNetworks.h>

#include <FirmataDefines.h>
#include <FirmataConstants.h>
#include <FirmataMarshaller.h>
#include <Firmata.h>
#include <FirmataParser.h>
#include <Boards.h>
*/



/*
 * Combined example code from Dynamixel Serial and Sparkfun
*/

#include <Dynamixel_Serial.h>       // Library needed to control Dynamixal servo
#include <SparkFun_MS5803_I2C.h>
#include <Wire.h>
//#include <SoftwareSerial.h>

#define SERVO_ID 0x01               // ID of which we will set Dynamixel too 
#define SERVO_ControlPin 0x02       // Control pin of buffer chip, NOTE: this does not matter becasue we are not using a half to full contorl buffer.
//#define SERVO_SET_Baudrate 100000    // Baud rate speed which the Dynamixel will be set too (57600)
//#define SERVO_SET_Baudrate 9600    // Baud rate speed which the Dynamixel will be set too (57600)
#define SERVO_SET_Baudrate 57600    // Baud rate speed which the Dynamixel will be set too (57600)
#define CW_LIMIT_ANGLE 0x001        // lowest clockwise angle is 1, as when set to 0 it set servo to wheel mode
#define CCW_LIMIT_ANGLE 0xFFF       // Highest anit-clockwise angle is 0XFFF, as when set to 0 it set servo to wheel mode

/*
 * Sparkfun sensor
 */


MS5803 sensor_p1(ADDRESS_HIGH);
MS5803 sensor_p2(ADDRESS_LOW);

//Create variables to store results
float temperature_c, temperature_f;
double pressure_abs_p1;
double pressure_abs_p2;
//double pressure_relative, altitude_delta, pressure_baseline;
//double base_altitude = 1655.0; // Altitude of SparkFun's HQ in Boulder, CO. in (m)

//SoftwareSerial portSensor(3, 4);


void setup(){
 delay(1000);                                                           // Give time for Dynamixel to start on power-up

 // Now that the Dynamixel is reset to factory setting we will program its Baudrate and ID
 //Dynamixel.begin(57600,SERVO_ControlPin);                 // Set Ardiuno Serial speed to factory default speed of 57600
 //Dynamixel.begin(9600,SERVO_ControlPin);
 //Dynamixel.setID(0xFE,SERVO_ID);                               // Broadcast to all Dynamixel IDs(0xFE) and set with new ID
 //delay(10);                                                     // Time needed for Dynamixel to set it's new ID before next instruction can be sent
 //Dynamixel.setStatusPaket(SERVO_ID,READ);                      // Tell Dynamixel to only return status packets when a "read" instruction is sent e.g. Dynamixel.readVoltage();
 //Dynamixel.setBaudRate(SERVO_ID,SERVO_SET_Baudrate);           // Set Dynamixel to new serial speed 
 //delay(30);                                                    // Time needed for Dynamixel to set it's new Baudrate


  Dynamixel.begin(SERVO_SET_Baudrate,SERVO_ControlPin);    // We now need to set Ardiuno to the new Baudrate speed 
  Dynamixel.ledState(SERVO_ID, ON);                            // Turn Dynamixel LED on
  delay(5);
  Dynamixel.setMode(SERVO_ID, SERVO,0x000,0xFFF);              // Turn mode to SERVO, must be WHEEL if using wheel mode
  delay(5);

/*
 * Sparkfun
 */

    // Start your preferred I2C object
    Wire.begin();
  //Initialize Serial Monitor
  //Serial.begin(9600);
  //Retrieve calibration constants for conversion math.
  sensor_p1.reset();
  sensor_p2.reset();
  
  sensor_p1.begin();
  sensor_p2.begin();

  //pressure_baseline = sensor_p1.getPressure(ADC_4096);
  //pressure_baseline = sensor_p2.getPressure(ADC_4096);

  //portSensor.begin(9600);

  /*
   * Data Logging
   * you may use Putty:

1. install putty:
sudo apt-get install putty putty-tools

2. run Putty. It should be inside the internet apps (I don't know why)

http://imgur.com/a/Dx695

3. in Putty select serial and specify the right port:

http://imgur.com/a/ecNqn

4. then on the left  under session go to the logging. select the printable output. and then specify the right address and file name for the output file:

http://imgur.com/a/OLL7q
   */

  //Serial.begin(9600);
  Serial.begin(57600);


}


int analogPin = A0;
int digitalIn = 4;
int val = 0;
int servo_write = 0;
int time_ms = 0;
int start_time = 0;
int sensor_collect_freq = 200;
int time_since_last_data = 0;
int sensor_time_zero = 0;

void loop(){

  /*
   * Move pump manually with potentiometer
   */
   /*
  val = analogRead(analogPin);
  servo_write = (int) ((val / 1023.0) * 4095.0);
  delayMicroseconds(1);
  Dynamixel.servo(SERVO_ID,servo_write,0x100);
  delayMicroseconds(1);
  */

   /*
   * Move pump with fixed start and stop but change the torque limit
   */
  
  //val = analogRead(analogPin);
  //int servo_max_torque = (int) ((val / 1023.0) * 4095.0);
  //int servo_max_torque = 1023;
  //Dynamixel.setMaxTorque(SERVO_ID, servo_max_torque);
  //delayMicroseconds(1);
  //Dynamixel.setHoldingTorque(SERVO_ID, true);
  //delay(2000);
  //Dynamixel.servo(SERVO_ID,2500,0x100);
  //delay(2000);
  //Dynamixel.servo(SERVO_ID,1500,0x100);


  /*
   * Send linear movement function to pump
   */
   
    //portSensor.listen();

   
  // Reset pump
  /*
  if (digitalRead(digitalIn) == LOW) {
    Dynamixel.servo(SERVO_ID,2500,0x3FF);
    start_time = (int) millis();
    time_ms = 0;
    servo_write = 0;
  } else {
    //Start: servo_write = 2500;
    //End: servo_write = 2000;
    time_ms = ((int) millis()) - start_time;
    servo_write = (-2000 * (time_ms / 1000.0)) + 2500;
    servo_write = max(min(servo_write, 2500), 2000);
    Dynamixel.servo(SERVO_ID,servo_write,0x3FF);

    
    // Reset pump once goal position hit
    if (servo_write == 2000) {
      Dynamixel.servo(SERVO_ID,2500,0x3FF);
      delay(500);
      time_ms = 0;
      start_time = (int) millis();
      servo_write = 0;
    }
    
    

    /*
    if (time_ms >= 1000) {
      time_ms = 0;
    }
    */

    //portSensor.println(pressure_abs);
    

    /*
    time_since_last_data = ((int) millis()) - sensor_time_zero;
    if (time_since_last_data >= sensor_collect_freq) {
      pressure_abs = sensor.getPressure(ADC_4096);
      Serial.println(pressure_abs);
      sensor_time_zero = (int) millis();
    }
    */
    
  //}
  
  //delay(1);
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
