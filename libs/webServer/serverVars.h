// serverVars.h
#ifndef SERVER_VARS_H
#define SERVER_VARS_H

#include <WiFi.h>
#include <WebServer.h>

extern const char *ssid;
extern const char *password;
extern IPAddress local_ip;
extern IPAddress gateway;
extern IPAddress subnet;
extern WebServer server;

#endif