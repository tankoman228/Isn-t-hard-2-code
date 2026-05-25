#pragma once

#include <Values.h>
#include <Physics.h>

inline Sq p = Sq(0, 0, 35);
inline float ex = 0, ey = 0; //eyes

inline float accelerate = 0;

float middle(float a, float b);
float middle(float a, float b, float c, float d, float e, float f);

inline float last_coordinates[6][2] = { 0,0,0,0,0,0,0,0,0,0,0,0 };

void render_player(float dt);
void player_processing(float dt);
