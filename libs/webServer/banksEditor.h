#ifndef BANKS_EDITOR_H
#define BANKS_EDITOR_H

#include <ArduinoJson.h>
#include <WebServer.h>

// Declarations – these globals are defined in jsonSetup.h
extern DynamicJsonDocument doc;
extern JsonArray banksArray;

extern WebServer server;

void handleBanksList();
void handleEditBank();
void handleSaveBank();

#endif