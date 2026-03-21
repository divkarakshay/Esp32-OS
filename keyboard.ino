int kbX=0,kbY=0,kbMode=0;

String lower="abcdefghijklmnopqrstuvwxyz";
String upper="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
String nums="0123456789!@#$";

char getKey(){
  String k=(kbMode==0)?lower:(kbMode==1)?upper:nums;
  int idx=kbY*6+kbX;
  if(idx<k.length()) return k[idx];
  return ' ';
}

void drawKeyboard(){

  int x=analogRead(VRX_PIN);
  int y=analogRead(VRY_PIN);

  if(x<1000) kbX--;
  if(x>3000) kbX++;
  if(y<1000) kbY--;
  if(y>3000) kbY++;

  if(kbX<0)kbX=5;if(kbX>5)kbX=0;
  if(kbY<0)kbY=5;if(kbY>5)kbY=0;

  if(digitalRead(BTN_SHIFT)==LOW){
    kbMode=(kbMode+1)%3;
    delay(200);
  }

  display.clearDisplay();
  display.setCursor(0,0);
  display.println(selectedSSID);
  display.println(inputText);

  for(int r=0;r<6;r++){
    for(int c=0;c<6;c++){
      int xx=c*20,yy=r*8+20;

      if(r==kbY&&c==kbX){
        display.fillRect(xx,yy,18,8,WHITE);
        display.setTextColor(BLACK);
      }else display.setTextColor(WHITE);

      display.setCursor(xx+2,yy);
      display.print(getKey());
    }
  }

  if(digitalRead(BTN_SELECT)==LOW){
    inputText+=getKey();
    delay(150);
  }

  if(digitalRead(BTN_BACK)==LOW){
    connectWiFi();
  }

  display.display();
}

void connectWiFi(){
  WiFi.begin(selectedSSID.c_str(),inputText.c_str());
  prefs.putString("ssid",selectedSSID);
  prefs.putString("pass",inputText);
  currentScreen=MAIN_MENU;
}