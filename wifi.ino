int wifiCount;
String ssidList[10];
int rssiList[10];
bool secureList[10];
int wifiIndex=0;

void scanWiFi(){
  WiFi.disconnect();
  wifiCount=WiFi.scanNetworks();

  for(int i=0;i<wifiCount&&i<10;i++){
    ssidList[i]=WiFi.SSID(i);
    rssiList[i]=WiFi.RSSI(i);
    secureList[i]=(WiFi.encryptionType(i)!=WIFI_AUTH_OPEN);
  }
}

void drawRSSI(int x,int y,int r){
  int bars=map(r,-100,-30,0,4);
  for(int i=0;i<bars;i++)
    display.fillRect(x+i*3,y-i*2,2,i*2+2,WHITE);
}

void drawWiFi(){

  int yVal=analogRead(VRY_PIN);
  if(yVal<1000) wifiIndex--;
  if(yVal>3000) wifiIndex++;

  if(wifiIndex<0) wifiIndex=wifiCount-1;
  if(wifiIndex>=wifiCount) wifiIndex=0;

  for(int i=0;i<wifiCount&&i<5;i++){
    int idx=(wifiIndex+i)%wifiCount;
    int y=i*12+12;

    if(i==0){
      display.fillRect(0,y,128,10,WHITE);
      display.setTextColor(BLACK);
    }else display.setTextColor(WHITE);

    display.setCursor(5,y);
    display.print(ssidList[idx]);

    drawRSSI(90,y+8,rssiList[idx]);
    if(secureList[idx]) display.drawRect(110,y,6,6,WHITE);
  }

  if(digitalRead(BTN_SELECT)==LOW){
    selectedSSID=ssidList[wifiIndex];
    inputText="";
    currentScreen=KEYBOARD_SCREEN;
    delay(200);
  }

  display.display();
}