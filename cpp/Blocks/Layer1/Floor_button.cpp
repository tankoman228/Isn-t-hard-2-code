#include <Blocks.hpp>

Floor_button::Floor_button(int _x, int _y, int _id, int rotation_, bool* target_, int group_, bool change_) {

	x = _x; y = _y; id = _id; group = group_; rotation = rotation_; layer = 1;
	box.setRotation(rotation);
	target = target_; init_AABB();
	change = change_;

	// TODO: box.setTexture(buttonblock);

	box.setTextureRect(IntRect(0, 0, 128, 128));
	box.setRotation(rotation);

	setTextColor();
	text.setString(to_string(group));
}

void Floor_button::cycle() {

	if (intersection(p, *this)) {
		box.setTextureRect(IntRect(128, 0, 128, 128));

		if (!target[group]) {
			open.play();
		}
		target[group] = true;

		return;
	}
	else {

		for (int k = 0; k < movables.size(); k++) {

			if (bx < movables[k]->ax || ax > movables[k]->bx || ay > movables[k]->by || by < movables[k]->ay) { continue; }
			if (abs(movables[k]->x - x) > 30 || abs(movables[k]->y - y) > 30) { continue; }

			box.setTextureRect(IntRect(128, 0, 128, 128));

			if (!target[group]) {
				open.play();
			}
			target[group] = true;

			return;

		}
	}

	if (target[group]) {
		open.play();
	}

	target[group] = false;
	box.setTextureRect(IntRect(0, 0, 128, 128));

}

void Floor_button::save(ofstream& save) {
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
	save << int(change) << ' ';
	save << "]" << endl;
}