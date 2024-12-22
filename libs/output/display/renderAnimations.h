// Function to animate a bitmap and update FPS
void animateBitmap(const unsigned char *bitmapArray[], int frames,
                   int frameDelay, int repetitions, int width, int height,
                   int xPos, int yPos) {
  for (int j = 0; j < repetitions; j++) {
    for (int i = 0; i < frames; i++) {
      display.clear();
      display.drawXbm(xPos, yPos, width, height, bitmapArray[i]);

      if (SHOW_FPS) {
        updateFPS();
      }
      display.display();
      if (FRAME_CAP) {
        delay(frameDelay); // delay for fixed framerate
      }
    }
  }
}

void bootAnimations() {
  animateBitmap(angryCat, 28, 16, 2, 30, 30, (DISPLAY_WIDTH - 30) / 2,
                (DISPLAY_HEIGHT - 30) / 2);
  animateBitmap(skate, 28, 16, 2, 32, 32, (DISPLAY_WIDTH - 32) / 2,
                (DISPLAY_HEIGHT - 30) / 2);
}

float easeInOutQuad(float t, float b, float c, float d) {
  t /= d / 2;
  if (t < 1) return c / 2 * t * t + b;
  t--;
  return -c / 2 * (t * (t - 2) - 1) + b;
}

float animatePosition(float a, float b, unsigned long startTime, unsigned long duration) {
  // Calculate elapsed time
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - startTime;

  // Clamp elapsed time to duration
  if (elapsedTime > duration) elapsedTime = duration;

  // Use easing function to interpolate
  float currentPosition = easeInOutQuad(elapsedTime, a, b - a, duration);
  // Use easing cubic
  // float currentPosition = easeInOut(elapsedTime, a, b - a, duration);

  // Stop animation if the position reaches the target
  if (elapsedTime >= duration) {
    return b;
  }

  return currentPosition;
}

// void animateRectangle(int startX, int endX, int scrollStartX, int scrollEndX,
//                       void currentUI(int x, int scroll), float duration = 250) {
//   unsigned long startTime = millis();

//   while (millis() - startTime < duration) {
//     unsigned long currentTime = millis() - startTime;
//     currentX = easeInOut(currentTime, startX, endX - startX, duration);
//     scrollCurrentX = easeInOut(currentTime, scrollStartX,
//                                scrollEndX - scrollStartX, duration);

//     currentUI(currentX, scrollCurrentX);
//     if (FRAME_CAP) {
//       delay(FRAME_DELAY);
//       delay(0); // Allow other tasks to run
//     }
//   }

//   currentX = endX;
//   scrollCurrentX = scrollEndX;
//   currentUI(currentX, scrollCurrentX);
// }
