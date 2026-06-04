#include <Blocks.hpp>

void Trigger::render() {
	update_scrolling();
	if (intersection(p, *this) && !stop) {
		stop = once_flag;
		trigger();
	}
}

void Trigger::editor_exist() {

	update_scrolling();

	zone_marker.setPosition(box.getPosition());

	// TODO: zone_marker.setTexture(block_choose);

	zone_marker.setOrigin(64, 64);
	zone_marker.setScale(scale * size / 64, scale * size / 64);
	zone_marker.setColor(Color(255, 255, 255, 155 + 55 * sin(float(tick) / 40)));

	window.draw(zone_marker);

	window.draw(box);

}

void Trigger::edit() {

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
}

void Trigger::save(ofstream& save) {
	save << "[ ";
	save << id << ' ';
	save << x << ' ';
	save << y << ' ';
	save << int(size) << ' ';
	save << "]" << endl;
}
