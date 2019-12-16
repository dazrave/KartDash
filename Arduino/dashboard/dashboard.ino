// Transmit
#include <SPI.h>
// #include <nRF24L01.h>
#include <RF24.h>
//create an RF24 object
RF24 radio(9, 8);  // CE, CSN

// Display
#include <TM1638lite.h>
TM1638lite tm(2, 3, 4);
byte buttons;

//address through which two modules communicate.
const byte addresses[][6] = {"00001", "00002"};

void setup()
{
  tm.reset();

  int LED = 0;
  while(LED <= 7){
    LEDon(LED);
    delay(300);
    LED++;
  }
  tm.reset();

  int thisTeam = 0;

  while(thisTeam == 0){
    tm.displayText(" A or 8 ");
    buttons = tm.readButtons();
    for(int button = 1; button < 9; button++){
       buttons = tm.readButtons();
       if(isButtonBeingPressed(button) && button == 1){
        thisTeam = 1;
        pushText("alpha", 2000);
        break;
       }
       if(isButtonBeingPressed(button) && button == 8){
        thisTeam = 2;
        pushText("bravo", 2000);
        break;
       }
    }
  }
  
  while(!Serial);
  Serial.begin(9600);

  radio.begin();
  radio.setPALevel(RF24_PA_MAX);

  if(thisTeam == 1){
    radio.setChannel(0x75);
    radio.openWritingPipe(0xF0F0F0F0E1LL);
    const uint64_t pipe = 0xE8E8F0F0E1LL;
    radio.openReadingPipe(1, pipe);
  } else {
    radio.setChannel(0x76);
    radio.openWritingPipe(0xF0F0F0F0E1LL);
    const uint64_t pipe = 0xE8E8F0F0E1LL;
    radio.openReadingPipe(1, pipe);
  }
  
  radio.enableDynamicPayloads();
  radio.powerUp();
  
  //set the address
  //radio.openWritingPipe(addresses[1]);
  //radio.openReadingPipe(1, addresses[0]);
  
  //Set module as transmitter
  //radio.stopListening();
  delay(500);
  pushText("READY...", 1500);


}



void loop(void)
{


  

  
  buttons = tm.readButtons();
  for(int button = 1; button < 9; button++){
     buttons = tm.readButtons();
     if(isButtonBeingPressed(button) && button == 5){
        const char text[] = "pit request!";
        radio.write(text, sizeof(text));
        delay(100);
        LEDon(0);
        delay(100);
        pushText("request", 2000);
     }
   }



  
  radio.startListening();
  char receivedMessage[32] = {0};
  if (radio.available()){
    radio.read(receivedMessage, sizeof(receivedMessage));
    radio.stopListening();
    blinkLED(0);
    String stringMessage(receivedMessage);

    if(stringMessage == "BOX"){
      tm.reset();
      tm.displayText("80X  8OX");
      bool waitForAccept = true;
      while (waitForAccept) {
        for(int button = 1; button < 9; button++){
           buttons = tm.readButtons();
           if(isButtonBeingPressed(button) && button == 5){
              waitForAccept = false;
              const char text[] = "box accepted!";
              radio.write(text, sizeof(text));
              pushText("ACCEPtED", 500);
           }
         }
      }
    }

    
    if(stringMessage == "GETSTRING"){
      pushText("received", 1000);
      const char text[] = "hello world!";
      radio.write(text, sizeof(text));
      pushText("reply", 1000);
    }
  }

  delay(500);
  
}

void pushText(String displayText, int delayAmount) {
  tm.displayText(" ");
  tm.displayText(displayText);
  delay(delayAmount);
  tm.displayText(" ");
  delay(500);
}

void blinkLED(int LEDNum) {
  tm.reset();
  const uint8_t LED = LEDNum;
  const uint8_t ON = 1;
  const uint8_t OFF = 0;
  tm.setLED(LED,ON);
  delay(500);
  tm.setLED(LED,OFF);
  delay(500);
  tm.reset();
}

void LEDon(int LEDNum) {
  const uint8_t LED = LEDNum;
  const uint8_t ON = 1;
  tm.setLED(LED,ON);
}
void LEDoff(int LEDNum) {
  const uint8_t LED = LEDNum;
  const uint8_t OFF = 0;
  tm.setLED(LED,OFF);
}

void doLEDs(uint8_t value) {
  for (uint8_t position = 0; position < 8; position++) {
    tm.setLED(position, value & 1);
    value = value >> 1;
  }
  
}

// This function will return true if a particular button n is currently being pressed.
boolean isButtonBeingPressed(int n){
 // Button 1 status shown by bit0 of the byte buttons returned by module.getButtons()
 // Button 2 status shown by bit1 or the byte buttons ...
 // Button 3 status shown by bit2...etc

 // n - the number of the button to be tested) should be an integer from 1 to 8
 if(n < 1 or n > 8) return false;

 // Read in the value of getButtons from the TM1638 module.
 buttons = tm.readButtons();

 // Which bit must we test for this button?
 int bitToLookAt = n - 1;

 // Read the value of the bit - either a 1 for button pressed, or 0 for not pressed.
 byte theValueOfTheBit = bitRead(buttons, bitToLookAt);

 // If the button is pressed, return true, otherwise return false.
 if(theValueOfTheBit == 1) 
   return true;
 else 
   return false;
}
