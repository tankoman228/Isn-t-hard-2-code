#include <Physics.h>
#include <cmath>

int sign(int a) {
	if (a > 0) { return 1; }
	return -1;
}

//in case of intersection collision processing
bool collide(Sq& a, Sq& b) {

	if (a.bx < b.ax || a.ax > b.bx || a.ay > b.by || a.by < b.ay) { return false; }

	float helper_s[2];

	helper_s[0] = (a.x - b.x);
	helper_s[1] = (a.y - b.y);


	if (abs(helper_s[0]) > abs(helper_s[1])) {

		if (helper_s[0] > 0) {
			a.x += a.repulsion;
			b.x -= b.repulsion;
		}
		else {
			a.x -= a.repulsion;
			b.x += b.repulsion;
		}

	}
	else {

		if (helper_s[1] > 0) {
			a.y += a.repulsion;
			b.y -= b.repulsion;
		}
		else {
			a.y -= a.repulsion;
			b.y += b.repulsion;
		}

	}

	a.init_AABB();
	b.init_AABB();

	return true;

}

//intersection condition only
bool intersection(Sq& a, Sq& b) {

	if (a.bx < b.ax || a.ax > b.bx || a.ay > b.by || a.by < b.ay) { return false; }

	return true;

}
