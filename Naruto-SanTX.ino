/*
  LoRa Simple Client for Arduino :
  Support Devices: LoRa Shield + Arduino 
  
  Example sketch showing how to create a simple messageing client, 
  with the RH_RF95 class. RH_RF95 class does not provide for addressing or
  reliability, so you should only use RH_RF95 if you do not need the higher
  level messaging abilities.

  It is designed to work with the other example LoRa Simple Server
  User need to use the modified RadioHead library from:
  https://github.com/dragino/RadioHead

  modified 16 11 2016
  by Edwin Chen <support@dragino.com>
  Dragino Technology Co., Limited
*/

#include <SPI.h>
#include <RH_RF95.h>

// Singleton instance of the radio driver
RH_RF95 rf95;
float frequency = 868.0;
uint8_t data[10];
int counter;

int row,x;
void setup() 
{
  Serial.begin(9600);
  
  Serial.println("Start LoRa Client");
  if (!rf95.init())
    Serial.println("init failed");
  
  rf95.setFrequency(frequency);
  
  rf95.setTxPower(13);

  
  rf95.setSpreadingFactor(7);
  
  
  rf95.setSignalBandwidth(125000);
  
  
  rf95.setCodingRate4(5);

      Serial.println("CLEARDATA");
  Serial.println("LABEL,Time,X,Y,Z,R");
}

void loop()
{
  Serial.println("Let's send to Gateway");
  
  data[0] = 1;
  data[1]=counter;
  counter++;

  if(counter==127)
  counter=0;

  
  rf95.send(data, sizeof(data));
  
  rf95.waitPacketSent();
  // Now wait for a reply
  int8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  if (rf95.waitAvailableTimeout(2000))
  { 
    // Should be a reply message for us now   
    if (rf95.recv(buf, &len))
   {
      Serial.print("got reply: ");
      for(int i=0;i<10;i++)
      {
      Serial.print(i);
      Serial.print(buf[i]);
      Serial.print(buf[i+20]);
      Serial.println(buf[i+30]);
      int X_out=i;
      int Y_out=buf[i];
      int Z_out=buf[i+20];
      int R_out=buf[i+30];
      
      Serial.print("DATA,TIME,"); Serial.print(X_out); Serial.print(","); Serial.print(Y_out); Serial.print(","); Serial.print(Z_out);Serial.print(","); Serial.println(R_out);                        
      row++;
      x++;
      }
      Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC);    
    }

  }

}


