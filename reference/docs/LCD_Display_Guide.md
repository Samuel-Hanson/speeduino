# LCD Display Integration Guide

## Hardware Setup

### LCD Module: 16x2 Character LCD (HD44780 Compatible)

**Pin Connections:**

| LCD Pin | Function | Arduino Mega Pin | Notes |
|---------|----------|------------------|-------|
| 1 | VSS | GND | Ground |
| 2 | VDD | 5V | Power |
| 3 | V0 | Contrast | See contrast options below |
| 4 | RS | D25 | Register Select |
| 5 | R/W | GND | Read/Write (tied to GND for write-only) |
| 6 | E | D26 | Enable |
| 7-10 | D0-D3 | Not connected | (4-bit mode) |
| 11 | D4 | D27 | Data bit 4 |
| 12 | D5 | D28 | Data bit 5 |
| 13 | D6 | D29 | Data bit 6 |
| 14 | D7 | D30 | Data bit 7 |
| 15 | A (LED+) | 5V via 220Ω resistor | Backlight anode |
| 16 | K (LED-) | GND | Backlight cathode |

### Contrast Control Options (LCD Pin 3 - V0)

You have two options for setting LCD contrast:

**Option A: Potentiometer (Adjustable - Recommended)**
```
5V → 10K Potentiometer Pin 1
GND → 10K Potentiometer Pin 3
LCD Pin 3 (V0) → Potentiometer Pin 2 (middle/wiper)
```
- Allows you to adjust contrast by turning the knob
- Best for fine-tuning display visibility
- 10K potentiometer is standard, but 1K-50K will work

**Option B: Fixed Resistor (Simple - No Adjustment)**
```
LCD Pin 3 (V0) → 2KΩ Resistor → GND
```
- Fixed contrast setting (no adjustment)
- **Tested value: 2KΩ provides good visibility** ✅
- Simpler wiring if you don't have a potentiometer
- If too dark/light, try 1KΩ (lighter) or 4.7KΩ (darker)

### Wiring Summary

**Data/Control Pins (D25-D30):**
- All 6 pins are consecutive and fully free according to GPIO reference
- No conflicts with existing Speeduino functions

**Power & Backlight:**
- 5V and GND from Arduino Mega
- **Backlight:** 220Ω resistor between 5V and LCD pin 15 (LED+)
- **Contrast:** Choose Option A (pot) or Option B (2KΩ resistor) above

---

## Software Integration

### Files Modified/Added

1. **platformio.ini** - Added LiquidCrystal library dependency
2. **speeduino/lcd_display.h** - LCD header with function declarations
3. **speeduino/lcd_display.cpp** - LCD implementation
4. **speeduino/init.cpp** - Added LCD initialization call

### Display States

The LCD module supports the following ECU states:

| State | Line 1 | Line 2 |
|-------|--------|--------|
| INIT | "Initializing..." | |
| READY | "READY" | "Waiting..." |
| CRANKING | "CRANKING" | "Starting engine" |
| RUNNING | "RUNNING" | "RPM: {value}" |
| ERROR | "ERROR!" | "Check system" |
| STOPPED | "STOPPED" | "Engine off" |

### Boot Sequence

1. LCD initializes during `initialiseAll()` in init.cpp
2. Displays "Speeduino ECU" / "Booting..." for 1 second
3. Automatically transitions to "READY" state
4. Can be updated via `updateLCD(state, rpm)` function

---

## Usage Examples

### Basic State Update
```cpp
#include "lcd_display.h"

// Update to show engine running at 3500 RPM
updateLCD(LcdState::RUNNING, 3500);
```

### Custom Message Display
```cpp
// Display custom message on line 0 (top row)
displayMessage(0, "Custom Message");

// Display on line 1 (bottom row)
displayMessage(1, "Status: OK");
```

### Clear Display
```cpp
clearLCD();
```

---

## Future Enhancements

Potential additions for the LCD display module:

- [ ] Display coolant temperature
- [ ] Display throttle position
- [ ] Display fuel pressure
- [ ] Display error codes
- [ ] Scrolling multi-line messages
- [ ] User-configurable display items
- [ ] Brightness control via PWM
- [ ] Menu system for settings
- [ ] Data logging status indicator

---

## Testing

### Initial Test (READY Message)

1. Upload firmware to Arduino Mega 2560
2. Power on the ECU
3. LCD should display:
   - Line 1: "Speeduino ECU"
   - Line 2: "Booting..."
   - (1 second delay)
   - Line 1: "READY"
   - Line 2: "Waiting..."

### Pin Verification

Use multimeter to verify:
- 5V on LCD pin 2 (VDD)
- 0V on LCD pins 1, 5, 16 (VSS, R/W, K)
- LCD pin 3 (V0) voltage:
  - **With potentiometer:** Adjustable ~0.5V to 1.5V (turn pot for best contrast)
  - **With 2KΩ resistor to GND:** ~0V (resistor sets fixed contrast)

---

## Troubleshooting

**No display / blank screen:**
- Check 5V power connection to LCD pin 2
- **MOST COMMON:** Contrast issue on pin 3:
  - With potentiometer: Turn it slowly in both directions
  - With fixed resistor: Try 2KΩ to GND (tested working value)
  - No resistor at all: Display will be blank - add 2KΩ to GND
- Verify LCD pin 5 (R/W) is connected to GND
- Check all ground connections

**Garbled characters:**
- Check data pin connections (D25-D30)
- Verify pin definitions in lcd_display.h match wiring
- Check for loose connections

**Backlight not working:**
- Check 220Ω resistor in series with pin 15
- Verify 5V connection to LED+ (pin 15)
- Check ground on LED- (pin 16)

**Display works but wrong pins:**
- Update pin definitions in `lcd_display.h` (LCD_RS_PIN through LCD_D7_PIN)
- Recompile and upload

---

## Pin Reservation

The following pins are now **RESERVED** for LCD display:

- **D25**: LCD RS (Register Select)
- **D26**: LCD Enable
- **D27**: LCD D4
- **D28**: LCD D5
- **D29**: LCD D6
- **D30**: LCD D7

These pins should not be used for other functions when LCD is enabled.

---

## Version History

- **v1.1** (2026-06-03): Documentation update
  - Added fixed 2KΩ resistor option for contrast (tested alternative to potentiometer)
  - Updated wiring guide with both contrast options
  - Improved troubleshooting section
  
- **v1.0** (2026-06-02): Initial LCD integration with basic state display
  - Boot message support
  - READY state display
  - Foundation for future enhancements
