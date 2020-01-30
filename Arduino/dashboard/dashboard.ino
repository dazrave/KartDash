// Include and setup Transceiver Module
#include <SPI.h>
#include <nRF24L01.h> // Not needed anymore? worth removing this line
#include <RF24.h>
RF24 radio(9, 8);  // CE, CSN

// #include <EEPROM.h> // Save to memory module

// Include and setup Display Module
#include <TM1638lite.h>
TM1638lite tm(2, 3, 4);
byte buttons;
int thisChannel = 0;
String lastDisplayedMessage;

void setup()
{
  Serial.begin(9600);

  bootUpLEDs();
  thisChannel = channelSelect();
  setupRadio();
}

String receivedCommand;

void loop(void)
{

  radioListen();
  delay(100);
  buttonListen();
  delay(100); // End of loop
}







