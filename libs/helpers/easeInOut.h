// Ease-in-out cubic function
float easeInOut(float t, float b, float c, float d) {
  t /= d / 2;
  if (t < 1)
    return c / 2 * t * t * t + b;
  t -= 2;
  return c / 2 * (t * t * t + 2) + b;
}
