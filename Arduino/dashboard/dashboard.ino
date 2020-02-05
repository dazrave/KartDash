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

// General setup
int thisChannel = 0;
String lastDisplayedMessage;
String receivedCommand;

// Heart beat setup
int pulse = 900000; // 1 pulse every 15 minutes (set in ms)
unsigned long heartBeatStart = millis(); // start heartbeat timer

void setup()
{
  while(!Serial);
    Serial.begin(9600);
    radio.begin();

  bootUpLEDs(); // Show loading LEDs
  thisChannel = channelSelect(); // Ask user to set channel
  setupRadio(); // Setup the radio
}

void loop(void)
{

  radioListen();  // Get radio commands
  delay(50);
  buttonListen(); // Get button commands
  delay(50);
  heartBeat(); // Occasionally reply to show we're still working
  
}

void heartBeat() {

  unsigned long currentTime = millis(); // get current time
  if (currentTime - heartBeatStart >= pulse) {
    heartBeatStart = millis(); // restart heartbeat timer
    radioSend("p;pulse;"+thisChannel); // Send a heartbeat
  }
  
}

