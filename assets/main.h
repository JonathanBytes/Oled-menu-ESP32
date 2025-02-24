#include "animations/main.h"
#include "iconsLogic.h"
#include "ui.h"

// Array of all bitmaps for convenience. (Total bytes used to store images in
// PROGMEM = 1024)
const unsigned char *iconAllArray[5] = {icon_drive, icon_amp_fndr,
                                        icon_amp_mrsh, icon_cab, icon_reverb};

const unsigned char *uiIconsAllArray[11] = {
    icon_back,     icon_gear,    icon_save,      icon_trash,
    icon_edit,     icon_home,    icon_knob,      icon_restart,
    icon_shutdown, icon_live, icon_brightness};

// Arreglo de los elementos de la UI. (Total bytes usados en PROGMEM = 240)
const unsigned char *uiAllArray[3] = {scrollbar, selection, paramSelection};
