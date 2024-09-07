#include <Arduino_Helpers.h>
#include <AH/Hardware/MultiPurposeButton.hpp>

MultiPurposeButton btn1{16}, btn2{4};

void configureButton(MultiPurposeButton &button) {
  button.setLongPressDelay(600);
  button.setMultiPressDelay(400);
  button.begin();
}

void buttonsSetup() {
  configureButton(btn1);
  configureButton(btn2);
}

using ValueArray = uint8_t[2];
void handleButton(MultiPurposeButton &button, bool direction, int totalIcons) {
  switch (button.update()) {
  case button.None:
    break;
  case button.PressStart:
    break;
  case button.ShortPressRelease:
    if (!direction) {
      selectedItem = (selectedItem - 1 + totalIcons) % totalIcons;
    } else {
      selectedItem = (selectedItem + 1) % totalIcons;
    }
    break;
  case button.LongPress:
    selectedItem = 0;
    currentPage = (currentPage == 0) ? 1 : 0; // toggle between pages
    break;
  }
  if (selectedItem >= firstVisibleItem + VISIBLE_ICONS) {
    firstVisibleItem = (firstVisibleItem + 1) % totalIcons;
  } else if (selectedItem < firstVisibleItem) {
    firstVisibleItem = (firstVisibleItem - 1 + totalIcons) % totalIcons;
  }
}

void handleButtonPresses(int totalIcons) {
  handleButton(btn1, false, totalIcons);
  handleButton(btn2, true, totalIcons);
}
