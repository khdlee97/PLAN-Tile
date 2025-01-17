// Basic demo for accelerometer readings from Adafruit LIS3DH

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

// Used for software SPI
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
// Used for hardware & software SPI
#define LIS3DH_CS 10


// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

void setup(void) {
#ifndef ESP8266
  while (!Serial);     
#endif

  Serial.begin(9600);
  
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    while (1);
  }
  
  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  
  //Serial.print("Range = "); Serial.print(2 << lis.getRange());  
  //Serial.println("G");
}

void loop() {
  lis.read();      // get X Y and Z data at once
  // Then print out the raw data
  Serial.print(""); Serial.print(lis.x); 
  Serial.print(","); Serial.print(lis.y); 
  Serial.print(","); Serial.print(lis.z); 

  /* Or....get a new sensor event, normalized */ 
  sensors_event_t event; 
  lis.getEvent(&event);
  
  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print(","); Serial.print(event.acceleration.x);
  Serial.print(","); Serial.print(event.acceleration.y); 
  Serial.print(","); Serial.print(event.acceleration.z); 
  //Serial.println(" m/s^2 ");

  Serial.println();
 
  delay(200); 
}
