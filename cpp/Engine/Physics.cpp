#include <Physics.h>
#include <cmath>

int sign(int a) {
	if (a > 0) { return 1; }
	return -1;
}

//in case of intersection collision processing
bool collide(Sq& a, Sq& b, float dt) {

	if (a.bx < b.ax || a.ax > b.bx || a.ay > b.by || a.by < b.ay) { return false; }

	float delta[2];

	delta[0] = (a.x - b.x);
	delta[1] = (a.y - b.y);

	float force = (a.hardness + b.hardness) * dt;

	// Выбирается конкретная сторона, с неё и отталкивает оба. Изменение произойдёт только при вызове move, у статичных sx, sy не используется
	if (abs(delta[0]) > abs(delta[1])) {
		a.sx += force * sign(delta[0]) / a.mass;
		b.sx -= force * sign(delta[0]) / b.mass;
	}
	else {
		a.sy += force * sign(delta[1]) / a.mass;
		b.sy -= force * sign(delta[1]) / b.mass;
	}

	return true;
}

//intersection condition only
bool intersection(Sq& a, Sq& b) {

	if (a.bx < b.ax || a.ax > b.bx || a.ay > b.by || a.by < b.ay) { return false; }

	return true;
}
