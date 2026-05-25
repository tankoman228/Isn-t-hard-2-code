#pragma once

#include <Physics_processing.h>

#include <Physics.h>
#include <Values.h>
#include <Player.h>
#include <Blocks.h>

void physics_processing(float dt) {

	if (context_menu) return; 

	player_processing(dt);

	for (int i = 0; i < map_floor.size(); i++) {
		map_floor[i]->cycle();

		for (int j = 0; j < movables.size(); j++) {
			if (intersection(*map_floor[i], *movables[j])) {

				float helper_s[2];

				helper_s[0] = map_floor[i]->x - movables[j]->x;
				helper_s[1] = map_floor[i]->y - movables[j]->y;

				if (abs(helper_s[0]) > abs(helper_s[1])) {

					if (abs(helper_s[0]) > 62 || abs(helper_s[0]) <= 1) {
						continue;
					}

					movables[j]->x += map_floor[i]->magnet * sign(helper_s[0]);
				}
				else {

					if (abs(helper_s[1]) > 62 || abs(helper_s[1]) <= 1) {
						continue;
					}

					movables[j]->y += map_floor[i]->magnet * sign(helper_s[1]);
				}

			}
		}

	}

	for (int i = 0; i < electric.size(); i++) {
		electric[i]->cycle();
	}

	for (int i = 0; i < map_basic.size(); i++) {
		map_basic[i]->cycle();
	}

	for (int i = 0; i < movables.size(); i++) {

		for (int j = 0; j < map_basic.size(); j++) {
			if (collide(*movables[i], *map_basic[j], dt)) {
			}
		}

		for (int j = 0; j < movables.size(); j++) {
			if (i != j) {
				if (collide(*movables[j], *movables[i], dt)) {
				};
			}
		}

		if (collide(p, *movables[i], dt)) {
			colint = 0;

			if (Keyboard::isKeyPressed(Keyboard::LControl)) {
				if (abs(p.sx) > 2 || abs(p.sy) > 2) {
					if (!push2.getStatus()) {
						push2.setVolume(7);
						push2.play();
					}
				}
			}
			else {
				if (abs(p.sx) > 1 || abs(p.sy) > 1) {
					push2.setVolume(100 * (abs(p.sx) + abs(p.sy)) / 40);
					push2.play();
				}
			}
		}

		movables[i]->cycle(dt);
	}

	Sleep(1);
}
