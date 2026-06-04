#include <Blocks.hpp>

Electric::Electric(int _x, int _y, int rotation, int _type, int _group) {
	// TODO: bg.setTexture(BGel);
	x = _x; y = _y; init_AABB();
	layer = 1;
	box.setRotation(rotation);
	type = _type;
	group = _group;
}

Electric::Electric() {
	// TODO: 
	//box.setTexture(void_el); 
	layer = 1;
	bg.setOrigin(64, 64);
	//bg.setTexture(BGel); 
	box.setTextureRect(IntRect(0, 0, 128, 128));
}

void Electric::set_connections(int* cons) {
	con[0] = cons[0];
	con[1] = cons[1];
	con[2] = cons[2];
	con[3] = cons[3];
}

void Electric::render() {
	update_scrolling();
	bg.setPosition(box.getPosition());
	bg.setScale(scale, scale);
	bg.setColor(Color(126 + charge * 2, 129 - charge * 2, 129 - charge * 2, 126 + charge * 2));
	window.draw(bg);
	window.draw(box);
}