#ifndef __FIRE_H_
#define __FIRE_H_

const uint8_t MAX_BULLETS = 118;

struct Bullet {
  int8_t x, y;
  bool fired = false;
};

extern Bullet fire[MAX_BULLETS];

void init_bullet();

void draw_bullet();
void move_bullet();
void trigger_bullet(int shipPos);
#endif

