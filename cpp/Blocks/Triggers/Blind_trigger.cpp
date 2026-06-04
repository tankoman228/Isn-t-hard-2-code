#include <Blocks.hpp>

void Blind_trigger::render() {

	update_scrolling();
	if (intersection(p, *this) && !stop) {
		//stop = once_flag;
		//trigger();

		if (fade_time < 255) {
			fade_time++;
		}
		blend.setColor(Color(0, 0, 0, fade_time));
		window.draw(blend);

	}
	else {
		if (fade_time > 0) {
			fade_time--;
			blend.setColor(Color(0, 0, 0, fade_time));
			window.draw(blend);
		}
	}
}

Blind_trigger::Blind_trigger(int id_, int x_, int y_, int size_) {

	box.setTexture(*MapFloorTextures[id]);
	id = id_; x = x_; y = y_; size = size_;
	magnet = 0;
	box.setOrigin(64, 64);
	init_AABB();
	box.setPosition((x - scrollx) * scale, (y - scrolly) * scale);
}
