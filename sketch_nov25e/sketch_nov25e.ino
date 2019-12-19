 
 int LED = 9;
 int Last_button = 0;


void setup() {
  pinMode(2,INPUT);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  Serial.begin(9600);
 
                 
}
void loop () {
  int input = digitalRead(2);
  Serial.println(input);
 if(input == 1 && Last_button == 0)

  {
    digitalWrite(LED,LOW);
    LED = LED+1;
    digitalWrite(LED,HIGH);


  }
  Last_button = input;
}
