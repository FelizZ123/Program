
#include <ESP8266WiFi.h>
#include <WiFiUDP.h>


//const char* ssid = "GMS-01";
//const char* password = "86390026";
//const char *ssid = "Nokia 6.1";
//const char *password = "12345678";
const char *ssid = "mmmm";
const char *password = "1234512345";


unsigned int UDPPort = 2390;                // local port to listen on
const char* host = "192.168.43.177";


int Status_LED = 2;
int packetSize, len, NumText;
String BufferString;
bool ClearStatus;


//char ReplyBuffer[] = "Prasit";


WiFiUDP Udp;



void setup() {

  Serial.begin(9600);


  pinMode(Status_LED, OUTPUT);


  digitalWrite(Status_LED, HIGH);

  delay(500);

  // ******************************************************

  Serial.print("Connecting to :");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
  }

  digitalWrite(Status_LED, LOW);
  delay(2000);

  digitalWrite(Status_LED, HIGH);
  delay(100);

  digitalWrite(Status_LED, LOW);
  delay(200);

  digitalWrite(Status_LED, HIGH);
  delay(100);

  digitalWrite(Status_LED, LOW);
  delay(200);

  //digitalWrite(Status_LED,HIGH);

  Serial.println();
  Serial.print("WiFi UDP Mode : ");
  Serial.println(WiFi.localIP().toString());

  delay(1000);

  digitalWrite(Status_LED, HIGH);


  Udp.begin(UDPPort);

  delay(500);
}




void loop() {




  if (Serial.available()) {

    int Buffer_1;
    byte DataRead[19];
    String BuffDataRead[19];
    byte BufferClear;
    bool BitClear;
    String NameString;


    if (ClearStatus) {

      goto Label_1;
    }

    DataRead[0] = Serial.read();

    if (DataRead[0] == 0x02) {

Label_1:
      ClearStatus = false;

      for (int i = 1; i < 19; i++) {

        while (!(Serial.available())) {

        }

        DataRead[i] = Serial.read();
      }

      if (DataRead[18] == 0x03) {

        if (DataRead[1] == 0x0C) {

          Buffer_1 = DataRead[1] + DataRead[2] + DataRead[3] + DataRead[4] + DataRead[5] + DataRead[6] + DataRead[7] + DataRead[8] + DataRead[9] + DataRead[10] + DataRead[11] + DataRead[12] + DataRead[13] + DataRead[14] + DataRead[15] + DataRead[16];
          if (Buffer_1 == DataRead[17]) {

            BufferString = "";

            for (int i = 0; i < 19; i++) {

              BufferString = BufferString + String(DataRead[i]);
            }

            char StringBuffer[(BufferString.length()) + 1];

            BufferString.toCharArray(StringBuffer, (BufferString.length()) + 1);

            Udp.beginPacket(host, UDPPort);                        //send ip to server
            Udp.write(StringBuffer);
            Udp.endPacket();

          }
        }
      }
    }
    else {

      BitClear = true;

      while (BitClear) {

        unsigned long previousMicros = micros();

        while (!(Serial.available())) {

          unsigned long currentMicros = micros();

          if (currentMicros - previousMicros >= 100) {

            goto Label_2;
          }
        }

        BufferClear = Serial.read();
        if (BufferClear == 0x02) {

          BitClear = false;
          ClearStatus = true;
        }
      }

Label_2:
      BitClear = false;
    }
  }





}
