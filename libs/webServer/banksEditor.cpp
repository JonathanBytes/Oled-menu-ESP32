#include "banksEditor.h"
#include "serverVars.h" // Contains the "server" instance

// Show a list of banks with an Edit button for each
void handleBanksList()
{
  String html = "<html><head><title>Banks List</title></head><body>";
  html += "<h1>Banks List</h1>";
  for (size_t i = 0; i < banksArray.size(); i++)
  {
    JsonObject bank = banksArray[i].as<JsonObject>();
    String bankName = bank["name"].as<const char *>();
    html += "<div style='margin-bottom:20px;padding:10px;border:1px solid #ccc;'>";
    html += "<strong>" + bankName + "</strong><br>";
    html += "<a href=\"/editBank?bank=" + String(i) + "\">Edit Bank</a>";
    html += "</div>";
  }
  html += "</body></html>";
  server.send(200, "text/html", html);
}

// Edit a single bank (chosen by query parameter "bank")
void handleEditBank()
{
  if (!server.hasArg("bank"))
  {
    server.send(400, "text/plain", "Bank index missing");
    return;
  }
  int bankIndex = server.arg("bank").toInt();
  if (bankIndex < 0 || bankIndex >= (int)banksArray.size())
  {
    server.send(400, "text/plain", "Invalid bank index");
    return;
  }

  JsonObject bank = banksArray[bankIndex].as<JsonObject>();
  String bankName = bank["name"].as<const char *>();

  String html = "<html><head><title>Edit Bank</title><meta name='viewport' content='width=device-width, initial-scale=1'></head><body>";
  html += "<h1>Edit Bank: " + bankName + "</h1>";

  // List presets
  JsonArray presets = bank["presets"].as<JsonArray>();
  for (size_t i = 0; i < presets.size(); i++)
  {
    JsonObject preset = presets[i].as<JsonObject>();
    String presetName = preset["name"].as<const char *>();
    html += "<h2>Preset: " + presetName + "</h2>";

    // Display onActivate messages
    html += "<h3>onActivate Messages</h3>";
    JsonArray onActivate = preset["onActivate"].as<JsonArray>();
    for (size_t j = 0; j < onActivate.size(); j++)
    {
      JsonObject msg = onActivate[j];
      String type = msg["type"].as<const char *>();
      int address = msg["address"];
      html += "<p>Message " + String(j + 1) + ": Type: " + type + ", Address: " + String(address);
      if (type == String("control_change"))
      {
        int value = msg.containsKey("value") ? msg["value"] : 0;
        html += ", Value: " + String(value);
      }
      html += "</p>";
    }
    // Optionally display onDeactivate messages similarly
    html += "<h3>onDeactivate Messages</h3>";
    JsonArray onDeactivate = preset["onDeactivate"].as<JsonArray>();
    for (size_t j = 0; j < onDeactivate.size(); j++)
    {
      JsonObject msg = onDeactivate[j];
      String type = msg["type"].as<const char *>();
      int address = msg["address"];
      html += "<p>Message " + String(j + 1) + ": Type: " + type + ", Address: " + String(address);
      if (type == String("control_change"))
      {
        int value = msg.containsKey("value") ? msg["value"] : 0;
        html += ", Value: " + String(value);
      }
      html += "</p>";
    }

    // Form to add a new message (for illustration, we add to onActivate)
    html += "<form action=\"/saveBank\" method=\"POST\" style='margin-bottom:20px;'>";
    html += "<input type=\"hidden\" name=\"bank\" value=\"" + String(bankIndex) + "\">";
    html += "<input type=\"hidden\" name=\"preset\" value=\"" + String(i) + "\">";
    html += "<label for=\"msgType\">Type:</label>";
    html += "<select name=\"type\" id=\"msgType\">";
    html += "<option value=\"control_change\">control_change</option>";
    html += "<option value=\"program_change\">program_change</option>";
    html += "</select><br>";
    html += "<label for=\"address\">Address (0-127):</label>";
    html += "<input type=\"number\" id=\"address\" name=\"address\" min=\"0\" max=\"127\"><br>";
    html += "<label for=\"value\">Value (0-127, optional for program_change):</label>";
    html += "<input type=\"number\" id=\"value\" name=\"value\" min=\"0\" max=\"127\"><br>";
    html += "<button type=\"submit\">Add Message to onActivate</button>";
    html += "</form>";
  }

  html += "<a href='/banksList'>Back to Banks List</a>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

// Handler to receive new message data and update the in-memory JSON
void handleSaveBank()
{
  if (!server.hasArg("bank") || !server.hasArg("preset") || !server.hasArg("type") || !server.hasArg("address"))
  {
    server.send(400, "text/plain", "Missing parameters");
    return;
  }
  int bankIndex = server.arg("bank").toInt();
  int presetIndex = server.arg("preset").toInt();
  String type = server.arg("type");
  int address = server.arg("address").toInt();
  String valueStr = server.arg("value");

  JsonObject bank = banksArray[bankIndex].as<JsonObject>();
  JsonArray presets = bank["presets"].as<JsonArray>();
  JsonObject preset = presets[presetIndex].as<JsonObject>();
  JsonArray onActivate = preset["onActivate"].as<JsonArray>();

  // Create a new message object and add it to onActivate
  JsonObject newMsg = onActivate.createNestedObject();
  newMsg["type"] = type;
  newMsg["address"] = address;
  if (type == String("control_change") && valueStr.length() > 0)
  {
    newMsg["value"] = valueStr.toInt();
  }

  // (Optionally, save the updated JSON to persistent storage such as EEPROM or SPIFFS)
  server.send(200, "text/plain", "Message added successfully");
}