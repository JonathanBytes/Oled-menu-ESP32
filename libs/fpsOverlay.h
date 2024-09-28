// Variables for FPS calculation and toggle
unsigned long previousMillis = 0;
int frameCount = 0;
float fps = 0;
// If you want an specific frame rate you can set it like this: int frameDelay =
// 1000 / desiredFPS; The fps should be 1000 / frameDelay if the performance is
// good.

void updateFPS() {
  frameCount++;
  unsigned long currentMillis = millis();

  // Calculate FPS every second
  if (currentMillis - previousMillis >= 1000) {
    fps = frameCount / ((currentMillis - previousMillis) / 1000.0);
    previousMillis = currentMillis;
    frameCount = 0;
  }

  // Set font
  display.setFont(ArialMT_Plain_10);

  // FPS text
  String fpsText = "FPS: " + String(fps, 2);

  // Get the width of the FPS string
  int textWidth = display.getStringWidth(fpsText);
  int textHeight = 7; // Font height is 10 pixels for ArialMT_Plain_10
  int padding = 2;    // Padding around text

  // Draw white rectangle to overwrite content below
  display.setColor(WHITE); // Set drawing color to black for text
  display.fillRect(
      0, DISPLAY_HEIGHT - (textHeight + padding), textWidth + padding,
      textHeight + padding); // Fill white background (+4 adds padding)

  // Draw the FPS text in black
  display.setColor(BLACK); // Set drawing color to white for rectangle
  display.drawString(padding / 2,
                     DISPLAY_HEIGHT - (textHeight + 3 + padding / 2),
                     fpsText); // Draw the FPS string in black

  // Set the color back to white for the rest of the display
  display.setColor(WHITE);
}
