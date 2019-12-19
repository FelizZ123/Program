
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
  
  digitalWrite(Status_LED,HIGH);
  digitalWrite(LED_1,HIGH);


  delay(500);
  
  // ******************************************************
  
  u8g2.firstPage();
  do {
    
      
  } while ( u8g2.nextPage() );
  

  delay(1000);
  
  // ******************************************************
  
  WiFi.begin(ssid,password);
  
  int i=1;
  while (WiFi.status() != WL_CONNECTED){
    
    delay(500);
    u8g2.firstPage();
    do {

      PrintOLED_Size1(i,2,".");
      
    } while ( u8g2.nextPage() );
    
    i++;
  }

  digitalWrite(Status_LED,LOW);
  delay(2000);

  digitalWrite(Status_LED,HIGH);
  delay(100);

  digitalWrite(Status_LED,LOW);
  delay(200);

  digitalWrite(Status_LED,HIGH);
  delay(100);
    
  digitalWrite(Status_LED,LOW);
  delay(200);

  u8g2.firstPage();
  do {

    PrintOLED_Size2(3,2,"Connected");
    PrintOLED_Size1(2,4,WiFi.localIP().toString());
      
  } while ( u8g2.nextPage() );
  
  delay(2000);  

  digitalWrite(Status_LED,HIGH);
  
  Udp.begin(UDPPort);
  
  u8g2.firstPage();
  do {

    
  } while ( u8g2.nextPage() );
}


      // ######################### OLED ###############################

    //PrintOLED_Size1(Col,Line,s); (9 Pixel Height:  18 Chr, 5 Line)
    //PrintOLED_Size2(Col,Line,s); (11 Pixel Height: 14 Chr, 4 Line)
    //PrintOLED_Size3(Col,Line,s); (13 Pixel Height: 11 Chr, 3 Line)
    //PrintOLED_Size4(Col,Line,s); (15 Pixel Height: 8 Chr, 3 Line)

    //u8g2_font_ncenB10_tr  (11 Pixel Height)
    //u8g2_font_crox4tb_tr  (13 Pixel Height)     
    //u8g2_font_fub35_tn    (number 35 Pixel Height)
    //u8g2_font_fub20_tn    (number 20 Pixel Height)

    //u8g2.drawXBMP(0, 32, cross_width, cross_height, cross_bits);
    //u8g2.setFont(u8g2_font_fub20_tn);     
    //u8g2.drawStr(8,48,"13:30:45"); 
      
    //u8g2.firstPage(); 
    //do {
      
        //
    //} while ( u8g2.nextPage() );



