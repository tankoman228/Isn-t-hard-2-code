#pragma once

int sign(int a) {
	if (a > 0) { return 1; }
	return -1;
}

//AABB-alike physics model
struct Sq {

	float x = 100, y = 100; float sx = 0, sy = 0;
	float ax = 0, bx = 200, ay = 0, by = 200; //AABB
	float size = 62; //from center to border
	short layer = 0;
	float mass = 2; //not used, but don't delete
	float repulsion = 0; //this is how much the object is repulsed from the other. (0 is immovable)
	float max_speed = 6;
	int id;

	bool choosen = false;

	void move() {

		ax = x - size;
		ay = y - size;

		bx = x + size;
		by = y + size;

		sx *= 0.96;
		sy *= 0.96;

		if (sx > max_speed) { sx = max_speed; } if (sx < -max_speed) { sx = -max_speed; }
		if (sy > max_speed) { sy = max_speed; } if (sy < -max_speed) { sy = -max_speed; }

		if (abs(sx) < 0.05) { sx = 0; } if (abs(sy) < 0.05) { sy = 0; }

		x += sx;
		y += sy;

	}

	void init_AABB() {
		ax = x - size;
		ay = y - size;

		bx = x + size;
		by = y + size;
	}

	void move(int x_, int y_) {
		x += x_; y += y_;
		init_AABB();
	}

	void move_to(const Sq& a) {
		x = a.x;
		y = a.y;
		init_AABB();
	}

	virtual void editing() {}
	virtual void edit() {}
	virtual void rotate(int angle) {}
	virtual void do_some_magic() {}

	virtual int get_layer() { return 0; }

	Sq() { sx = 0; sy = 0; }
	Sq(int _x, int _y, int _size) {
		//player spawn only

		sx = 0; sy = 0;

		repulsion = 2;
		max_speed = 2.2;
		x = _x;
		y = _y;
		size = _size;
		init_AABB();
	}
	void unset_player() {
		sx = 0; sy = 0;

		repulsion = 2;
		max_speed = 2.2;

		size = 35;
		init_AABB();
	}

};

//in case of intersection collision processing
bool collide(Sq& a, Sq& b) {

	if (a.bx < b.ax || a.ax > b.bx || a.ay > b.by || a.by < b.ay) { return false; }

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
