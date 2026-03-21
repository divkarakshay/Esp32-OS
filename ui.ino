void drawIcon(int x,int y,int t){
  if(t==0) display.drawRect(x,y,8,8,WHITE);
  if(t==1) display.drawCircle(x+4,y+4,3,WHITE);
  if(t==2) display.drawLine(x,y,x+8,y+8,WHITE);
  if(t==3) display.drawPixel(x+4,y+4,WHITE);
}

void drawMenu(String m[],int size){
  if(selectedIndex<0) selectedIndex=size-1;
  if(selectedIndex>=size) selectedIndex=0;

  smoothIndex+=(selectedIndex-smoothIndex)*0.2;

  for(int i=0;i<size;i++){
    int y=(i*12+12)-(smoothIndex*12);

    if(i==selectedIndex){
      display.fillRect(0,y,128,10,WHITE);
      display.setTextColor(BLACK);
    }else display.setTextColor(WHITE);

    drawIcon(2,y,i);
    display.setCursor(15,y);
    display.println(m[i]);
  }
  display.setTextColor(WHITE);
}

void drawScreen(){
  display.clearDisplay();

  switch(currentScreen){

    case MAIN_MENU: drawMenu(mainMenu,4); break;
    case GAMES_MENU: drawMenu(gamesMenu,3); break;
    case SETTINGS_MENU: drawMenu(settingsMenu,3); break;
    case WIFI_MENU: drawWiFi(); return;
    case KEYBOARD_SCREEN: drawKeyboard(); return;

    case GAME_SCREEN:
      runGame();
      return;
  }

  display.display();
}