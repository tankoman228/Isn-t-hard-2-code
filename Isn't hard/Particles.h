#pragma once

#include "Values.h"

class Particles {
public:
	bool enabled = false;
	float size, x = 0, y = 0, alpha, alpha_speed, speed_x, speed_y, scale_, scale_speed;
	int timer, rotation_speed;
	Sprite particle;
	void render() {
		particle.setPosition(scale * (x - scrollx), scale * (y - scrolly));
		x += speed_x; y += speed_y;
		particle.setColor(Color::Color(255, 255, 255, alpha));
		alpha += alpha_speed;
		particle.setScale(scale_ * scale, scale_ * scale);
		scale_ *= scale_speed;
		if (timer < 0) { enabled = false; }
		timer -= 1;
		particle.rotate(rotation_speed);
		window.draw(particle);
	}
};
Particles particle[3][40];

class BG_particles {

	float x, y, /*sx, sy,*/ timer = 0;
	float scale_speed;

	Sprite box;

	int spawn_fade;
	int color[3];

public:

	BG_particles() {

		blue1_.loadFromFile("Textures\\BG\\BG.png");

		box.setOrigin(64, 64);
		blue1_.setSmooth(true);

		x = rand() % (2000);
		y = rand() % (2000);

		scale_speed = 1 + float(rand() % 200) / 30000;

		timer = 20;

		box.setPosition(x, y);
		box.setScale(UI_scale * 15, UI_scale * 15);
		box.setColor(Color::Color(255, 255, 255, 255));

		box.setTexture(blue1_);

		spawn_fade = 255;

	}

	void respawn() {

		c_cross3.loadFromFile("Textures\\Electricity\\C cross 3.png");

		blue1_.loadFromFile("Textures\\BG\\BG.png");

		x = -200 + rand() % (screenw + 400);
		y = -300 + rand() % (screenh + 600);

		color[0] = 0;
		color[1] = 0;
		color[2] = 0;

		color[0] += rand() % 215;
		color[1] += rand() % 215;
		color[2] += rand() % 215;

		if (lvlnum > 1 && lvlnum < 15) {
			color[0] = 50;
			color[1] = 100;
			color[2] = 200;
		}
		if (lvlnum > 15 && lvlnum < 23) {
			color[0] = 200;
			color[1] = 50;
			color[2] = 50;
		}
		color[0] += tick % 26 + rand() % 25;
		color[1] += tick % 26 + rand() % 25;
		color[2] += tick % 26 + rand() % 25;

		if (lvlnum > 23 && lvlnum < 31) {
			color[0] = 0;
			color[1] = 60;
			color[2] = 10;
			color[1] += tick % 26 + rand() % 25;
			color[2] += tick % 26 + rand() % 25;
		}

		//sx = float(rand() % 200) / 2000;
		//sy = float(rand() % 200) / 2000;

		//if (rand() % 2 == 0) { sx *= -1; }
		//if (rand() % 2 == 1) { sy *= -1; }

		/*scale_speed = 1 - float(rand() % 2000) / 500000;*/

		timer = 455 + rand() % 2095;

		box.setPosition(x, y);
		box.setOrigin(64,64);
		box.setScale(UI_scale * 18, 18 * UI_scale);
		box.setColor(Color::Color(255, 255, 255, 255));
		//box.setRotation(rand() % 360);

		spawn_fade = 255;

	}

	void cycle() {

		timer--;
		if (timer < 1) {
			respawn();
		}

		if (spawn_fade > 1) {
			spawn_fade--;

			box.setColor(Color::Color(color[0], color[1], color[2], 256 - spawn_fade));

			/*box.scale(0.9999, 0.9999);*/

			/*box.scale(scale_speed, scale_speed);*/
			//box.move(sx, sy);

			window.draw(box);
			return;
		}
		else {
			if (timer < 255) {
				box.setColor(Color::Color(color[0], color[1], color[2], timer));
			}
			//else {
			//	/*box.setColor(Color::Color(255, 255, 255, 255));*/
			//}
		}
		/*box.scale(scale_speed, scale_speed);*/
		//box.move(sx, sy);
		/*box.scale(0.9999, 0.9999);*/

		window.draw(box);

	}

};
BG_particles bg_particles[20];

Texture broken, smoke, Coin, dark, tp_p;
void smoke_spawn(string type, int x, int y) {

	logg << "Smoke spawn: " << type << " \n";;

	srand((unsigned)time(NULL));
	for (k = 0; k < 3; k++) {
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
	for (k = 0; k < 3; k++) {
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
