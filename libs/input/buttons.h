// filepath: /home/jonathan/Arduino/oledMenuESP32/libs/input/buttons.h
#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>
#include <AH/Hardware/MultiPurposeButton.hpp>
// Declarations go here
extern void updateLeds();
extern void configureButton(MultiPurposeButton &button);
extern void buttonsSetup();
extern void handleButton(MultiPurposeButton &button, bool direction);
extern void handleRotaryButton(MultiPurposeButton &rotbtn);
extern void handleButtonPresses();

#endif