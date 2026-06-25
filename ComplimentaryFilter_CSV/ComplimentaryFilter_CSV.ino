#include <Wire.h>
#include "SparkFun_BMI270_Arduino_Library.h"

BMI270 imu;
uint8_t i2cAddress = BMI2_I2C_PRIM_ADDR;

float pastTime;
float fusionAngleX;
float fusionAngleY;
float gyroAngleX = 0.0;
float gyroAngleY = 0.0;
float gyroAngleZ = 0.0;
float alpha = 0.98;

void setup() 
{
  Serial.begin(115200);
  Wire.begin();
  while(imu.beginI2C(i2cAddress) != BMI2_OK)
  {
    delay(1000);
  }

  imu.getSensorData();
  fusionAngleX = atan2(imu.data.accelY, imu.data.accelZ) * (180/M_PI);
  fusionAngleY = atan2(imu.data.accelX, imu.data.accelZ) * (180/M_PI);
  pastTime = millis();
}


void loop()
{
  imu.getSensorData();
  float currentTime = millis();

  //timestamp printing
  Serial.print(currentTime);
  Serial.print(",");

  //GyroX Only Angle
  gyroAngleX = gyroAngleX + ((imu.data.gyroX/1000) * (currentTime - pastTime));
  Serial.print(gyroAngleX, 3);
  Serial.print(",");

  //GyroY Only Angle
  gyroAngleY = gyroAngleY + ((imu.data.gyroY/1000) * (currentTime - pastTime));
  Serial.print(gyroAngleY, 3);
  Serial.print(",");

  //GyroZ Only Angle
  gyroAngleZ = gyroAngleZ + ((imu.data.gyroZ/1000) * (currentTime - pastTime));
  Serial.print(gyroAngleZ, 3);
  Serial.print(",");

  //AccelX Only Angle
  float accelAngleX = atan2(imu.data.accelY, imu.data.accelZ) * (180/M_PI);
  Serial.print(accelAngleX, 3);
  Serial.print(",");

  //AccelY Only Angle
  float accelAngleY = atan2(imu.data.accelX, imu.data.accelZ) * (180/M_PI);
  Serial.print(accelAngleY, 3);
  Serial.print(",");

  //Complimentary Filter Fusion AngleX
  fusionAngleX = (alpha * (fusionAngleX + ((imu.data.gyroX/1000) * (currentTime - pastTime)))) + ((1 - alpha) * (accelAngleX));
  Serial.print(fusionAngleX, 3);
  Serial.print(",");

  //Complimentary Filter Fusion AngleX
  fusionAngleY = (alpha * (fusionAngleY + ((imu.data.gyroY/1000) * (currentTime - pastTime)))) + ((1 - alpha) * (accelAngleY));
  Serial.println(fusionAngleY, 3);

  //CSV order: timestamp(ms),gyrox(deg),gyroy(deg),gyrox(deg),accelx(deg),accely(deg),compfilterx(deg),compfiltery(deg)

  pastTime = currentTime;
  delay(20);
}
