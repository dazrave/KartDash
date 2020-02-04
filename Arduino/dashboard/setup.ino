// Setup Functions
int channelSelect() { 
  thisChannel = 0;
  Serial.println("Channel?");
  tm.displayText("CHANNEL?");
  while(thisChannel == 0){
    buttons = tm.readButtons();
    for(int button = 1; button < 9; button++){
       buttons = tm.readButtons();
       if(isButtonBeingPressed(button) && button == 1){
        thisChannel = 1;
        sendToScreen("alpha", 2, false);
        return thisChannel;
       }
       if(isButtonBeingPressed(button) && button == 2){
        thisChannel = 2;
        sendToScreen("bravo", 2, false);
        return thisChannel;
       }
      if(isButtonBeingPressed(button) && button == 3){
        thisChannel = 3;
        sendToScreen("charlie", 2, false);
        return thisChannel;
       }
      if(isButtonBeingPressed(button) && button == 4){
        thisChannel = 4;
        sendToScreen("delta", 2, false);
        return thisChannel;
       }
    }
  }
  delay(100);
  return thisChannel;
}

void setupRadio_OLD(){

  Serial.println("Setting up Radio...");
  while(!Serial);
    Serial.begin(9600);
    radio.begin();

  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(0x76);
  
  radio.openWritingPipe(0xF0F0F0F0E1LL);
  const uint64_t pipe = 0xE8E8F0F0E1LL;
  radio.openReadingPipe(1, pipe);

  radio.enableDynamicPayloads();
  radio.powerUp();

  sendToScreen("READY...", 2, false);
  delay(100);
}

void setupRadio(){
  radio.setPALevel(RF24_PA_MAX);
  //set the address
  radio.openReadingPipe(0, address);
  radio.startListening();
}