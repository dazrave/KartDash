// Radio functions
void radioListen(){

  ///Serial.println("radioListen()");
  radio.startListening();
  char receivedMessage[32] = {0};

  //blinkLED(0); // Blink LED-0 to show we're listening for a command

  if (radio.available()){

    blinkLED(1); // Blink LED-1 to show we've received a message
    
    radio.read(receivedMessage, sizeof(receivedMessage));
    String stringMessage(receivedMessage);
    radio.stopListening();
    if(receivedMessage){
      boolean acceptCommand = processMessage(receivedMessage); // Check who the message is for
      if (acceptCommand) {
        //processCommand(receivedMessage);
      }
    }

    
    
    delay(100);
    return;
  }
}

boolean processMessage(String receivedMessage) {

    //const char acknowledgeMessage = receivedMessage;
    const char* acknowledgeMessage = receivedMessage.c_str();
    String destination = parseMessage(receivedMessage,';',0);
    Serial.println("Heard: "+receivedMessage);
    Serial.println("Intended for: "+destination);
    
    Serial.println(destination);

    if (destination.toInt() == 0 || destination.toInt() == thisChannel) {
      // Send acknowledgement message back
      //const char text[] = {acknowledgeMessage};

      //const char text[] = thisChannel;
      const char*text = receivedMessage.c_str()
      ;

      int i = 0;
      while(i <= 3){ // Send acknowledgement a few times just to be sure
        //radio.write(text, sizeof(text));
        radio.write(text, strlen(text));
        //Serial.println("Blink LED 2");
        blinkLED(2); // blink led 2 to show something was sent
        delay(50);
        i++;
      }

      delay(100);
      return true;
    }
}

void radioSend(String message){
  radio.stopListening();
  const char*text = message.c_str();
  radio.write(&text, sizeof(text));
  Serial.println("Sending: "+message);
  delay(1000);
  radio.startListening();
  //blinkLED(5); // blink led 5 to show something was sent
  //delay(100);
  //blinkLED(5);
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
  delay(100);
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}