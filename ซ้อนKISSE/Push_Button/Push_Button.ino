
  int LED_1 = 12;           // Digital pin 12
  int LED_2 = 11;           // Digital pin 11
  int LED_3 = 10;           // Digital pin 10
  int LED_4 = 9;            // Digital pin 9

  int Switch_1 = 8;         // Digital pin 8
  int Switch_2 = 5;         // Digital pin 5
  int Switch_3 = 4;         // Digital pin 4

  int Status_Sw1, Status_Sw2, Status_Sw3;

  
void setup() {
  // put your setup code here, to run once:

  pinMode(LED_1, OUTPUT);               // Active "LOW"
  pinMode(LED_2, OUTPUT);               // Active "LOW"
  pinMode(LED_3, OUTPUT);               // Active "LOW"
  pinMode(LED_4, OUTPUT);               // Active "LOW"

  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, HIGH);
  digitalWrite(LED_3, HIGH);
  digitalWrite(LED_4, HIGH);
  
  pinMode(Switch_1, INPUT);             // Active "LOW"
  pinMode(Switch_2, INPUT);             // Active "LOW"
  pinMode(Switch_3, INPUT);             // Active "LOW"
}


void loop() {
  // put your main code here, to run repeatedly:

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Status_Sw1 = digitalRead(Switch_1);
    if(Status_Sw1 == 0){

      digitalWrite(LED_1, LOW);
      digitalWrite(LED_2, HIGH);
      digitalWrite(LED_3, HIGH);
      digitalWrite(LED_4, HIGH);
    }

    while (Status_Sw1 == 0) {

      Status_Sw1 = digitalRead(Switch_1);
    }

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Status_Sw2 = digitalRead(Switch_2);
    if(Status_Sw2 == 0){

      digitalWrite(LED_1, HIGH);
      digitalWrite(LED_2, LOW);
      digitalWrite(LED_3, HIGH);
      digitalWrite(LED_4, HIGH);
    }

    while (Status_Sw2 == 0) {

      Status_Sw2 = digitalRead(Switch_2);
    }

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Status_Sw3 = digitalRead(Switch_3);
    if(Status_Sw3 == 0){

      digitalWrite(LED_1, HIGH);
      digitalWrite(LED_2, HIGH);
      digitalWrite(LED_3, LOW);
      digitalWrite(LED_4, LOW);
    }

    while (Status_Sw3 == 0) {

      Status_Sw3 = digitalRead(Switch_3);
    }
}


