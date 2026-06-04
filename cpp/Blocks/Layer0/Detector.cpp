#include <Blocks.hpp>

Detector::Detector(int _x, int _y, int _id, int rotation_, bool* target_, int group_, bool reversed_) {

	basic_init(_x, _y, rotation_, _id);
	x = _x; y = _y; id = _id; group = group_; layer = 0; init_AABB(); rotation = rotation_;
	box.setRotation(rotation);
	target = target_;
	reversed = reversed_;

	text.setString(to_string(group));

	box.setTexture(*MapBasicTextures[id]);

	box.setTextureRect(IntRect(0, 0, 128, 128));
	box.setRotation(rotation);
	setTextColor();
}

void Detector::cycle() {

	if_collide();
	/*program();*/

	block.setPosition((x - scrollx) * scale, (y - scrolly) * scale);

	switch (int(box.getRotation())) {
		case 0:

			for (int k = 0; k < 3; k++) {
				block.move(scale * 128, 0);
				if (playerS.getGlobalBounds().intersects(block.getGlobalBounds())) {
					target[group] = reversed; break;
				}
			}

			break;

		case 90:

			for (int k = 0; k < 3; k++) {
				block.move(0, scale * 128);
				if (playerS.getGlobalBounds().intersects(block.getGlobalBounds())) {
					target[group] = reversed; break;
				}
			}

			break;

		case 180:

			for (int k = 0; k < 3; k++) {
				block.move(-scale * 128, 0);
				if (playerS.getGlobalBounds().intersects(block.getGlobalBounds())) {
					target[group] = reversed; break;
				}
			}

			break;

		case 270:

			for (int k = 0; k < 3; k++) {
				block.move(0, -scale * 128);
				if (playerS.getGlobalBounds().intersects(block.getGlobalBounds())) {
					target[group] = reversed; break;
				}
			}

		break;
	}
}

void Detector::save(ofstream& save) {
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