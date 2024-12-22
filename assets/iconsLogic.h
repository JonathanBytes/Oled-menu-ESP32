#include "icons.h"

int brightness = 0;

struct IconParams {
  const unsigned char *icon;
  const char *name;
  const char *params[4];
  int ccNumbers[4];
  int paramValues[4];
  int paramsCount;
};

IconParams iconParamsArray[] = {
    {icon_drive,
     "Drive",
     {"Gain", "Tone", "Mix", "Level"},
     {10, 11, 12, 13},
     {0, 15, 48, 100},
     4},
    {icon_amp_fndr,
     "Amp Fender",
     {"Volume", "Bass", "Mid", "Treb"},
     {20, 21, 22, 23},
     {0, 0, 0, 0},
     4},
    {icon_amp_mrsh,
     "Amp Marshall",
     {"Vol", "Bass", "Mid", "Treb"},
     {30, 31, 32, 33},
     {0, 0, 0, 0},
     4},
    {icon_cab,
     "Cab",
     {"Mic", "Pos", "Dist", "Level"},
     {40, 41, 42, 43},
     {0, 0, 0, 0},
     4},
    {icon_reverb,
     "Reverb",
     {"Decay", "Mix", "L-Cut", "H-Cut"},
     {50, 51, 52, 53},
     {0, 0, 0, 0},
     4},
    {icon_brightness,
     "Brightness",
     {"Value", "", "", ""},
     {60, 61, 62, 63},
     {brightness, 0, 0, 0},
     1},
    {icon_fps_overlay,
     "FPS Overlay",
     {"Value", "", "", ""},
     {0, 0, 0, 0},
     {0, 0, 0, 0},
     1},
    {icon_fps_lock,
     "FPS Lock",
     {"Enable", "Max FPS", "", ""},
     {0, 0, 0, 0},
     {0, 0, 0, 0},
     2},
};

// Brightness from params
// int displayBrightness = iconParamsArray[5].paramValues[0];

int getIconParamsCount(const unsigned char *icon) {
  for (const auto &iconParams : iconParamsArray) {
    if (iconParams.icon == icon) {
      return iconParams.paramsCount;
    }
  }
  return 0;
}
