#pragma once

#include "Values.h"
#include "Physics.h"

Sq p = Sq(0, 0, 35);

float accelerate = 0;
#define eyes_accelerate 0.1;

float middle(float a, float b) {
	return (a + b) / 2;
}
float middle(float a, float b, float c, float d, float e, float f) {
	return (a + b + c + d + e + f) / 6;
}

float last_coordinates[6][2] = { 0,0,0,0,0,0,0,0,0,0,0,0 };

void render_player() {

	//повороты
	switch (dir) {
	case 1:
		if (playerS.getRotation() != 270) {
			if ((playerS.getRotation() < 90) || (playerS.getRotation() > 270)) {
				playerS.rotate(-5);
			}
			else {
				playerS.rotate(5);
			}
			colint = 0;
		}
		break;
	case 2:
		if (playerS.getRotation() != 315) {
			if ((playerS.getRotation() < 315) && (playerS.getRotation() > 135)) {
				playerS.rotate(5);
			}
			else {
				playerS.rotate(-5);
			}
		}
		break;
	case 3:
		if (playerS.getRotation() != 0) {
			if (playerS.getRotation() < 180) {
				playerS.rotate(-5);
			}
			else {
				playerS.rotate(5);
			}
			colint = 0;
		}
		break;
	case 4:
		if (playerS.getRotation() != 45) {
			if ((playerS.getRotation() < 225) && (playerS.getRotation() > 45)) {
				playerS.rotate(-5);
			}
			else {
				playerS.rotate(5);
			}
		}
		break;
	case 5:
		if (playerS.getRotation() != 90) {
			if ((playerS.getRotation() < 270) && (playerS.getRotation() > 90)) {
				playerS.rotate(-5);
			}
			else {
				playerS.rotate(5);
			}
			colint = 0;
		}
		break;
	case 6:
		if (playerS.getRotation() != 135) {
			if ((playerS.getRotation() < 315) && (playerS.getRotation() > 135)) {
				playerS.rotate(-5);
			}
			else {
				playerS.rotate(5);
			}
		}
		break;
	case 7:
		if (playerS.getRotation() != 180) {
			if (playerS.getRotation() > 180) {
				playerS.rotate(-5);
			}
			else {
				playerS.rotate(5);
			}
			colint = 0;
		}
		break;
	case 8:
		if (playerS.getRotation() != 225) {
			if ((playerS.getRotation() < 225) && (playerS.getRotation() > 45)) {
				playerS.rotate(5);
			}
			else {
				playerS.rotate(-5);
			}
		}
		break;
	}

	if (ey > 0) { ey -= 0.025; } if (ey < 0) { ey += 0.025; }
	if (ex > 0) { ex -= 0.025; } if (ex < 0) { ex += 0.025; }

	if (ex > 0) { ex -= 0.2; }
	if (ex < 0) { ex += 0.2; }
	if (ey > 0) { ey -= 0.2; }
	if (ey < 0) { ey += 0.2; }

	if (ex > 3) { ex = 3; }
	if (ex < -4) { ex = -4; }
	if (ey > 3) { ey = 3; }
	if (ey < -3) { ey = -3; }

	last_coordinates[0][0] = (p.x - scrollx) * scale;
	last_coordinates[0][1] = (p.y - scrolly) * scale;

	last_coordinates[5][0] = last_coordinates[4][0];
	last_coordinates[4][0] = last_coordinates[3][0];
	last_coordinates[3][0] = last_coordinates[2][0];
	last_coordinates[2][0] = last_coordinates[1][0];
	last_coordinates[1][0] = last_coordinates[0][0];

	last_coordinates[5][1] = last_coordinates[4][1];
	last_coordinates[4][1] = last_coordinates[3][1];
	last_coordinates[3][1] = last_coordinates[2][1];
	last_coordinates[2][1] = last_coordinates[1][1];
	last_coordinates[1][1] = last_coordinates[0][1];

	playerS.setPosition(middle(last_coordinates[0][0], last_coordinates[1][0], last_coordinates[2][0], last_coordinates[3][0], last_coordinates[4][0], last_coordinates[5][0]),middle(last_coordinates[0][1], last_coordinates[1][1], last_coordinates[2][1], last_coordinates[3][1], last_coordinates[4][1], last_coordinates[5][1]));
	eyes.setPosition(playerS.getPosition());
	eyes.setRotation(playerS.getRotation());
	eyes.move(player_scale * ex * scale, player_scale * ey * scale);

	playerS.setScale(player_scale * scale, player_scale * scale);
	eyes.setScale(player_scale * scale, player_scale * scale);

	window.draw(playerS);
	window.draw(eyes);

	if (tick % 500 > 460) {
		eyes.setPosition(playerS.getPosition());
		eyes.setTexture(blink);
		if (tick % 500 < 480) {
			eyes.setTextureRect(IntRect(75 * floor((tick % 500 - 480) / 2), 0, 75, 75));
		}
		if (tick % 500 >= 480) {
			eyes.setTextureRect(IntRect(75 * (8 - floor((tick % 500 - 480) / 2)), 0, 75, 75));
		}
		window.draw(eyes);
		eyes.setTexture(eyes_t);
		eyes.setTextureRect(IntRect(0, 0, 75, 75));
	}
	//blinking

}

void player_processing() {

	#define sx p.sx
	#define sy p.sy

	do {

		if (Keyboard::isKeyPressed(Keyboard::LControl)) {
			accelerate = 0.1; p.max_speed = 3;
		}
		else {
			accelerate = 0.057; p.max_speed = 2.2;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {
			if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
				sx += accelerate; sy -= accelerate; dir = 2; ex += eyes_accelerate; ey -= eyes_accelerate;
			}
			else {
				if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
					sx -= accelerate; sy -= accelerate; dir = 8; ex -= eyes_accelerate; ey -= eyes_accelerate;
				}
				else {
					sy -= accelerate; dir = 1; ey -= eyes_accelerate;
				}
			}
			break;

		}
		if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {
			if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
				sx += accelerate; sy += accelerate; dir = 4; ex += eyes_accelerate; ey += eyes_accelerate;
			}
			else {
				if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
					sx -= accelerate; sy += accelerate; dir = 6; ex -= eyes_accelerate; ey += eyes_accelerate;
				}
				else {
					sy += accelerate; dir = 5; ey += eyes_accelerate;
				}
			}
			break;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
			sx += accelerate; dir = 3; ex += eyes_accelerate; break;
		}
		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
			sx -= accelerate; dir = 7; ex -= eyes_accelerate; break;
		}

	} while (false);

	if (Keyboard::isKeyPressed(Keyboard::LShift)) {
		sx *= 0.95;
		sy *= 0.95;
	}

	#undef sx
	#undef sy

	p.move();

}
