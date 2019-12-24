
  
#define Switch_1        13
#define Switch_2        12
#define Heater_On       11
#define Heater_Level    9
#define Lighter         6
#define Fan_On          8
#define Fan_Speed       10
#define Mist_Pump       7



  uint8_t Status_Sw1, Status_Sw2;

  bool TestStatus = false; 
  int mist = 0;

  
void setup() {

  Serial.begin(9600);
  

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

  if(TestStatus){

    digitalWrite(Fan_On, HIGH);
    digitalWrite(Heater_On, LOW);
    

    for(int i=0; i <= 255; i=i+2){

      //analogWrite(Fan_Speed, i);
      analogWrite(Heater_Level,i);
      //analogWrite(Lighter, i);

      Serial.println(i);
      
      delay(200);
    }


//    mist = ~mist;
//    digitalWrite(Mist_Pump,LOW);
//    delay(1000);

//    digitalWrite(Fan_On, HIGH);
//    digitalWrite(Heater_On, HIGH);
    
//    analogWrite(Fan_Speed, 0);
//    analogWrite(Heater_Level, 0);
//    analogWrite(Lighter, 0);
      
//    delay(4000);
  }
  
 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Status_Sw1 = digitalRead(Switch_1);
  if(Status_Sw1 == 0){

    TestStatus = true;

    delay(25); 
  }
  while (Status_Sw1 == 0){

    Status_Sw1 = digitalRead(Switch_1);
  }
  
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Status_Sw2 = digitalRead(Switch_2);
  if(Status_Sw2 == 0){

    //
    
    delay(25);
  }
  while (Status_Sw2 == 0){

    Status_Sw2 = digitalRead(Switch_2);
  }

}
