#include <SoftwareSerial.h>
#define Switch_1        13
#define Switch_2        12
#define Lighter         6
#define Switch_1        13
#define Switch_2        12
#define Heater_On       11
#define Heater_Level    9
#define Fan_On          8
#define Fan_Speed       10
#define Mist_Pump       7

int zero = 0;
uint8_t Status_Sw1, Status_Sw2;
int error_Hu = 0;
int error_Heater = 0;
int error_Light = 0;
byte DataRead[17];
bool ClearStatus;
char Datatran[255];

int base_Hu = 200;
String base_Huu;
int base_Heater = 200;
String base_Heaterr;
int base_Light = 200;
String base_Lightt;


float Hu ;
float Tem ;
int a ;
int b ;
int c ;
int Light;
SoftwareSerial ESPPort(2, 3);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ESPPort.begin(9600);

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
  ClearStatus = false;

  delay(1000);
}

void loop() {
  delay(100);
  Status_Sw1 = digitalRead(Switch_1);
  Status_Sw2 = digitalRead(Switch_2);
  digitalWrite(Mist_Pump, Status_Sw1);
  CommandReadSensor();
  //  Serial.print("OK");
  //  Serial.print(DataRead[0], HEX );
  //  Serial.print(" ");
  //  Serial.print(DataRead[1], HEX );
  //  Serial.print("  ");
  //  Serial.print(DataRead[2], HEX );
  //  Serial.print(" ");
  //  Serial.print(DataRead[3], HEX );
  //  Serial.print(" ");
  //  Serial.print(DataRead[4], HEX );
  //  Serial.print(" ");
  //  Serial.print(DataRead[5], HEX );
  //  Serial.print("   ");
  //  Serial.print(DataRead[6], HEX );
  //  Serial.print(" ");
  //  Serial.print(DataRead[7], HEX );
  //  Serial.print(" ");
  //  Serial.print(DataRead[8], HEX );
  //  Serial.print("  ");
  //  Serial.print(DataRead[9], HEX );
  //  Serial.print("   ");
  //  Serial.print(DataRead[10], HEX );
  //  Serial.print(" ");
  //  Serial.print(DataRead[11], HEX );
  //  Serial.print(" ");
  //  Serial.print(DataRead[12]);
  //  Serial.print(" ");
  //  Serial.print(DataRead[13], HEX );
  //  Serial.print(" ");
  //  Serial.print(DataRead[14], HEX );
  //  Serial.print(" ");
  //  Serial.println(DataRead[15], HEX );
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

  String Buffer_2;
  String Humanity = String(DataRead[3]) + String(DataRead[4]) + "." + String(DataRead[5]);
  String Temp = String(DataRead[7]) + String(DataRead[8]) + "." + String(DataRead[9]);
  String Light_1 = String(DataRead[10]);
  String Light_2 = String(DataRead_11);
  String Light_3 = String(DataRead[12]);
  Hu = Humanity.toFloat();
  Tem = Temp.toFloat();
  a = Light_1.toInt();
  b = Light_2.toInt();
  c = Light_3.toInt();
  Light = (a * 16 * 16) + (b * 16) + c;
  digitalWrite(Fan_On, HIGH);

  light();
  heater();
  humanity();

  Buffer_2 = base_Huu + base_Heaterr + base_Lightt + String(Status_Sw1);
  Buffer_2.toCharArray(Datatran, 255);
  ESPPort.write(Datatran, 10);
  Serial.println(Buffer_2);
  delay(25);

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

void light()
{
  if (Light <= 1500 && Light >= 1400)
  {
    error_Light = 0;
  }
  if (Light <= 1400 && Light >= 1300)
  {
    error_Light = -1;
  }
  if (Light <= 1300 && Light >= 1200)
  {
    error_Light = -2;
  }
  if (Light <= 1200 && Light >= 1100)
  {
    error_Light = -3;
  }
  if (Light <= 1100)
  {
    error_Light = -4;
  }
  if (Light <= 1600 && Light >= 1500)
  {
    error_Light = 1;
  }
  if (Light <= 1700 && Light >= 1600)
  {
    error_Light = 2;
  }
  if (Light <= 1800 && Light >= 1700)
  {
    error_Light = 3;
  }
  if (Light <= 1900 && Light >= 1800)
  {
    error_Light = 4;
  }
  if ( Light >= 1900)
  {
    error_Light = 5;
  }

  float kp = 0.5;
  int level = kp * error_Light;;
  base_Light = base_Light - level;
  if (base_Light < 1)
  {
    base_Light = 2;
  }
  if (base_Light > 255)
  {
    base_Light = 254;
  }
  analogWrite(Lighter, base_Light);
  if (base_Light < 10)
  {
    base_Lightt = String(zero) + String(zero) + String(base_Light);
  }
  else if (base_Light < 100)
  {
    base_Lightt = String(zero)  + String(base_Light);
  }
  else
  {
    base_Lightt = String(base_Light);
  }
}

void heater()
{
//  if (Tem == 25 )
//  {
//    error_Heater = 0;
//  }
//  if (Tem == 24)
//  {
//    error_Heater = -1;
//  }
//  if (Tem == 23)
//  {
//    error_Heater = -2;
//  }
//  if (Tem == 22)
//  {
//    error_Heater = -3;
//  }
//  if (Tem <= 21 )
//  {
//    error_Heater = -4;
//  }
//  if (Tem == 26)
//  {
//    error_Heater = 1;
//  }
//  if (Tem == 27)
//  {
//    error_Heater = 2;
//  }
//  if (Tem == 28)
//  {
//    error_Heater = 3;
//  }
//  if (Tem == 29)
//  {
//    error_Heater = 4;
//  }
//  if ( Tem >= 30)
//  {
//    error_Heater = 5;
//  }
//
//  int kp = 2;
//  int level = kp * error_Heater;
//  base_Heater = base_Heater - level;
//  //  analogWrite(Lighter, base); //  digitalWrite(Fan_On, HIGH);
//  //  digitalWrite(Heater_On, LOW);
//  //
//  //    analogWrite(Fan_Speed, 255);
//  if (base_Heater < 1)
//  {
//    base_Heater = 2;
//  }
//  if (base_Heater > 255)
//  {
//    base_Heater = 254;
//  }
  analogWrite(Heater_Level, base_Heater);
  if (base_Heater < 10)
  {
    base_Heaterr = String(zero) + String(zero) + String(base_Heater);
  }
  else if (base_Heater < 100)
  {
    base_Heaterr = String(zero)  + String(base_Heater);
  }
  else
  {
    base_Heaterr = String(base_Heater);
  }
}

void humanity()
{
//  if (Hu <= 83 && Hu >= 78)
//  {
//    error_Hu = 0;
//  }
//  if (Hu < 78 && Hu >= 73)
//  {
//    error_Hu = 1;
//  }
//  if (Hu < 73 && Hu >= 68)
//  {
//    error_Hu = 2;
//  }
//  if (Hu < 68 && Hu >= 63)
//  {
//    error_Hu = 3;
//  }
//  if (Hu < 63)
//  {
//    error_Hu = 4;
//  }
//  if (Hu <= 88 && Hu > 83)
//  {
//    error_Hu = -1;
//  }
//  if (Hu <= 93 && Hu > 88)
//  {
//    error_Hu = -2;
//  }
//  if (Hu <= 98 && Hu > 93)
//  {
//    error_Hu = -3;
//  }
//  if (Hu <= 99 && Hu > 98)
//  {
//    error_Hu = -4;
//  }
//  if ( Hu >= 99)
//  {
//    error_Hu = -5;
//  }
//
//  int kp = 2;
//  int level = kp * error_Hu;;
//  base_Hu = base_Hu - level;
//  digitalWrite(Fan_On, HIGH);
//  //  digitalWrite(Heater_On, LOW);
//  //
//  if (base_Hu < 1)
//  {
//    base_Hu = 2;
//  }
//  if (base_Hu > 255)
//  {
//    base_Hu = 254;
//  }
  analogWrite(Fan_Speed, base_Hu);
  if (base_Hu < 10)
  {
    base_Huu = String(zero) + String(zero) + String(base_Hu);
  }
  else if (base_Hu < 100)
  {
    base_Huu = String(zero)  + String(base_Hu);
  }
  else
  {
    base_Huu = String(base_Hu);
  }
}
