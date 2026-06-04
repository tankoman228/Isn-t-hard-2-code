#include <Blocks.h>

Special::Special(int _x, int _y, int _id, int rotation_, int _look) {

	basic_init(_x, _y, rotation_, _id);
	look = _look; layer = 0;
	init_AABB();

	box.setTexture(*MapBasicTextures[id]);

	box.setTextureRect(IntRect(look * 128, 0, 128, 128));
	box.setRotation(rotation);

}

void Special::cycle() {

	switch (id) {
		case 16:
			break;
		case 17:
			if_collide();
			break;

		case 31:
			if (intersection(*this, p)) {
				achievement(lvlnum, look);
				x = -1000000;
				y = -1000000;
				init_AABB();
			}

			break;
	}
}

void Special::render() {

	update_scrolling();

	float helper_s2, helper_s[2];

	switch (id) {
		case 16:

			helper_s[0] = (x - px);
			helper_s2 = helper_s[0] * helper_s[0];
			helper_s[1] = (y - py);
			helper_s2 += helper_s[1] * helper_s[1];

			// TODO: box.setTexture(gravs);
			if (look == 0) { box.rotate(-2 * tick % 360); }
			else { box.rotate(2 * tick % 360); }
			window.draw(box);

			// TODO: box.setTexture(grav);
			if (look == 0) { box.rotate(2 * tick % 360); }
			else { box.rotate(-2 * tick % 360); }

			if (!look) {
				p.sx += helper_s[0] / helper_s2 * 100;
				p.sy += helper_s[1] / helper_s2 * 100;
			}
			else {
				p.sx -= helper_s[0] / helper_s2 * 80;
				p.sy -= helper_s[1] / helper_s2 * 80;
			}
			if_collide();
			break;
		case 17:
			helper_s[0] = (x - px);
			helper_s2 = helper_s[0] * helper_s[0];
			helper_s[1] = (y - py);
			helper_s2 += helper_s[1] * helper_s[1];

			helper_s2 = sqrt(helper_s2);
			if (helper_s2 < 384) {
				box.setColor(Color(255, 255, 255, 280 - (helper_s2 / 1.5)));
				if (helper_s2 < 100) {
					box.setColor(Color(255, 255, 255, 280 - (helper_s2 / 3)));
				}
			}
			else { box.setColor(Color(255, 255, 255, 0)); }
		break;
	}
	if ((id != 31) /*|| mode == "editor" TODO: отрендерить в редакторе*/) {
		window.draw(box);
	}
}

void Special::editing() {

	//edit();
	if (editor_mode != 4) { return; }

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

	if (cursor.getGlobalBounds().intersects(box.getGlobalBounds())) {
		if (Mouse::isButtonPressed(Mouse::Left) && !onclick) {
			look++; onclick = true;

		}
		if (Mouse::isButtonPressed(Mouse::Right) && !onclick) {
			look = 0; onclick = true;
		}
		if (id == 16) {
			box.setTextureRect(IntRect(128 * look, 0, 128, 128));
		}
	}

	text.setPosition(box.getPosition());

	if (id == 31) { text.setString("A" + to_string(look)); }
	else { text.setString(" "); }

	window.draw(text);

}

void Special::save(ofstream& save) {
	save << "[ ";
	save << id << ' ';
	save << x << ' ';
	save << y << ' ';
	save << rotation << ' ';
	save << look << ' ';
	save << "]" << endl;
}