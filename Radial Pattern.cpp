//RadialPattern
//Stepko and Sutaburosu
//04/05/22
bool setupm = 1;
const uint8_t C_X = LED_COLS / 2;
const uint8_t C_Y = LED_ROWS / 2;
const uint8_t mapp = 255 / LED_COLS;
struct{
  uint8_t angle;
  uint8_t radius;
} rMap[LED_COLS][LED_ROWS];

void draw() {
  FastLED.clear();
  if (setupm) {
    setupm = 0;
    for (int8_t x = -C_X; x < C_X + (LED_COLS % 2); x++) {
      for (int8_t y = -C_Y; y < C_Y + (LED_ROWS % 2); y++) {
        rMap[x + C_X][y + C_Y].angle = 128 * (atan2(y, x) / PI);
        rMap[x + C_X][y + C_Y].radius = hypot(x, y) * mapp; //thanks Sutaburosu
      }
    }
  }

  static byte speed = 2;
  static uint32_t t;
  t += speed;
  for (uint8_t x = 0; x < LED_COLS; x++) {
    for (uint8_t y = 0; y < LED_ROWS; y++) {
      byte angle = rMap[x][y].angle;
      byte radius = rMap[x][y].radius;
      leds[XY(x, y)].g = (((angle+t/6)/32%2) ^ (((radius-t)/64)%2))*220;
      leds[XY(x, y)].r = (((angle+t)/32%2) ^ (((radius-t/2)/64)%2))*255;
      //leds[XY(x, y)].b = (((angle)/32%2) ^ (((radius)/64)%2))*255;
    }
  }

  delay(20);
}