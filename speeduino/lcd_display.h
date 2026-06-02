/*
Speeduino - Simple engine management for the Arduino Mega 2560 platform
Copyright (C) Josh Stewart
A full copy of the license may be found in the projects root directory
*/
/** @file
 * LCD Display module for debugging and status display.
 * 
 * Supports 16x2 character LCD with HD44780 controller in 4-bit parallel mode.
 * Uses pins D25-D30 (all free GPIO according to pin mapping).
 */

#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <Arduino.h>

// LCD Configuration
#define LCD_COLS 16
#define LCD_ROWS 2

// Pin definitions - Using free GPIO D25-D30
#define LCD_RS_PIN   25
#define LCD_EN_PIN   26
#define LCD_D4_PIN   27
#define LCD_D5_PIN   28
#define LCD_D6_PIN   29
#define LCD_D7_PIN   30

// LCD Display States
enum class LcdState : uint8_t {
  INIT,           // Initializing
  READY,          // System ready, waiting for crank
  CRANKING,       // Engine cranking
  RUNNING,        // Engine running
  ERROR,          // Error condition
  STOPPED         // Engine stopped
};

/**
 * @brief Initialize the LCD display
 * 
 * Sets up the LCD hardware and displays initial boot message.
 * Should be called once during system initialization.
 */
void initLCD(void);

/**
 * @brief Update LCD display with current ECU state
 * 
 * @param state The current ECU operational state
 * @param rpm Current engine RPM (optional, 0 if not running)
 */
void updateLCD(LcdState state, uint16_t rpm = 0);

/**
 * @brief Display a custom message on the LCD
 * 
 * @param line Line number (0 or 1)
 * @param message Message to display (max 16 chars)
 */
void displayMessage(uint8_t line, const char* message);

/**
 * @brief Clear the LCD display
 */
void clearLCD(void);

#endif // LCD_DISPLAY_H
