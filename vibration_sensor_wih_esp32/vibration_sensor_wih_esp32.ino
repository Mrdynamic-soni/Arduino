#define vib_pin D1
void setup() {
  Serial.begin(9600);
  pinMode(vib_pin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   long vibration = vib_init();
  Serial.println(vibration);

}
long vib_init(){
  long vibration = pulseIn(vib_pin,HIGH); 
  return vibration;
}
