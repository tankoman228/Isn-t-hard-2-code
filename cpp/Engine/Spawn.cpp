#include <Blocks.h>
#include <Particles.h>

void spawn_movable(int x, int y, int _type) {
	movables.push_back(new Movable(x, y, *MapBasicTextures[5], IntRect(_type / 90 * 128, 0, 128, 128)));
}

void smoke_spawn(string type, int x, int y) {

	logg << "Smoke spawn: " << type << " \n";;
	for (int k = 0; k < 3; k++) {
		if (!particle[k][0].enabled) {
			for (int ws = 0; ws < partnum; ws++) {
				particle[k][ws].x = x;
				particle[k][ws].y = y;
				particle[k][ws].alpha = 255;
				particle[k][ws].enabled = true;
				particle[k][ws].rotation_speed = 0;
				particle[k][ws].particle.setRotation(rand() % 360);
			}
			if (type == "smoke") {
				for (int ws = 0; ws < partnum; ws++) {
					particle[k][ws].speed_x = 5 - rand() % 10;
					particle[k][ws].speed_y = 5 - rand() % 10;
					particle[k][ws].scale_speed = 1.04;
					particle[k][ws].alpha = 200;
					particle[k][ws].alpha_speed = -3;
					particle[k][ws].particle.setTexture(smoke);
					particle[k][ws].timer = 65;
					particle[k][ws].rotation_speed = 3 - rand() % 6;
					particle[k][ws].particle.setOrigin(128, 128);
					particle[k][ws].scale_ = 0.5;
					particle[k][ws].particle.setTextureRect(IntRect(0, 0, 256, 256));
				}
			}
			if (type == "cryst") {
				for (int ws = 0; ws < partnum; ws++) {
					particle[k][ws].speed_x = 2 - rand() % 4;
					particle[k][ws].speed_y = 2 - rand() % 4;
					particle[k][ws].scale_speed = 0.99;
					particle[k][ws].alpha_speed = -3;
					particle[k][ws].alpha = 155;
					particle[k][ws].particle.setTexture(broken);
					particle[k][ws].timer = 38;
					particle[k][ws].scale_ = 1;
					particle[k][ws].rotation_speed = 4 - rand() % 8;
					particle[k][ws].particle.setOrigin(rand() % 32, rand() % 32);
					particle[k][ws].y -= 10;
					particle[k][ws].particle.setTextureRect(IntRect(0, 0, 32, 32));
				}
			}
			if (type == "coin") {
				for (int ws = 0; ws < partnum; ws++) {
					particle[k][ws].speed_x = 0.6;
					particle[k][ws].speed_y = -0.6;
					if (ws != 1) { particle[k][ws].x = -10000; particle[k][ws].y = -10000; }
					particle[k][ws].scale_speed = 1.002;
					particle[k][ws].alpha_speed = -4;
					particle[k][ws].alpha = 255;
					particle[k][ws].particle.setTexture(Coin);
					particle[k][ws].timer = 60;
					particle[k][ws].scale_ = 1;
					particle[k][ws].rotation_speed = 0;
					particle[k][ws].particle.setOrigin(32, 32);
					particle[k][ws].particle.setRotation(0);
					particle[k][ws].y -= 10;
					particle[k][ws].particle.setTextureRect(IntRect(0, 0, 64, 64));
				}
			}
			if (type == "dark") {
				for (int ws = 0; ws < partnum; ws++) {
					particle[k][ws].particle.setTexture(dark);
					particle[k][ws].speed_x = 1 - rand() % 3;
					particle[k][ws].speed_y = 1 - rand() % 3;
					particle[k][ws].scale_speed = 1.04;
					particle[k][ws].alpha = 61;
					particle[k][ws].alpha_speed = -1;
					particle[k][ws].scale_ = 2.6;
					particle[k][ws].timer = 60;
					particle[k][ws].rotation_speed = rand() % 3;
					particle[k][ws].particle.setOrigin(40, 40);
					particle[k][ws].particle.setTextureRect(IntRect(0, 0, 100, 100));
				}
			}
			if (type == "tp") {
				for (int ws = 0; ws < partnum; ws++) {
					particle[k][ws].particle.setTexture(tp_p);
					particle[k][ws].speed_x = 2 - rand() % 5;
					particle[k][ws].speed_y = 2 - rand() % 5;
					particle[k][ws].scale_speed = 0.99;
					particle[k][ws].alpha = 128;
					particle[k][ws].alpha_speed = -2;
					particle[k][ws].scale_ = float(rand() % 20) / 10;
					particle[k][ws].timer = 60;
					particle[k][ws].rotation_speed = 3 - rand() % 7;
					particle[k][ws].particle.setOrigin(64, 64);
					particle[k][ws].particle.setTextureRect(IntRect(0, 0, 128, 128));
				}
			}
			if (type == "mech") {
				for (int ws = 0; ws < partnum; ws++) {
					particle[k][ws].particle.setTexture(dark);
					particle[k][ws].speed_x = 3 - rand() % 7;
					particle[k][ws].speed_y = 3 - rand() % 7;
					particle[k][ws].scale_speed = 1.015;
					particle[k][ws].alpha = 128;
					particle[k][ws].alpha_speed = -2;
					particle[k][ws].scale_ = 0.8;
					particle[k][ws].timer = 60;
					particle[k][ws].rotation_speed = 3 - rand() % 7;
					particle[k][ws].particle.setOrigin(64, 64);
					particle[k][ws].particle.setTextureRect(IntRect(0, 0, 128, 128));
				}
			}
			break;
		}
	}
}

