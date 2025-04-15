// serverVars.cpp
#include "serverVars.h"

const char *ssid = "ESPMIDI config";
const char *password = "Papita34";
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WebServer server(80);