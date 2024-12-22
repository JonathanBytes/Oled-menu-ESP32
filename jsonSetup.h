#include "banks.h" // Include your JSON data header file
#include <ArduinoJson.h>
#include <pgmspace.h>

// Declare a global DynamicJsonDocument
DynamicJsonDocument doc(4096); // Adjust size to fit your JSON structure
JsonArray banksArray;
JsonObject currentBank;
JsonArray presets;
JsonObject currentPreset;
String currentPresetName;
String currentBankName;

void jsonSetup() {
  // Copy JSON from PROGMEM to RAM and parse it
  DeserializationError error = deserializeJson(doc, banks);

  // Check for errors in JSON parsing
  if (error) {
    Serial.print(F("Failed to parse JSON: "));
    Serial.println(error.c_str());
    while (true)
      ; // Halt execution on error
  }

  // Debug: Print parsed JSON data
  banksArray = doc.as<JsonArray>();
  // for (JsonObject bank : banksArray) {
  //   const char *bankName = bank["name"];
  //   Serial.print("Bank Name: ");
  //   Serial.println(bankName);

  //   JsonArray presets = bank["presets"];
  //   for (JsonObject preset : presets) {
  //     const char *presetName = preset["name"];
  //     Serial.print("  Preset Name: ");
  //     Serial.println(presetName);

  //     JsonArray onActivate = preset["onActivate"];
  //     Serial.println("    On Activate:");
  //     for (JsonObject message : onActivate) {
  //       const char *type = message["type"];
  //       int address = message["address"];
  //       int value = message.containsKey("value") ? message["value"] : -1;

  //       Serial.print("      Type: ");
  //       Serial.print(type);
  //       Serial.print(", Address: ");
  //       Serial.print(address);
  //       if (value != -1) {
  //         Serial.print(", Value: ");
  //         Serial.print(value);
  //       }
  //       Serial.println();
  //     }

  //     JsonArray onDeactivate = preset["onDeactivate"];
  //     Serial.println("    On Deactivate:");
  //     for (JsonObject message : onDeactivate) {
  //       const char *type = message["type"];
  //       int address = message["address"];
  //       int value = message.containsKey("value") ? message["value"] : -1;

  //       Serial.print("      Type: ");
  //       Serial.print(type);
  //       Serial.print(", Address: ");
  //       Serial.print(address);
  //       if (value != -1) {
  //         Serial.print(", Value: ");
  //         Serial.print(value);
  //       }
  //       Serial.println();
  //     }
  //   }
  // }

  currentPresetName = banksArray[0]["presets"][0]["name"].as<const char *>();
  currentBankName = banksArray[0]["name"].as<const char *>();

  Serial.println(F("JSON setup complete."));
}
