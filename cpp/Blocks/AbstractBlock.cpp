#include <Blocks.h>

void AbstractBlock::do_some_magic() {
	box.setColor(Color(90, 255, 90, 255));
	window.draw(box);
	box.setColor(Color(255, 255, 255, 255));
}

void AbstractBlock::update_scrolling() {
	box.setScale(scale * 1.017, scale * 1.009);
	box.setPosition(scale * (x - scrollx), scale * (y - scrolly));
}

bool AbstractBlock::if_collide() {

	if (intersection(p, *this)) {

		p.sx = 0; p.sy = 0;

		do {
			// TODO: что-то мне не нравится эта физика
			block_collision = true;

			float dx = (px - x);
			float dy = (py - y);

			if (abs(dx) > abs(dy)) {
				px += 0.1 * sign(dx);
			}
			else {
				py += 0.1 * sign(dy);
			}

			p.init_AABB();
		} while (intersection(p, *this));

		return true;
	}

	return false;
}

void AbstractBlock::rotate(int angle) {
	rotation += angle;
	if (angle >= 360) { rotation -= 360; }
	if (angle < 0) { rotation += 360; }
	box.setRotation(rotation);
	last_angle = box.getRotation();
}

void AbstractBlock::editing() {
	if (editor_mode != 4) { return; }

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
	E_rotate_block2.box.setScale(scale, scale);
}

void AbstractBlock::editor_exist() {
	update_scrolling();
	window.draw(box);
}

void AbstractBlock::setOpacity(int new_opacity /*0 is invisible, 255 is maximum*/) {
	box.setColor(Color(255, 255, 255, new_opacity));
}

void AbstractBlock::render() { update_scrolling(); window.draw(box); }

void AbstractBlock::save(ofstream& save) {
	save << "[ ";
	save << id << ' ';
	save << x << ' ';
	save << y << ' ';
	save << rotation << ' ';
	save << int(box.getTextureRect().left / 128) << ' ';
	save << "]" << endl;
}

bool* AbstractBlock::getTarget() {
	return dmode;
}

int AbstractBlock::getGroup() { return 0; }

bool AbstractBlock::getReverse() {
	return false;
}

void AbstractBlock::basic_init(int x_, int y_, int rotation_, int _id) {
	x = x_; y = y_; rotation = rotation_; id = _id; init_AABB();
}