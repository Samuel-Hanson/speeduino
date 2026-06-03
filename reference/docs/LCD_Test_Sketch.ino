/*
 * Simple LCD Test Sketch
 * Upload this to your Arduino Mega to verify LCD wiring before using with Speeduino
 * 
 * Pin connections:
 * LCD RS  -> D25
 * LCD EN  -> D26
 * LCD D4  -> D27
 * LCD D5  -> D28
 * LCD D6  -> D29
 * LCD D7  -> D30
 * 
 * LCD VSS (Pin 1)  -> GND
 * LCD VDD (Pin 2)  -> 5V
 * LCD V0  (Pin 3)  -> Potentiometer middle (10K pot between GND and 5V)
 * LCD R/W (Pin 5)  -> GND (IMPORTANT!)
 * LCD A   (Pin 15) -> 5V via 220Ω resistor
 * LCD K   (Pin 16) -> GND
 */

#include <LiquidCrystal.h>

// Pin definitions - matching Speeduino LCD module
const int LCD_RS = 25;
const int LCD_EN = 26;
const int LCD_D4 = 27;
const int LCD_D5 = 28;
const int LCD_D6 = 29;
const int LCD_D7 = 30;

// Initialize LCD object
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void setup() {
  // Set all LCD pins as outputs explicitly
  pinMode(LCD_RS, OUTPUT);
  pinMode(LCD_EN, OUTPUT);
  pinMode(LCD_D4, OUTPUT);
  pinMode(LCD_D5, OUTPUT);
  pinMode(LCD_D6, OUTPUT);
  pinMode(LCD_D7, OUTPUT);
  
  // Small delay for stability
  delay(100);
  
  // Initialize 16x2 LCD
  lcd.begin(16, 2);
  
  // Clear screen
  lcd.clear();
  
  // Display test message
  lcd.setCursor(0, 0);
  lcd.print("LCD TEST OK!");
  
  lcd.setCursor(0, 1);
  lcd.print("Pins: D25-D30");
  
  // Turn on built-in LED to show sketch is running
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  // Blink the built-in LED to show the sketch is running
  static unsigned long lastBlink = 0;
  static bool ledState = false;
  
  if (millis() - lastBlink > 1000) {
    ledState = !ledState;
    digitalWrite(LED_BUILTIN, ledState);
    lastBlink = millis();
    
    // Update a counter on the LCD
    static int counter = 0;
    lcd.setCursor(14, 1);
    lcd.print("  "); // Clear last 2 chars
    lcd.setCursor(14, 1);
    lcd.print(counter % 100); // Display counter 0-99
    counter++;
  }
}
