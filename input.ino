void handleInput(){

  int y=analogRead(VRY_PIN);

  if(y<1000){
    selectedIndex--;
    lastActivity = millis();
  }

  if(y>3000){
    selectedIndex++;
    lastActivity = millis();
  }

  if(digitalRead(BTN_SELECT)==LOW){

    lastActivity = millis();

    if(currentScreen==MAIN_MENU){
      if(selectedIndex==0) currentScreen=GAMES_MENU;
      else if(selectedIndex==1){scanWiFi();currentScreen=WIFI_MENU;}
      else if(selectedIndex==2) currentScreen=SETTINGS_MENU;
    }
    else if(currentScreen==GAMES_MENU){
      startGame(selectedIndex);
      currentScreen=GAME_SCREEN;
    }
    else if(currentScreen==SETTINGS_MENU){
      handleSettings();
    }

    delay(200);
  }

  if(digitalRead(BTN_BACK)==LOW){
    lastActivity = millis();
    currentScreen=MAIN_MENU;
    selectedIndex=0;
    delay(200);
  }
}