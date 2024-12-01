#include "AiEsp32RotaryEncoder.h"

#define ROT_CLK 38
#define ROT_DT 37
#define ROT_SW 36

#define ROTARY_ENCODER_STEPS 4
// paramaters for button
unsigned long shortPressAfterMiliseconds =
    50; // how long short press shoud be. Do not set too low to avoid bouncing
        // (false press events).
unsigned long longPressAfterMiliseconds = 600; // how long long press shoud be.

AiEsp32RotaryEncoder rotaryEncoder =
    AiEsp32RotaryEncoder(ROT_CLK, ROT_DT, ROT_SW, -1, ROTARY_ENCODER_STEPS);

void IRAM_ATTR readEncoderISR() { rotaryEncoder.readEncoder_ISR(); }

void rotaryEncoderSetup() {
  rotaryEncoder.begin();
  rotaryEncoder.setup(readEncoderISR);
  rotaryEncoder.setAcceleration(0);

  rotaryEncoder.correctionOffset = 2; // try with zero or ROTARY_ENCODER_STEPS/2
  rotaryEncoder.isButtonPulldown = false;
  rotaryEncoder.areEncoderPinsPulldownforEsp32 = true;

  rotaryEncoder.setBoundaries(-500, 500, false); // select delivery
  rotaryEncoder.disableAcceleration();
}

void handleRotaryEncoder(int totalIcons) {
  int16_t encoderDelta = rotaryEncoder.encoderChanged();
  if (currentMode == ICONS_MODE) {
    if (encoderDelta < 0) {
      // Move to next selection
      selectedItem = (selectedItem - 1 + totalIcons) % totalIcons;
    }
    if (encoderDelta > 0) {
      // Move to previous selection
      selectedItem = (selectedItem + 1) % totalIcons;
    }
    if (selectedItem >= firstVisibleItem + VISIBLE_ICONS) {
      firstVisibleItem = (firstVisibleItem + 1) % totalIcons;
    } else if (selectedItem < firstVisibleItem) {
      firstVisibleItem = (firstVisibleItem - 1 + totalIcons) % totalIcons;
    }

    // Ensure selectedItem is within bounds
    if (selectedItem < 0) {
      selectedItem = 0;
    } else if (selectedItem >= totalIcons) {
      selectedItem = totalIcons - 1;
    }
  } else if (currentMode == PARAMS_MODE) {
    if (selectedParam == -1) {
      int paramsCount =
          getIconParamsCount(pages[currentPage].icons[selectedItem]);
      if (encoderDelta < 0) {
        // Move to next parameter
        hoveredParam = (hoveredParam - 1 + paramsCount) % paramsCount;
      }
      if (encoderDelta > 0) {
        // Move to previous parameter
        hoveredParam = (hoveredParam + 1) % paramsCount;
      }
    }

    // Change parameter value if in editing mode
    if (selectedParam != -1) {
      for (auto &iconParams : iconParamsArray) {
        if (iconParams.icon == pages[currentPage].icons[selectedItem]) {
          iconParams.paramValues[selectedParam] = constrain(
              iconParams.paramValues[selectedParam] + encoderDelta, 0, 100);
          break;
        }
      }
    }
  }
}
