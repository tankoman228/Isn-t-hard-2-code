#include <Blocks.h>

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

void Switcher::setTextColor() {

	if (target == a) {
		text.setFillColor(Color::White); return;
	}
	if (target == b) {
		text.setFillColor(Color::Black); return;
	}
	if (target == c) {
		text.setFillColor(Color::Red); return;
	}
	if (target == barmode) {
		text.setFillColor(Color::Magenta); return;
	}
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
	save << int(irreversible) << ' ';
	save << "]" << endl;
}

void Switcher::editing() {

	//edit();
	if (editor_mode != 4) { return; }

	text.setString(to_string(group));

	if (option_mode) {

		E_edit_block.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y - 40 * scale);
		E_edit_block.box.setScale(scale * 0.4, scale * 0.4);

		if (E_edit_block.if_click()) {
			option_mode = !option_mode;
		}

		E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 200 * scale);
		E_arrow[1].setPosition(box.getPosition().x + 200 * scale, box.getPosition().y);
		E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 200 * scale);
		E_arrow[3].setPosition(box.getPosition().x - 200 * scale, box.getPosition().y);

		E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
		E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
		E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
		E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);

		E_edit_color.box.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y + 40 * scale);
		E_edit_color.bg_box.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y + 40 * scale);
		E_edit_color.box.setScale(0.5 * scale, 0.5 * scale);
		E_edit_color.bg_box.setScale(0.45 * scale, 0.45 * scale);
		E_edit_color.bg_box.setColor(text.getFillColor());

		E_rotate_block.box.setPosition(box.getPosition()); E_rotate_block.box.move(80 * scale, -80 * scale);
		E_rotate_block2.box.setPosition(box.getPosition()); E_rotate_block2.box.move(-80 * scale, -80 * scale);

		E_rotate_block.box.setScale(scale, scale);
		//E_rotate_block.bg_box.setScale(scale * 0.5, scale * 0.5);
		E_rotate_block2.box.setScale(scale, scale);
		//E_rotate_block2.bg_box.setScale(scale * 0.5, scale * 0.5);

		setTextColor();
		E_edit_color.bg_box.setColor(text.getFillColor());

		if (E_edit_color.if_click()) {

			if (target == a) {
				target = crystal; return;
			}
			if (target == b) {
				target = lmode; return;
			}
			if (target == c) {
				target = barmode; return;
			}
			if (target == barmode) {
				target = dmode; return;
			}
		}

		E_edit_number.box.setPosition(box.getPosition());
		E_edit_number.box.move(-40 * scale, 40 * scale);
		E_edit_number.box.setScale(scale * 0.5, scale * 0.5);
		E_edit_number.bg_box.setScale(scale * 0.5, scale * 0.5);

		if (E_edit_number.if_click()) {

			if (Mouse::isButtonPressed(Mouse::Left)) {
				group++; onclick = true;
				last_group = group;
			}
			if (Mouse::isButtonPressed(Mouse::Right)) {
				if (group > 0) {
					group--; onclick = true;
					last_group = group;
				}
			}

		}

		text.setPosition(E_edit_number.box.getPosition());
		text.setString(to_string(group));
		text.move(-25 * UI_scale, -30 * UI_scale);

		window.draw(text);

	}
	else {

		if (E_edit_block.if_click()) {
			option_mode = !option_mode;
		}

		if (!onclick && Mouse::isButtonPressed(Mouse::Left) && cursor.getGlobalBounds().intersects(box.getGlobalBounds())) {
			group++; onclick = true; last_group = group;
		}
		if (!onclick && Mouse::isButtonPressed(Mouse::Right) && cursor.getGlobalBounds().intersects(box.getGlobalBounds())) {
			group = 0; onclick = true; last_group = group;
		}

		E_edit_block.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y - 40 * scale);
		E_edit_block.box.setScale(scale * 0.4, scale * 0.4);

		E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 128 * scale);
		E_arrow[1].setPosition(box.getPosition().x + 128 * scale, box.getPosition().y);
		E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 128 * scale);
		E_arrow[3].setPosition(box.getPosition().x - 128 * scale, box.getPosition().y);

		E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
		E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
		E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
		E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);

		E_rotate_block.box.setPosition(box.getPosition()); E_rotate_block.box.move(80 * scale, -80 * scale);
		E_rotate_block2.box.setPosition(box.getPosition()); E_rotate_block2.box.move(-80 * scale, -80 * scale);

		E_rotate_block.box.setScale(scale, scale);
		//E_rotate_block.bg_box.setScale(scale * 0.5, scale * 0.5);
		E_rotate_block2.box.setScale(scale, scale);
		//E_rotate_block2.bg_box.setScale(scale * 0.5, scale * 0.5);
	}
}