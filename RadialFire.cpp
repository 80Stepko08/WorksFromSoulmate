//RadialFire
//Stepko and Sutaburosu
//23/12/21
bool setupm = 1;
#define C_X (LED_COLS / 2)
#define C_Y (LED_ROWS / 2)
byte XY_angle[LED_COLS][LED_ROWS];
byte XY_radius[LED_COLS][LED_ROWS];
void draw() {
   if (setupm) {
    setupm = 0;
    for (int8_t x = -C_X; x < C_X + (LED_COLS % 2); x++) {
      for (int8_t y = -C_Y; y < C_Y + (LED_ROWS % 2); y++) {
        XY_angle[x + C_X][y + C_Y] = 128 * (atan2(y, x) / PI);
        XY_radius[x + C_X][y + C_Y] = hypot(x, y); //thanks Sutaburosu
      }
    }
  }
  static byte scaleX = 16;
  static byte scaleY = 1;

  static byte speed = 24;
  static uint32_t t;
  t += speed;
  for (uint8_t x = 0; x < LED_COLS; x++) {
    for (uint8_t y = 0; y < LED_ROWS; y++) {
      byte angle = XY_angle[x][y];
      byte radius = XY_radius[x][y];
      int16_t Bri = inoise8(angle*scaleX, (radius * scaleY)-t ) - radius * (255 / LED_ROWS);
      byte Col = Bri;
      if (Bri < 0) Bri = 0;
      if (Bri != 0) Bri = 256 - (Bri * 0.2);
      nblend(leds[XY(x, y)], ColorFromPalette(HeatColors_p, Col, Bri), speed);
    }
  }

  delay(20);
}