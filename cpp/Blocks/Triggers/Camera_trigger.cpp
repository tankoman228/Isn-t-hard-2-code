#include <Blocks.hpp>

void Camera_trigger::trigger() {

	scroll_pinned = true;

	if (box.getPosition().x > screenw * 0.55) {
		scrollx += 1;
	}
	if (box.getPosition().x < screenw * 0.45) {
		scrollx -= 1;
	}
	if (box.getPosition().y > screenh * 0.55) {
		scrolly += 1;
	}
	if (box.getPosition().y < screenh * 0.45) {
		scrolly -= 1;
	}

	if (abs(box.getPosition().x - screenw * 0.5) > 20 || abs(box.getPosition().y - screenh * 0.5) > 20) {

		for (int auf = 0; auf < 3; auf++) {

			if (box.getPosition().x > screenw * 0.55) {
				scrollx += 14;
			}
			if (box.getPosition().x < screenw * 0.45) {
				scrollx -= 14;
			}
			if (box.getPosition().y > screenh * 0.55) {
				scrolly += 14;
			}
			if (box.getPosition().y < screenh * 0.45) {
				scrolly -= 14;
			}

			update_scrolling();

		}

	}
}

Camera_trigger::Camera_trigger(int id_, int x_, int y_, int size_) {
	id = id_; x = x_; y = y_; size = size_;
	magnet = 0;
	box.setOrigin(64, 64);
	init_AABB();
	box.setPosition((x - scrollx) * scale, (y - scrolly) * scale);
	box.setTexture(*MapFloorTextures[id]);
}