# ESP32-OS Copilot Instructions

## Project Overview
ESP32-OS is a multi-tab Arduino sketch for an ESP32 microcontroller with a 128x64 OLED display, analog joystick input, and Bluetooth gaming capabilities. It's a game console OS with menu navigation, WiFi connectivity, and multiple arcade games (Snake, Pong, Flappy Bird).

## Architecture & Critical Patterns

### Multi-Tab Structure
- **Main entry point**: `Esp32-OS.ino` - Contains `setup()`, `loop()`, global state, and hardware pin definitions
- **Modular design**: Each `.ino` file represents a feature module (games, UI, input, storage, sound, connectivity)
- **Forward declarations in main file**: Required for cross-tab function calls (see top of `Esp32-OS.ino`)
- **Global state sharing**: All modules access shared globals: `display`, `prefs`, `highScore`, `currentScreen`, `selectedIndex`, `lastActivity`

### Screen State Machine
```
enum ScreenState: MAIN_MENU → GAMES_MENU → GAME_SCREEN → back to MAIN_MENU
                  ↓ SETTINGS_MENU → handleSettings()
                  ↓ WIFI_MENU → keyboard entry → WiFi connection
```
- Navigate with joystick Y-axis (`VRY_PIN` 35)
- Select with `BTN_SELECT` (pin 32), back with `BTN_BACK` (pin 25)
- Core loop: `handleInput()` → `drawScreen()`

### Game Integration Pattern
Each game module (snake, pong, flappy) follows:
1. `init[Game]()` - Initialize state (position, length, score)
2. `update[Game]()` - Update logic each frame (collision, movement)
3. `draw[Game]()` - Render to display

**Key**: Games don't directly call `display.display()` - `runGame()` in `games.ino` handles rendering. High score stored in `prefs` ("high" key).

### Global Variable Convention
Critical shared state in `Esp32-OS.ino`:
- `currentScreen` - Current UI state
- `selectedIndex` - Menu cursor position
- `highScore` - Persisted across power cycles
- `lastActivity` - Timestamp for idle detection/dimming
- `display` - OLED object (Adafruit SSD1306)
- `prefs` - NVS storage (Preferences library)
- `bleGamepad` - Bluetooth gamepad instance

**When adding features**: Declare globals in main file first, forward-declare functions in main file's header section.

### Display & UI Conventions
- **Resolution**: 128x64 pixels, 1-bit mono (WHITE/BLACK only)
- **Menu rendering** (`ui.ino`): Uses `drawMenu()` with smooth index animation (`smoothIndex`)
- **Text**: 12-pixel row height, icons drawn as simple shapes (rect, circle, line, pixel)
- **Clearing**: Always call `display.clearDisplay()` before rendering; `display.display()` at end to flush

### Pin Configuration (Fixed Hardware Map)
```
VRX_PIN = 34 (X-axis analog)
VRY_PIN = 35 (Y-axis analog)
BTN_SELECT = 32 (digital input with pullup)
BTN_BACK = 25
BTN_SHIFT = 26 (mode toggle for keyboard)
BUZZER = 33 (PWM tone generation)
I2C SDA = 21, SCL = 22 (for OLED)
```

### Data Persistence (Preferences Library)
- Namespace: `"sys"` (main), `"game"` (optional for game-specific data)
- Common keys: `"high"` (high score), `"ssid"`, `"pass"` (WiFi), `"lastGame"`, `"lastScore"`
- Pattern: `prefs.putInt("key", value)`, `prefs.getInt("key", default)`

### Input Handling Conventions
- Joystick Y-axis: `y < 1000` = up, `y > 3000` = down, else idle
- Joystick X-axis: `x < 1000` = left, `x > 3000` = right
- Debounce: Add `delay(200)` after button press to prevent rapid-fire
- Idle timeout: Compare `millis() - lastActivity > displayTimeout` (default 10s, configurable)

### Sound (ESP32 PWM/Tone via Buzzer)
- Use **new ESP32 Core 3.0+ syntax**: `ledcAttach(pin, freq, resolution)` and `ledcWriteTone(pin, frequency)`
- Pattern: `beep(frequency, duration_ms)` - sets tone, delays, stops
- Examples: `playEatSound()` (1200 Hz), `playGameOverSound()` (400 Hz)

