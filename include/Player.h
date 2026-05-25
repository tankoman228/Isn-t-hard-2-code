#pragma once

#include <Values.h>
#include <Physics.h>

inline Sq p = Sq(0, 0, 35);
inline float ex = 0, ey = 0; //eyes

inline float accelerate = 0;
#define eyes_accelerate 0.1;

float middle(float a, float b);
float middle(float a, float b, float c, float d, float e, float f);

inline float last_coordinates[6][2] = { 0,0,0,0,0,0,0,0,0,0,0,0 };

void render_player();
void player_processing();
