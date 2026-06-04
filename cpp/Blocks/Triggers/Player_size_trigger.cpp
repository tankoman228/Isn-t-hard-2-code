#include <Blocks.hpp>

void Player_size_trigger::trigger() {

	smoke_spawn("smoke", p.x, p.y);
	sound_b.play();

	player_scale *= player_scale_multiplier;
	p.size *= player_scale_multiplier;
	// TODO: изменение силы по размеру
	//p.repulsion /= player_scale_multiplier;
	//p.repulsion /= player_scale_multiplier;
	//p.repulsion /= player_scale_multiplier;
	p.init_AABB();
}

void Player_size_trigger::edit() {

	if (editor_mode != 4) { return; }

	E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 128 * scale);
	E_arrow[1].setPosition(box.getPosition().x + 128 * scale, box.getPosition().y);
	E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 128 * scale);
	E_arrow[3].setPosition(box.getPosition().x - 128 * scale, box.getPosition().y);

	E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
	E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
	E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
	E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);

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

	if (!onclick && box.getGlobalBounds().intersects(cursor.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
		onclick = true;
		player_scale_multiplier *= 1.15;
	}
	if (!onclick && box.getGlobalBounds().intersects(cursor.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Right)) {
		onclick = true;
		player_scale_multiplier *= 0.95;
	}

	text.setPosition(box.getPosition());
	text.setString(to_string(player_scale_multiplier));

	window.draw(text);
}

Player_size_trigger::Player_size_trigger(int id_, int x_, int y_, int size_, float _player_scale_multiplier) {

	id = id_; x = x_; y = y_; size = size_;
	once_flag = true;
	player_scale_multiplier = _player_scale_multiplier;

	magnet = 0;
	box.setOrigin(64, 64);
	init_AABB();
	box.setPosition((x - scrollx) * scale, (y - scrolly) * scale);
	box.setTexture(*MapFloorTextures[id]);
}

void Player_size_trigger::save(ofstream& save) {
	save << "[ ";
	save << id << ' ';
	save << x << ' ';
	save << y << ' ';
	save << int(size) << ' ';
	save << player_scale_multiplier << ' ';
	save << "]" << endl;
}