#include <ESP8266WiFi.h>
#include <WiFiUDP.h>


#define Switch_1        13
#define Switch_2        12

unsigned int UDPPort = 888 ;
const char* host = "192.168.43.177";
const char* ssid = "mmmm";
const char* password = "1234512345";
WiFiUDP Udp;
int packet, packetSize, len, NumText;
String NameString;
String BufferString, CalString;
String Readdata;

uint8_t Status_Sw1, Status_Sw2;
byte DataRead[15];
bool ClearStatus;
//String Readdata;


void setup() {

  Serial.begin(9600);
  Serial.print("Connecting to  ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
  pinMode(Switch_1, INPUT);
  pinMode(Switch_2, INPUT);

  ClearStatus = false;
  delay(1000);
  
  Udp.begin(UDPPort);
  Serial.println();
  Serial.print("WiFi UDP Mode : ");
  Serial.println(WiFi.localIP().toString());

}





void loop() {



  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Status_Sw1 = digitalRead(Switch_1);
  if (Status_Sw1 == 0) {


    CommandReadSensor();

    Serial.print(" ");
    Serial.print("OK");
    Serial.print(" ");
    Serial.print(DataRead[1], HEX);
    Serial.print("  ");
    Serial.print(DataRead[2], HEX);
    Serial.print(" ");
    Serial.print(DataRead[3], HEX);
    Serial.print(" ");
    Serial.print(DataRead[4], HEX);
    Serial.print(" ");
    Serial.print(DataRead[5], HEX);
    Serial.print("   ");
    Serial.print(DataRead[6], HEX);
    Serial.print(" ");
    Serial.print(DataRead[7], HEX);
    Serial.print(" ");
    Serial.print(DataRead[8], HEX);
    Serial.print("  ");
    Serial.print(DataRead[9], HEX);
    Serial.print("   ");
    Serial.print(DataRead[10], HEX);
    Serial.print(" ");
    Serial.print(DataRead[11], HEX);
    Serial.print(" ");
    Serial.print(DataRead[12], HEX);
    Serial.print("  ");
    Serial.print(DataRead[13], HEX);
    Serial.print("  ");
    Serial.println(DataRead[14], HEX);


    delay(25);
  }
  while (Status_Sw1 == 0) {

    Status_Sw1 = digitalRead(Switch_1);
  }

  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Status_Sw2 = digitalRead(Switch_2);
  if (Status_Sw2 == 0) {

    //

    delay(25);
  }
  while (Status_Sw2 == 0) {

    Status_Sw2 = digitalRead(Switch_2);
  }
  
  NameString = String(DataRead[0]) + String(DataRead[1]) + String(DataRead[2]) + String(DataRead[3]) + String(DataRead[4]) + String(DataRead[5]) + String(DataRead[6]) + String(DataRead[7]) + String(DataRead[8]) + String(DataRead[9]) + String(DataRead[10]) + String(DataRead[11]) + String(DataRead[12]) + String(DataRead[13]) + String(DataRead[14]) + String("*");
  char StringBuffer[255];
  Serial.println();
  NameString.toCharArray(StringBuffer,255);
  Udp.begin(UDPPort);
  Udp.beginPacket(host, UDPPort);
  Udp.write(StringBuffer);
  Udp.endPacket();

}



// *************************************************************
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
