int LED   = 8;
int LastButtonState =0; 
int Button = 0;
void setup() {
  pinMode (2,INPUT);
  pinMode (13,OUTPUT);
  pinMode (12,OUTPUT);
  pinMode (11,OUTPUT);
  pinMode (10,OUTPUT);
  Serial.begin(9600);
}

void loop() {
 Button = digitalRead (2);
  if (Button==1 && LastButtonState == 0)
  {
    LED = LED+1;
    digitalWrite (LED+1,HIGH);
    digitalWrite (LED,LOW); 
  }   
 LastButtonState = Button;
}