### WiFi & Keyboard Flow
1. `scanWiFi()` scans networks, stores SSID/RSSI in arrays
2. User selects SSID in WiFi menu
3. Transitions to `KEYBOARD_SCREEN` for password entry
4. `drawKeyboard()` cycles through lowercase/uppercase/numbers with `BTN_SHIFT`
5. `connectWiFi()` persists credentials to NVS before connecting

### Common Cross-Module Dependencies
- Games → `sound.ino`: Call `playGameOverSound()`, `playEatSound()`
- Games → Storage: Access `prefs`, `highScore`
- Menu navigation → `ui.ino`: `drawMenu()`, menu arrays
- Input → All modules: `handleInput()` in loop, sets `currentScreen`, `selectedIndex`
- Idle detection: `loop()` checks `lastActivity` for dimming logic

## Development Workflow

### Adding a New Game
1. Create `newgame.ino` with `initNewGame()`, `updateNewGame()`, `drawNewGame()`
2. Add forward declarations to top of `Esp32-OS.ino`
3. Add entry to `gamesMenu[]` array
4. Add case in `startGame()` switch (e.g., `if(g==3) initNewGame();`)
5. Add case in `runGame()` switch to call update/draw functions

### Adding a New Menu Option
1. Create new menu array in `Esp32-OS.ino` (e.g., `String myMenu[] = {...}`)
2. Add ScreenState enum value if needed
3. Handle navigation in `handleInput()` with BTN_SELECT check
4. Create corresponding render function (e.g., `drawMyMenu()`)
5. Add case in `drawScreen()` switch

### Testing & Debugging on ESP32
- Use `Serial.begin(115200)` - monitor in Arduino IDE Serial Monitor
- Common issues: Display I2C address (default 0x3C), SSD1306 allocation failure → check pin 21/22
- Buzzer not working: Verify `ledcAttach()` and `ledcWriteTone()` syntax (Core 3.0+)
- Bluetooth not visible: Ensure `initBluetooth()` called in setup, device in pairing mode

## Project-Specific Conventions

- **No external functions in game loops**: Games should NOT call `display.display()` - rendering happens in `runGame()`
- **Minimal global state in game tabs**: Keep game logic isolated; use main file globals for system state
- **Joystick deadzone**: X/Y thresholds are 1000 (low) and 3000 (high) out of 4095 raw ADC
- **High score persistence**: Always save via `prefs.putInt("high", highScore)` when beaten (see `snake.ino` pattern)
- **Menu wrapping**: Indices wrap around at boundaries (if `selectedIndex < 0` → last item)
- **Smooth animations**: Use `smoothIndex = smoothIndex + (target - smoothIndex) * damping` for UI transitions (damping ≈ 0.2)

## Dependency Map
```
Esp32-OS.ino (main)
├── ui.ino (drawMenu, drawScreen)
├── games.ino (startGame, runGame dispatcher)
│   ├── snake.ino (initSnake, updateSnake, drawSnake)
│   ├── pong.ino (initPong, updatePong, drawPong)
│   └── flappy.ino (initFlappy, updateFlappy, drawFlappy)
├── input.ino (handleInput → state machine)
├── sound.ino (beep, playEatSound, playGameOverSound)
├── storage.ino (saveGame)
├── clock.ino (drawDigitalClock, drawAnalogClock)
├── bluetooth.ino (initBluetooth, sendBTControls)
├── wifi.ino (scanWiFi, connectWiFi, drawWiFi, drawKeyboard)
└── keyboard.ino (drawKeyboard, getKey)
```

## Libraries & Hardware
- **Display**: Adafruit_SSD1306 (I2C), Adafruit_GFX
- **Connectivity**: WiFi (ESP32 built-in), BleGamepad (Bluetooth)
- **Storage**: Preferences (ESP32 NVS)
- **Input**: Analog joystick (ADC), three digital buttons (GPIO with pullup)
- **Sound**: PWM tone generation via ESP32 LEDC peripheral
