#include <AH/Hardware/MultiPurposeButton.hpp>

MultiPurposeButton btn1{4}, btn2{16}, rotbtn{5};

int snapshots = 4;
int currentSnapshot = 0;

void updateLeds() {
  if (!fading) { // Solo permitimos cambiar LEDs si no está en fade
    LED_CHANGE = true;

    // Actualizar el estado de los LEDs según el snapshot actual
    if (currentSnapshot == 0) {
      LED1_ON = true;
      LED2_ON = false;
      LED3_ON = false;
    } else if (currentSnapshot == 1) {
      LED1_ON = false;
      LED2_ON = true;
      LED3_ON = false;
    } else if (currentSnapshot == 2) {
      LED1_ON = false;
      LED2_ON = false;
      LED3_ON = true;
    } else if (currentSnapshot == 3) {
      LED1_ON = true;
      LED2_ON = true;
      LED3_ON = true;
    }

    fading = true; // Marcar que estamos en un fade
  }
}

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
      currentSnapshot--;
      if (currentSnapshot < 0) {
        currentSnapshot = snapshots - 1;
      }
      midi.sendCC({69, Channel_1}, currentSnapshot);
      selectedItem = (selectedItem - 1 + totalIcons) % totalIcons;
    } else {
      currentSnapshot++;
      if (currentSnapshot > (snapshots - 1)) {
        currentSnapshot = 0;
      }
      midi.sendCC({69, Channel_1}, currentSnapshot);
      selectedItem = (selectedItem + 1) % totalIcons;
    }
    updateLeds();
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
    // midi.sendCC({69, Channel_1}, 9);
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
