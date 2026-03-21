#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <Preferences.h>

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pins
#define VRX_PIN 34
#define VRY_PIN 35
#define BTN_SELECT 32
#define BTN_BACK 25
#define BUZZER 33

// State
enum ScreenState { MAIN_MENU, GAMES_MENU, SETTINGS_MENU, WIFI_MENU, INFO_SCREEN, GAME_SCREEN };
ScreenState currentScreen = MAIN_MENU;

int selectedIndex = 0;
int selectedGame = 0;

// Preferences
Preferences prefs;
int highScore = 0;

// Idle
unsigned long lastActivity = 0;
int displayTimeout = 10000;
bool dimmed = false;

// Clock
int clockMode = 0;

// Menus
String mainMenu[] = {"Games", "WiFi", "Settings", "Info"};
String gamesMenu[] = {"Snake", "Pong", "Flappy"};
String settingsMenu[] = {"Clock Style", "Timeout"};

void setup() {
  Serial.begin(115200);

  pinMode(BTN_SELECT, INPUT_PULLUP);
  pinMode(BTN_BACK, INPUT_PULLUP);

  Wire.begin(21, 22);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(10, 20);
  display.println("ESP32 BOY");
  display.display();
  delay(1500);

  prefs.begin("game", false);
  highScore = prefs.getInt("high", 0);

  initSound();
  lastActivity = millis();
}

void loop() {

  if (millis() - lastActivity > displayTimeout) dimmed = true;
  else dimmed = false;

  display.ssd1306_command(SSD1306_SETCONTRAST);
  display.ssd1306_command(dimmed ? 10 : 255);

  if (dimmed) {
    display.clearDisplay();
    if (clockMode == 0) drawDigitalClock();
    else drawAnalogClock();
    display.display();
    return;
  }

  handleInput();
  drawScreen();
}