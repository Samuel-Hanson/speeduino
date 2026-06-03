/*
Speeduino - Simple engine management for the Arduino Mega 2560 platform
Copyright (C) Josh Stewart
A full copy of the license may be found in the projects root directory
*/
/** @file
 * LCD Display implementation.
 */

#include "lcd_display.h"
#include <LiquidCrystal.h>

// Global LCD object - using 4-bit parallel mode
// LiquidCrystal(rs, enable, d4, d5, d6, d7)
static LiquidCrystal lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

static LcdState currentState = LcdState::INIT;

/**
 * @brief Initialize the LCD display
 */
void initLCD(void)
{
  // Initialize LCD with dimensions
  lcd.begin(LCD_COLS, LCD_ROWS);
  
  // Clear display
  lcd.clear();
  
  // Display boot message
  lcd.setCursor(0, 0);
  lcd.print("Speeduino ECU");
  
  lcd.setCursor(0, 1);
  lcd.print("Booting...");
  
  // Brief delay to show boot message
  delay(1000);
  
  // Show READY state
  updateLCD(LcdState::READY);
}

/**
 * @brief Update LCD display with current ECU state
 */
void updateLCD(LcdState state, uint16_t rpm)
{
  // Only update if state has changed (reduces flicker)
  if (state != currentState || state == LcdState::RUNNING)
  {
    currentState = state;
    lcd.clear();
    
    switch (state)
    {
      case LcdState::INIT:
        lcd.setCursor(0, 0);
        lcd.print("Initializing...");
        break;
        
      case LcdState::READY:
        lcd.setCursor(0, 0);
        lcd.print("READY");
        lcd.setCursor(0, 1);
        lcd.print("Waiting...");
        break;
        
      case LcdState::CRANKING:
        lcd.setCursor(0, 0);
        lcd.print("CRANKING");
        lcd.setCursor(0, 1);
        lcd.print("Starting engine");
        break;
        
      case LcdState::RUNNING:
        lcd.setCursor(0, 0);
        lcd.print("RUNNING");
        lcd.setCursor(0, 1);
        lcd.print("RPM: ");
        lcd.print(rpm);
        break;
        
      case LcdState::ERROR:
        lcd.setCursor(0, 0);
        lcd.print("ERROR!");
        lcd.setCursor(0, 1);
        lcd.print("Check system");
        break;
        
      case LcdState::STOPPED:
        lcd.setCursor(0, 0);
        lcd.print("STOPPED");
        lcd.setCursor(0, 1);
        lcd.print("Engine off");
        break;
    }
  }
}

/**
 * @brief Display a custom message on the LCD
 */
void displayMessage(uint8_t line, const char* message)
{
  if (line < LCD_ROWS)
  {
    lcd.setCursor(0, line);
    lcd.print("                "); // Clear line
    lcd.setCursor(0, line);
    lcd.print(message);
  }
}

/**
 * @brief Clear the LCD display
 */
void clearLCD(void)
{
  lcd.clear();
}
