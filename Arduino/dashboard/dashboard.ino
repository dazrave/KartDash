//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

// Include and setup Display Module
#include <TM1638lite.h>
TM1638lite tm(2, 3, 4);
byte buttons;
int thisChannel = 0;
String lastDisplayedMessage;

void setup()
{
  while(!Serial);
    Serial.begin(9600);
    radio.begin();

  bootUpLEDs();
  thisChannel = channelSelect();

  setupRadio();
}

String receivedCommand;

void loop(void)
{

  //radioSend("1;push");
  //delay(100);

  radioListen();
  delay(100);
  buttonListen();
  delay(100); // End of loop
}







