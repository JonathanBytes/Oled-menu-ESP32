#include "animations/main.h"
#include "icons.h"
#include "ui.h"

// Arreglo de todos los íconos. (Total bytes usados en PROGMEM = 640)
const unsigned char *iconAllArray[5] = {icon_drive, icon_amp_fndr,
                                        icon_amp_mrsh, icon_cab, icon_reverb};

// Arreglo de los elementos de la UI. (Total bytes usados en PROGMEM = 240)
const unsigned char *uiAllArray[3] = {scrollbar, scrollindicator, selection};
