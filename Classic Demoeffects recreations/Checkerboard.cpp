void draw() {
  uint16_t a = millis() >> 4;
  for (byte z = 2; z < 6; z++) {
    uint8_t Xx = sin8((a >> 2) + (z << 5)) >> 3;
    uint8_t Yy = sin8((a >> 1) + (z << 5)) >> 3;
    CRGB col = CHSV(((z << 8) - 1) / 5, 255, ~(255 / z));
    for (byte x = 0; x < LED_COLS; x++) {
      for (byte y = 0; y < LED_ROWS; y++) {
        leds[XY(x, y)] = (((x+Xx)/(z << 1)%2) ^ ((y+Yy)/(z << 1)%2)) ? col : (z == 2) ? CRGB(0, 0, 0) : leds[XY(x, y)];
      }
    }
  }
}