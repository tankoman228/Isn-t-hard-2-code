#include <Blocks.h>

Door::Door(int _x, int _y, int _id, int rotation_, bool* target_, int _group, bool reversed_) {

	basic_init(_x, _y, rotation_, _id);
	target = target_; group = _group; layer = 1;
	/*magnet = -0.15;*/

	box.setTexture(*MapFloorTextures[id]);
	box.setTextureRect(IntRect(0, 0, 128, 128));

	switch (id) {
		case 2:  reversed = false; box.setTextureRect(IntRect(0, 0, 128, 128)); break;
		case 3:  reversed = true; box.setTextureRect(IntRect(128, 0, 128, 128)); break;
		case 15: reversed = true; box.setTextureRect(IntRect(0, 0, 128, 128)); break;
		case 16: reversed = false; box.setTextureRect(IntRect(128, 0, 128, 128)); break;
		case 23: reversed = false; box.setTextureRect(IntRect(0, 0, 128, 128)); break;
		case 24: reversed = true; box.setTextureRect(IntRect(128, 0, 128, 128)); break;
		case 38: reversed = false; box.setTextureRect(IntRect(0, 0, 128, 128)); break;
		case 39: reversed = true; box.setTextureRect(IntRect(128, 0, 128, 128)); break;
		case 40: reversed = false; box.setTextureRect(IntRect(0, 0, 128, 128)); break;
		case 41: reversed = true; box.setTextureRect(IntRect(128, 0, 128, 128)); break;
	}

	reversed = reversed_;

	box.setRotation(rotation);
	setTextColor();
	text.setString(to_string(group));

}

void Door::cycle() {
	if (target[group]) {
		if (reversed) {
			box.setTextureRect(IntRect(0, 0, 128, 128));
		}
		else {
			box.setTextureRect(IntRect(128, 0, 128, 128));
			if_collide();

			for (int k = 0; k < movables.size(); k++) {
				if (collide(*this, *movables[k], 0.5)) { // TODO: dt
					/*if (abs(movables[k]->x - x) < 3 || abs(movables[k]->y - y) < 3) {
						smoke_spawn("smoke", x, y);
						sound_b.play();
						movables[k]->x = -999999;
						return;
					}*/
				}
			}

		}
	}
	else {
		if (reversed) {
			box.setTextureRect(IntRect(128, 0, 128, 128));
			if_collide();

			for (int k = 0; k < movables.size(); k++) {
				if (collide(*this, *movables[k], 0.5)) { // TODO: dt
					//if (abs(movables[k]->x - x) < 3 || abs(movables[k]->y - y) < 3) {
					//	smoke_spawn("smoke", x, y);
					//	sound_b.play();
					//	movables[k]->x = -999999;
					//	return;
					//}
				}
			}
		}
		else {
			box.setTextureRect(IntRect(0, 0, 128, 128));
		}
	}
}

void Door::save(ofstream& save) {
	save << "[ ";
	save << id << ' ';
	save << x << ' ';
	save << y << ' ';
	save << rotation << ' ';

	if (target == a) {
		save << "dmode" << ' ';
	}
	if (target == b) {
		save << "crystal" << ' ';
	}
	if (target == c) {
		save << "lmode" << ' ';
	}
	if (target == barmode) {
		save << "barmode" << ' ';
	}
	save << group << ' ';
	save << int(reversed) << ' ';
	save << "]" << endl;
}

bool Door::getReverse() {
	return reversed;
}