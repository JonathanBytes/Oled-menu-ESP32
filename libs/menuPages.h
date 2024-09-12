struct Page {
  const unsigned char** icons;
  int iconCount;
};

// Define los íconos de cada página
const unsigned char* iconsPage1[] = {icon_drive, icon_amp_fndr, icon_amp_mrsh, icon_cab, icon_reverb};
const unsigned char* iconsPage2[] = {icon_back, icon_gear, icon_save};

// Crear páginas
Page pages[] = {
    {iconsPage1, sizeof(iconsPage1) / sizeof(iconsPage1[0])}, // Página 1 con 5 íconos
    {iconsPage2, sizeof(iconsPage2) / sizeof(iconsPage2[0])}  // Página 2 con 3 íconos
};

// Número total de páginas
int totalPages = sizeof(pages) / sizeof(pages[0]);
