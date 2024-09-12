#ifndef CONSTANTS_H
#define CONSTANTS_H

const int DISPLAY_WIDTH = 128;
const int DISPLAY_HEIGHT = 64;
const int ICON_WIDTH = 28;
const int ICON_HEIGHT = 28;
const int ICON_SPACING = 3;
const int ITEM_WIDTH = ICON_WIDTH + ICON_SPACING;
const int SCROLL_BAR_WIDTH = 7;
const int SCROLL_BAR_HEIGHT = 3;
const int VISIBLE_ICONS =
    DISPLAY_WIDTH / (ICON_SPACING + ICON_WIDTH); // in this case 4

const int BUTTON_PREV_PIN = 16;
const int BUTTON_NEXT_PIN = 4;

#endif
