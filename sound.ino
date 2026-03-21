#define BUZZER 33

void initSound() {
  ledcSetup(0, 2000, 8);
  ledcAttachPin(BUZZER, 0);
}

void beep(int freq, int duration) {
  ledcWriteTone(0, freq);
  delay(duration);
  ledcWriteTone(0, 0);
}

void playEatSound() {
  beep(1000, 50);
}

void playGameOverSound() {
  beep(500, 200);
}