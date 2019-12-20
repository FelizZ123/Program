#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

const char *ssid = "mmmm";
const char *password = "1234512345";

unsigned int UDPPort = 2390;                // local port to listen on
const char* host = "192.168.137.67";

int Status_LED = 2;
int packetSize, len, NumText;
String BufferString;
bool ClearStatus;
char Data[255];

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
  Serial.println();
  Serial.print("WiFi UDP Mode : ");
  Serial.println(WiFi.localIP().toString());
  delay(1000);
  digitalWrite(Status_LED, HIGH);
  Udp.begin(UDPPort);
  delay(500);
}

void loop() {
  if (Serial.available())
  {
    String Buffer_1;
    char DataRead[14];
    Buffer_1 = Serial.readString();
    Serial.println(Buffer_1);
    Buffer_1.toCharArray(DataRead, 14);
    Udp.beginPacket(host, UDPPort);                        //send ip to server
    Udp.write(DataRead);
    Udp.endPacket();
  }
}
