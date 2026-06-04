#include <Blocks.hpp>

View_det::View_det(int _x, int _y, int _id, int rotation_, bool* target_, int group_) {

	basic_init(_x, _y, rotation_, _id);
	group = group_; init_AABB(); layer = 0;
	box.setRotation(rotation); text.setString(to_string(group));
	target = target_;

	box.setTextureRect(IntRect(0, 0, 128, 128));
	box.setTexture(*MapBasicTextures[id]);
	box.setRotation(rotation);

	setTextColor();
}

void View_det::cycle() {
	if_collide();
}

void View_det::render() {

	box.setTextureRect(IntRect(0, 0, 128, 128));

	cursor.setPosition(playerS.getPosition());
	cursor.setRotation(playerS.getRotation());
	cursor.setOrigin(0.2, 8);
	cursor.setScale(150 * scale, 27 * scale);

	if (cursor.getGlobalBounds().intersects(box.getGlobalBounds())) {
		target[group] = true;
	}
	else { target[group] = false; box.setTextureRect(IntRect(128, 0, 128, 128)); }

	update_scrolling();
	window.draw(box);

	cursor.setPosition(Mouse::getPosition().x - window.getPosition().x, (Mouse::getPosition().y) - window.getPosition().y);
	cursor.setScale(1, 1); cursor.setOrigin(4, 4);
	cursor.setScale(1, 1);

}