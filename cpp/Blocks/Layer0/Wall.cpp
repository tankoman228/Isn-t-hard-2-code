#include <Blocks.h>

Wall::Wall(int _x, int _y, int _id, int rotation_, int look) {

	basic_init(_x, _y, rotation_, _id);
	layer = 0;
	init_AABB();

	box.setTexture(*MapBasicTextures[id]);
	switch (id) {
		case 14: size = 40; init_AABB(); break;
	}

	box.setTextureRect(IntRect(look * 128, 0, 128, 128));
	box.setRotation(rotation);
}

void Wall::cycle() {
	if_collide();
}

void Wall::edit() {

	if (!onclick && editor_mode == 4 && box.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
		if (Mouse::isButtonPressed(Mouse::Left)) {
			box.setTextureRect(IntRect(box.getTextureRect().left + 128, 0, 128, 128));
			onclick = true; return;
		}
		if (Mouse::isButtonPressed(Mouse::Right)) {
			if (box.getTextureRect().left > 0) { box.setTextureRect(IntRect(box.getTextureRect().left - 128, 0, 128, 128)); }
			onclick = true; return;
		}
	}
}