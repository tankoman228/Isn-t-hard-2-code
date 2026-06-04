#include <Blocks.hpp>

Switcher::Switcher(int _x, int _y, int _id, int rotation_, bool* target_, int group_, bool irreversible_) {

	basic_init(_x, _y, rotation_, _id);
	irreversible = irreversible_;
	layer = 0;

	box.setRotation(rotation);

	target = target_;
	group = group_;

	text.setString(to_string(group));

	box.setTexture(*MapBasicTextures[id]);

	box.setTextureRect(IntRect(0, 0, 128, 128));
	box.setRotation(rotation);
	setTextColor();
}

void Switcher::editor_exist() {

	render();
	text.setPosition((x - scrollx + 20) * scale, (y - scrolly + 5) * scale);
	text.setCharacterSize(40 * scale);
	window.draw(text);
}

void Switcher::update() {

	if (target[group]) {
		box.setTextureRect(IntRect(128, 0, 128, 128));
	}
	else {
		box.setTextureRect(IntRect(0, 0, 128, 128));
	}
}

void Switcher::cycle() {

	if (if_collide() && available) {

		if ((dir % 2 == 1) && colint > 25) {

			colint = -5;

			if (target[group]) { target[group] = false; }
			else { target[group] = true; }

			if (irreversible) { available = false; }

			switch (id) {
				case 2: s1.play(); break;
				case 15: _break.play(); smoke_spawn("cryst", x, y); break;
			}

			update();
		}
	}
}

void Switcher::save(ofstream& save) {
	save << "[ " << id << ' ' << x << ' ' << y << ' ' << rotation << ' ';

	if (target == a)
		save << "dmode" << ' ';
	else if (target == b)
		save << "crystal" << ' ';
	else if (target == c)
		save << "lmode" << ' ';
	else if (target == barmode)
		save << "barmode" << ' ';

	save << group << ' ' << int(irreversible) << ' ' << "]" << endl;
}

