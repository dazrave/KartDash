// LED Functions
void blinkLED(int LEDNum) {
  const uint8_t LED = LEDNum;
  const uint8_t ON = 1;
  const uint8_t OFF = 0;
  tm.setLED(LED,ON);
  //Serial.println("LED Blink");
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

void bootUpLEDs(){
  tm.reset(); 
  int LED = 0;
  while(LED <= 7){
    LEDon(LED);
    Serial.println("Start Up LED");
    delay(300);
    LED++;
  }
  tm.reset();
}

void allLED(String LEDswitch){
  int n = 0;
  while(n < 8){
    if(LEDswitch == "on"){
      LEDon(n);
    } else {
      LEDoff(n);
    }
    n++;
  }
}


void countDownLEDs(int time){
  allLED("on");
  int LED = 7;
  time = time * 1000;
  int wait = time / LED;

  while(LED <= 7){
    delay(wait);
    LEDoff(LED);
    LED--;
  }
  delay(100);
  return;


}