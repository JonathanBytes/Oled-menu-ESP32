#include "AiEsp32RotaryEncoder.h"

#define ROT_CLK 18
#define ROT_DT 19
#define ROT_SW 5

#define ROTARY_ENCODER_STEPS 4
AiEsp32RotaryEncoder rotaryEncoder =
    AiEsp32RotaryEncoder(ROT_CLK, ROT_DT, ROT_SW, -1, ROTARY_ENCODER_STEPS);

void IRAM_ATTR readEncoderISR() { rotaryEncoder.readEncoder_ISR(); }

void rotary_onButtonClick()
{
    static unsigned long lastTimePressed = 0;
    if (millis() - lastTimePressed < 200)
        return;
    lastTimePressed = millis();
  
    // Change page
    selectedItem = 0;
    currentPage = (currentPage + 1) % totalPages; // toggle between pages

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
    rotary_onButtonClick();
  }
}
