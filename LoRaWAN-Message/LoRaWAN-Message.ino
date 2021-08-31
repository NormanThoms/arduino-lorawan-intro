#include <MKRWAN.h>
#include "arduino_secrets.h"

LoRaModem modem;

void setup() {  
  Serial.begin(9600);
  while (!Serial);
   
  // change this to your regional band (eg. US915, AS923, ...)
  if (!modem.begin(US915)) {
    Serial.println("Failed to start module");
    while (1) {}
  };
  
  Serial.print("Your module version is: ");
  Serial.println(modem.version());
  Serial.print("Arduino FW VERSION: ");
  Serial.println(ARDUINO_FW_VERSION);
   
  if (modem.version() != ARDUINO_FW_VERSION) {
    Serial.println("Please make sure that the latest modem firmware is installed.");
    Serial.println("To update the firmware upload the 'MKRWANFWUpdate_standalone.ino' sketch.");
  }
  
  Serial.print("Your device EUI is: ");
  Serial.println(modem.deviceEUI());

  // Enable US915-928 channels
  // LoRaWAN® Regional Parameters and TTN specification: channels 8 to 15 plus 65 
  modem.sendMask("ff000001f000ffff00020000");
  Serial.println(modem.getChannelMask());
  modem.setADR(true);

  Serial.println("Connecting...");
  int connected = modem.joinOTAA(APP_EUI, APP_KEY);

  if (!connected) {
    Serial.println("Something went wrong; are you indoor? Move near a window and retry");
    while (1) {}
  }

  delay(5000);

  Serial.println("Sending message...");
  modem.setPort(3);
  modem.beginPacket();
  modem.print("Hello");
    
  int error = modem.endPacket(true);
  
  if (error > 0) {
    Serial.println("Message sent correctly!");
  } else {
    Serial.println("Error sending message :(");
  }
}

void loop() {
}