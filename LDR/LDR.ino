int ldr = A0 ;
void setup() {
 pinMode(A0,OUTPUT);
 Serial.begin(9600);
}

void loop() {
  val = analogRead(A0);
 Serial.print("val = ")
 Serial.print(val);
 if(val < 100) {
  digitalWrite(A0,HIGH);
 }
 else{
  digitalWrite(A0,LOW);
 }
 delay(100);
 }
