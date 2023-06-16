//Idea from https://www.youtube.com/watch?v=HsA-6KIbgto&ab_channel=GreatScott%21
//Octopus
//Stepko and Sutaburosu
//22/05/22
#define legs 3
bool setupm = 1;
const uint8_t C_X = LED_COLS / 2;
const uint8_t C_Y = LED_ROWS / 2;
const uint8_t mapp = 255 / max(LED_ROWS, LED_COLS);
struct {
  uint8_t angle;
  uint8_t radius;
}
rMap[LED_COLS][LED_ROWS];
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
  static byte speed = 3;
  static uint16_t t;
  t += speed;
  for (uint8_t x = 0; x < LED_COLS; x++) {
    for (uint8_t y = 0; y < LED_ROWS; y++) {
      byte angle = rMap[x][y].angle;
      byte radius = rMap[x][y].radius;
      leds[XY(x, y)] = CHSV(t / 2 - radius, 255, sin8(sin8((angle * 4 - radius) / 4 + t) + radius - t * 2 + angle * legs));
    }
  }
  delay(16);
}