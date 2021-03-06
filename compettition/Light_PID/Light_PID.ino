#define Switch_1        13
#define Switch_2        12
#define Heater_On       11
#define Heater_Level    9
#define Lighter         6
#define Fan_On          8
#define Fan_Speed       10
#define Mist_Pump       7
int error = 0;
uint8_t Status_Sw1, Status_Sw2;
byte DataRead[17];
bool ClearStatus;
char Datatran[255];


int base = 200;
float Hu ;
float Tem ;
int a ;
int b ;
int c ;
int Light;

void setup() {
  // put your setup code here, to run once:
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
  analogWrite(Lighter, 255);
  digitalWrite(Fan_On, LOW);
  analogWrite(Fan_Speed, 0);
  digitalWrite(Mist_Pump, LOW);
  ClearStatus = false;

  delay(1000);
}

void loop() {
  Status_Sw1 = digitalRead(Switch_1);
  Status_Sw2 = digitalRead(Switch_2);
  //  if (Status_Sw2 == 0)
  //  {
  //    digitalWrite(7,HIGH);
  //  }
  //  else
  //  {
  //    digitalWrite(7,LOW);
  //  }
  //digitalWrite(7,HIGH);

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

  String Buffer_2 = String(DataRead[0]) + String(DataRead[3]) + String(DataRead[4]) + String(DataRead[5]) + String(DataRead[7]) + String(DataRead[8]) + String(DataRead[9]) + String(DataRead_10) + String(DataRead_11) + String(DataRead[12]) + String(DataRead[13]) +  String(DataRead[14]) + String(DataRead[15]);
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
  //  Serial.println("Humanity = " + String(Hu) + ":" + "Temp = " + String(Tem) + ":" + "Light" + String(Light));
  //  delay(25);
  if (Light <= 1550 && Light >= 1450)
  {
    error = 0;
  }
  if (Light <= 1450 && Light >= 1350)
  {
    error = -1;
  }
  if (Light <= 1350 && Light >= 1250)
  {
    error = -2;
  }
  if (Light <= 1250 && Light >= 1150)
  {
    error = -3;
  }
  if (Light <= 1150)
  {
    error = -4;
  }
  if (Light <= 1650 && Light >= 1550)
  {
    error = 1;
  }
  if (Light <= 1750 && Light >= 1650)
  {
    error = 2;
  }
  if (Light <= 1850 && Light >= 1750)
  {
    error = 3;
  }
  if (Light <= 1950 && Light >= 1850)
  {
    error = 4;
  }
  if ( Light >= 1950)
  {
    error = 5;
  }

  int kp = 2;
  int level = kp * error;;
  base = base - level;
  if (base < 1)
  {
    base = 0;
  }
  if (base > 255)
  {
    base = 254;
  }
  analogWrite(Lighter, base);
  Serial.print("error = " + String(error) + "." + " level = " + String(level) + "base = " + String(base));
  //  digitalWrite(Fan_On, HIGH);
  //  digitalWrite(Heater_On, LOW);
  //
  //  analogWerite(Fan_Speed, 255);
  //  analogWrite(Heater_Level, 255);
  //  analogWrite(Lighter, 255);

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
