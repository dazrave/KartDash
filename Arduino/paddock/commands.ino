

void sendCommand(){
  //sendToScreen("Set ALrT", 3, true);
  radioSend("1;push;5");
  sendToScreen("  PUSH  ", 3, true);
  delay(100);
  radioSend("1;push;5");

  // sendToScreen("  PUSH  ", 0, true);

}