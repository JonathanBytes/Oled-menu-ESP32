#include <Arduino_Helpers.h>
#include "midi.h"
#include "analogPots.h"
#include "buttons.h"
#include "rotaryEncoder.h"

void hardwareSetup() {
  midi.begin(); // Inicializar la interfaz MIDI
  analogPotsSetup();
  buttonsSetup();
  rotaryEncoderSetup();
}

// Función para calcular el acumulado de íconos antes de la página actual
uint8_t getPreviousIconsCount(int page) {
  uint8_t iconSum = 0;
  for (int i = 0; i < page; i++) {
    iconSum +=
        pages[i].iconCount; // Sumar la cantidad de íconos de cada página previa
  }
  return iconSum;
}

void handleHardware(int totalIcons) {

  // Calculamos el valor base en función del número de íconos previos a la
  // página actual
  uint8_t previousIconsCount = getPreviousIconsCount(currentPage);
  uint8_t startValue =
      1 + (previousIconsCount *
           4); // Cada ícono ocupa 4 espacios en el cálculo de CC

  // Cálculo de los valores CC para los potenciómetros en función del ítem
  // seleccionado
  potCCValues[0] = (4 * selectedItem) + startValue;
  potCCValues[1] = potCCValues[0] + 1;
  potCCValues[2] = potCCValues[0] + 2;
  potCCValues[3] = potCCValues[0] + 3;

  // Manejamos los potenciómetros usando las CC calculadas dinámicamente
  // handlePots();
  if (currentPage == getPageIndexByName("volume")) {
    handlePots();
  }
  handleButtonPresses();
  handleRotaryEncoder(totalIcons);
}
