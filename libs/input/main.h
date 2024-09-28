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
  uint8_t analog1CC = (4 * selectedItem) + startValue;
  uint8_t analog2CC = analog1CC + 1;
  uint8_t analog3CC = analog1CC + 2;
  uint8_t analog4CC = analog1CC + 3;

  // Manejamos los potenciómetros usando las CC calculadas dinámicamente
  handlePot(analog1, analog1CC);
  handlePot(analog2, analog2CC);
  handlePot(analog3, analog3CC);
  handlePot(analog4, analog4CC);
  handleButtonPresses(totalIcons);
  handleRotaryEncoder(totalIcons);
}
