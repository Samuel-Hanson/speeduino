# Speeduino GPIO Pin Reference - Arduino Mega 2560

This document provides a comprehensive reference for GPIO pin availability and usage on the **Arduino Mega 2560** platform running Speeduino firmware (v0.4 board configuration - most common).

---

## Pin Availability Summary

### ✅ Fully Available Digital Pins (Default v0.4 Firmware)

The following digital pins are **not assigned** by default and can be used for custom functions:

- **D1** (TX - avoid if using serial communication)
- **D13** (Built-in LED - technically available but visible indicator when toggled)
- **D14-15**
- **D21-23** 
- **D24** (Note: used by stepper motor if enabled)
- **~~D25-D30~~** (**RESERVED for LCD Display** - see LCD_Display_Guide.md)
- **D31-33**
- **D35-37**
- **D39**
- **D41**
- **D53**

**Note:** D0 (RX) should be avoided if using Serial communication for TunerStudio.

### ✅ Fully Available Analog Pins

- **A6-A7** (2 pins)
- **A9-A15** (7 pins)

**Total available analog inputs:** 9 pins

---

## Pin Assignments by Function

### 🔴 Critical Engine Control Pins (DO NOT USE)

These pins are essential for engine operation and should **never** be repurposed:

| Pin | Function | Description |
|-----|----------|-------------|
| D19 | Trigger (RPM1) | **Primary crank sensor** - Most critical pin |
| D18 | Trigger 2 (RPM2) | Cam sensor input |
| D3  | Trigger 3 | Secondary cam sensor |
| D2  | Flex Fuel | Flex fuel sensor (requires interrupt capability) |
| D20 | VSS | Vehicle speed sensor |

---

### ⛽ Fuel Injection Outputs

| Pin | Channel | Notes |
|-----|---------|-------|
| D8  | Injector 1 | |
| D9  | Injector 2 | |
| D10 | Injector 3 | |
| D11 | Injector 4 | |
| D12 | Injector 5 | |
| D50 | Injector 6 | ⚠️ **Conflicts with Coil 4!** |

---

### 🔥 Ignition Outputs

| Pin | Channel | Notes |
|-----|---------|-------|
| D40 | Coil 1 | |
| D38 | Coil 2 | |
| D52 | Coil 3 | |
| D50 | Coil 4 | ⚠️ **Conflicts with Injector 6!** |
| D34 | Coil 5 | |

**Note:** The pin conflict on D50 means you can use either 6 injectors OR 4+ ignition channels, but not both simultaneously.

---

### 📊 Analog Sensor Inputs

| Pin | Sensor | Description |
|-----|--------|-------------|
| A0  | IAT | Intake Air Temperature |
| A1  | CLT | Coolant Temperature |
| A2  | TPS | Throttle Position Sensor |
| A3  | MAP | Manifold Absolute Pressure |
| A4  | Battery | Battery voltage reference |
| A5  | Baro | Barometric pressure sensor |
| A8  | O2 | Primary oxygen sensor |

---

### ⚙️ Auxiliary Control Outputs

| Pin(s) | Function | Description |
|--------|----------|-------------|
| D4  | VVT_1 | Variable Valve Timing output 1 |
| D5  | Idle 1 | Single-wire idle control (PWM) |
| D6  | Idle 2 | Two-wire idle control |
| D7  | Boost | Boost/wastegate control |
| D16, D17, D24 | Stepper Motor | Direction, Step, Enable (for stepper idle) |
| D42-D44, D46 | WMI | Water/methanol injection system |
| D43 | Reset Control | Arduino reset control output |
| D45 | Fuel Pump | Fuel pump relay control |
| D47 | Cooling Fan | Radiator fan control |
| D48 | Display Reset / VVT_2 | OLED display reset OR VVT output 2 |
| D49 | Tacho Out | Tachometer signal output |
| D51 | Launch Control | Launch/anti-lag control input |

---

## Safest Pins for Custom Applications

If you need GPIO for custom features (e.g., additional sensors, outputs, datalogging, displays), use these pins first:

### **Recommended Free Digital Pins:**
- **D21, D22, D23** - Consecutive, good for I2C/SPI/custom protocols
- **D25-D33** - Large block of 9 consecutive pins
- **D35-D37** - 3 consecutive pins
- **D39, D41, D53** - Individual pins

