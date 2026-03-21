void initSound() {
  ledcSetup(0, 2000, 8);
  ledcAttachPin(BUZZER, 33);
}

void beep(int f, int d) {
  ledcWriteTone(0, f);
  delay(d);
  ledcWriteTone(0, 0);
}

void playEatSound(){ beep(1200,50); }
void playGameOverSound(){ beep(400,200); }