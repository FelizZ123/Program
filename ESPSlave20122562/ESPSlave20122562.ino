
#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <Wire.h>
#include <U8g2lib.h>


#define Height_Size1 13
#define Height_Size2 16
#define Height_Size3 21
#define Height_Size4 22
#define Width_Size1 7
#define Width_Size2 9
#define Width_Size3 11
#define Width_Size4 15


#define Status_LED  2
#define Switch_1    14
#define Switch_2    16
#define LED_1       13

/*
  #define GMSlogo_width 24
  #define GMSlogo_height 24
  static const unsigned char GMSlogo_bits[] U8X8_PROGMEM  = {
  0x00, 0x18, 0x00, 0x00, 0x24, 0x00, 0x00, 0x24, 0x00, 0x00, 0x42, 0x00,
  0x00, 0x42, 0x00, 0x00, 0x42, 0x00, 0x00, 0x81, 0x00, 0x00, 0x81, 0x00,
  0xC0, 0x00, 0x03, 0x38, 0x3C, 0x1C, 0x06, 0x42, 0x60, 0x01, 0x42, 0x80,
  0x01, 0x42, 0x80, 0x06, 0x42, 0x60, 0x38, 0x3C, 0x1C, 0xC0, 0x00, 0x03,
  0x00, 0x81, 0x00, 0x00, 0x81, 0x00, 0x00, 0x42, 0x00, 0x00, 0x42, 0x00,
  0x00, 0x42, 0x00, 0x00, 0x24, 0x00, 0x00, 0x24, 0x00, 0x00, 0x18, 0x00, };
*/

//const char* ssid = "GMS-01";
//const char* password = "86390026";
const char *ssid = "mmmm";
const char *password = "1234512345";


unsigned int UDPPort = 2390;                // local port to listen on

int HexToDe = 0;
int Status_Sw1, Status_Sw2;
int packetSize, len, NumText;
String NameString, BufferString;



WiFiUDP Udp;
U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);   // All Boards without Reset of the Display



void setup() {

  Serial.begin(9600);
  Wire.begin();
  u8g2.begin();


  pinMode(Status_LED, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(Switch_1, INPUT);
  pinMode(Switch_2, INPUT);

  digitalWrite(Status_LED, HIGH);
  digitalWrite(LED_1, HIGH);


  delay(500);

  // ******************************************************

  u8g2.firstPage();
  do {


  } while ( u8g2.nextPage() );


  delay(1000);

  // ******************************************************

  WiFi.begin(ssid, password);

  int i = 1;
  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    u8g2.firstPage();
    do {

      PrintOLED_Size1(i, 2, ".");

    } while ( u8g2.nextPage() );

    i++;
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

  u8g2.firstPage();
  do {

    PrintOLED_Size2(3, 2, "Connected");
    PrintOLED_Size1(2, 4, WiFi.localIP().toString());

  } while ( u8g2.nextPage() );

  delay(2000);

  digitalWrite(Status_LED, HIGH);

  Udp.begin(UDPPort);

  u8g2.firstPage();
  do {


  } while ( u8g2.nextPage() );
}

void loop() {
  // put your main code here, to run repeatedly:
  packetSize = Udp.parsePacket();
  if (Udp.available())
  {
    char packetBuffer[packetSize];                      //buffer to hold incoming packet
    len = Udp.read(packetBuffer, packetSize);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
    Serial.println(packetBuffer);
    String Humanity = String(packetBuffer[1]) + String(packetBuffer[2]) + "." + String(packetBuffer[3]);
    String Temp = String(packetBuffer[4]) + String(packetBuffer[5]) + "." + String(packetBuffer[6]);
    String aa = String(packetBuffer[7]);
    String bb = String(packetBuffer[8])+String(packetBuffer[9]);
//    String cc = String(packetBuffer[10])+String(packetBuffer[11]);
//    String dd = String(packetBuffer[12]);
    int a = aa.toInt();
    int b = bb.toInt();
//    int c = cc.toInt();
//    int d = dd.toInt();
    int f = (a*16)+b;
    Serial.println(String(a) + '.' + String(b) + '.' + '.' + String(f));
    u8g2.firstPage();
    do {
      //            PrintOLED_Size2(1,1,"MistMaker:");
      //            PrintOLED_Size2(12,1,StringBuff_4);
      PrintOLED_Size2(3, 1, "Sensor Data");
      // HUMI ===========
      PrintOLED_Size2(1, 2, "Humi:       %");
      PrintOLED_Size2(7, 2, Humanity);
      // TEMP ===========
      PrintOLED_Size2(1, 3, "Temp:       C");
      PrintOLED_Size2(7, 3, Temp);
      // LIGHT ===========
      PrintOLED_Size2(1, 4, "Light:    ");
      PrintOLED_Size2(8, 4, String(f));

    } while ( u8g2.nextPage() );
  }
}






void PrintOLED_Size1 (int Col, int Line, String s)
{
  int len;

  len = s.length();
  char StringBuff[len + 1];
  s.toCharArray(StringBuff, len + 1);

  u8g2.setFont(u8g2_font_t0_13b_tf);

  if (Line == 1) {
    if (Col == 1) {

      u8g2.drawStr(0, 10, StringBuff);
    }
    else {

      u8g2.drawStr((Col - 1)*Width_Size1, 10, StringBuff);
    }
  }
  else {

    u8g2.drawStr((Col - 1)*Width_Size1, ((Line - 1)*Height_Size1) + 10, StringBuff);
  }
}

void PrintOLED_Size2 (int Col, int Line, String s) {

  int len;

  len = s.length();
  char StringBuff[len + 1];
  s.toCharArray(StringBuff, len + 1);

  u8g2.setFont(u8g2_font_t0_18b_tf);

  if (Line == 1) {
    if (Col == 1) {

      u8g2.drawStr(0, 12, StringBuff);
    }
    else {

      u8g2.drawStr((Col - 1)*Width_Size2, 12, StringBuff);
    }
  }
  else {

    u8g2.drawStr((Col - 1)*Width_Size2, ((Line - 1)*Height_Size2) + 12, StringBuff);
  }
}

void PrintOLED_Size3 (int Col, int Line, String s) {

  int len;

  len = s.length();
  char StringBuff[len + 1];
  s.toCharArray(StringBuff, len + 1);

  u8g2.setFont(u8g2_font_t0_22b_tf);

  if (Line == 1) {
    if (Col == 1) {

      u8g2.drawStr(0, 15, StringBuff);
    }
    else {

      u8g2.drawStr((Col - 1)*Width_Size3, 15, StringBuff);
    }
  }
  else {

    u8g2.drawStr((Col - 1)*Width_Size3, ((Line - 1)*Height_Size3) + 15, StringBuff);
  }
}

void PrintOLED_Size4 (int Col, int Line, String s) {

  int len;

  len = s.length();
  char StringBuff[len + 1];
  s.toCharArray(StringBuff, len + 1);

  u8g2.setFont(u8g2_font_courB18_tf);

  if (Line == 1) {
    if (Col == 1) {

      u8g2.drawStr(0, 15, StringBuff);
    }
    else {

      u8g2.drawStr((Col - 1)*Width_Size4, 15, StringBuff);
    }
  }
  else {

    u8g2.drawStr((Col - 1)*Width_Size4, ((Line - 1)*Height_Size4) + 15, StringBuff);
  }
}
