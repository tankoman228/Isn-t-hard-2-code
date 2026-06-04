#include <Blocks.h>

bool* TargetGroupController::getTarget() {

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

int TargetGroupController::getGroup() {
	return group;
}

bool TargetGroupController::getReverse() {
	return reversed;
}

void TargetGroupController::editing() {

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

void TargetGroupController::setTextColor() {
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

void TargetGroupController::editor_exist() {
	render();
	text.setPosition((x - scrollx + 20) * scale, (y - scrolly + 5) * scale);
	text.setCharacterSize(40 * scale);
	window.draw(text);
}
