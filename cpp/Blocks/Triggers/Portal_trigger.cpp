#include <Blocks.hpp>

void Portal_trigger::trigger() {
	scrollx += delta_x;
	scrolly += delta_y;

	p.move(delta_x, delta_y);

	last_coordinates[0][0] = scale * (p.x - scrollx);
	last_coordinates[1][0] = scale * (p.x - scrollx);
	last_coordinates[2][0] = scale * (p.x - scrollx);
	last_coordinates[3][0] = scale * (p.x - scrollx);
	last_coordinates[4][0] = scale * (p.x - scrollx);
	last_coordinates[5][0] = scale * (p.x - scrollx);

	last_coordinates[0][1] = scale * (p.y - scrolly);
	last_coordinates[1][1] = scale * (p.y - scrolly);
	last_coordinates[2][1] = scale * (p.y - scrolly);
	last_coordinates[3][1] = scale * (p.y - scrolly);
	last_coordinates[4][1] = scale * (p.y - scrolly);
	last_coordinates[5][1] = scale * (p.y - scrolly);

	logg << "Teleport! Deltas: " << delta_x << " " << delta_y << endl;
}

Portal_trigger::Portal_trigger(int id_, int x_, int y_, int size_, int dx, int dy) {

	id = id_; x = x_; y = y_; size = size_;

	delta_x = dx; delta_y = dy;

	box.setTexture(*MapFloorTextures[id]);
	// TODO: box2.setTexture(t_portal2);

	box.setOrigin(64, 64);
	box2.setOrigin(64, 64);
	init_AABB();

	E_plus.is_checked = false;
	E_Rt.is_checked = false;
	E_M.is_checked = true;
	E_player.is_checked = false;
	E_multichoose.is_checked = false;
}

void Portal_trigger::edit() {

	if (editor_mode != 4) { return; }

	E_arrow[0].setPosition(box2.getPosition().x, box2.getPosition().y - 128 * scale);
	E_arrow[1].setPosition(box2.getPosition().x + 128 * scale, box2.getPosition().y);
	E_arrow[2].setPosition(box2.getPosition().x, box2.getPosition().y + 128 * scale);
	E_arrow[3].setPosition(box2.getPosition().x - 128 * scale, box2.getPosition().y);

	E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
	E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
	E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
	E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);

	if (E_arrow[0].if_click()) {
		delta_y -= 128;
	}
	if (E_arrow[1].if_click()) {
		delta_x += 128;
	}
	if (E_arrow[2].if_click()) {
		delta_y += 128;
	}
	if (E_arrow[3].if_click()) {
		delta_x -= 128;
	}

	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		if (!on_keyboard_click) {
			if (Keyboard::isKeyPressed(Keyboard::LShift)) { move(0, 16); delta_y -= 16; }
			else { move(0, 128); delta_y -= 128; }
			on_keyboard_click = !Keyboard::isKeyPressed(Keyboard::LControl);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		if (!on_keyboard_click) {
			if (Keyboard::isKeyPressed(Keyboard::LShift)) { move(-16, 0);  delta_x += 16; }
			else { move(-128, 0); delta_x += 128; }
			on_keyboard_click = !Keyboard::isKeyPressed(Keyboard::LControl);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		if (!on_keyboard_click) {
			if (Keyboard::isKeyPressed(Keyboard::LShift)) { move(0, -16); delta_y += 16; }
			else { move(0, -128); delta_y += 128; }
			on_keyboard_click = !Keyboard::isKeyPressed(Keyboard::LControl);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		if (!on_keyboard_click) {
			if (Keyboard::isKeyPressed(Keyboard::LShift)) { move(16, 0); delta_x -= 16; }
			else { move(128, 0); delta_x -= 128; }
			on_keyboard_click = !Keyboard::isKeyPressed(Keyboard::LControl);
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::W)) {
		if (!on_keyboard_click) {
			if (Keyboard::isKeyPressed(Keyboard::LShift)) { move(0, 16); delta_y -= 16; }
			else { delta_y -= 128; }
			on_keyboard_click = !Keyboard::isKeyPressed(Keyboard::LControl);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		if (!on_keyboard_click) {
			if (Keyboard::isKeyPressed(Keyboard::LShift)) { move(-16, 0);  delta_x += 16; }
			else { delta_x += 128; }
			on_keyboard_click = !Keyboard::isKeyPressed(Keyboard::LControl);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		if (!on_keyboard_click) {
			if (Keyboard::isKeyPressed(Keyboard::LShift)) { move(0, -16); delta_y += 16; }
			else { delta_y += 128; }
			on_keyboard_click = !Keyboard::isKeyPressed(Keyboard::LControl);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		if (!on_keyboard_click) {
			if (Keyboard::isKeyPressed(Keyboard::LShift)) { move(16, 0); delta_x -= 16; }
			else { delta_x -= 128; }
			on_keyboard_click = !Keyboard::isKeyPressed(Keyboard::LControl);
		}
	}

	T_plus.setPosition(box.getPosition().x + scale * 94, box.getPosition().y + scale * 94);
	T_plus.box.setScale(scale * 0.7, scale * 0.7);
	T_minus.setPosition(box.getPosition().x - scale * 94, box.getPosition().y + scale * 94);
	T_minus.box.setScale(scale * 0.7, scale * 0.7);

	if (T_plus.if_click()) {
		size *= 1.25; last_size = size; onclick = true;
	}
	if (T_minus.if_click()) {
		size *= 0.85; last_size = size; onclick = true;
	}

	E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 128 * scale);
	E_arrow[1].setPosition(box.getPosition().x + 128 * scale, box.getPosition().y);
	E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 128 * scale);
	E_arrow[3].setPosition(box.getPosition().x - 128 * scale, box.getPosition().y);

	on_portal_trigger_edit = true;
}

void Portal_trigger::editor_exist() {

	update_scrolling();

	zone_marker.setPosition(box.getPosition());

	// TODO: zone_marker.setTexture(block_choose);

	zone_marker.setOrigin(64, 64);
	zone_marker.setScale(scale * size / 64, scale * size / 64);
	zone_marker.setColor(Color(255, 255, 255, 155 + 55 * sin(float(tick) / 40)));

	window.draw(zone_marker);

	box2.setPosition(box.getPosition());
	box2.move(scale * delta_x, scale * delta_y);
	box2.setScale(scale, scale);

	zone_marker2.setPosition(box2.getPosition());

	// TODO: zone_marker2.setTexture(block_choose);

	zone_marker2.setOrigin(64, 64);
	zone_marker2.setScale(scale * size / 64, scale * size / 64);
	zone_marker2.setColor(Color(255, 255, 255, 155 + 55 * sin(float(tick) / 40)));

	window.draw(zone_marker2);

	window.draw(box);
	window.draw(box2);

	Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(box.getPosition())),
		sf::Vertex(sf::Vector2f(box2.getPosition()))
	};

	window.draw(line, 2, sf::Lines);

}

void Portal_trigger::save(ofstream& save) {
	save << "[ ";
	save << id << ' ';
	save << x << ' ';
	save << y << ' ';
	save << int(size) << ' ';
	save << delta_x << ' ';
	save << delta_y << ' ';
	save << "]" << endl;
}
