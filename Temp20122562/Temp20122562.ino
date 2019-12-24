
#define Switch_1        13
#define Switch_2        12
#define Heater_On       11
#define Heater_Level    9
#define Lighter         6
#define Fan_On          8
#define Fan_Speed       10
#define Mist_Pump       7

uint8_t Status_Sw1, Status_Sw2;
void setup() {
  // put your setup code here, to run once:
pinMode(Switch_1, INPUT);
  pinMode(Switch_2, INPUT);
  pinMode(Heater_On, OUTPUT);
  pinMode(Heater_Level, OUTPUT);
  pinMode(Lighter, OUTPUT);
  pinMode(Fan_On, OUTPUT);
  pinMode(Fan_Speed, OUTPUT);
  pinMode(Mist_Pump, OUTPUT);

  digitalWrite(Heater_On, LOW);
  analogWrite(Heater_Level, 0);
  analogWrite(Lighter, 0);
  digitalWrite(Fan_On, LOW);
  analogWrite(Fan_Speed, 0);
  digitalWrite(Mist_Pump, LOW);

  delay(1000);
}

void loop() {
 Status_Sw1 = digitalRead(Switch_1);
  Status_Sw2 = digitalRead(Switch_2);
  digitalWrite(Fan_On, HIGH);
  if (Status_Sw1 == 0)
  {
    analogWrite(Heater_Level, 0);
  }
 
  if (Status_Sw2 == 0) {
    analogWrite(Heater_Level, 255);
  }
  

}
