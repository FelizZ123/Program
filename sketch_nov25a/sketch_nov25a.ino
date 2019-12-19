void setup() {
  pinMode(12,OUTPUT);//กำหนดขาเอาต์พุต
pinMode(11,OUTPUT);//กำหนดขาเอาต์พุต

}

void loop() {
 digitalWrite(12,HIGH);
 digitalWrite(11,LOW);
 delay(150);
 digitalWrite(11,HIGH);
 digitalWrite(12,LOW);
 delay(150);
 }
