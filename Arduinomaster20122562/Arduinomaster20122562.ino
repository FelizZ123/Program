#include <SoftwareSerial.h>
#define Switch_1        13
#define Switch_2        12
#define Lighter         6

uint8_t Status_Sw1, Status_Sw2;
byte DataRead[17];
bool ClearStatus;
char Datatran[255];
SoftwareSerial ESPPort(2, 3);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ESPPort.begin(9600);

  pinMode(Switch_1, INPUT);
  pinMode(Switch_2, INPUT);
  pinMode(Lighter, OUTPUT);

  ClearStatus = false;
  analogWrite(Lighter, 0);

  delay(1000);
}

void loop() {
  Status_Sw1 = digitalRead(Switch_1);
  Status_Sw2 = digitalRead(Switch_2);
  if(Status_Sw2 == 0)
  {
    analogWrite(Lighter, 255);
  }
  else
  {
    analogWrite(Lighter, 0);
  }
  if (Status_Sw1 == 0) {
    CommandReadSensor();
    Serial.print("OK");
    Serial.print(DataRead[0], HEX );
    Serial.print(" ");
    Serial.print(DataRead[1], HEX );
    Serial.print("  ");
    Serial.print(DataRead[2], HEX );
    Serial.print(" ");
    Serial.print(DataRead[3], HEX );
    Serial.print(" ");
    Serial.print(DataRead[4], HEX );
    Serial.print(" ");
    Serial.print(DataRead[5], HEX );
    Serial.print("   ");
    Serial.print(DataRead[6], HEX );
    Serial.print(" ");
    Serial.print(DataRead[7], HEX );
    Serial.print(" ");
    Serial.print(DataRead[8], HEX );
    Serial.print("  ");
    Serial.print(DataRead[9], HEX );
    Serial.print("   ");
    Serial.print(DataRead[10], HEX );
    Serial.print(" ");
    Serial.print(DataRead[11], HEX );
    Serial.print(" ");
    Serial.print(DataRead[12]);
    Serial.print(" ");
    Serial.print(DataRead[13], HEX );
    Serial.print(" ");
    Serial.print(DataRead[14], HEX );
    Serial.print(" ");
    Serial.println(DataRead[15], HEX );
    byte g = 0;
    String DataRead_10;
    if ((DataRead[10]) < 10)
    {
      DataRead_10 = String(g) + String(DataRead[10]);
    }
    else
    {
      DataRead_10 = String(DataRead[10]);
    }
    String DataRead_11;
    if ((DataRead[11]) < 10)
    {
      DataRead_11 = String(g) + String(DataRead[11]);
    }
    else
    {
      DataRead_11 = String(DataRead[11]);
    }

    String Buffer_2 = String(DataRead[0]) + String(DataRead[3]) + String(DataRead[4]) + String(DataRead[5]) + String(DataRead[7]) + String(DataRead[8]) + String(DataRead[9]) + String(DataRead_10) + String(DataRead_11) + String(DataRead[12]) + String(DataRead[13]) +  String(DataRead[14]) + String(DataRead[15]);
    Buffer_2.toCharArray(Datatran, 255);
    ESPPort.write(Datatran, 14);
    Serial.println(Buffer_2);
    delay(25);
  }
  while (Status_Sw1 == 0) {

    Status_Sw1 = digitalRead(Switch_1);
  }
}
void CommandReadSensor() {

  boolean LoopRead = true;
  int Buffer_1;
  byte CommandSend[5];
  byte BufferClear;
  bool BitClear;


  //0x02 0x0A 0x23 0x2D 0x03
  CommandSend[0] = 0x02;
  CommandSend[1] = 0x0A;
  CommandSend[2] = 0x23;
  CommandSend[3] = 0x2D;
  CommandSend[4] = 0x03;

  Serial.write(CommandSend, 5);

  while (LoopRead) {

    if (Serial.available()) {

      if (ClearStatus) {

        goto Label_1;
      }

      DataRead[0] = Serial.read();

      if (DataRead[0] == 0x02) {

Label_1:
        ClearStatus = false;

        for (int i = 1; i < 15; i++) {

          while (!(Serial.available())) {

            //
          }

          DataRead[i] = Serial.read();
        }

        if (DataRead[14] == 0x03) {

          if (DataRead[1] == 0x0B) {

            Buffer_1 = DataRead[1] + DataRead[2] + DataRead[3] + DataRead[4] + DataRead[5] + DataRead[6] + DataRead[7] + DataRead[8] + DataRead[9] + DataRead[10] + DataRead[11] + DataRead[12];
            if (DataRead[13] == Buffer_1) {

              //Status = true;

            }
          }
        }
        else {

          goto Label_2;
        }

        LoopRead = false;
      }

      else {
Label_2:
        BitClear = true;

        while (BitClear) {

          unsigned long previousMicros = micros();

          while (!(Serial.available())) {

            unsigned long currentMicros = micros();

            if (currentMicros - previousMicros >= 100) {

              goto Label_3;
            }
          }

          BufferClear = Serial.read();
          if (BufferClear == 0x02) {

            BitClear = false;
            ClearStatus = true;
          }
        }

        //Label_3:
        //BitClear = false;
        //LoopRead = false;
      }
    }

Label_3:
    BitClear = false;
    LoopRead = false;
  }
}
