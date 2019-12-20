
#include <Wire.h>


#define DS1307Addr    0x68  

  
#define Switch_1        13
#define Switch_2        12



  uint8_t Status_Sw1, Status_Sw2;
  uint8_t data[7];
  
  
  
void setup(){

  Serial.begin(9600);
  Wire.begin();

  pinMode(Switch_1, INPUT);
  pinMode(Switch_2, INPUT);
  

  delay(1000);

}



void loop(){

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Status_Sw1 = digitalRead(Switch_1);
  if(Status_Sw1 == 0){

    Serial.println("Set RTC");
      
    Wire.beginTransmission(DS1307Addr);             // Send the slave address then the command.
    Wire.write(0x00);                               // 0x0E
  
        // Write the data low byte first.
    Wire.write(0x00);                             // SECONDS
    Wire.write(0x30);                             // MINUTES
    Wire.write(0x13);                             // HOURS
    Wire.write(0x04);                             // DAY
    Wire.write(0x31);                             // DATE
    Wire.write(0x10);                             // MONTH
    Wire.write(0x19);                             // YEAR
    Wire.write(0x00);                             // CONTROL
    
    Wire.endTransmission();
    
    delay(25); 
  }
  while (Status_Sw1 == 0){

    Status_Sw1 = digitalRead(Switch_1);
  }

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Status_Sw2 = digitalRead(Switch_2);
  if(Status_Sw2 == 0){

    Serial.println("Read RTC");
      
    ReadCalendar();

    Serial.print(data[2],HEX);
    Serial.print(":");
    Serial.print(data[1],HEX);
    Serial.print(":");
    Serial.print(data[0],HEX);
    Serial.print("_");
      
    if(data[3] == 1){

      Serial.print("MON");
    }

    else if(data[3] == 2){

      Serial.print("TUE");
    }
    
    else if(data[3] == 3){

      Serial.print("WED");
    }
  
    else if(data[3] == 4){

      Serial.print("THU");
    }

    else if(data[3] == 5){

      Serial.print("FRI");
    }
  
    else if(data[3] == 6){

      Serial.print("SAT");
    }
  
    else if(data[3] == 7){

      Serial.print("SUN");
    }
  
    Serial.print("_");
    Serial.print(data[4],HEX);
    Serial.print("-");
  
    Serial.print(data[5],HEX);
    Serial.print("-");
    Serial.print("20");
    Serial.println(data[6],HEX);
         
    delay(25);
  }
  while (Status_Sw2 == 0){

    Status_Sw2 = digitalRead(Switch_2);
  }
  
}


// -----------------------------------------------------------------------------------

void ReadCalendar(){

  // *********************** Process Read DS1307 **********************************
        
  Wire.beginTransmission(DS1307Addr);                       // Send the slave address then the command
  Wire.write(0x00);                                           // 
  Wire.endTransmission();
  
  Wire.requestFrom(DS1307Addr,7);                           // request 3 bytes from slave device

  while(Wire.available()){
    
    for(int i=0; i<7; i++){

      data[i] = Wire.read();
    }
  }
}
