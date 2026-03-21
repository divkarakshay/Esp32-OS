void handleSettings() {
  if (selectedIndex == 0) {
    clockMode = !clockMode;
  }
  if (selectedIndex == 1) {
    displayTimeout += 5000;
    if (displayTimeout > 30000) displayTimeout = 5000;
  }
}