// Include and setup Transceiver Module
#include <SPI.h>
#include <nRF24L01.h> // Not needed anymore? worth removing this line
#include <RF24.h>
RF24 radio(9, 8);  // CE, CSN

//#include <EEPROM.h> // Save to memory module
//#include <Keypad.h> // Setup Keypad
//const byte ROWS = 4; 
//const byte COLS = 3;

//char hexaKeys[ROWS][COLS] = {
//  {'1', '2', '3'},
//  {'4', '5', '6'},
//  {'7', '8', '9'},
//  {'*', '0', '#'}
//};

//byte rowPins[ROWS] = {9, 8, 7, 6}; 
//byte colPins[COLS] = {5, 4, 3}; 

//Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

// Include and setup Display Module
#include <TM1638lite.h>
TM1638lite tm(2, 3, 4);
byte buttons;

int thisChannel = 1; // Default Channel
String lastDisplayedMessage;

void setup()
{
  Serial.begin(9600);

  Serial.println("Starting Up");
  //bootUpLEDs();
  //LEDon(0);
  //LEDoff(1);
  //LEDoff(2);
  //LEDoff(3);

  setupRadio();
}

String receivedCommand;

void loop(void)
{
  //radioListen();
  //delay(50);
  //buttonListen();
  //delay(50);

  radioSend("1;push");
  delay(10000);

  ///char customKey = customKeypad.getKey();
  //if (customKey){
  //  Serial.println(customKey);
  //}
}







