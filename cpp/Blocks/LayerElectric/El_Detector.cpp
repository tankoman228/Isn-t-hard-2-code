#include <Blocks.hpp>

void El_Detector::setTextColor() {

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

bool* El_Detector::getTarget() {

	if (target == a) {
		return dmode;
	}
	if (target == b) {
		return crystal;
	}
	if (target == c) {
		return lmode;
	}
	if (target == barmode) {
		return barmode;
	}

}

int  El_Detector::getGroup() {
	return group;
}

El_Detector::El_Detector(int x_, int y_, int rotation_, int type_, bool* target_, int group_) {
	x = x_; y = y_; rotation = rotation_;  init_AABB();
	target = target_;
	group = group_; electric = true;
	/*con[0] = con_;*/
	box.setTexture(*MapFloorTextures[id]);
	box.setRotation(rotation);
	box.setOrigin(64, 64);
	type = type_; id = type;
	text.setString(to_string(group));
	setTextColor();
}

void El_Detector::cycle() {

	rech(*this, con[0]);

	if (charge > 25) {
		// TODO: box.setTexture(c_sensor_on);
		target[group] = true;
	}
	else {
		// TODO: box.setTexture(c_sensor);
		target[group] = false;
	}

}

void El_Detector::save(ofstream& save) {
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

	save << "]" << endl;
}

void El_Detector::editing() {

	//edit();
	if (editor_mode != 4) { return; }

	E_rotate_block.box.setPosition(box.getPosition()); E_rotate_block.box.move(80 * scale, -80 * scale);
	E_rotate_block2.box.setPosition(box.getPosition()); E_rotate_block2.box.move(-80 * scale, -80 * scale);

	E_rotate_block.box.setScale(scale, scale);
	//E_rotate_block.bg_box.setScale(scale * 0.5, scale * 0.5);
	E_rotate_block2.box.setScale(scale, scale);
	//E_rotate_block2.bg_box.setScale(scale * 0.5, scale * 0.5);

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

		if (!onclick && Mouse::isButtonPressed(Mouse::Left) && cursor.getGlobalBounds().intersects(box.getGlobalBounds())) {
			group++; onclick = true; last_group = group;
		}
		if (!onclick && Mouse::isButtonPressed(Mouse::Right) && cursor.getGlobalBounds().intersects(box.getGlobalBounds())) {
			group = 0; onclick = true; last_group = group;
		}

		E_edit_block.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y - 40 * scale);
		E_edit_block.box.setScale(scale * 0.4, scale * 0.4);

		if (E_edit_block.if_click()) {
			option_mode = !option_mode;
		}

		E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 128 * scale);
		E_arrow[1].setPosition(box.getPosition().x + 128 * scale, box.getPosition().y);
		E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 128 * scale);
		E_arrow[3].setPosition(box.getPosition().x - 128 * scale, box.getPosition().y);

		E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
		E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
		E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
		E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);
	}
}

void El_Detector::editor_exist() {

	update_scrolling();
	window.draw(box);

	text.setPosition((x - scrollx + 20) * scale, (y - scrolly + 5) * scale);
	text.setCharacterSize(40 * scale);
	text.setString(to_string(group));

	window.draw(text);
}