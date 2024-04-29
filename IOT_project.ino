#include "Motor.h"
#include "Ultrasonic.h"


void setup() {

  // Initalisation data transfer rate in baud
  //The Baud rate refers to the total number of signal units transmitted in one secoc:\temp\IOT_project\IOT_project\libraries\Accelerometer\src\Accelerometer.h c:\temp\IOT_project\IOT_project\libraries\Accelerometer\src\Accelerometer.cppnd. The Bit rate refers to the total Bits transmitted in one unit time. Baud rate indicates the total number of times the overall state of a given signal changes/ alters. Bit rate indicates the total bits that travel per second.
 
  Serial.begin(9600);
  
  // Initalisation for a Bluetooth®️ Low Energy central
  
  BLEInit();
  
  // Initalisation for a Ultrasonic Low Energy central
  
  UltraSInit();

}

void loop() { 
  // wait for a Bluetooth®️ Low Energy central
  Serial.println("Run Car");
  Motor();
}
