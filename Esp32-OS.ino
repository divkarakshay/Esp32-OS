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

// State
enum ScreenState { MAIN_MENU, GAMES_MENU, SETTINGS_MENU, WIFI_MENU, INFO_SCREEN, GAME_SCREEN };
ScreenState currentScreen = MAIN_MENU;

int selectedIndex = 0;
int selectedGame = 0;

// Preferences
Preferences prefs;
int highScore = 0;

// Menu
String mainMenu[] = {"Games", "WiFi", "Settings", "Info"};
String gamesMenu[] = {"Snake", "Pong", "Flappy"};

// Function declarations
void drawMenu(String menu[], int size);
void handleInput();
void drawScreen();

// External functions
void initSnake();
void updateSnake();
void drawSnake();

void initPong();
void updatePong();
void drawPong();

void initFlappy();
void updateFlappy();
void drawFlappy();

void scanWiFi();
void drawWiFi();

void setup() {
  Serial.begin(115200);

  pinMode(BTN_SELECT, INPUT_PULLUP);
  pinMode(BTN_BACK, INPUT_PULLUP);

  Wire.begin(21, 22);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // Boot screen
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(10, 20);
  display.println("ESP32");
  display.setCursor(10, 40);
  display.println("BOY");
  display.display();
  delay(1500);

  prefs.begin("game", false);
  highScore = prefs.getInt("high", 0);
}

void loop() {
  handleInput();
  drawScreen();
}