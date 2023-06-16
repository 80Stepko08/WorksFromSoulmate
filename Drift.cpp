#define CenterX ((LED_COLS / 2) - 0.5)
#define CenterY ((LED_ROWS / 2) - 0.5)
const byte maxDim = max(LED_COLS, LED_ROWS);
byte effect= 0;
bool change = true;

void drawPixelXYF(float x, float y,
  const CRGB & color) {
  // extract the fractional parts and derive their inverses
  uint8_t xx = (x - (int) x) * 255, yy = (y - (int) y) * 255, ix = 255 - xx, iy = 255 - yy;
  // calculate the intensities for each affected pixel
  #define WU_WEIGHT(a, b)((uint8_t)(((a) * (b) + (a) + (b)) >> 8))
  uint8_t wu[4] = {
    WU_WEIGHT(ix, iy),
    WU_WEIGHT(xx, iy),
    WU_WEIGHT(ix, yy),
    WU_WEIGHT(xx, yy)
  };
  // multiply the intensities by the colour, and saturating-add them to the pixels
  for (uint8_t i = 0; i < 4; i++) {
    int16_t xn = x + (i & 1), yn = y + ((i >> 1) & 1);
    CRGB clr = leds[XY(xn, yn)];
    clr.r = qadd8(clr.r, (color.r * wu[i]) >> 8);
    clr.g = qadd8(clr.g, (color.g * wu[i]) >> 8);
    clr.b = qadd8(clr.b, (color.b * wu[i]) >> 8);
    leds[XY(xn, yn)] = clr;
  }
  #undef WU_WEIGHT
}

draw() {
  FastLED.clear(); //fadeToBlackBy(leds, NUM_LEDS, 16);
  unsigned long t = millis()/20;
  for(float i = 1; i <maxDim / 2.; i+=0.5) {
    double angle = radians(t * (maxDim/2-i));
    drawPixelXYF(CenterX + sin(angle) * i, CenterY + cos(angle) * i, ColorFromPalette(PartyColors_p, (i * 20) + (t / 20)));
    switch(effect){
    case 1: case 3: drawPixelXYF(CenterX + cos(angle) * i, CenterY + sin(angle) * i, ColorFromPalette(PartyColors_p, (i * 20) + (t / 20)));break;
  }}
  switch(effect){
    case 2: case 3: blur2d(leds, LED_COLS, LED_ROWS, 16); break;
  }
  delay(16);
}