#ifndef __METEORITES_H_
#define __METEORITES_H_
const uint8_t MAX_METEORITES = 4;

struct Meteorites {
  int8_t x, y, vx;
};

extern Meteorites meteo[MAX_METEORITES];

void init_meteo();
void move_meteo();
void draw_meteo();
#endif

