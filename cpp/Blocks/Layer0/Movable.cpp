#include <Blocks.h>

Movable::Movable(int _x, int _y, Texture& t, IntRect r) {

	box.setTexture(t);
	box.setTextureRect(r);
	box.setOrigin(64, 64);

	InitMovablePhysics(_x, _y);
}

Movable::Movable(int _x, int _y, int _look) {

	box.setTexture(*MapBasicTextures[5]);
	box.setTextureRect(IntRect(128 * _look, 0, 128, 128));
	box.setOrigin(64, 64);

	InitMovablePhysics(_x, _y);
}

void Movable::InitMovablePhysics(int _x, int _y) {

	id = 5; x = _x; y = _y;

	hardness = MovableHardness;
	friction = MovableFriction;
	parameter = 2;
}

void Movable::editor_behave() {
	box.setScale(scale, scale);
	box.setPosition(scale * (x - scrollx), scale * (y - scrolly));
	window.draw(box);
}

void Movable::cycle(float dt) {

	anticheat.move_to(*this);

	if (intersection(anticheat, p)) {
		colint = -1;
	}

	move(dt);

}

void Movable::save(ofstream& save) {
	save << "[ ";
	save << int(x) << ' ';
	save << int(y) << ' ';
	save << int(box.getTextureRect().left / 128) << ' ';
	save << "]" << endl;
}

void Movable::editing() {
	if (editor_mode != 4) { return; }

	E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 128 * scale);
	E_arrow[1].setPosition(box.getPosition().x + 128 * scale, box.getPosition().y);
	E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 128 * scale);
	E_arrow[3].setPosition(box.getPosition().x - 128 * scale, box.getPosition().y);

	E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
	E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
	E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
	E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);
}

//editor flickering
void Movable::do_some_magic() {
	box.setColor(Color(90, 255, 90, 255));
	window.draw(box);
	box.setColor(Color(255, 255, 255, 255));
}

void Movable::render() {
	box.setScale(scale, scale);
	box.setPosition(scale * (x - scrollx), scale * (y - scrolly));

	window.draw(box);
}