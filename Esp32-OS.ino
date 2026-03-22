#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <Preferences.h>
#include <BleGamepad.h>
#include "time.h"

// ---------- ADDED FORWARD DECLARATIONS ----------
// This tells the compiler these exist in other tabs (sound.ino, snake.ino, etc.)
void playGameOverSound(); 
void playEatSound();
void initSound();
void initBluetooth();
void sendBTControls();
void handleInput();
void drawScreen();
void drawDigitalClock();
void drawAnalogClock();
void saveGame(int id, int s); // If you have a save function

// ---------- GLOBAL VARIABLES ----------
int highScore = 0; // Fixed: Defined here so snake.ino can see it

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
// We move the display declaration here so it's globally accessible
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pins
#define VRX_PIN 34
#define VRY_PIN 35
#define BTN_SELECT 32
#define BTN_BACK 25
#define BTN_SHIFT 26
#define BUZZER 33

// State
enum ScreenState {
  MAIN_MENU, GAMES_MENU, SETTINGS_MENU,
  WIFI_MENU, KEYBOARD_SCREEN, GAME_SCREEN
};
ScreenState currentScreen = MAIN_MENU;

// Core
Preferences prefs;
BleGamepad bleGamepad;

// Menu
String mainMenu[] = {"Games","WiFi","Settings","BT"};
String gamesMenu[] = {"Snake","Pong","Flappy"};
String settingsMenu[] = {"Clock Style","Timeout","Sound"};

// UI
int selectedIndex=0;
float smoothIndex=0;

// Clock + Idle
int clockMode = 0; // 0 digital, 1 analog
unsigned long lastActivity = 0;
int displayTimeout = 10000;
bool dimmed = false;

// WiFi / Keyboard
String selectedSSID="";
String inputText="";
bool enteringPassword=true;

// ---------- SETUP ----------
void setup(){
  Serial.begin(115200);

  pinMode(BTN_SELECT,INPUT_PULLUP);
  pinMode(BTN_BACK,INPUT_PULLUP);
  pinMode(BTN_SHIFT,INPUT_PULLUP);

  Wire.begin(21,22);
  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  // Load High Score from memory on startup
  prefs.begin("sys", false);
  highScore = prefs.getInt("high", 0); 

  initSound();
  initBluetooth(); // Commented out if not yet implemented in other tabs

  // Auto reconnect WiFi
  String s = prefs.getString("ssid","");
  String p = prefs.getString("pass","");
  if(s != "") WiFi.begin(s.c_str(), p.c_str());

  configTime(19800, 0, "pool.ntp.org");

  lastActivity = millis();
}

// ---------- LOOP ----------
void loop(){

  sendBTControls(); // Commented out if not yet implemented

  // 🕒 Idle detection
  if(millis() - lastActivity > displayTimeout)
    dimmed = true;
  else
    dimmed = false;

  // 🌙 Dim display logic
  if(dimmed) {
    display.clearDisplay();
    display.ssd1306_command(SSD1306_SETCONTRAST);
    display.ssd1306_command(10);
    
    if(clockMode == 0) drawDigitalClock();
    else drawAnalogClock();
    display.display();
    return;
  } else {
    display.clearDisplay();
    display.ssd1306_command(SSD1306_SETCONTRAST);
    display.ssd1306_command(255);
  }

  handleInput();
  drawScreen();
}