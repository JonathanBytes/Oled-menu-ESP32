void drawIcons(int page) {
  if (page < 0 || page >= totalPages)
    return; // Validate page

  const Page &currentPage = pages[page];   // Get current page
  int iconsToDraw = currentPage.iconCount; // Number of icons

  // Draw icons
  for (int i = 0; i < VISIBLE_ICONS && i < iconsToDraw; i++) {
    int iconIndex = (firstVisibleItem + i) % iconsToDraw;
    display.drawXbm(3 + ITEM_WIDTH * i, 0, ICON_WIDTH, ICON_HEIGHT,
                    currentPage.icons[iconIndex]);
  }
  // Draw parameters of the selected icon if it has parameters
  if (currentPage.icons[selectedItem] != nullptr) {
    const unsigned char *selectedIcon = currentPage.icons[selectedItem];
    drawIconParameters(selectedIcon);
  }
}
