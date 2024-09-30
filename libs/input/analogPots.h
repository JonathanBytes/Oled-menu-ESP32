#include <AH/Hardware/FilteredAnalog.hpp>

unsigned long last_update_time =
    0; // To track the last time the display was updated
const unsigned long display_duration = 3000; // Display duration in milliseconds

// Define the analog pins in an array
int analogPins[] = {33, 35, 34, 39}; // Pin numbers for analog inputs

const int numAnalogs =
    sizeof(analogPins) / sizeof(analogPins[0]); // Total number of analog pins
const int filtering = 4;
const int bitPrecision = 12;

// Define an array of FilteredAnalog objects
FilteredAnalog<bitPrecision, // Output precision in bits
               filtering,    // The amount of filtering
               uint32_t,     // The integer type for the filter calculations
               analog_t      // The integer type for the upscaled analog values
               >
    analogs[numAnalogs] = {analogPins[0], analogPins[1], analogPins[2],
                           analogPins[3]};

// Variables to store potentiometer values
int potValues[numAnalogs] = {0, 0, 0, 0}; // Initial values for all pots
int potCCValues[numAnalogs] = {0, 0, 0, 0};
int updatedPotIndex = -1; // To track which potentiometer was updated
const String potLabels[numAnalogs] = {"Clean", "Rythm", "Solo", "Master"}; // Labels for the pots

void analogPotsSetup() {
  // Select the correct ADC resolution
  for (int i = 0; i < numAnalogs; i++) {
    analogs[i].setupADC();
    analogs[i].resetToCurrentValue();
  }
}

void handlePots() {
  for (int i = 0; i < numAnalogs; i++) {
    if (analogs[i].update()) {
      int new_value = map(analogs[i].getValue(), 0, 4080, 0, 100);

      // Only update if the value has changed significantly
      int tolerance = 1;
      if (potValues[i] > new_value + tolerance || potValues[i] < new_value - tolerance) {
        potValues[i] = new_value;

        int ccValue = map(analogs[i].getValue(), 0, 4080, 0, 127); // Map the value to 0-127
        midi.sendCC({potCCValues[i], Channel_1}, ccValue); // Send the CC message

        // Set updatedPotIndex to track the last updated potentiometer
        updatedPotIndex = i;
        last_update_time = millis();  // Update the timestamp when a change happens
      }
    }
  }
}

// Function to determine if the circle should be drawn
bool shouldDrawCircle() {
  return (millis() - last_update_time < display_duration);
}
