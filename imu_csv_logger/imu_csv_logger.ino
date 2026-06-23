#include <Wire.h>
#include "SparkFun_BMI270_Arduino_Library.h"

BMI270 imu;
uint8_t i2cAddress = BMI2_I2C_PRIM_ADDR;

void setup() 
{
  Serial.begin(115200);
  Wire.begin();
  while(imu.beginI2C(i2cAddress) != BMI2_OK)
  {
    delay(1000);
  }
}

void loop()
{
  imu.getSensorData();

  Serial.print(millis());
  Serial.print(",");

  Serial.print(imu.data.gyroX, 3);
  Serial.print(",");
  Serial.print(imu.data.gyroY, 3);
  Serial.print(",");
  Serial.print(imu.data.gyroZ, 3);
  Serial.print(",");

  Serial.print(imu.data.accelX, 3);
  Serial.print(",");
  Serial.print(imu.data.accelY, 3);
  Serial.print(",");
  Serial.println(imu.data.accelZ, 3);
  
  delay(20);
}
