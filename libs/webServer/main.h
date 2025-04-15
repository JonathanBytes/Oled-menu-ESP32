#include <WebServer.h>
#include <WiFi.h>

#include "serverVars.h"
#include "serverVars.cpp"
#include "pages.h"
#include "banksEditor.h" // Include our new editor routes
#include "banksEditor.cpp"

void setupServerRoutes()
{
  // Configurar rutas del servidor
  server.onNotFound(handleNotFound);
  server.on("/", handleRoot);
  server.on("/todo", handleTODO);

  // New routes for bank editing:
  server.on("/banksList", HTTP_GET, handleBanksList);
  server.on("/editBank", HTTP_GET, handleEditBank);
  server.on("/saveBank", HTTP_POST, handleSaveBank);
}

void setupServer()
{

  // AP Mode
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);

  delay(100);

  setupServerRoutes();
  server.begin(); // Iniciar servidor web
}
