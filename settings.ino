void handleSettings() {

  // Clock Style toggle
  if (selectedIndex == 0) {
    clockMode = !clockMode;
  }

  // Display timeout control
  if (selectedIndex == 1) {
    displayTimeout += 5000;
    if (displayTimeout > 30000)
      displayTimeout = 5000;
  }

  // Sound toggle (placeholder for now)
  if (selectedIndex == 2) {
    // future: enable/disable sound
  }
}