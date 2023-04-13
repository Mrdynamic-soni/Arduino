#include <Adafruit_MPU6050.h>

//starting adafruit library for mpu6050
Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  mpu.begin();//starting mpu for  reading
}

void loop() {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

      
//Accelerometer reading
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  
//gyroscope reading
  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");
  delay(1000);

}
