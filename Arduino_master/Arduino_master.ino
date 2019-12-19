

#include <SoftwareSerial.h>

  
#define Switch_1        13
#define Switch_2        12



  uint8_t Status_Sw1, Status_Sw2;
  uint8_t VHeat, VLight, VFan;
  String SerialRecieve, SoftwareRecieve;
  byte Mist, Data0, Data1, Data2, DataF0, DataF1, DataF2, DataH0, DataH1, DataH2, Temp4, Temp3, Temp2, Temp1, Temp0;
 
 
  
  SoftwareSerial ESPPort(2,3);

  
  
void setup(){

  Serial.begin(9600);
  ESPPort.begin(9600);
  

  pinMode(Switch_1, INPUT);
  pinMode(Switch_2, INPUT);
  
  delay(1000);

}


  
void loop(){

  
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Status_Sw1 = digitalRead(Switch_1);
  if(Status_Sw1 == 0){

    CommandSendData(255, 127, 20, 'F');

    delay(25); 
  }
  while (Status_Sw1 == 0){

    Status_Sw1 = digitalRead(Switch_1);
  }
  
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Status_Sw2 = digitalRead(Switch_2);
  if(Status_Sw2 == 0){

      
    delay(25);
  }
  while (Status_Sw2 == 0){

    Status_Sw2 = digitalRead(Switch_2);
  }


}



  // *************************************************************

void BytetoPersent(uint8_t NuM){

  int TextNum;
  uint8_t result;
  String StringBuff;
  byte b1;
  
  
  result = (NuM * 100) / 255;
  StringBuff = String(result);
  TextNum = StringBuff.length();

  char DataString[TextNum+1];
  StringBuff.toCharArray(DataString,TextNum+1);

  if(TextNum == 3){

    b1 = byte(DataString[0]);
    Data2 = b1 & 0x0F;
    b1 = byte(DataString[1]);
    Data1 = b1 & 0x0F;
    b1 = byte(DataString[2]);
    Data0 = b1 & 0x0F;
  }
  else if(TextNum == 2){

    Data2 = 0x00;
    b1 = byte(DataString[0]);
    Data1 = b1 & 0x0F;
    b1 = byte(DataString[1]);
    Data0 = b1 & 0x0F;
  }
  else if(TextNum == 1){

    Data2 = 0x00;
    Data1 = 0x00;
    b1 = byte(DataString[0]);
    Data0 = b1 & 0x0F;
  }
}



  // *************************************************************
void CommandSendData(uint8_t F, uint8_t H, uint8_t L, byte M){

  int Buffer_1;
  byte CommandSend[19];
  String BuffDataRead[19];
  
  
  CommandSend[0] = 0x02;
  CommandSend[1] = 0x0C;

  CommandSend[2] = M;

  BytetoPersent(F);
  DataF2 = Data2;
  DataF1 = Data1;
  DataF0 = Data0;
  CommandSend[3] = DataF2;
  CommandSend[4] = DataF1;
  CommandSend[5] = DataF0;
              
  BytetoPersent(H);
  DataH2 = Data2;
  DataH1 = Data1;
  DataH0 = Data0;
  CommandSend[6] = DataH2;
  CommandSend[7] = DataH1;
  CommandSend[8] = DataH0;
   
  BytetoPersent(L);
  CommandSend[9] = Data2;
  CommandSend[10] = Data1;
  CommandSend[11] = Data0;
   
  CommandSend[12] = 0x00;
  CommandSend[13] = 0x00;
  CommandSend[14] = 0x00;
  CommandSend[15] = 0x00; 
  CommandSend[16] = 0x00;

  Buffer_1 = 0x0C + M + DataF2 + DataF1 + DataF0 + DataH2 + DataH1 + DataH0 + Data2 + Data1 + Data0 + 0x00 + 0x00 + 0x00 + 0x00 + 0x00;
  CommandSend[17] = Buffer_1;

  CommandSend[18] = 0x03;

  ESPPort.write(CommandSend, 19);                              
}
