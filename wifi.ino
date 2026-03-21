int wifiCount;
String ssid[10];

void scanWiFi(){
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  wifiCount = WiFi.scanNetworks();

  for(int i=0;i<wifiCount && i<10;i++){
    ssid[i]=WiFi.SSID(i);
  }
}

void drawWiFi(){
  for(int i=0;i<wifiCount && i<5;i++){
    display.setCursor(0, i*10+12);
    display.println(ssid[i]);
  }
}