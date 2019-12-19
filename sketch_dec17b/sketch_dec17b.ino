void setup() {
pinMode(11,OUTPUT);
pinMode(9,OUTPUT);
pinMode(10,OUTPUT);
pinMode(8,OUTPUT);
pinMode(3,OUTPUT);
pinMode(2,OUTPUT);
}

void loop() {
analogWrite(9,100);
digitalWrite(11,0);
analogWrite(10,250);
digitalWrite(8,1);
analogWrite(2,250);
digitalWrite(3,0);
}
