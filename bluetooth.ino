void initBluetooth(){
  bleGamepad.begin();
}

void sendBTControls(){
  if(!bleGamepad.isConnected()) return;

  int x=map(analogRead(VRX_PIN),0,4095,-32767,32767);
  int y=map(analogRead(VRY_PIN),0,4095,-32767,32767);

  bleGamepad.setLeftThumb(x,y);

  if(digitalRead(BTN_SELECT)==LOW)
    bleGamepad.press(BUTTON_1);
  else
    bleGamepad.release(BUTTON_1);
}