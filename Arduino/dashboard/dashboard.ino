// Include and setup Transceiver Module
#include <SPI.h>
// #include <nRF24L01.h> // Not needed anymore? worth removing this line
#include <RF24.h>
RF24 radio(9, 8);  // CE, CSN

// Include and setup Display Module
#include <TM1638lite.h>
TM1638lite tm(2, 3, 4);
byte buttons;


//address through which two modules communicate.
// const byte addresses[][6] = {"00001", "00002"}; // More unused/old code!

void setup()
{
  Serial.begin(9600);
  bootUpLEDs();
  int thisTeam = teamSelect();
  setupRadio(thisTeam);
}

void loop(void)
{
  string receivedCommand = radioListen();
  commandActions(receivedCommand);
  readButtons();
  delay(500); // End of loop
}


// Setup Functions
void bootUpLEDs(){
  tm.reset(); 
  int LED = 0;
  while(LED <= 7){
    LEDon(LED);
    delay(300);
    LED++;
  }
  tm.reset();
}

int teamSelect() {
  int thisTeam = 0;
  while(thisTeam == 0){
    tm.displayText(" A or 8 ");
    buttons = tm.readButtons();
    for(int button = 1; button < 9; button++){
       buttons = tm.readButtons();
       if(isButtonBeingPressed(button) && button == 1){
        thisTeam = 1;
        sendToScreen("alpha", 2, false);
        break;
       }
       if(isButtonBeingPressed(button) && button == 8){
        thisTeam = 2;
        sendToScreen("bravo", 2, false);
        break;
       }
    }
  }
  return thisTeam;
}

void setupRadio(int thisTeam){
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
  delay(500);
  sendToScreen("READY...", 2, false);
}

// Loop functions
void commandActions(string receivedString){
  tm.displayText(" "); // reset display only
  String receivedCommand = parseMessage(receivedString,';',0);
  String receivedValue = parseMessage(receivedString,';',1);
  if(receivedCommand == "box"){
    sendToScreen("80X  8OX", 15, true);
  }
  if(receivedCommand == "push"){
    sendToScreen("  PUSH  ", 5, false);
  }
  if(receivedCommand == "blue"){
    sendToScreen("  8LUE  ", 5, false);
  }
  if(receivedCommand == "stint"){
    // sendToScreen("  8LUE  ", 5, false)
  }
}

String parseMessage(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

// Radio functions
string radioListen(){
  radio.startListening();
  char receivedMessage[32] = {0};
  if (radio.available()){
    blinkLED(0); // blink led 0 to show something was recieved
    radio.read(receivedMessage, sizeof(receivedMessage));
    radio.stopListening();
    String stringMessage(receivedMessage);
    radioSend(receivedMessage); // Send message back to confirm it arrived
    return receivedMessage;
  }
}
void radioSend(string receivedMessage){
  const char text[] = receivedMessage;
  radio.write(text, sizeof(text));
  blinkLED(1); // blink led 1 to show something was sent
}

// Display functions
void sendToScreen(String displayText, int delayAmount, boolean requestAcceptance) {
  tm.displayText(" "); // clear the display
  tm.displayText(displayText); // display the message
  Serial.println(displayText); // Debug push to monitor
  delayAmount = delayAmount * 1000; // calculate the actual delay in ms
  if (requestAcceptance == false) {
    delay(delayAmount);
  } else {
    waitForAccept(delayAmount);  
  }
  tm.displayText(" "); // clear the display again
  delay(100);
}

// Button functions
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
readButtons(){
  buttons = tm.readButtons();
  for(int button = 1; button < 9; button++){
     buttons = tm.readButtons();
     if(isButtonBeingPressed(button) && button == 5){
        const char text[] = "pit request!";
        radio.write(text, sizeof(text));
        delay(100);
        LEDon(0);
        delay(100);
        sendToScreen("request", 2, false);
     }
   }
}
void waitForAccept(int waitAmount){
  bool waitForAccept = true;
  unsigned long startTime = millis();
  while (waitForAccept) {
    for(int button = 1; button < 9; button++){
      buttons = tm.readButtons();
      if(isButtonBeingPressed(button) && button == 5){
        waitForAccept = false;
        const char text[] = "Accepted!";
        radio.write(text, sizeof(text));
        sendToScreen("ACCEPtED", 1, false);
      }
      if (currentTime - startTime >= waitAmount) {
        const char text[] = "No Response";
        radio.write(text, sizeof(text));
        break;
      }
    }
    unsigned long currentTime = millis();
  }
}


// LED Functions
void blinkLED(int LEDNum) {
  const uint8_t LED = LEDNum;
  const uint8_t ON = 1;
  const uint8_t OFF = 0;
  tm.setLED(LED,ON);
  delay(200);
  tm.setLED(LED,OFF);
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
