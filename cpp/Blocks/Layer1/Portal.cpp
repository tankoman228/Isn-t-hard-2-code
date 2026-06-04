#include <Blocks.hpp>

Portal::Portal(int _x, int _y, int _id, int _tp_to) {
	box.setOrigin(64, 64);
	x = _x; y = _y; id = _id; tp_to = _tp_to; layer = 1;
	size = 20; init_AABB();

	box.setTexture(*MapFloorTextures[id]);

	switch (id) {
	case 7: break;
	case 8: tx[tp_to] = x; ty[tp_to] = y; break;
	}

	box.setTextureRect(IntRect(0, 0, 128, 128));
	box.setRotation(0);
}

void Portal::render() {

	if (id == 7) {

		spiral[tp_to].setPosition((x - scrollx) * scale, (y - scrolly) * scale);

		if (spiral[tp_to].getGlobalBounds().intersects(playerS.getGlobalBounds())) {

			if ((!on_teleport) && (teleport_frame == 0)) {
				tp_s.play();
			}

			playerS.setColor(Color(255, 255, 255, 260 - teleport_frame * 4));
			eyes.setColor(Color(255, 255, 255, 260 - teleport_frame * 4));

			playerS.setRotation(teleport_frame * 5);
			spiral[tp_to].rotate(2);

			on_teleport = true;
			px = x;
			py = y;

			teleport_frame += 1.75;
			teleport_to = tp_to;

			if (teleport_frame > 10) {
				if (teleport_frame > 13) {
					if (teleport_frame > 16) {
						spiral[tp_to].setTextureRect(IntRect(768, 0, 256, 256));
					}
					else {
						spiral[tp_to].setTextureRect(IntRect(512, 0, 256, 256));
					}
				}
				else {
					spiral[tp_to].setTextureRect(IntRect(256, 0, 256, 256));
				}
			}

		}

	}

	if (id == 8) {

		if ((tp_to == teleport_to) && (teleport_frame > 64)) {

			on_teleport = false;
			playerS.setScale(scale, scale);
			eyes.setScale(scale, scale);
			spiral[tp_to].setTextureRect(IntRect(0, 0, 256, 256));

			px = x;
			py = y;

			playerS.setRotation((rand() % 4) * 90);

			//playerS.setColor(Color::White);
			//eyes.setColor(Color::White);
		}

	}

	update_scrolling();
	window.draw(box);

}

void Portal::save(ofstream& save) {
	save << "[ ";
	save << id << ' ';
	save << x << ' ';
	save << y << ' ';
	save << tp_to << ' ';
	save << "]" << endl;
}

void Portal::editor_exist() {

	update_scrolling(); window.draw(box);

	text.setPosition(box.getPosition());
	text.setString(to_string(tp_to + 1));
	window.draw(text);
}

void Portal::edit() {

	if (!onclick && Mouse::isButtonPressed(Mouse::Left) && box.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
		tp_to++;
		onclick = true;
		if (tp_to > 4) {
			tp_to = 0;
		}
	}

}