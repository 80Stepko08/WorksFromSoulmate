bool dir = 1;
byte size = LED_COLS / 8;
void fill_circle(uint8_t cx, uint8_t cy, uint8_t radius) {
  static uint8_t shift;
  EVERY_N_MILLISECONDS(250) {
    if (dir) shift++;
    else shift--;
  }
  for (int8_t y = -radius; y <= radius; y++) {
    for (int8_t x = -radius; x <= radius; x++) {
      if (x * x + y * y <= radius * radius)
        leds[XY(cx + x, cy + y)] = CHSV(0, ((((radius + x + shift) / 2) % 2) xor(((radius + y) / 2) % 2)) * 255, map(sqrt((x * x + y * y)), 0, radius * 1.5, 255, 64));
    }
  }
}

struct { int16_t PosX = LED_COLS * 5;
  int16_t PosY = LED_ROWS * 10 - size * 10;
  int8_t SpeedX = 5;
  float SpeedY = 2; } ball;

void draw() {
  FastLED.clear();
  ball.PosX += ball.SpeedX;
  ball.PosY += ball.SpeedY;
  ball.SpeedY -= 0.9;
  if ((ball.PosX >= (LED_COLS - size) * 10) || (ball.PosX < size * 10)) { constrain(ball.PosX, size * 10, (LED_COLS - size) * 10);
    ball.SpeedX = -ball.SpeedX;
    dir = !dir; }
  if (ball.PosY < size * 10) { constrain(ball.PosY, size * 10, (LED_ROWS - size) * 10);
    ball.SpeedY = -ball.SpeedY; }
  fill_circle(ball.PosX / 10, ball.PosY / 10, size);
}