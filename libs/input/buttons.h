#include <AH/Hardware/MultiPurposeButton.hpp>

MultiPurposeButton btn1{16}, btn2{4}, rotbtn{5};

void configureButton(MultiPurposeButton &button) {
  button.setLongPressDelay(600);
  button.setMultiPressDelay(400);
  button.begin();
}

void buttonsSetup() {
  configureButton(btn1);
  configureButton(btn2);
  configureButton(rotbtn);
}

void handleButton(MultiPurposeButton &button, bool direction, int totalIcons) {
  switch (button.update()) {
  case button.None:
    break;
  case button.PressStart:
    break;
  case button.ShortPressRelease:
    if (!direction) {
      midi.sendCC({69, Channel_1}, 9);
    } else {
      midi.sendCC({69, Channel_1}, 8);
    }
    break;
  case button.LongPress:
    // Change page
    selectedItem = 0;
    currentPage = (currentPage + 1) % totalPages; // toggle between pages
    break;
  }
}

void handleRotaryButton(MultiPurposeButton &rotbtn) {
  switch (rotbtn.update()) {
  case rotbtn.None:
    break;
  case rotbtn.PressStart:
    break;
  case rotbtn.ShortPressRelease:
    midi.sendCC({69, Channel_1}, 9);
    break;
  case rotbtn.LongPress:
    // Change page
    selectedItem = 0;
    currentPage = (currentPage + 1) % totalPages; // toggle between pages
    break;
  }
}

void handleButtonPresses(int totalIcons) {
  handleButton(btn1, false, totalIcons);
  handleButton(btn2, true, totalIcons);
  handleRotaryButton(rotbtn);
}
