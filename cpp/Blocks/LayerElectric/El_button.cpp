#include <Blocks.hpp>

El_button::El_button(int _x, int _y, int _rotation, bool _reversed) {
	x = _x; y = _y; size = 40; type = 46; id = 46; init_AABB(); rotation = _rotation; reversed = _reversed;
	box.setRotation(_rotation);
	box.setTexture(*MapFloorTextures[id]);
	box.setOrigin(64, 64); magnet = 0.3; electric = true;
}

void El_button::cycle() {

	for (int k = 0; k < movables.size(); k++) {
		if (intersection(*this, *movables[k])) {

			if (reversed) {
				if (charge < 63) {
					charge += 1;
					if (charge < 20) {
						charge += 10;
					}
				}
				return;
			}

			if (charge > 0) {
				charge -= 1;
				if (charge > 10) {
					charge -= 6;
				}
			}

			return;
		}
	}

	if (reversed) {
		if (intersection(*this, p)) {
			box.setTextureRect(IntRect(128, 0, 128, 128));
			if (charge < 63) {
				charge += 1;
				if (charge < 20) {
					charge += 10;
				}
			} return;
		}
		else {

			box.setTextureRect(IntRect(0, 0, 128, 128));
			if (charge > 0) {
				charge -= 1;
				if (charge > 10) {
					charge -= 6;
				}
			}
		}
	}
	else {
		if (intersection(*this, p)) {
			box.setTextureRect(IntRect(128, 0, 128, 128));
			if (charge > 0) {
				charge -= 1;
				if (charge > 10) {
					charge -= 6;
				}
			} return;
		}
		else {
			box.setTextureRect(IntRect(0, 0, 128, 128));
			if (charge < 63) {
				charge += 1;
				if (charge < 20) {
					charge += 10;
				}
			}
		}
	}

}

void El_button::save(ofstream& save) {
	save << "[ ";
	save << id << ' ';
	save << x << ' ';
	save << y << ' ';
	save << rotation << ' ';

	save << int(reversed) << ' ';

	save << "]" << endl;
}
