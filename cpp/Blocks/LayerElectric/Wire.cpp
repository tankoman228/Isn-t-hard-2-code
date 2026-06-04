#include <Blocks.hpp>

Wire::Wire(int _x, int _y, int rotation_, int _type) {

	x = _x; y = _y; rotation = rotation_; init_AABB();
	type = _type; id = type;
	box.setOrigin(64, 64);
	box.setRotation(rotation);
	electric = true;

	box.setTexture(*MapFloorTextures[id]);
	switch (type) {
		case 25: con_size = 1; break;
		case 26: con_size = 2; break;
		case 27: con_size = 2; break;
		case 28: con_size = 3; break;
		case 29: con_size = 4; break;
		case 32: con_size = 2; break;
	}
}

void Wire::cycle() {

	if ((type == 32) && (rand() % 2 == 0)) { return; }

	for (int k = 0; k < con_size; k++) {
		rech(*this, con[k]);
	}

}

void Wire::save(ofstream& save) {
	save << "[ ";
	save << id << ' ';
	save << x << ' ';
	save << y << ' ';
	save << rotation << ' ';
	save << "]" << endl;
}
