#pragma once

#include <cmath>

// Параметры подвижных коробок
#define MovableHardness 20
#define MovableFriction 20

// Параметры физики/управления игрока
#define PlayerMaxSpeed   2000
#define PlayerAccelerate 4096
#define PlayerHardness   50
#define PlayerMass 		 0.5
#define PlayerFriction   2048

int sign(int a);

//AABB-alike physics model
struct Sq {

	float x = 100, y = 100; float sx = 0, sy = 0;
	float ax = 0, bx = 200, ay = 0, by = 200; //AABB
	float size = 62; //from center to border
	short layer = 0;
	float parameter = 2; // скрытый параметр для игровой сущности, какой: зависит от типа, костыль, ранее был ещё и массой

	float hardness = 64;  // квадратный корень силы, что создаёт при столкновении на другой объект на 8 пикселей проникновения
	float mass = 1;       // насколько будет движок делить применяемые к объекту силы

	float max_speed = 25;
	float friction = 30; // замедление за секунду
	int id = 0;

	bool choosen = false;

	// Шаг физики на основе своей скорости, для неподвижных можно просто не вызывать
	void move(float dt) {

		// Лимиты скорости
		if (sx > max_speed) { sx = max_speed; } if (sx < -max_speed) { sx = -max_speed; }
		if (sy > max_speed) { sy = max_speed; } if (sy < -max_speed) { sy = -max_speed; }

		// смещение ключевых точек
		x += sx * dt;
		y += sy * dt;

		ax = x - size;
		ay = y - size;

		bx = x + size;
		by = y + size;

		// Трение
		if (abs(sx) < friction * dt) sx = 0;
		else sx -= sign(sx) * friction * dt;

		if (abs(sy) < friction * dt) sy = 0;
		else sy -= sign(sy) * friction * dt;

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
		x = _x;
		y = _y;
		size = _size;

		friction = PlayerFriction;
		mass = PlayerMass;
		hardness = PlayerHardness;

		init_AABB();
	}

	void unset_player() {
		sx = 0; sy = 0;
		size = 35;

		friction = PlayerFriction;
		mass = PlayerMass;
		hardness = PlayerHardness;

		init_AABB();
	}

};

//in case of intersection collision processing
bool collide(Sq& a, Sq& b, float dt);

//intersection condition only
bool intersection(Sq& a, Sq& b);
