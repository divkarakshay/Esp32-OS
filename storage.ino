void saveGame(int game, int score) {
  prefs.putInt("lastGame", game);
  prefs.putInt("lastScore", score);
}

int getLastGame() {
  return prefs.getInt("lastGame", 0);
}