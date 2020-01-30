// Include and setup Transceiver Module
#include <SPI.h>
#include <nRF24L01.h> // Not needed anymore? worth removing this line
#include <RF24.h>
RF24 radio(9, 8);  // CE, CSN

// Include and setup Display Module
#include <TM1638lite.h>
TM1638lite tm(2, 3, 4);
byte buttons;
int thisChannel;
String lastDisplayedMessage;

void setup()
{
  Serial.begin(9600);
  //sendToScreen("P15 S1:13", 5, false);
  //sendToScreen(" DEFEND ", 3, false);
  //sendToScreen("STAY OUT", 3, false);
  //sendToScreen("CHILLOUT", 3, false);
  //sendToScreen("CHECFUEL", 3, false);
  //sendToScreen("CHEC  IN", 3, false);
  //sendToScreen("8OX SOON", 3, false);
  //sendToScreen("8OX  8OX", 3, false);
  //sendToScreen("  8LUE  ", 3, false);
  //sendToScreen("  PUSH  ", 3, false);

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







