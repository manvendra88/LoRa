/*
  LoRa Simple Arduino Server :
  Support Devices: 
  * LoRa Mini
  * LoRa Shield + Arduino;
  * LoRa GPS Shield + Arduino. 
  
  Example sketch showing how to create a simple messageing server, 
  with the RH_RF95 class. RH_RF95 class does not provide for addressing or
  reliability, so you should only use RH_RF95 if you do not need the higher
  level messaging abilities.

  It is designed to work with the other example LoRa Simple Client

  modified 16 11 2016
  by Edwin Chen <support@dragino.com>
  Dragino Technology Co., Limited
*/

#include <SPI.h>
#include <RH_RF95.h>

// Singleton instance of the radio driver
RH_RF95 rf95;
int crc;
int led = A2;
float frequency = 868.0;

int8_t arr[50],i;
void setup() 
{
  pinMode(led, OUTPUT);     
  Serial.begin(9600);
 // while (!Serial) ; // Wait for serial port to be available
  Serial.println("Start Sketch");
  if (!rf95.init())
    Serial.println("init failed");
  // Setup ISM frequency
  rf95.setFrequency(frequency);
  // Setup Power,dBm
  rf95.setTxPower(13);
  rf95.setSpreadingFactor(7);
  
  // Defaults BW Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
  Serial.print("Listening on frequency: ");
  Serial.println(frequency);
}

void loop()
{
  if (rf95.available())
  {
    // Should be a message for us now   
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf95.recv(buf, &len))
    {
      digitalWrite(led, HIGH);
      RH_RF95::printBuffer("request: ", buf, len);
      Serial.print("got request: ");
      Serial.println(buf[0]);
      Serial.println(buf[1]);
      Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC);


      
      arr[i]=rf95.lastRssi();
      arr[i+20]=rf95.packetSnr();
      arr[i+30]=buf[1];
      i++;
    
      if(i==900) //if(i%10==0)
      {
      // Send a reply
      i=0;
      rf95.send(arr, sizeof(arr));
      rf95.waitPacketSent();
      Serial.println("Sent a reply");
      digitalWrite(led, LOW);
      }
    }
    else
    {
      Serial.println("recv failed");
    }
  }
}


