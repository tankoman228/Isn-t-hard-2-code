#pragma once

#include <Values.h>

class Particles {
public:
	bool enabled = false;
	float size, x = 0, y = 0, alpha, alpha_speed, speed_x, speed_y, scale_, scale_speed;
	int timer, rotation_speed;
	Sprite particle;
	void render() {
		particle.setPosition(scale * (x - scrollx), scale * (y - scrolly));
		x += speed_x; y += speed_y;
		particle.setColor(Color(255, 255, 255, alpha));
		alpha += alpha_speed;
		particle.setScale(scale_ * scale, scale_ * scale);
		scale_ *= scale_speed;
		if (timer < 0) { enabled = false; }
		timer -= 1;
		particle.rotate(rotation_speed);
		window.draw(particle);
	}
};
inline Particles particle[3][40];

class BG_particles {

	float x, y, /*sx, sy,*/ timer = 0;
	float scale_speed;

	Sprite box;

	int spawn_fade;
	int color[3];

public:

	BG_particles() {

		// TODO:blue1_.loadFromFile("Textures/BG/BG.png");

		box.setOrigin(64, 64);
		// TODO:blue1_.setSmooth(true);

		x = rand() % (2000);
		y = rand() % (2000);

		scale_speed = 1 + float(rand() % 200) / 30000;

		timer = 20;

		box.setPosition(x, y);
		box.setScale(UI_scale * 15, UI_scale * 15);
		box.setColor(Color(255, 255, 255, 255));

		// TODO:box.setTexture(blue1_);

		spawn_fade = 255;

	}

	void respawn() {
		// TODO: blue1_.loadFromFile("Textures/BG/BG.png");

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
		box.setColor(Color(255, 255, 255, 255));
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

			box.setColor(Color(color[0], color[1], color[2], 256 - spawn_fade));

			/*box.scale(0.9999, 0.9999);*/

			/*box.scale(scale_speed, scale_speed);*/
			//box.move(sx, sy);

			window.draw(box);
			return;
		}
		else {
			if (timer < 255) {
				box.setColor(Color(color[0], color[1], color[2], timer));
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
inline BG_particles bg_particles[20];

inline Texture broken, smoke, Coin, dark, tp_p;

void smoke_spawn(string type, int x, int y);
void smoke_spawn(string type, int x, int y, int look);