void smoke_spawn(string type, int x, int y, int look) {

	logg << "Smoke spawn: " << type << " \n";;

	srand((unsigned)time(NULL));
	for (int k = 0; k < 3; k++) {
		if (!particle[k][0].enabled) {
			for (int ws = 0; ws < partnum; ws++) {
				particle[k][ws].x = x;
				particle[k][ws].y = y;
				particle[k][ws].alpha = 255;
				particle[k][ws].enabled = true;
				particle[k][ws].rotation_speed = 0;
				particle[k][ws].particle.setRotation(rand() % 360);
			}
			if (type == "smoke") {
				for (int ws = 0; ws < partnum; ws++) {
					particle[k][ws].speed_x = 5 - rand() % 10;
					particle[k][ws].speed_y = 5 - rand() % 10;
					particle[k][ws].scale_speed = 1.04;
					particle[k][ws].alpha = 200;
					particle[k][ws].alpha_speed = -3;
					particle[k][ws].particle.setTexture(smoke);
					particle[k][ws].timer = 65;
					particle[k][ws].rotation_speed = 3 - rand() % 6;
					particle[k][ws].particle.setOrigin(128, 128);
					particle[k][ws].scale_ = 0.5;
					particle[k][ws].particle.setTextureRect(IntRect(0, 0, 256, 256));
				}
			}
			if (type == "cryst") {
				for (int ws = 0; ws < partnum; ws++) {
					particle[k][ws].speed_x = 2 - rand() % 4;
					particle[k][ws].speed_y = 2 - rand() % 4;
					particle[k][ws].scale_speed = 0.99;
					particle[k][ws].alpha_speed = -3;
					particle[k][ws].alpha = 155;
					particle[k][ws].particle.setTexture(broken);
					particle[k][ws].timer = 38;
					particle[k][ws].scale_ = 1;
					particle[k][ws].rotation_speed = 4 - rand() % 8;
					particle[k][ws].particle.setOrigin(rand() % 32, rand() % 32);
					particle[k][ws].y -= 10;
					particle[k][ws].particle.setTextureRect(IntRect(0, 0, 32, 32));
				}
			}
			if (type == "coin") {
				for (int ws = 0; ws < partnum; ws++) {
					particle[k][ws].speed_x = 0.6;
					particle[k][ws].speed_y = -0.6;
					if (ws != 1) { particle[k][ws].x = -100; particle[k][ws].y = -100; }
					particle[k][ws].scale_speed = 1.002;
					particle[k][ws].alpha_speed = -4;
					particle[k][ws].alpha = 255;
					particle[k][ws].particle.setTexture(Coin);
					particle[k][ws].timer = 60;
					particle[k][ws].scale_ = 1;
					particle[k][ws].rotation_speed = 0;
					particle[k][ws].particle.setOrigin(32, 32);
					particle[k][ws].particle.setRotation(0);
					particle[k][ws].y -= 10;
					particle[k][ws].particle.setTextureRect(IntRect(0, 0, 64, 64));
				}
			}
			if (type == "dark") {
				for (int ws = 0; ws < partnum; ws++) {
					particle[k][ws].particle.setTexture(dark);
					particle[k][ws].speed_x = 1 - rand() % 3;
					particle[k][ws].speed_y = 1 - rand() % 3;
					particle[k][ws].scale_speed = 1.04;
					particle[k][ws].alpha = 61;
					particle[k][ws].alpha_speed = -1;
					particle[k][ws].scale_ = 2.6;
					particle[k][ws].timer = 60;
					particle[k][ws].rotation_speed = rand() % 3;
					particle[k][ws].particle.setOrigin(40, 40);
					particle[k][ws].particle.setTextureRect(IntRect(0, 0, 100, 100));
				}
			}
			if (type == "tp") {
				for (int ws = 0; ws < partnum; ws++) {
					particle[k][ws].particle.setTexture(tp_p);
					particle[k][ws].speed_x = 2 - rand() % 5;
					particle[k][ws].speed_y = 2 - rand() % 5;
					particle[k][ws].scale_speed = 0.99;
					particle[k][ws].alpha = 128;
					particle[k][ws].alpha_speed = -2;
					particle[k][ws].scale_ = float(rand() % 20) / 10;
					particle[k][ws].timer = 60;
					particle[k][ws].rotation_speed = 3 - rand() % 7;
					particle[k][ws].particle.setOrigin(64, 64);
					particle[k][ws].particle.setTextureRect(IntRect(0, 0, 128, 128));
				}
			}
			if (type == "mech") {
				for (int ws = 0; ws < partnum; ws++) {
					particle[k][ws].particle.setTexture(dark);
					particle[k][ws].speed_x = 3 - rand() % 7;
					particle[k][ws].speed_y = 3 - rand() % 7;
					particle[k][ws].scale_speed = 1.015;
					particle[k][ws].alpha = 128;
					particle[k][ws].alpha_speed = -2;
					particle[k][ws].scale_ = 0.8;
					particle[k][ws].timer = 60;
					particle[k][ws].rotation_speed = 3 - rand() % 7;
					particle[k][ws].particle.setOrigin(64, 64);
					particle[k][ws].particle.setTextureRect(IntRect(128 * look, 0, 128, 128));
				}
			}
			break;
		}
	}
}
