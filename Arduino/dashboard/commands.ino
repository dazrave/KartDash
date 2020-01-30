// Loop functions
void processCommand(String receivedString){

  Serial.println(receivedString);

  String thisMessage;
  //int delay;
  
  String receivedCommand = parseMessage(receivedString,';',1);
  String receivedValue = parseMessage(receivedString,';',2);
  //String receivedDelay = parseMessage(receivedString,';',3);

  if(receivedCommand == "box"){
    sendToScreen("8OX  8OX", 15, true);
  }
  if(receivedCommand == "push"){
    sendToScreen("  PUSH  ", 5, false);
  }
  if(receivedCommand == "blue"){
    sendToScreen("  8LUE  ", 5, false);
  }
  if(receivedCommand == "stint"){
    // sendToScreen("  8LUE  ", 5, false)
    //lastDisplayedMessage = thisMessage;
  }
  if(receivedString == "pit"){
    pitRequester();
  }
  delay(100);
}

void pitRequester(){

  bool waitForAccept = true;
  unsigned long startTime = millis();
  int waitAmount = 20 * 1000;

  String sentMessage = thisChannel+";pitRequest;";

  radioSend(sentMessage); // SEND PIT REQUEST

  tm.displayText("PIt Rqst");
  radio.startListening();
  char receivedMessage[32] = {0};
  
  while (waitForAccept) {
    unsigned long currentTime = millis();

    // WAIT FOR ACKNOWLEDGEMENT

    if (currentTime - startTime >= waitAmount) {
      waitForAccept = false;
      sendToScreen("NO REPLY", 4, false);
      //tm.displayText(" ");
      break;
    }
    if (radio.available()){
      radio.read(receivedMessage, sizeof(receivedMessage));
      String stringMessage(receivedMessage);
      radio.stopListening();

      boolean acceptCommand = processMessage(receivedMessage); // Check who the message is for
      String receivedCommand = parseMessage(receivedMessage,';',1);

      if (acceptCommand && receivedCommand == "pitRequest") {
        sendToScreen("  HOLD  ", 6, false);
        waitForAccept = false;
        break;
      }

 
        

    }
    
    blinkLED(7);
    delay(100);
  }



}