### **Recommended Free Analog Pins:**
- **A9-A15** - 7 consecutive analog inputs (excellent for additional sensors)
- **A6-A7** - 2 additional analog inputs

---

## Common Configurations

### 4-Cylinder Sequential (4 Injectors + 4 Coils)
- Uses: D8-D11 (injectors), D34, D38, D40, D50 (coils)
- **Available pins:** Most of the ranges listed above

### 6-Cylinder Sequential (6 Injectors + 3 Coils)  
- Uses: D8-D12 + D50 (injectors), D34, D38, D40 (coils)
- **Pin conflict:** D50 shared between Injector 6 and Coil 4
- **Available pins:** Slightly fewer options due to D50 conflict

### 8-Cylinder (8 Injectors + 4/5 Coils)
- Uses: D8-D12 + additional pins from scheduler configuration
- Check `platformio.ini` build flags: `-DINJ_CHANNELS=8 -DIGN_CHANNELS=1`

---

## Pin Mapping Configuration

Pin mappings are defined in `/speeduino/init.cpp` within the `setPinMapping()` function. Different board IDs (case 1, 2, 3, etc.) define different pin layouts. The v0.4 board is **case 3**.

To customize pins, modify the appropriate case statement or create a custom board configuration.

---

## Hardware Considerations

### Current Limitations
- **Digital outputs** driving high-current loads (injectors, coils, relays) require external drivers (e.g., ULN2803, MOSFET modules)
- **Analog inputs** are 0-5V on Mega 2560 (10-bit ADC, 1024 steps)
- **Interrupt pins** on Mega 2560: D2, D3, D18, D19, D20, D21 (useful for frequency-based sensors)
- **PWM-capable pins:** Most digital pins, but verify timer conflicts if using for time-critical operations

### Protection
- Always use appropriate pull-up/pull-down resistors
- Protect analog inputs with voltage dividers if sensor outputs >5V
- Use flyback diodes on inductive loads (relays, solenoids)

---

## Board Variants

This reference is specific to the **Arduino Mega 2560** (ATmega2560 microcontroller). Other supported platforms have different pin assignments:

- **Teensy 3.5/3.6/4.1**: Different pin numbers - see `#if defined(CORE_TEENSY*)` blocks in `init.cpp`
- **STM32**: Completely different port/pin naming (PA0, PB1, etc.)

Always verify pin assignments for your specific hardware platform.

---

## Quick Reference Table

| Range | Status | Type | Count | Best For |
|-------|--------|------|-------|----------|
| D21-D23 | ✅ Free | Digital | 3 | I2C, SPI devices |
| D25-D30 | 🟡 LCD | Digital | 6 | **LCD Display (RS, EN, D4-D7)** |
| D31-D33 | ✅ Free | Digital | 3 | General GPIO |
| D35-D37 | ✅ Free | Digital | 3 | General GPIO |
| D39, D41, D53 | ✅ Free | Digital | 3 | Individual signals |
| A9-A15 | ✅ Free | Analog | 7 | Extra sensors (pressure, temp, etc.) |
| A6-A7 | ✅ Free | Analog | 2 | Additional analog inputs |
| D2, D3, D18-D20 | 🔴 Used | Digital | 5 | **Critical engine sensors** |
| D8-D12 | 🔴 Used | Digital | 5 | Fuel injectors |
| D34, D38, D40, D50, D52 | 🔴 Used | Digital | 5 | Ignition coils |
| A0-A5, A8 | 🔴 Used | Analog | 7 | Engine sensors |

---

## Version Information

- **Document created:** June 2026
- **Firmware version:** Speeduino 202504-dev
- **Board configuration:** v0.4 (Arduino Mega 2560)
- **Default channel configuration:** 4 injectors, 5 ignition channels

---

## Additional Resources

- [Speeduino Wiki](https://wiki.speeduino.com)
- [Source code: init.cpp](../speeduino/init.cpp) - Pin mapping definitions
- [LCD Display Integration Guide](LCD_Display_Guide.md) - Details on LCD hardware setup and usage
- [Source code: globals.cpp](../speeduino/globals.cpp) - Pin variable declarations
- [TunerStudio configuration: speeduino.ini](./speeduino.ini) - Board layout definitions
