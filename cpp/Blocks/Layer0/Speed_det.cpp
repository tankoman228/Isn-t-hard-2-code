#include <Blocks.hpp>

Speed_det::Speed_det(int _x, int _y, int _id, int rotation_, bool* target_, int group_) {

	basic_init(_x, _y, rotation_, _id);
	group = group_;
	init_AABB();
	layer = 0;
	box.setRotation(rotation); text.setString(to_string(group));
	target = target_;

	box.setTextureRect(IntRect(0, 0, 128, 128));
	box.setTexture(*MapBasicTextures[id]);
	box.setRotation(rotation);

	setTextColor();
}

void Speed_det::cycle() {
	if_collide();
}

void Speed_det::render() {

	update_scrolling();

	float helper = abs(p.sx) + abs(p.sy);
	// TODO: box.setTexture(speed_det);

	if (helper > 0.85) { target[group] = true; }
	if (helper < 0.5 && (tick % 50) == 1) { target[group] = false; }

	box.setTextureRect(IntRect(128, 0, 128, 128));
	box.setColor(Color(255, 255, 255, 190 + helper * 30));

	box.setRotation(helper * 2.5 + tick % 360 / 2);
	window.draw(box);

	box.setRotation(0);
	box.setColor(Color(255, 255, 255, 255));

	box.setTextureRect(IntRect(0, 0, 128, 128));

	window.draw(box);
}

void Speed_det::editor_exist() {

	update_scrolling();
	window.draw(box);

	text.setPosition((x - scrollx + 20) * scale, (y - scrolly + 5) * scale);
	text.setCharacterSize(40 * scale);
	window.draw(text);
}