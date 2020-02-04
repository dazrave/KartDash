// Display functions
void sendToScreen(String displayText, int delayAmount, boolean requestAcceptance) {
  tm.displayText(" "); // clear the display
  tm.displayText(displayText); // display the message
  Serial.println("Display: "+displayText); // Debug push to monitor
  delayAmount = delayAmount * 1000; // calculate the actual delay in ms
  if (requestAcceptance == false) {
    delay(delayAmount);
  } else {
    waitForAccept(delayAmount);  
  }
  lastDisplayedMessage = displayText;
  tm.displayText(" "); // clear the display again
  delay(100);
}

void showLastDisplay(){
  sendToScreen(lastDisplayedMessage, 5, false);
  delay(100);
}