#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin Definitions
const int SENSOR_PIN = A0;
const int BUTTON_PIN = 2;
const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

// Color variables (Default starts warm orange/yellow)
int redFactor = 255;
int greenFactor = 128;
int blueFactor = 0;

int lastButtonState = HIGH;

void setup() {
  lcd.init();
  lcd.backlight();
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Seed random generator using noise from an unconnected analog pin
  randomSeed(analogRead(A1));

  lcd.setCursor(0, 0);
  lcd.print("Room Brightness:");
}

void loop() {
  // Read button press state
  int buttonState = digitalRead(BUTTON_PIN);

  // Detect button press (transition from HIGH to LOW)
  if (buttonState == LOW && lastButtonState == HIGH) {
    // Pick new random color ratios (0 to 255)
    redFactor = random(0, 256);
    greenFactor = random(0, 256);
    blueFactor = random(0, 256);
    delay(50); // Debounce delay
  }
  lastButtonState = buttonState;

  // Read room light level (0% = Dark, 100% = Bright)
  int rawValue = analogRead(SENSOR_PIN);
  int percent = map(rawValue, 1023, 0, 0, 100);
  percent = constrain(percent, 0, 100);

  // Increased sensitivity dimming calculation:
  // - Room light >= 50%: LED is completely OFF (0 brightness)
  // - Room light <= 0%: LED is at MAX (255 brightness)
  long masterBrightness = map(percent, 50, 0, 0, 255);
  masterBrightness = constrain(masterBrightness, 0, 255);

  // Scale chosen color channels according to room darkness
  int finalRed = (redFactor * masterBrightness) / 255;
  int finalGreen = (greenFactor * masterBrightness) / 255;
  int finalBlue = (blueFactor * masterBrightness) / 255;

  analogWrite(RED_PIN, finalRed);
  analogWrite(GREEN_PIN, finalGreen);
  analogWrite(BLUE_PIN, finalBlue);

  // Update LCD Screen
  lcd.setCursor(0, 1);
  lcd.print("Level: ");
  lcd.print(percent);
  lcd.print("%   ");

  delay(100);
}