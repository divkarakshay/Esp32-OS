void drawMenu(String menu[], int size) {
  if (selectedIndex < 0) selectedIndex = size - 1;
  if (selectedIndex >= size) selectedIndex = 0;

  for (int i = 0; i < size; i++) {
    int y = i * 12 + 12;

    if (i == selectedIndex) {
      display.fillRect(0, y, 128, 10, WHITE);
      display.setTextColor(BLACK);
    } else {
      display.setTextColor(WHITE);
    }

    display.setCursor(5, y);
    display.println(menu[i]);
  }

  display.setTextColor(WHITE);
}

void drawScreen() {
  display.clearDisplay();

  display.fillRect(0, 0, 128, 10, WHITE);
  display.setTextColor(BLACK);
  display.setCursor(5, 1);
  display.println("ESP32 BOY");
  display.setTextColor(WHITE);

  switch (currentScreen) {
    case MAIN_MENU:
      drawMenu(mainMenu, 4);
      break;

    case GAMES_MENU:
      drawMenu(gamesMenu, 3);
      break;

    case SETTINGS_MENU:
      drawMenu(settingsMenu, 2);
      break;

    case WIFI_MENU:
      drawWiFi();
      break;

    case INFO_SCREEN:
      display.setCursor(10, 30);
      display.println("Mini OS Ready");
      break;

    case GAME_SCREEN:
      if (selectedGame == 0) { updateSnake(); drawSnake(); }
      if (selectedGame == 1) { updatePong(); drawPong(); }
      if (selectedGame == 2) { updateFlappy(); drawFlappy(); }
      break;
  }

  display.display();
}