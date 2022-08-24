#pragma once

#include "Physics.h"
#include "Values.h"
#include "Player.h"

void physics_processing() {

	while (window.isOpen()) {

		if (stop_physics || context_menu) {
			logg << "Physics was paused" << endl;
			while (stop_physics || context_menu) { Sleep(300); }
			logg << "Physics continue" << endl;
		}

		player_processing();

		for (i = 0; i < map_floor.size(); i++) {
			map_floor[i]->cycle();

			for (j = 0; j < movables.size(); j++) {
				if (intersection(*map_floor[i], *movables[j])) {

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

		for (i = 0; i < electric.size(); i++) {
			electric[i]->cycle();
		}

		for (i = 0; i < map_basic.size(); i++) {
			map_basic[i]->cycle();
		}

		for (i = 0; i < movables.size(); i++) {

			for (j = 0; j < map_basic.size(); j++) {
				if (collide(*movables[i], *map_basic[j])) {
					/*movables[j]->sx /= 2; movables[j]->sy /= 2;*/

					/*collide(*movables[i], *map_basic[j]);*/
				}
			}

			for (j = 0; j < movables.size(); j++) {
				if (i != j) {
					if (collide(*movables[j], *movables[i])) {
						/*movables[i]->move(); movables[j]->move();*/
						movables[j]->sx /= 2; movables[j]->sy /= 2;
						movables[i]->sx /= 2; movables[i]->sy /= 2;

						p.sx /= 2.35;
						p.sy /= 2.35;
					};
				}
			}

			if (collide(p, *movables[i])) {
				p.sx /= 1.09;
				p.sy /= 1.09;

				colint = 0;

				if (Keyboard::isKeyPressed(Keyboard::LControl)) {
					if (abs(p.sx) > 2 || abs(p.sy) > 2) {
						if (!push2.getStatus()) {
							push2.setVolume(7);
							push2.play();
							p.sx /= 2;
							p.sy /= 2;
						}
					}
				}
				else {
					if (abs(p.sx) > 1 || abs(p.sy) > 1) {
						push2.setVolume(100 * (abs(p.sx) + abs(p.sy)) / 40);
						push2.play();
						p.sx /= 3;
						p.sy /= 3;
					}
				}

				/*p.move(-p.sx, -p.sy);*/
			}

			movables[i]->cycle();
		}

		Sleep(1);

	}
	if (!window.isOpen()) {
		logg << "Error! Physics has been stopped!" << endl;
		mode = "menu";
		close = true;
	}
	logg << "Physics has been stopped" << endl;
}
