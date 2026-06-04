#include <Blocks.hpp>

Generator::Generator(int _x, int _y, int rotation_, int type, bool generator_) {
	electric = true;
	// TODO: bg.setTexture(BGel); 
	x = _x; y = _y; rotation = rotation_; id = type; init_AABB();
	box.setRotation(rotation);
	/*con[0] = con_;*/ box.setOrigin(64, 64);
	generator = generator_;

	box.setTexture(*MapFloorTextures[id]);
	con_size = 1;
}

void Generator::cycle() {

	if (generator) {
		if (charge < 63) {
			charge += 1;
			if (charge < 20) {
				charge += 10;
			}
		}
	}
	else {
		if (charge > 0) {
			if (tick % 2 == 0) { charge -= 1; }
			if (charge > 10) {
				charge -= 4;
			}
		}
	}

	rech(*this, con[0]);

}

void Generator::editor_exist() {

	update_scrolling();
	window.draw(box);

	text.setString(to_string(generator));
	text.setPosition(box.getPosition());

	window.draw(text);
}

void Generator::save(ofstream& save) {
	save << "[ ";
	save << id << ' ';
	save << x << ' ';
	save << y << ' ';
	save << rotation << ' ';
	save << int(generator) << ' ';
	save << "]" << endl;
}
