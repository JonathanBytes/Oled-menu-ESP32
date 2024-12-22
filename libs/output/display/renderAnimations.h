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

float animatePosition(float start, float target, unsigned long startTime, int duration) {
  unsigned long elapsedTime = millis() - startTime;

  // Ensure we don't overshoot the duration
  if (elapsedTime >= duration) {
    return target; // Snap to the target at the end of the animation
  }

  // Use an easing function for smooth animation
  float t = (float)elapsedTime / duration;
  t = (t > 1.0) ? 1.0 : t; // Clamp t to [0, 1]

  // Easing: SmoothStep
  t = t * t * (3.0f - 2.0f * t);

  float interpolated = start + (target - start) * t;

  // Snap to target if within 1 pixel
  if (abs(interpolated - target) < 1.0f) {
    return target;
  }

  return interpolated;
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
