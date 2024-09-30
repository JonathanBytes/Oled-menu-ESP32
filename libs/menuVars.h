int selectedItem = 0;
int firstVisibleItem = 0;
int currentPage = 0;

struct Page {
  const unsigned char **icons;
  int iconCount;
};

// Define los íconos de cada página
const unsigned char *iconsPage1[] = {icon_back, icon_gear};
const unsigned char *iconsPage2[] = {icon_back, icon_drive,  icon_amp_fndr,
                                     icon_cab,  icon_reverb, icon_save};
const unsigned char *iconsPage3[] = {icon_back, icon_drive,  icon_amp_mrsh,
                                     icon_cab,  icon_reverb, icon_save};

// Crear páginas
Page pages[] = {
    {iconsPage1,
     sizeof(iconsPage1) / sizeof(iconsPage1[0])}, // Página 1 con 6 íconos
    {iconsPage2,
     sizeof(iconsPage2) / sizeof(iconsPage2[0])}, // Página 2 con 3 íconos
    {iconsPage3,
     sizeof(iconsPage3) / sizeof(iconsPage3[0])}, // Página 3 con 6 íconos
};

// Número total de páginas
int totalPages = sizeof(pages) / sizeof(pages[0]);

