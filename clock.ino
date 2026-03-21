#include <math.h>

void drawDigitalClock() {
  struct tm t;
  if (!getLocalTime(&t)) return;

  display.setTextSize(2);
  display.setCursor(20, 25);

  if (t.tm_hour < 10) display.print("0");
  display.print(t.tm_hour);
  display.print(":");

  if (t.tm_min < 10) display.print("0");
  display.print(t.tm_min);
}

void drawAnalogClock() {
  struct tm t;
  if (!getLocalTime(&t)) return;

  int cx = 64, cy = 32;

  // Clock circle
  display.drawCircle(cx, cy, 20, WHITE);

  // Hour hand
  float hourAngle = ((t.tm_hour % 12) + t.tm_min / 60.0) * 30 * PI / 180;
  int hx = cx + 10 * cos(hourAngle);
  int hy = cy + 10 * sin(hourAngle);

  // Minute hand
  float minAngle = t.tm_min * 6 * PI / 180;
  int mx = cx + 15 * cos(minAngle);
  int my = cy + 15 * sin(minAngle);

  display.drawLine(cx, cy, hx, hy, WHITE);
  display.drawLine(cx, cy, mx, my, WHITE);
}