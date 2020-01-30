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

void buttonListen(){
  
  buttons = tm.readButtons();
  for(int button = 1; button < 9; button++){
     buttons = tm.readButtons();
     if(isButtonBeingPressed(button) && button == 1){
        //processCommand("pit")
        String channel = String(thisChannel);
        sendToScreen(channel, 2, false);
     }
     if(isButtonBeingPressed(button) && button == 5){
        processCommand("pit");
     }
     if(isButtonBeingPressed(button) && button == 8) {
       showLastDisplay();
     }
     
   }
   
   return;
  
}


void waitForAccept(int waitAmount){
  bool waitForAccept = true;
  unsigned long startTime = millis();

  while (waitForAccept) {
    unsigned long currentTime = millis();
    for(int button = 1; button < 9; button++){
      buttons = tm.readButtons();
      if(isButtonBeingPressed(button) && button == 1){
        waitForAccept = false;
        //const char text[] = "Accepted!";
        //radio.write(text, sizeof(text));
        sendToScreen("ACCEPtED", 1, false);
        break;
      }
    }
    if (currentTime - startTime >= waitAmount) {
      //const char text[] = "No Response";
      //radio.write(text, sizeof(text));
      delay(100);
      break;
    }
    delay(100);
  }


}