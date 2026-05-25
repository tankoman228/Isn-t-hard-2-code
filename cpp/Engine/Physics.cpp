#include <Physics.h>
#include <cmath>

int sign(int a) {
	if (a > 0) { return 1; }
	return -1;
}

//in case of intersection collision processing
bool collide(Sq& a, Sq& b, float dt) {

	if (a.bx < b.ax || a.ax > b.bx || a.ay > b.by || a.by < b.ay) { return false; }

	float deepthX = (a.x - b.x);
	float deepthY = (a.y - b.y);

	// AABB, надо разделять стороны в коллизии
	if (abs(deepthX) > abs(deepthY)) {
		float forceX = (a.hardness + b.hardness) * dt * deepthX * abs(deepthX) / 64.0;
		a.sx += forceX / a.mass;
		b.sx -= forceX / b.mass;
	}
	else {
		float forceY = (a.hardness + b.hardness) * dt * deepthY * abs(deepthY) / 64.0;
		a.sy += forceY / a.mass;
		b.sy -= forceY / b.mass;
	}

	return true;
}

//intersection condition only
bool intersection(Sq& a, Sq& b) {

	if (a.bx < b.ax || a.ax > b.bx || a.ay > b.by || a.by < b.ay) { return false; }

	return true;
}
