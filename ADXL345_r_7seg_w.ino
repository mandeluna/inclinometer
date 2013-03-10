// Wire Master Reader

// Reads data from an I2C/TWI ADXL345
// Refer to the "Wire Slave Sender" example for use with this

// Created 09 March 2013 by Steven Wart (steve@wart.ca)
//

#include <Wire.h>
#include <math.h>

#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

#define X0 0x32
#define X1 0x33
#define Y0 0x34
#define Y1 0x35
#define Z0 0x36
#define Z1 0x37

Adafruit_7segment matrix = Adafruit_7segment();

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  
  // Activate the 7-segment i2c
  matrix.begin(0x70);
  
  //Turning on the ADXL345
  Wire.beginTransmission(0x1D); // transmit to ADXL345
  Wire.write(0x2D);              // POWER_CTL
  Wire.write(0x09);              // measurement mode, 4hz wakeup
  Wire.endTransmission();       // stop transmitting
}

int num_samples = 10;    // take the average of multiple samples

void loop()
{
  float sum = 0.0f;
  
  for (int i=0; i < num_samples; i++)
  {
    float z = getZ();  // +z is up from the top of the pcb
    float y = getY();  // +y is lengthwise to the right
    
    float angle = atan2(z, y) * 180.0f / M_PI;  // angle will be between -360 and 360 degrees
    sum += angle;
    delay(15);
  } 
  
  float average = round(sum / num_samples);
  matrix.printFloat(average);
  matrix.writeDisplay();
}

byte requestByte(char dir)
{
  Wire.beginTransmission(0x1D); // transmit to ADXL345
  Wire.write(dir);
  Wire.endTransmission(); // stop transmitting
  Wire.requestFrom(0x1D, 1); // request 1 byte from ADXL345
  while(Wire.available())
  {
    return(Wire.read()); //  
  }
}

int getX()
{
  int val = requestByte(X0);
  val += requestByte(X1) << 8;
  return val;
}

int getY()
{
  int val = requestByte(Y0);
  val += requestByte(Y1) << 8;
  return val;
}

int getZ()
{
  int val = requestByte(Z0);
  val += requestByte(Z1) << 8;
  return val;
}
