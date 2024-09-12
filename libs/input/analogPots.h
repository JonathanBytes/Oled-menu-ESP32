#include <AH/Hardware/FilteredAnalog.hpp>

int analog1Pin = 33;
int analog2Pin = 35; // 32 used by wifi (maybe)
int analog3Pin = 34;
int analog4Pin = 39; // Labeled as VN on board
const int filtering = 6;

// Create a filtered analog object:
FilteredAnalog<7,         // Output precision in bits
               filtering, // The amount of filtering
               uint32_t,  // The integer type for the filter calculations
               analog_t   // The integer type for the upscaled analog values
               >
    analog1 = analog1Pin;

FilteredAnalog<7,         // Output precision in bits
               filtering, // The amount of filtering
               uint32_t,  // The integer type for the filter calculations
               analog_t   // The integer type for the upscaled analog values
               >
    analog2 = analog2Pin;

FilteredAnalog<7,         // Output precision in bits
               filtering, // The amount of filtering
               uint32_t,  // The integer type for the filter calculations
               analog_t   // The integer type for the upscaled analog values
               >
    analog3 = analog3Pin;

FilteredAnalog<7,         // Output precision in bits
               filtering, // The amount of filtering
               uint32_t,  // The integer type for the filter calculations
               analog_t   // The integer type for the upscaled analog values
               >
    analog4 = analog4Pin;

void analogPotsSetup() {
  // Select the correct ADC resolution
  analog1.setupADC();
  analog2.setupADC();
  analog3.setupADC();
  analog4.setupADC();
  // Initialize the filter to whatever the value on the input is right now
  // (otherwise, the filter is initialized to zero and you get transients)
  analog1.resetToCurrentValue();
  analog2.resetToCurrentValue();
  analog3.resetToCurrentValue();
  analog4.resetToCurrentValue();
}

void handlePot(AH::FilteredAnalog<7, filtering, uint32_t, analog_t> &analog,
               int CCNumber) {
  if (analog.update()) {
    midi.sendCC({CCNumber, Channel_1}, analog.getValue());
  }
}
