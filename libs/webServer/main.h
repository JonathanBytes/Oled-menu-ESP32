#include <WebServer.h>
#include <WiFi.h>

#include "serverVars.h"
#include "pages.h"

void setupServerRoutes() {
  // Configurar rutas del servidor
  server.onNotFound(handleNotFound);
  server.on("/", handleRoot);
  server.on("/todo", handleTODO);
  server.on("/setBank", handleSetBank);
  server.on("/editBank", handleEditBank); // Nueva ruta para editar banco
  server.on("/saveBank", handleSaveBank); // Nueva ruta para guardar banco
}

void setupServer() {

  // AP Mode
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);

  delay(100);

  setupServerRoutes();
  server.begin(); // Iniciar servidor web
}
