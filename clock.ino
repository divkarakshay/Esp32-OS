#include <math.h>

int hours = 10;
int minutes = 30;

void drawDigitalClock() {
  display.setTextSize(2);
  display.setCursor(20, 25);
  display.print(hours);
  display.print(":");
  if (minutes < 10) display.print("0");
  display.print(minutes);
}

void drawAnalogClock() {
  int cx = 64, cy = 32;

  display.drawCircle(cx, cy, 20, WHITE);

  float angle = (hours % 12) * 30 * PI / 180;
  int hx = cx + 10 * cos(angle);
  int hy = cy + 10 * sin(angle);

  display.drawLine(cx, cy, hx, hy, WHITE);
}