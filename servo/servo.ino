#include <Servo.h>

Servo sv;
void setup() {
  sv.attach(2);

}

void loop() {
  sv.write(0);
  delay(500);

  sv.write(180);
  delay(500);

}
