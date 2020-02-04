//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 10);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

void setup()
{
  Serial.flush();
  Serial.begin(9600);

  radio.begin();
  
  //set the address
  radio.openWritingPipe(address);
  
  //Set module as transmitter
  radio.stopListening();
  Serial.println("Ready...");
}
void loop()
{
  //Send message to receiver
  const char text[] = "1;push;5";
  radio.write(&text, sizeof(text));
  Serial.println("Sending...");
  
  delay(20000);
}