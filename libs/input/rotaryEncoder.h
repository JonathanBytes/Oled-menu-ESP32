#include "AiEsp32RotaryEncoder.h"

#define ROT_CLK 18
#define ROT_DT 19
#define ROT_SW 5

#define ROTARY_ENCODER_STEPS 4
//paramaters for button
unsigned long shortPressAfterMiliseconds = 50;   //how long short press shoud be. Do not set too low to avoid bouncing (false press events).
unsigned long longPressAfterMiliseconds = 600;  //how long long press shoud be.

AiEsp32RotaryEncoder rotaryEncoder =
    AiEsp32RotaryEncoder(ROT_CLK, ROT_DT, ROT_SW, -1, ROTARY_ENCODER_STEPS);

void IRAM_ATTR readEncoderISR() { rotaryEncoder.readEncoder_ISR(); }

void on_button_short_click() {
}

void on_button_long_click() {
  // Change page
  selectedItem = 0;
  currentPage = (currentPage + 1) % totalPages; // toggle between pages
}

void handle_rotary_button() {
  static unsigned long lastTimeButtonDown = 0;
  static bool wasButtonDown = false;

  bool isEncoderButtonDown = rotaryEncoder.isEncoderButtonDown();
  //isEncoderButtonDown = !isEncoderButtonDown; //uncomment this line if your button is reversed

  if (isEncoderButtonDown) {
    if (!wasButtonDown) {
      //start measuring
      lastTimeButtonDown = millis();
    }
    //else we wait since button is still down
    wasButtonDown = true;
    return;
  }

  //button is up
  if (wasButtonDown) {
    //click happened, lets see if it was short click, long click or just too short
    if (millis() - lastTimeButtonDown >= longPressAfterMiliseconds) {
      on_button_long_click();
    } else if (millis() - lastTimeButtonDown >= shortPressAfterMiliseconds) {
      on_button_short_click();
    }
  }
  wasButtonDown = false;
}

void rotaryEncoderSetup() {
  rotaryEncoder.begin();
  rotaryEncoder.setup(readEncoderISR);
  rotaryEncoder.setAcceleration(0);

  rotaryEncoder.correctionOffset = 2; // try with zero or ROTARY_ENCODER_STEPS/2
  rotaryEncoder.isButtonPulldown = false;
  rotaryEncoder.areEncoderPinsPulldownforEsp32 = true;

  rotaryEncoder.setBoundaries(-500, 500, false); // select delivery
}

void handleRotaryEncoder(int totalIcons) {
  int16_t encoderDelta = rotaryEncoder.encoderChanged();
  if (encoderDelta < 0) {
    // Move to next selection
    selectedItem = (selectedItem - 1 + totalIcons) % totalIcons;
  } 
  if (encoderDelta > 0) {
    // Move to previous selection
    selectedItem = (selectedItem + 1) % totalIcons;
  }
  if (rotaryEncoder.isEncoderButtonClicked()) {
    handle_rotary_button();
  }
}
