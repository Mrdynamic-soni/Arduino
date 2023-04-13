void setup() {
  // put your setup code here, to run once:
 pinMode(A0,INPUT);
 Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:
  int x = analogRead(A0);
  float temp = (x/1024.0)*3300.0;
  float Temp = (0.5*temp);
  Serial.print("Raw value = ");
  Serial.print(analogRead(A0));
  Serial.print(", Temp = ");
  Serial.println(Temp);
  delay(1000);
}
