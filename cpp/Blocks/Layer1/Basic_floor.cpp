#include <Blocks.h>

Basic_floor::Basic_floor(int _x, int _y, int _id, int rotation_, int look) {

	basic_init(_x, _y, rotation_, _id); init_AABB(); layer = 1;

	box.setTexture(*MapFloorTextures[id]);

	box.setTextureRect(IntRect(look * 128, 0, 128, 128));
	box.setRotation(rotation);
}

void Basic_floor::cycle() {}

void Basic_floor::edit() {

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