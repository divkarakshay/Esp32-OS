// sound.ino

#define BUZZER 33 // Ensure this matches your wiring

void initSound() {
  // New ESP32 Core 3.0+ syntax: ledcAttach(pin, freq, resolution)
  ledcAttach(BUZZER, 2000, 8); 
}

void beep(int f, int d) {
  // New syntax: ledcWriteTone(pin, frequency)
  ledcWriteTone(BUZZER, f);
  delay(d);
  ledcWriteTone(BUZZER, 0);
}

void playEatSound() {
  beep(1200, 50);
}

void playGameOverSound() {
  beep(400, 200);
}