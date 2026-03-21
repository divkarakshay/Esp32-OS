void handleInput() {
  int y = analogRead(VRY_PIN);

  if (y < 1000) { selectedIndex--; lastActivity = millis(); }
  if (y > 3000) { selectedIndex++; lastActivity = millis(); }

  if (digitalRead(BTN_SELECT) == LOW) {
    lastActivity = millis();

    if (currentScreen == MAIN_MENU) {
      if (selectedIndex == 0) currentScreen = GAMES_MENU;
      else if (selectedIndex == 1) { currentScreen = WIFI_MENU; scanWiFi(); }
      else if (selectedIndex == 2) currentScreen = SETTINGS_MENU;
      else if (selectedIndex == 3) currentScreen = INFO_SCREEN;

      selectedIndex = 0;
    }
    else if (currentScreen == GAMES_MENU) {
      selectedGame = selectedIndex;
      currentScreen = GAME_SCREEN;

      if (selectedGame == 0) initSnake();
      if (selectedGame == 1) initPong();
      if (selectedGame == 2) initFlappy();
    }

    delay(200);
  }

  if (digitalRead(BTN_BACK) == LOW) {
    lastActivity = millis();
    currentScreen = MAIN_MENU;
    selectedIndex = 0;
    delay(200);
  }
}