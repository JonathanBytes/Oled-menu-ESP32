// Variables for FPS calculation and toggle
unsigned long previousMillis = 0;
int frameCount = 0;
float fps = 0;
// If you want an specific frame rate you can set it like this: int frameDelay = 1000 / desiredFPS;
// The fps should be 1000 / frameDelay if the performance is good.

// Function to calculate and display FPS
void updateFPS() {
  frameCount++;
  unsigned long currentMillis = millis();
  
  // Calculate FPS every second
  if (currentMillis - previousMillis >= 1000) {
    fps = frameCount / ((currentMillis - previousMillis) / 1000.0);
    previousMillis = currentMillis;
    frameCount = 0;
  }
  
  // Display FPS in the top-left corner
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, DISPLAY_HEIGHT - 10, "FPS: " + String(fps, 2));
}
