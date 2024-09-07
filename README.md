# OLED Display Menu with Button Navigation

This project implements an icon-based menu system using an **OLED display** (128x32 pixels) and buttons for navigation. The menu consists of multiple pages with icons that the user can scroll through and select. It is designed for the **ESP32** platform and uses multitasking to run the display updates in parallel with user input handling.

## Features

- **Icon-Based Menu**: The display shows a menu with 4 visible icons at a time, with additional icons scrollable.
- **Button Navigation**: Two buttons allow the user to navigate between icons and switch between different menu pages.
- **Animated Scrollbar and Selection**: A scrollbar and selection rectangle animate as the user moves through the menu.
- **Boot Animations**: A series of boot animations are displayed when the device powers on.
- **Multitasking**: Uses FreeRTOS tasks to run the display loop independently of other tasks, providing smooth performance.

## Components

### Hardware

- **ESP32** development board
- **OLED Display** (128x32 pixels, I2C connection)
- **Two push buttons** (connected to GPIO pins)

### Libraries

- **U8g2**: For controlling the OLED display and rendering graphics.
- **Arduino_Helpers**: Provides utilities to simplify Arduino code.
- **MultiPurposeButton**: Handles short press, long press, and multi-press events for buttons.

## Setup

### Pin Configuration

- **OLED SDA**: GPIO 21
- **OLED SCL**: GPIO 22
- **Previous Button**: GPIO 16
- **Next Button**: GPIO 4

### Wiring

Connect the OLED display to the I2C pins of the ESP32, and wire the buttons to their respective GPIO pins with pull-down resistors.

### Software

1. Install [ **U8g2** ](https://github.com/olikraus/u8g2) via Arduino Library Manager.
2. Install **Arduino_Helpers** and **MultiPurposeButton**:

   - Add the following libraries to your `libraries` folder or via the Library Manager:
     - **Arduino_Helpers**: [GitHub Repository](https://github.com/tttapa/Arduino-Helpers)
     - **MultiPurposeButton**: Part of the **Arduino_Helpers** library.

3. Clone this repository into your Arduino `sketches` folder.

4. Open the `ImageTesting.ino` file in the Arduino IDE.

## File Structure

```
/ImageTesting
  ├── /assets           # Icons and graphics
  ├── /libs             # Code for handling display and buttons
  ├── ImageTesting.ino  # Main program file
  └── README.md         # Project documentation
```

### Main Files

- **ImageTesting.ino**: Main Arduino sketch with setup and loop functions.
- **/libs/display.cpp**: Handles the display rendering, animations, and updates.
- **/libs/input/buttons.cpp**: Handles the button presses and debouncing.
- **/assets/icons.h**: Contains the icons for the menu and boot animations.

## Usage

1. **Power on the ESP32**: The boot animations will display automatically.
2. **Navigate the menu**: Use the previous and next buttons to scroll through the icons and hold any button to switch between pages.
3. **Selection Animation**: As you scroll, a selection rectangle moves smoothly (ease-in-out) with animations, and the scrollbar updates to show your position.