void loop() {

  

      // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Status_Sw1 = digitalRead(Switch_1);
  if(Status_Sw1 == 0){


  }

  while (Status_Sw1 == 0) {

    Status_Sw1 = digitalRead(Switch_1);
  }


    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Status_Sw2 = digitalRead(Switch_2);
  if(Status_Sw2 == 0){


  }

  while (Status_Sw2 == 0) {

    Status_Sw2 = digitalRead(Switch_2);
  }


  // ------------------------------------------------------

  packetSize = Udp.parsePacket();                   // if there's data available, read a packet

  if(Udp.available()){

    int i;
    
    char packetBuffer[packetSize];                      //buffer to hold incoming packet
    len = Udp.read(packetBuffer, packetSize);
    
    if (len > 0){
      
      packetBuffer[len] = 0;
    }

    
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    BufferString = "";
    if(packetBuffer[5] == '0'){
      if(packetBuffer[6] == '0'){

        i = 7;
      }
      else{

        i = 6;
      }
    }
    else{
      
      i = 5;
    }
    
    for (i; i < 8; i++){
      
      BufferString = BufferString + String(packetBuffer[i]);
    }
    
    len = BufferString.length();  
    char StringBuff_1[len+1];
    BufferString.toCharArray(StringBuff_1,len+1);

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    BufferString = "";
    if(packetBuffer[8] == '0'){
      if(packetBuffer[9] == '0'){

        i = 10;
      }
      else{

        i = 9;
      }
    }
    else{
      
      i = 8;
    }
    
    for (i; i < 11; i++){
      
      BufferString = BufferString + String(packetBuffer[i]);
    }
    
    len = BufferString.length();  
    char StringBuff_2[len+1];
    BufferString.toCharArray(StringBuff_2,len+1);

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    BufferString = "";
    if(packetBuffer[11] == '0'){
      if(packetBuffer[12] == '0'){

        i = 13;
      }
      else{

        i = 12;
      }
    }
    else{
      
      i = 11;
    }
    
    for (i; i < 14; i++){
      
      BufferString = BufferString + String(packetBuffer[i]);
    }
    
    len = BufferString.length();  
    char StringBuff_3[len+1];
    BufferString.toCharArray(StringBuff_3,len+1);

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    BufferString = "";

    for (i=3; i < 5; i++){
      
      BufferString = BufferString + String(packetBuffer[i]);
    }
    
    len = BufferString.toInt();
     
    if(len == 78){

      BufferString = "ON";  
    }
    else if(len == 70){

      BufferString = "OFF";    
    }

    len = BufferString.length();  
    char StringBuff_4[len+1];
    BufferString.toCharArray(StringBuff_4,len+1);



        
    u8g2.firstPage();
    do {

      PrintOLED_Size2(1,1,"MistMaker:");
      PrintOLED_Size2(12,1,StringBuff_4);     
      PrintOLED_Size2(1,2,"Fan:    %");
      PrintOLED_Size2(6,2,StringBuff_1);
      PrintOLED_Size2(1,3,"Heater:    %");
      PrintOLED_Size2(9,3,StringBuff_2);
      PrintOLED_Size2(1,4,"Lighting:    %");
      PrintOLED_Size2(11,4,StringBuff_3);
      
    } while ( u8g2.nextPage() );
  }

}




  // ################################################################

void PrintOLED_Size1 (int Col,int Line,String s){
    
  int len;
  
  len = s.length();  
  char StringBuff[len+1];
  s.toCharArray(StringBuff,len+1);

  u8g2.setFont(u8g2_font_t0_13b_tf);

  if(Line == 1){
    if(Col == 1){

      u8g2.drawStr(0,10,StringBuff);
    }
    else{

      u8g2.drawStr((Col-1)*Width_Size1,10,StringBuff);
    }
  }
  else{

    u8g2.drawStr((Col-1)*Width_Size1,((Line-1)*Height_Size1)+10,StringBuff);
  }
}

void PrintOLED_Size2 (int Col,int Line,String s){
    
  int len;
  
  len = s.length();  
  char StringBuff[len+1];
  s.toCharArray(StringBuff,len+1);

  u8g2.setFont(u8g2_font_t0_18b_tf);
  
  if(Line == 1){  
    if(Col == 1){

      u8g2.drawStr(0,12,StringBuff);
    }
    else{

      u8g2.drawStr((Col-1)*Width_Size2,12,StringBuff);
    }
  }
  else{

    u8g2.drawStr((Col-1)*Width_Size2,((Line-1)*Height_Size2)+12,StringBuff);
  }
}

void PrintOLED_Size3 (int Col,int Line,String s){
    
  int len;
  
  len = s.length();  
  char StringBuff[len+1];
  s.toCharArray(StringBuff,len+1);

  u8g2.setFont(u8g2_font_t0_22b_tf);

  if(Line == 1){
    if(Col == 1){

      u8g2.drawStr(0,15,StringBuff);
    }
    else{

      u8g2.drawStr((Col-1)*Width_Size3,15,StringBuff);
    }
  }
  else{

    u8g2.drawStr((Col-1)*Width_Size3,((Line-1)*Height_Size3)+15,StringBuff);
  }
}

void PrintOLED_Size4 (int Col,int Line,String s){
    
  int len;
  
  len = s.length();  
  char StringBuff[len+1];
  s.toCharArray(StringBuff,len+1);

  u8g2.setFont(u8g2_font_courB18_tf);

  if(Line == 1){
    if(Col == 1){

      u8g2.drawStr(0,15,StringBuff);
    }
    else{

      u8g2.drawStr((Col-1)*Width_Size4,15,StringBuff);
    }
  }
  else{

    u8g2.drawStr((Col-1)*Width_Size4,((Line-1)*Height_Size4)+15,StringBuff);
  }
}
