#pragma once

#include <UI.h>
#include <Particles.h>
#include <Voids.h>
#include <Physics.h>
#include <Player.h>

#define px p.x
#define py p.y

#undef sx
#undef sy

#define psx p.sx
#define psy p.sy

struct Movable : public Sq {

	Sprite box;
	Sq anticheat = Sq(0,0,67); //Player mustn't get coin if it is blocked with movable!

	Movable(int _x, int _y, Texture &t, IntRect r) {

		box.setTexture(t);
		box.setTextureRect(r);
		box.setOrigin(64, 64);

		InitMovablePhysics(_x, _y);
	}

	Movable(int _x, int _y, int _look) {

		box.setTexture(*MapBasicTextures[5]);
		box.setTextureRect(IntRect(128 * _look, 0, 128, 128));
		box.setOrigin(64, 64);

		InitMovablePhysics(_x, _y);
	}

	void InitMovablePhysics(int _x, int _y) {

		id = 5; x = _x; y = _y;

		hardness = MovableHardness;
		friction = MovableFriction;
		parameter = 2;
	}

	void editor_behave() {
		box.setScale(scale, scale);
		box.setPosition(scale * (x - scrollx), scale * (y - scrolly));
		window.draw(box);
	}

	void cycle(float dt) {

		anticheat.move_to(*this);

		if (intersection(anticheat, p)) {
			colint = -1;
		}

		move(dt);	

	}

	void save(ofstream& save) {
		save << "[ ";
		save << int(x) << ' ';
		save << int(y) << ' ';
		save << int(box.getTextureRect().left / 128) << ' ';
		save << "]" << endl;
	}

	void editing() {
		//edit();

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
	void do_some_magic() {
		box.setColor(Color(90, 255, 90, 255));
		window.draw(box);
		box.setColor(Color(255, 255, 255, 255));
	}

	void render() {
		box.setScale(scale, scale);
		box.setPosition(scale * (x - scrollx), scale * (y - scrolly));

		window.draw(box);
	}

};

void spawn_movable(int x, int y, int _type);

const inline bool* a = dmode;
const inline bool* b = crystal;
const inline bool* c = lmode;
const inline bool* d = barmode;

struct Block : public Sq {

	Sprite box;
	int rotation = 0; float magnet = 0.14;
	bool electric = false;

	//editor flickering
	void do_some_magic() {
		box.setColor(Color(90, 255, 90, 255));
		window.draw(box);
		box.setColor(Color(255, 255, 255, 255));
	}

	void update_scrolling() {
		box.setScale(scale * 1.017, scale * 1.009);
		box.setPosition(scale * (x - scrollx), scale * (y - scrolly));
	}

	bool if_collide() {

		if (intersection(p, *this)) {

			p.sx = 0; p.sy = 0;

			do {
				// TODO: что-то мне не нравится эта физика
				block_collision = true;

				float dx = (px - x);
				float dy = (py - y);

				if (abs(dx) > abs(dy)) {
					px += 0.1 * sign(dx);
				}
				else {
					py += 0.1 * sign(dy);
				}

				p.init_AABB();
			}
			while (intersection(p, *this));

			return true;
		}

		return false;
	}

	void rotate(int angle) {
		rotation += angle;
		if (angle >= 360) { rotation -= 360; }
		if (angle < 0) { rotation += 360; }
		box.setRotation(rotation);
		last_angle = box.getRotation();
	}

	virtual void cycle() {}

	void editing() {
		//edit();

		if (editor_mode != 4) { return; }

		E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 128 * scale);
		E_arrow[1].setPosition(box.getPosition().x + 128 * scale, box.getPosition().y);
		E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 128 * scale);
		E_arrow[3].setPosition(box.getPosition().x - 128 * scale, box.getPosition().y);

		E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
		E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
		E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
		E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);

		E_rotate_block.box.setPosition(box.getPosition()); E_rotate_block.box.move(80 * scale, -80 * scale);
		E_rotate_block2.box.setPosition(box.getPosition()); E_rotate_block2.box.move(-80 * scale, -80 * scale);

		E_rotate_block.box.setScale(scale, scale);
		E_rotate_block2.box.setScale(scale, scale);
	}

	virtual void editor_exist() { 
		update_scrolling(); 
		window.draw(box); 
	}

	void setOpacity(int new_opacity /*0 is invisible, 255 is maximum*/) {
		box.setColor(Color(255, 255, 255, new_opacity));
	}

	virtual void render() { update_scrolling(); window.draw(box); }

	virtual void save(ofstream &save) { 
		save << "[ ";
		save << id << ' ';
		save << x << ' ';
		save << y << ' ';
		save << rotation << ' ';
		save << int(box.getTextureRect().left / 128) << ' ';
		save << "]" << endl;
	}

	virtual bool* getTarget() {
		return dmode;
	}

	virtual int getGroup() { return 0; }

	virtual bool getReverse() {
		return false;
	}

	Block(int x_, int y_, int rotation_, int _id) {
		x = x_; y = y_; rotation = rotation_; id = _id; init_AABB();
	}

	Block() {}
};

//Main layer

struct Basic : public Block {

	Basic(int _x, int _y, int _id, int rotation_, int look) : Block(_x, _y, rotation_, _id) {

		layer = 0;
		init_AABB();

		box.setTexture(*MapBasicTextures[id]);
		switch(id) {
			case 14: size = 40; init_AABB(); break;
		}

		box.setTextureRect(IntRect(look * 128, 0, 128, 128));
		box.setRotation(rotation);

	}

	void cycle() {
		if_collide();
	}

	void editor_behave() {

	}

	void edit() {

		if (!onclick && editor_mode == 4 && box.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
			if (Mouse::isButtonPressed(Mouse::Left)) {
				box.setTextureRect(IntRect(box.getTextureRect().left + 128, 0, 128, 128));
				onclick = true; return;
			}
			if (Mouse::isButtonPressed(Mouse::Right)) {
				if (box.getTextureRect().left > 0) { box.setTextureRect(IntRect(box.getTextureRect().left - 128, 0, 128, 128)); }
				onclick = true; return;
			}
		}

	}

};

struct Activators : public Block {

	bool irreversible, available = true; bool* target; int group;
	Text text = Text(::text);

	void setTextColor() {

		if (target == a) {
			text.setFillColor(Color::White); return;
		}
		if (target == b) {
			text.setFillColor(Color::Black); return;
		}
		if (target == c) {
			text.setFillColor(Color::Red); return;
		}
		if (target == barmode) {
			text.setFillColor(Color::Magenta); return;
		}
	}

	Activators(int _x, int _y, int _id, int rotation_, bool* target_, int group_, bool irreversible_) : Block(_x, _y, rotation_, _id) {

		irreversible = irreversible_;
		layer = 0; group = group_;

		box.setRotation(rotation);
		target = target_;
		text.setString(to_string(group));

		box.setTexture(*MapBasicTextures[id]);

		box.setTextureRect(IntRect(0, 0, 128, 128));
		box.setRotation(rotation);
		setTextColor();
	}

	void editor_exist() {

		render();
		text.setPosition((x - scrollx + 20) * scale, (y - scrolly + 5) * scale);
		text.setCharacterSize(40 * scale);
		window.draw(text);
	}

	void update() {

		if (target[group]) {
			box.setTextureRect(IntRect(128, 0, 128, 128));
		}
		else {
			box.setTextureRect(IntRect(0, 0, 128, 128));
		}

	}

	void cycle() {

		if (if_collide() && available) {

			if ((dir%2 == 1) && colint > 25) {

				colint = -5;

				if (target[group]) { target[group] = false; }
				else { target[group] = true; }

				if (irreversible) { available = false; }

				switch (id) {

				case 2: s1.play(); break;
				case 15: _break.play(); smoke_spawn("cryst",x,y); break;

				}

				update();

			}

		}

	}

	void save(ofstream& save) {
		save << "[ ";
		save << id << ' ';
		save << x << ' ';
		save << y << ' ';
		save << rotation << ' ';

		if (target == a) {
			save << "dmode" << ' ';
		}
		if (target == b) {
			save << "crystal" << ' ';
		}
		if (target == c) {
			save << "lmode" << ' ';
		}
		if (target == barmode) {
			save << "barmode" << ' ';
		}
		save << group << ' ';
		save << int(irreversible) << ' ';
		save << "]" << endl;
	}

	void editing() {

		//edit();
		if (editor_mode != 4) { return; }

		text.setString(to_string(group));

		if (option_mode) {

			E_edit_block.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y - 40 * scale);
			E_edit_block.box.setScale(scale * 0.4, scale * 0.4);

			if (E_edit_block.if_click()) {
				option_mode = !option_mode;
			}

			E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 200 * scale);
			E_arrow[1].setPosition(box.getPosition().x + 200 * scale, box.getPosition().y);
			E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 200 * scale);
			E_arrow[3].setPosition(box.getPosition().x - 200 * scale, box.getPosition().y);

			E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);

			E_edit_color.box.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y + 40 * scale);
			E_edit_color.bg_box.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y + 40 * scale);
			E_edit_color.box.setScale(0.5 * scale, 0.5 * scale);
			E_edit_color.bg_box.setScale(0.45 * scale, 0.45 * scale);
			E_edit_color.bg_box.setColor(text.getFillColor());

			E_rotate_block.box.setPosition(box.getPosition()); E_rotate_block.box.move(80 * scale, -80 * scale);
			E_rotate_block2.box.setPosition(box.getPosition()); E_rotate_block2.box.move(-80 * scale, -80 * scale);

			E_rotate_block.box.setScale(scale, scale);
			//E_rotate_block.bg_box.setScale(scale * 0.5, scale * 0.5);
			E_rotate_block2.box.setScale(scale, scale);
			//E_rotate_block2.bg_box.setScale(scale * 0.5, scale * 0.5);

			setTextColor();
			E_edit_color.bg_box.setColor(text.getFillColor());

			if (E_edit_color.if_click()) {

				if (target == a) {
					target = crystal; return;
				}
				if (target == b) {
					target = lmode; return;
				}
				if (target == c) {
					target = barmode; return;
				}
				if (target == barmode) {
					target = dmode; return;
				}
			}

			E_edit_number.box.setPosition(box.getPosition());
			E_edit_number.box.move(-40 * scale, 40 * scale);
			E_edit_number.box.setScale(scale * 0.5, scale * 0.5);
			E_edit_number.bg_box.setScale(scale * 0.5, scale * 0.5);

			if (E_edit_number.if_click()) {

				if (Mouse::isButtonPressed(Mouse::Left)) {
					group++; onclick = true;
					last_group = group;
				}
				if (Mouse::isButtonPressed(Mouse::Right)) {
					if (group > 0) {
						group--; onclick = true;
						last_group = group;
					}
				}

			}
			
			text.setPosition(E_edit_number.box.getPosition());
			text.setString(to_string(group));
			text.move(-25 * UI_scale, -30 * UI_scale);

			window.draw(text);

		}
		else {

			if (E_edit_block.if_click()) {
				option_mode = !option_mode;
			}

			if (!onclick && Mouse::isButtonPressed(Mouse::Left) && cursor.getGlobalBounds().intersects(box.getGlobalBounds())) {
				group++; onclick = true; last_group = group;
			}
			if (!onclick && Mouse::isButtonPressed(Mouse::Right) && cursor.getGlobalBounds().intersects(box.getGlobalBounds())) {
				group = 0; onclick = true; last_group = group;
			}

			E_edit_block.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y - 40 * scale);
			E_edit_block.box.setScale(scale * 0.4, scale * 0.4);

			E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 128 * scale);
			E_arrow[1].setPosition(box.getPosition().x + 128 * scale, box.getPosition().y);
			E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 128 * scale);
			E_arrow[3].setPosition(box.getPosition().x - 128 * scale, box.getPosition().y);

			E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);

			E_rotate_block.box.setPosition(box.getPosition()); E_rotate_block.box.move(80 * scale, -80 * scale);
			E_rotate_block2.box.setPosition(box.getPosition()); E_rotate_block2.box.move(-80 * scale, -80 * scale);

			E_rotate_block.box.setScale(scale, scale);
			//E_rotate_block.bg_box.setScale(scale * 0.5, scale * 0.5);
			E_rotate_block2.box.setScale(scale, scale);
			//E_rotate_block2.bg_box.setScale(scale * 0.5, scale * 0.5);
		}
	}

	bool* getTarget() {

		if (target == a) {
			return dmode;
		}
		if (target == b) {
			return crystal;
		}
		if (target == c) {
			return lmode;
		}
		if (target == barmode) {
			return barmode;
		}

	}

	int getGroup() {
		return group;
	}

};

struct Detector : public Block {

	bool change = false; bool* target; int group;
	Text text = Text(::text);
	//function<void()> program = {};

	bool* getTarget() {

		if (target == a) {
			return dmode;
		}
		if (target == b) {
			return crystal;
		}
		if (target == c) {
			return lmode;
		}
		if (target == barmode) {
			return barmode;
		}

	}

	int getGroup() {
		return group;
	}

	void player_detector_program() {

		block.setPosition((x - scrollx) * scale, (y - scrolly) * scale);

		switch (int(box.getRotation())) {
		case 0: 

			for (int k = 0; k < 3; k++) {
				block.move(scale * 128, 0);
				if (playerS.getGlobalBounds().intersects(block.getGlobalBounds())) {
					target[group] = change; break;
				}
			}

			break;

		case 90:
			
			for (int k = 0; k < 3; k++) {
				block.move(0, scale * 128);
				if (playerS.getGlobalBounds().intersects(block.getGlobalBounds())) {
					target[group] = change; break;
				}
			}

			break;

		case 180:

			for (int k = 0; k < 3; k++) {
				block.move(-scale * 128, 0);
				if (playerS.getGlobalBounds().intersects(block.getGlobalBounds())) {
					target[group] = change; break;
				}
			}

			break;

		case 270:

			for (int k = 0; k < 3; k++) {
				block.move(0, -scale * 128);
				if (playerS.getGlobalBounds().intersects(block.getGlobalBounds())) {
					target[group] = change; break;
				}
			}

			break;
		}

	}

	void setTextColor() {

		if (target == a) {
			text.setFillColor(Color::White); return;
		}
		if (target == b) {
			text.setFillColor(Color::Black); return;
		}
		if (target == c) {
			text.setFillColor(Color::Red); return;
		}
		if (target == barmode) {
			text.setFillColor(Color::Magenta); return;
		}
	}

	Detector(int _x, int _y, int _id, int rotation_, bool* target_, int group_, bool change_) : Block(_x, _y, rotation_, _id) {

		x = _x; y = _y; id = _id; group = group_; layer = 0; init_AABB(); rotation = rotation_;
		box.setRotation(rotation);
		target = target_;
		change = change_;

		text.setString(to_string(group));

		box.setTexture(*MapBasicTextures[id]);

		box.setTextureRect(IntRect(0, 0, 128, 128));
		box.setRotation(rotation);
		setTextColor();
	}

	void cycle() {

		if_collide();
		/*program();*/
		player_detector_program();

	}

	void save(ofstream& save) {
		save << "[ ";
		save << id << ' ';
		save << x << ' ';
		save << y << ' ';
		save << rotation << ' ';

		if (target == a) {
			save << "dmode" << ' ';
		}
		if (target == b) {
			save << "crystal" << ' ';
		}
		if (target == c) {
			save << "lmode" << ' ';
		}
		if (target == barmode) {
			save << "barmode" << ' ';
		}
		save << group << ' ';

		save << int(change) << ' ';

		save << "]" << endl;
	}

	void editor_exist() {
		render();
		text.setPosition((x - scrollx + 20) * scale, (y - scrolly + 5) * scale);
		text.setCharacterSize(40 * scale);
		window.draw(text);
	}

	void editing() {

		//edit();
		if (editor_mode != 4) { return; }

		text.setString(to_string(group));

		E_rotate_block.box.setPosition(box.getPosition()); E_rotate_block.box.move(80 * scale, -80 * scale);
		E_rotate_block2.box.setPosition(box.getPosition()); E_rotate_block2.box.move(-80 * scale, -80 * scale);

		E_rotate_block.box.setScale(scale, scale);
		//E_rotate_block.bg_box.setScale(scale * 0.5, scale * 0.5);
		E_rotate_block2.box.setScale(scale, scale);
		//E_rotate_block2.bg_box.setScale(scale * 0.5, scale * 0.5);

		if (option_mode) {

			E_edit_block.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y - 40 * scale);
			E_edit_block.box.setScale(scale * 0.4, scale * 0.4);

			if (E_edit_block.if_click()) {
				option_mode = !option_mode;
			}

			E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 200 * scale);
			E_arrow[1].setPosition(box.getPosition().x + 200 * scale, box.getPosition().y);
			E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 200 * scale);
			E_arrow[3].setPosition(box.getPosition().x - 200 * scale, box.getPosition().y);

			E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);

			E_edit_color.box.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y + 40 * scale);
			E_edit_color.bg_box.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y + 40 * scale);
			E_edit_color.box.setScale(0.5 * scale, 0.5 * scale);
			E_edit_color.bg_box.setScale(0.45 * scale, 0.45 * scale);
			E_edit_color.bg_box.setColor(text.getFillColor());


			setTextColor();
			E_edit_color.bg_box.setColor(text.getFillColor());

			if (E_edit_color.if_click()) {

				if (target == a) {
					target = crystal; return;
				}
				if (target == b) {
					target = lmode; return;
				}
				if (target == c) {
					target = barmode; return;
				}
				if (target == barmode) {
					target = dmode; return;
				}
			}

			E_edit_number.box.setPosition(box.getPosition());
			E_edit_number.box.move(-40 * scale, 40 * scale);
			E_edit_number.box.setScale(scale * 0.5, scale * 0.5);
			E_edit_number.bg_box.setScale(scale * 0.5, scale * 0.5);

			if (E_edit_number.if_click()) {

				if (Mouse::isButtonPressed(Mouse::Left)) {
					group++; onclick = true;
					last_group = group;
				}
				if (Mouse::isButtonPressed(Mouse::Right)) {
					if (group > 0) {
						group--; onclick = true;
						last_group = group;
					}
				}

			}

			text.setPosition(E_edit_number.box.getPosition());
			text.setString(to_string(group));
			text.move(-25 * UI_scale, -30 * UI_scale);

			window.draw(text);

		}
		else {

			E_edit_block.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y - 40 * scale);
			E_edit_block.box.setScale(scale * 0.4, scale * 0.4);

			if (E_edit_block.if_click()) {
				option_mode = !option_mode;
			}

			if (!onclick && Mouse::isButtonPressed(Mouse::Left) && cursor.getGlobalBounds().intersects(box.getGlobalBounds())) {
				group++; onclick = true; last_group = group;
			}
			if (!onclick && Mouse::isButtonPressed(Mouse::Right) && cursor.getGlobalBounds().intersects(box.getGlobalBounds())) {
				group = 0; onclick = true; last_group = group;
			}

			E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 128 * scale);
			E_arrow[1].setPosition(box.getPosition().x + 128 * scale, box.getPosition().y);
			E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 128 * scale);
			E_arrow[3].setPosition(box.getPosition().x - 128 * scale, box.getPosition().y);

			E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);
		}
	}

	bool getReverse() {
		return change;
	}

};

struct Questions : public Block {

	void update() {

		//box.setTextureRect(IntRect(0, 0, 128, 128)); box.setTexture(smth3);
		if (id != 29) {
			id = 4;
			box.setTexture(*MapBasicTextures[id]);
		}
		init_AABB();
	}

	int look;
	Text txt = Text(::text);

	Questions(int _x, int _y, int _id, int rotation_, int _look) : Block(_x, _y, rotation_, _id) {

		x = _x; y = _y; id = _id; look = _look; rotation = rotation_; layer = 0;
		init_AABB();

		box.setTexture(*MapBasicTextures[id]);

		box.setTextureRect(IntRect(look * 128, 0, 128, 128));
		box.setRotation(rotation);

		if (id == 3) { coins_required++; }
		if (id == 29) {
			box.setTextureRect(IntRect(0, 0, 128, 128));
		}

		switch (id) {
			case 3: txt.setString("Coin"); txt.setFillColor(Color::White); break;
			case 6: txt.setString("Boom"); txt.setFillColor(Color::Red); break;
			case 18: txt.setString("Movable");  txt.setFillColor(Color::White); break;
			case 19: txt.setString("Set all"); txt.setFillColor(Color::White); break;
			case 20: txt.setString("Unset all"); txt.setFillColor(Color::White); break;
			case 29: txt.setString("Pusher");  txt.setFillColor(Color::Cyan); break;
		}

	}

	void cycle() {

		// TODO: что за хрень, которая ещё и дублируется?!
		if (look == -1 && id == 29) {

			float dx = (x - px);
			float dy  = (y - py);

			if (abs(dx) > abs(dy)) {
				p.sx -= sign(dx) * 1;
			}
			else {
				p.sy -= sign(dy) * 1;
			}

			if (tick % 130 == 0) {
				look = 0; box.setTextureRect(IntRect(0, 0, 128, 128));
			}
		}

		if (if_collide()) {

			if ((dir % 2 == 1) && colint > 20) {

				switch (id) {

				case 3: sound_c.play(); id = 4; coins_gathered++; smoke_spawn("coin", x, y); break;
				case 6: sound_b.play(); smoke_spawn("smoke", x, y); x = -99999; y = -99999; break;
				case 18: open.play(); spawn_movable(x,y,look); smoke_spawn("mech", x, y, look); x = -99999; y = -99999; break;
				case 19: 
					open.play(); 
					smoke_spawn("mech", x, y, look); 
					
					for (int k = 0; k < 999; k++) {
						dmode[k] = true;
						barmode[k] = true;
						lmode[k] = true;
						crystal[k] = true;
					}

					break;
				case 20:
					open.play();
					smoke_spawn("mech", x, y, look);

					for (int k = 0; k < 999; k++) {
						dmode[k] = false;
						barmode[k] = false;
						lmode[k] = false;
						crystal[k] = false;
					}

					break;

				case 29:

					float dx = (x - px);
					float dy = (y - py);

					float s = dy * dy + dx * dx;

					p.sx -= dx / s * 300;
					p.sy -= dy / s * 300;

					look = -1;

					box.setTextureRect(IntRect(128, 0, 128, 128));

					break;
				}

				update();

			}

		}

	}

	void editor_exist() {

		render();

		txt.setCharacterSize(UI_scale * scale * 40);
		txt.setPosition((x - scrollx - UI_scale * 50) * scale, (y - scrolly - UI_scale * 30) * scale);

		window.draw(txt);
	}

};

struct Movable_spawn : public Block {

	bool exist = true; int look; 

	Movable_spawn(int _x, int _y, int _look) : Block(_x, _y, 0, 5) {

		look = _look; layer = 0; init_AABB();
		box.setTexture(*MapBasicTextures[id]);
		box.setTextureRect(IntRect(128 * look, 0, 128, 128));

	}

	void cycle() {
		if (exist) {
			exist = false;
			spawn_movable(x, y, look);
			id = -1;
		}
	}
};

struct Special : public Block {

	int look;
	Special(int _x, int _y, int _id, int rotation_, int _look) : Block(_x, _y, rotation_, _id) {

		id = _id; look = _look; layer = 0;
		init_AABB();

		box.setTexture(*MapBasicTextures[id]);

		box.setTextureRect(IntRect(look * 128, 0, 128, 128));
		box.setRotation(rotation);

	}

	void cycle() {

		switch (id) {
		case 16:
			break;
		case 17:
			if_collide();
			break;

		case 31:

			if (intersection(*this,p)) {
				achievement(lvlnum, look);
				x = -1000000;
				y = -1000000;
				init_AABB();
			}

			break;

		}

	}
	void render() {

		update_scrolling();

		float helper_s2, helper_s[2];

		switch (id) {
		case 16:

			helper_s[0] = (x - px);
			helper_s2 = helper_s[0] * helper_s[0];
			helper_s[1] = (y - py);
			helper_s2 += helper_s[1] * helper_s[1];

			// TODO: box.setTexture(gravs);
			if (look == 0) { box.rotate(-2 * tick % 360); }
			else { box.rotate(2 * tick % 360); }
			window.draw(box);

			// TODO: box.setTexture(grav);
			if (look == 0) { box.rotate(2 * tick % 360); }
			else { box.rotate(-2 * tick % 360); }

			if (!look) {
				p.sx += helper_s[0] / helper_s2 * 100;
				p.sy += helper_s[1] / helper_s2 * 100;
			}
			else {
				p.sx -= helper_s[0] / helper_s2 * 80;
				p.sy -= helper_s[1] / helper_s2 * 80;
			}
			if_collide();
			break;
		case 17:
			helper_s[0] = (x - px);
			helper_s2 = helper_s[0] * helper_s[0];
			helper_s[1] = (y - py);
			helper_s2 += helper_s[1] * helper_s[1];

			helper_s2 = sqrt(helper_s2);
			if (helper_s2 < 384) {
				box.setColor(Color(255, 255, 255, 280 - (helper_s2 / 1.5)));
				if (helper_s2 < 100) {
					box.setColor(Color(255, 255, 255, 280 - (helper_s2 / 3)));
				}
			}
			else { box.setColor(Color(255, 255, 255, 0)); }
			break;
		}
		if ((id != 31) /*|| mode == "editor" TODO: отрендерить в редакторе*/) {
			window.draw(box); 
		}
	}

	void editing() {

		//edit();
		if (editor_mode != 4) { return; }

		E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 200 * scale);
		E_arrow[1].setPosition(box.getPosition().x + 200 * scale, box.getPosition().y);
		E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 200 * scale);
		E_arrow[3].setPosition(box.getPosition().x - 200 * scale, box.getPosition().y);

		E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
		E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
		E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
		E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);

		E_edit_color.box.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y + 40 * scale);
		E_edit_color.bg_box.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y + 40 * scale);
		E_edit_color.box.setScale(0.5 * scale, 0.5 * scale);
		E_edit_color.bg_box.setScale(0.45 * scale, 0.45 * scale);
		E_edit_color.bg_box.setColor(text.getFillColor());

		E_rotate_block.box.setPosition(box.getPosition()); E_rotate_block.box.move(80 * scale, -80 * scale);
		E_rotate_block2.box.setPosition(box.getPosition()); E_rotate_block2.box.move(-80 * scale, -80 * scale);

		E_rotate_block.box.setScale(scale, scale);
		//E_rotate_block.bg_box.setScale(scale * 0.5, scale * 0.5);
		E_rotate_block2.box.setScale(scale, scale);
		//E_rotate_block2.bg_box.setScale(scale * 0.5, scale * 0.5);

		if (cursor.getGlobalBounds().intersects(box.getGlobalBounds())) {
			if (Mouse::isButtonPressed(Mouse::Left) && !onclick) {
				look++; onclick = true;
				
			}
			if (Mouse::isButtonPressed(Mouse::Right) && !onclick) {
				look = 0; onclick = true;
			}
			if (id == 16) {
				box.setTextureRect(IntRect(128 * look, 0, 128, 128));
			}
		}

		text.setPosition(box.getPosition());

		if (id == 31) { text.setString("A" + to_string(look)); }
		else { text.setString(" "); }

		window.draw(text);

	}

	void save(ofstream& save) {
		save << "[ ";
		save << id << ' ';
		save << x << ' ';
		save << y << ' ';
		save << rotation << ' ';
		save << look << ' ';
		save << "]" << endl;
	}

};

struct View_det : public Block {

	bool* target; int group;
	Text text = Text(::text);

	void setTextColor() {

		if (target == a) {
			text.setFillColor(Color::White); return;
		}
		if (target == b) {
			text.setFillColor(Color::Black); return;
		}
		if (target == c) {
			text.setFillColor(Color::Red); return;
		}
		if (target == barmode) {
			text.setFillColor(Color::Magenta); return;
		}
	}

	bool* getTarget() {

		if (target == a) {
			return dmode;
		}
		if (target == b) {
			return crystal;
		}
		if (target == c) {
			return lmode;
		}
		if (target == barmode) {
			return barmode;
		}

	}

	int getGroup() {
		return group;
	}

	View_det(int _x, int _y, int _id, int rotation_, bool* target_, int group_) : Block(_x, _y, rotation_, _id)  {

		x = _x; y = _y; id = _id; group = group_; init_AABB(); rotation = rotation_; layer = 0;
		box.setRotation(rotation); text.setString(to_string(group));
		target = target_;

		box.setTextureRect(IntRect(0, 0, 128, 128));
		box.setTexture(*MapBasicTextures[id]);
		box.setRotation(rotation);

		setTextColor();

	}

	void cycle() {

		if_collide();

	}

	void render() {

		box.setTextureRect(IntRect(0, 0, 128, 128));

		cursor.setPosition(playerS.getPosition());
		cursor.setRotation(playerS.getRotation());
		cursor.setOrigin(0.2, 8);
		cursor.setScale(150 * scale, 27 * scale);

		if (cursor.getGlobalBounds().intersects(box.getGlobalBounds())) {
			target[group] = true;

		}
		else { target[group] = false; box.setTextureRect(IntRect(128, 0, 128, 128)); }

		update_scrolling();
		window.draw(box);

		cursor.setPosition(Mouse::getPosition().x - window.getPosition().x, (Mouse::getPosition().y) - window.getPosition().y);
		cursor.setScale(1, 1); cursor.setOrigin(4, 4);
		cursor.setScale(1, 1);

	}

	void save(ofstream& save) {
		save << "[ ";
		save << id << ' ';
		save << x << ' ';
		save << y << ' ';
		save << rotation << ' ';

		if (target == a) {
			save << "dmode" << ' ';
		}
		if (target == b) {
			save << "crystal" << ' ';
		}
		if (target == c) {
			save << "lmode" << ' ';
		}
		if (target == barmode) {
			save << "barmode" << ' ';
		}
		save << group << ' ';
		save << "]" << endl;
	}

	void editor_exist() {
		render();
		text.setPosition((x - scrollx + 20) * scale, (y - scrolly + 5) * scale);
		text.setCharacterSize(40 * scale);
		window.draw(text);
	}

	void editing() {

		//edit();
		if (editor_mode != 4) { return; }

		text.setString(to_string(group));

		E_rotate_block.box.setPosition(box.getPosition()); E_rotate_block.box.move(80 * scale, -80 * scale);
		E_rotate_block2.box.setPosition(box.getPosition()); E_rotate_block2.box.move(-80 * scale, -80 * scale);

		E_rotate_block.box.setScale(scale, scale);
		//E_rotate_block.bg_box.setScale(scale * 0.5, scale * 0.5);
		E_rotate_block2.box.setScale(scale, scale);
		//E_rotate_block2.bg_box.setScale(scale * 0.5, scale * 0.5);

		if (option_mode) {

			E_edit_block.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y - 40 * scale);
			E_edit_block.box.setScale(scale * 0.4, scale * 0.4);

			if (E_edit_block.if_click()) {
				option_mode = !option_mode;
			}

			E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 200 * scale);
			E_arrow[1].setPosition(box.getPosition().x + 200 * scale, box.getPosition().y);
			E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 200 * scale);
			E_arrow[3].setPosition(box.getPosition().x - 200 * scale, box.getPosition().y);

			E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);

			E_edit_color.box.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y + 40 * scale);
			E_edit_color.bg_box.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y + 40 * scale);
			E_edit_color.box.setScale(0.5 * scale, 0.5 * scale);
			E_edit_color.bg_box.setScale(0.45 * scale, 0.45 * scale);
			E_edit_color.bg_box.setColor(text.getFillColor());

			setTextColor();
			E_edit_color.bg_box.setColor(text.getFillColor());

			if (E_edit_color.if_click()) {

				if (target == a) {
					target = crystal; return;
				}
				if (target == b) {
					target = lmode; return;
				}
				if (target == c) {
					target = barmode; return;
				}
				if (target == barmode) {
					target = dmode; return;
				}
			}

			E_edit_number.box.setPosition(box.getPosition());
			E_edit_number.box.move(-40 * scale, 40 * scale);
			E_edit_number.box.setScale(scale * 0.5, scale * 0.5);
			E_edit_number.bg_box.setScale(scale * 0.5, scale * 0.5);

			if (E_edit_number.if_click()) {

				if (Mouse::isButtonPressed(Mouse::Left)) {
					group++; onclick = true;
					last_group = group;
				}
				if (Mouse::isButtonPressed(Mouse::Right)) {
					if (group > 0) {
						group--; onclick = true;
						last_group = group;
					}
				}

			}

			text.setPosition(E_edit_number.box.getPosition());
			text.setString(to_string(group));
			text.move(-25 * UI_scale, -30 * UI_scale);

			window.draw(text);

		}
		else {

			E_edit_block.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y - 40 * scale);
			E_edit_block.box.setScale(scale * 0.4, scale * 0.4);

			if (E_edit_block.if_click()) {
				option_mode = !option_mode;
			}

			if (!onclick && Mouse::isButtonPressed(Mouse::Left) && cursor.getGlobalBounds().intersects(box.getGlobalBounds())) {
				group++; onclick = true; last_group = group;
			}
			if (!onclick && Mouse::isButtonPressed(Mouse::Right) && cursor.getGlobalBounds().intersects(box.getGlobalBounds())) {
				group = 0; onclick = true; last_group = group;
			}

			E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 128 * scale);
			E_arrow[1].setPosition(box.getPosition().x + 128 * scale, box.getPosition().y);
			E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 128 * scale);
			E_arrow[3].setPosition(box.getPosition().x - 128 * scale, box.getPosition().y);

			E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);
		}
	}

};

struct Speed_det : public Block {

	bool* target; int group;
	Text text = Text(::text);

	bool* getTarget() {

		if (target == a) {
			return dmode;
		}
		if (target == b) {
			return crystal;
		}
		if (target == c) {
			return lmode;
		}
		if (target == barmode) {
			return barmode;
		}

	}

	int getGroup() {
		return group;
	}

	void setTextColor() {

		if (target == a) {
			text.setFillColor(Color::White); return;
		}
		if (target == b) {
			text.setFillColor(Color::Black); return;
		}
		if (target == c) {
			text.setFillColor(Color::Red); return;
		}
		if (target == barmode) {
			text.setFillColor(Color::Magenta); return;
		}
	}

	Speed_det(int _x, int _y, int _id, int rotation_, bool* target_, int group_) : Block(_x, _y, rotation_, _id)  {

		x = _x; y = _y; id = _id; group = group_; init_AABB(); rotation = rotation_; layer = 0;
		box.setRotation(rotation); text.setString(to_string(group));
		target = target_;

		box.setTextureRect(IntRect(0, 0, 128, 128));
		box.setTexture(*MapBasicTextures[id]);
		box.setRotation(rotation);

		setTextColor();
	}

	void cycle() {

		if_collide();

	}

	void render() {

		update_scrolling();

		float helper = abs(p.sx) + abs(p.sy);
		// TODO: box.setTexture(speed_det);

		if (helper > 0.85) { target[group] = true; }
		if (helper < 0.5 && (tick % 50) == 1) { target[group] = false; }

		box.setTextureRect(IntRect(128, 0, 128, 128));
		box.setColor(Color(255, 255, 255, 190 + helper * 30));

		box.setRotation(helper * 2.5 + tick % 360 / 2);
		window.draw(box);

		box.setRotation(0);
		box.setColor(Color(255, 255, 255, 255));

		box.setTextureRect(IntRect(0, 0, 128, 128));

		window.draw(box);
	}

	void save(ofstream& save) {
		save << "[ ";
		save << id << ' ';
		save << x << ' ';
		save << y << ' ';
		save << rotation << ' ';

		if (target == a) {
			save << "dmode" << ' ';
		}
		if (target == b) {
			save << "crystal" << ' ';
		}
		if (target == c) {
			save << "lmode" << ' ';
		}
		if (target == barmode) {
			save << "barmode" << ' ';
		}
		save << group << ' ';
		save << "]" << endl;
	}

	void editor_exist() {

		update_scrolling();
		window.draw(box);

		text.setPosition((x - scrollx + 20) * scale, (y - scrolly + 5) * scale);
		text.setCharacterSize(40 * scale);
		window.draw(text);
	}

	void editing() {

		//edit();
		if (editor_mode != 4) { return; }

		text.setString(to_string(group));

		E_rotate_block.box.setPosition(box.getPosition()); E_rotate_block.box.move(80 * scale, -80 * scale);
		E_rotate_block2.box.setPosition(box.getPosition()); E_rotate_block2.box.move(-80 * scale, -80 * scale);

		E_rotate_block.box.setScale(scale, scale);
		//E_rotate_block.bg_box.setScale(scale * 0.5, scale * 0.5);
		E_rotate_block2.box.setScale(scale, scale);
		//E_rotate_block2.bg_box.setScale(scale * 0.5, scale * 0.5);

		if (option_mode) {

			E_edit_block.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y - 40 * scale);
			E_edit_block.box.setScale(scale * 0.4, scale * 0.4);

			if (E_edit_block.if_click()) {
				option_mode = !option_mode;
			}

			E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 200 * scale);
			E_arrow[1].setPosition(box.getPosition().x + 200 * scale, box.getPosition().y);
			E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 200 * scale);
			E_arrow[3].setPosition(box.getPosition().x - 200 * scale, box.getPosition().y);

			E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);

			E_edit_color.box.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y + 40 * scale);
			E_edit_color.bg_box.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y + 40 * scale);
			E_edit_color.box.setScale(0.5 * scale, 0.5 * scale);
			E_edit_color.bg_box.setScale(0.45 * scale, 0.45 * scale);
			E_edit_color.bg_box.setColor(text.getFillColor());

			setTextColor();
			E_edit_color.bg_box.setColor(text.getFillColor());

			if (E_edit_color.if_click()) {

				if (target == a) {
					target = crystal; return;
				}
				if (target == b) {
					target = lmode; return;
				}
				if (target == c) {
					target = barmode; return;
				}
				if (target == barmode) {
					target = dmode; return;
				}
			}

			E_edit_number.box.setPosition(box.getPosition());
			E_edit_number.box.move(-40 * scale, 40 * scale);
			E_edit_number.box.setScale(scale * 0.5, scale * 0.5);
			E_edit_number.bg_box.setScale(scale * 0.5, scale * 0.5);

			if (E_edit_number.if_click()) {

				if (Mouse::isButtonPressed(Mouse::Left)) {
					group++; onclick = true;
					last_group = group;
				}
				if (Mouse::isButtonPressed(Mouse::Right)) {
					if (group > 0) {
						group--; onclick = true;
						last_group = group;
					}
				}

			}

			text.setPosition(E_edit_number.box.getPosition());
			text.setString(to_string(group));
			text.move(-25 * UI_scale, -30 * UI_scale);

			window.draw(text);

		}
		else {

			if (E_edit_block.if_click()) {
				option_mode = !option_mode;
			}

			if (!onclick && Mouse::isButtonPressed(Mouse::Left) && cursor.getGlobalBounds().intersects(box.getGlobalBounds())) {
				group++; onclick = true; last_group = group;
			}
			if (!onclick && Mouse::isButtonPressed(Mouse::Right) && cursor.getGlobalBounds().intersects(box.getGlobalBounds())) {
				group = 0; onclick = true; last_group = group;
			}

			E_edit_block.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y - 40 * scale);
			E_edit_block.box.setScale(scale * 0.4, scale * 0.4);

			E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 128 * scale);
			E_arrow[1].setPosition(box.getPosition().x + 128 * scale, box.getPosition().y);
			E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 128 * scale);
			E_arrow[3].setPosition(box.getPosition().x - 128 * scale, box.getPosition().y);

			E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);
		}
	}
};

//Floor

struct Basic_floor : public Block {

	Basic_floor(int _x, int _y, int _id, int rotation_, int look) : Block(_x, _y, rotation_, _id) {

		x = _x; y = _y; id = _id; init_AABB(); rotation = rotation_; layer = 1;

		box.setTexture(*MapFloorTextures[id]);

		box.setTextureRect(IntRect(look * 128, 0, 128, 128));
		box.setRotation(rotation);

	}

	void cycle() {

	}

	void edit() {

		if (!onclick && editor_mode == 4 && box.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
			if (Mouse::isButtonPressed(Mouse::Left)) {
				box.setTextureRect(IntRect(box.getTextureRect().left + 128, 0, 128, 128));
				onclick = true; return;
			}
			if (Mouse::isButtonPressed(Mouse::Right)) {
				if (box.getTextureRect().left > 0) { box.setTextureRect(IntRect(box.getTextureRect().left - 128, 0, 128, 128)); }
				onclick = true; return;
			}
		}

	}

};

struct Special_floor : public Block {

	int look;
	Special_floor(int _x, int _y, int _id, int rotation_, int _look) : Block(_x, _y, rotation_, _id)  {

		x = _x; y = _y; id = _id; look = _look; rotation = rotation_; layer = 1;
		box.setRotation(rotation);
		box.setTexture(*MapFloorTextures[id]);

		switch (id) {
			case 19: magnet = 0; size = 40; break;
			case 43: size = 65; parameter = look; break;
			case 45: parameter = look; break;
		}

		init_AABB();

		box.setTextureRect(IntRect(0, 0, 128, 128));
		box.setRotation(rotation);

	}

	void cycle() {
		switch (id) {
		case 6:
			break;
		case 18:
			//Fake block
			break;

		case 19:

			for (int j = 0; j < movables.size(); j++) {
				if (intersection(*movables[j],*this)) {
					switch (int(box.getRotation())) {
					case 0: movables[j]->x += 0.5; break;
					case 90: movables[j]->y += 0.5; break;
					case 180: movables[j]->x -= 0.5; break;
					case 270: movables[j]->y -= 0.5; break;
					}
				}

			}

			break;

		case 43:

			if (tp_rech == 0) {
				if (intersection(*this, p)) {

					for (int k = 0; k < map_floor.size(); k++) {
						if (map_floor[k] == this) { continue; }

						if (map_floor[k]->id == 43 && map_floor[k]->parameter == parameter) {
							px = map_floor[k]->x;
							py = map_floor[k]->y; tp_rech = 80;

							last_coordinates[0][0] = scale * (p.x - scrollx);
							last_coordinates[1][0] = scale * (p.x - scrollx);
							last_coordinates[2][0] = scale * (p.x - scrollx);
							last_coordinates[3][0] = scale * (p.x - scrollx);
							last_coordinates[4][0] = scale * (p.x - scrollx);
							last_coordinates[5][0] = scale * (p.x - scrollx);

							last_coordinates[0][1] = scale * (p.y - scrolly);
							last_coordinates[1][1] = scale * (p.y - scrolly);
							last_coordinates[2][1] = scale * (p.y - scrolly);
							last_coordinates[3][1] = scale * (p.y - scrolly);
							last_coordinates[4][1] = scale * (p.y - scrolly);
							last_coordinates[5][1] = scale * (p.y - scrolly);

							smoke_spawn("tp",x,y); smoke_spawn("tp", map_floor[k]->x, map_floor[k]->y); 
							tp2.play(); teleport_frame = 50;

							switch (int(map_floor[k]->box.getRotation())) {
							case 0: ::px += 50; break;
							case 90: ::py += 50; break;
							case 180: ::px -= 50; break;
							case 270: ::py -= 50; break;
							}

							break;

						}

					}

				}
				else {
					for (int k = 0; k < movables.size(); k++) {
						if (intersection(*this, *movables[k])) {

							for (int c = 0; c < map_floor.size(); c++) {
								if (map_floor[c] == this) { continue; }
								
								if (map_floor[c]->id == 43 && map_floor[c]->parameter == parameter) {
									movables[k]->x = map_floor[c]->x;
									movables[k]->y = map_floor[c]->y; tp_rech = 150;
									smoke_spawn("tp", x, y); smoke_spawn("tp", map_floor[c]->x, map_floor[c]->y);
									tp2.play(); teleport_frame = 50;
								}

							}

						}
					}
				}
			}
			else {
				for (int k = 0; k < movables.size(); k++) {
					if (intersection(*this, *movables[k])) {
						switch (int(box.getRotation())) {
						case 0: movables[k]->sx += 1; break;
						case 90: movables[k]->sy += 1; break;
						case 180: movables[k]->sx -= 1; break;
						case 270: movables[k]->sy -= 1; break;
						}
					}
				}
			}

			break;

		case 45:

			box.setTextureRect(IntRect(0, 0, 128, 128));

			switch (int(box.getRotation())) {
			case 0:
				
				if (px > x && py < y) {
					barmode[int(parameter)] = true;
				}
				else {
					barmode[int(parameter)] = false;
					box.setTextureRect(IntRect(128, 0, 128, 128));
				}
				break;

			case 90:

				if (px > x && py > y) {
					barmode[int(parameter)] = true;
				}
				else {
					barmode[int(parameter)] = false;
					box.setTextureRect(IntRect(128, 0, 128, 128));
				}
				break;

			case 180:

				if (px < x && py > y) {
					barmode[int(parameter)] = true;
				}
				else {
					barmode[int(parameter)] = false;
					box.setTextureRect(IntRect(128, 0, 128, 128));
				}
				break;

			case 270:

				if (px < x && py < y) {
					barmode[int(parameter)] = true;
				}
				else {
					barmode[int(parameter)] = false;
					box.setTextureRect(IntRect(128, 0, 128, 128));
				}
				break;

			}

			break;
   
		default: break;
		}
	}

	void render() {

		update_scrolling();
		float helper_s2 = 0;
		float helper_s[2];

		switch (id) {

		case 6:

			if (coins_gathered >= coins_required) {
				// TODO: box.setTexture(finon);
				if (intersection(p,*this)) {
					alpha -= 1;
				}
			}
			break;

		case 18:

			box.setColor(Color(255, 255, 255, 255));

			helper_s[0] = x - px;
			helper_s2 += helper_s[0] * helper_s[0];
			helper_s[1] = y - py;

			helper_s2 += helper_s[1] * helper_s[1];
			helper_s2 = sqrt(helper_s2);

			/* TODO: 
			switch (look) {
			case 1: box.setTexture(blue); break;
			case 2: box.setTexture(switch_t); break;
			case 3: box.setTexture(smth); break;
			case 4: box.setTexture(smth2); break;
			case 5: box.setTexture(movable); break;
			case 6: box.setTexture(smth); break;
			case 7: box.setTexture(wall); break;
			case 8: box.setTexture(gr); break;
			case 9: box.setTexture(grb); break;
			case 10: box.setTexture(green); break;
			case 11: box.setTexture(greenw); break;
			case 12: box.setTexture(roseb); break;
			case 13: box.setTexture(rb); break;
			case 14: box.setTexture(fl); break;
			case 15: box.setTexture(crys); break;
			case 16: box.setTexture(grav); break;
			case 17: box.setTexture(whitewall); break;
				deafult: box.setTexture(wall); break;
			}*/

			window.draw(box);

			if (helper_s2 < 262) {
				box.setColor(Color(255, 255, 255, 256 - (helper_s2 - 8)));
				if (helper_s2 < 50) {
					box.setColor(Color(255, 255, 255, 255));
				}

				// TODO: box.setTexture(noth);
			}

			window.draw(box);

			break;

		case 43:

			box.setTextureRect(IntRect(128, 0, 128, 128));

			box.rotate(tick % 360);

			if (tp_rech > 0) {
				box.setColor(Color(255, 255, 255, 255 - tp_rech));
				window.draw(box);
				box.setColor(Color::White);
			}
			else { window.draw(box); }

			box.rotate(-(tick % 360));

			box.setTextureRect(IntRect(0, 0, 128, 128));

			window.draw(box);

			break;
		}

		window.draw(box);

	}

	void save(ofstream& save) {
		save << "[ ";
		save << id << ' ';
		save << x << ' ';
		save << y << ' ';
		save << rotation << ' ';
		save << look << ' ';
		save << "]" << endl;
	}

	void edit() {

		if (!onclick && box.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
			if (Mouse::isButtonPressed(Mouse::Left)) {
				look++; if (id == 18) { last_group = look; }
				onclick = true; return;
			}
			if (Mouse::isButtonPressed(Mouse::Right)) {	
				if (look > 0) { look--; last_group = look; }
				return;
			}
		}

	}

	void editor_exist() {

		switch (id) {

		case 6:
			break;
		case 18:

			// TODO: box.setTexture(noth);
			window.draw(box);

			box.setColor(Color(255, 255, 255, 128));

			/*
			switch (look) {
			case 1: box.setTexture(blue); break;
			case 2: box.setTexture(switch_t); break;
			case 3: box.setTexture(smth); break;
			case 4: box.setTexture(smth2); break;
			case 5: box.setTexture(movable); break;
			case 6: box.setTexture(smth); break;
			case 7: box.setTexture(wall); break;
			case 8: box.setTexture(gr); break;
			case 9: box.setTexture(grb); break;
			case 10: box.setTexture(green); break;
			case 11: box.setTexture(greenw); break;
			case 12: box.setTexture(roseb); break;
			case 13: box.setTexture(rb); break;
			case 14: box.setTexture(fl); break;
			case 15: box.setTexture(crys); break;
			case 16: box.setTexture(grav); break;
			case 17: box.setTexture(whitewall); break;
			deafult: box.setTexture(wall); break;
			}*/

			break;

		case 43:

			box.setTextureRect(IntRect(128, 0, 128, 128));

			box.rotate(tick % 360);

			if (tp_rech > 0) {
				box.setColor(Color(255, 255, 255, 255 - tp_rech));
				window.draw(box);
				box.setColor(Color::White);
			}
			else { window.draw(box); }

			box.rotate(-(tick % 360));

			box.setTextureRect(IntRect(0, 0, 128, 128));

			/*
			TODO: рендер в редакторе стрелочки
			if (mode == "editor") {
				// TODO: box.setTexture(_arrow);
				box.setColor(Color(255, 255, 255, 128));
				window.draw(box);
				// TODO: box.setTexture(portal2);

				text.setPosition(box.getPosition());
				parameter = look;
				text.setString(to_string(int(parameter)));
				text.setFillColor(Color::White);
				window.draw(text);
			}*/

			break;
		}

		update_scrolling();
		window.draw(box);
	}
};

struct Portal : public Block {

	int tp_to;
	Portal(int _x, int _y, int _id, int _tp_to) {
		box.setOrigin(64, 64);
		x = _x; y = _y; id = _id; tp_to = _tp_to; layer = 1; 
		size = 20; init_AABB();

		box.setTexture(*MapFloorTextures[id]); 

		switch (id) {
			case 7: break;
			case 8: tx[tp_to] = x; ty[tp_to] = y; break;
		}

		box.setTextureRect(IntRect(0, 0, 128, 128));
		box.setRotation(0);
	}

	void render() {

		if (id == 7) { 

			spiral[tp_to].setPosition((x - scrollx) * scale, (y - scrolly) * scale); 

			if (spiral[tp_to].getGlobalBounds().intersects(playerS.getGlobalBounds())) {

				if ((!on_teleport) && (teleport_frame == 0)) {
					tp_s.play();
				}

				playerS.setColor(Color(255, 255, 255, 260 - teleport_frame * 4));
				eyes.setColor(Color(255, 255, 255, 260 - teleport_frame * 4));

				playerS.setRotation(teleport_frame * 5);
				spiral[tp_to].rotate(2);

				on_teleport = true;
				px = x;
				py = y;

				teleport_frame += 1.75;
				teleport_to = tp_to;

				if (teleport_frame > 10) {
					if (teleport_frame > 13) {
						if (teleport_frame > 16) {
							spiral[tp_to].setTextureRect(IntRect(768, 0, 256, 256));
						}
						else {
							spiral[tp_to].setTextureRect(IntRect(512, 0, 256, 256));
						}
					}
					else {
						spiral[tp_to].setTextureRect(IntRect(256, 0, 256, 256));
					}
				}

			}

		}

		if (id == 8) {
			
			if ((tp_to == teleport_to) && (teleport_frame > 64)) {
				
				on_teleport = false;
				playerS.setScale(scale, scale);
				eyes.setScale(scale, scale);
				spiral[tp_to].setTextureRect(IntRect(0, 0, 256, 256));

				px = x;
				py = y;

				playerS.setRotation((rand() % 4) * 90);
			
				//playerS.setColor(Color::White);
				//eyes.setColor(Color::White);
			}

		}

		update_scrolling();
		window.draw(box);

	}

	void save(ofstream& save) {
		save << "[ ";
		save << id << ' ';
		save << x << ' ';
		save << y << ' ';
		save << tp_to << ' ';
		save << "]" << endl;
	}

	void editor_exist() {

		update_scrolling(); window.draw(box);

		text.setPosition(box.getPosition());
		text.setString(to_string(tp_to + 1));
		window.draw(text);
	}

	void edit() {

		if (!onclick && Mouse::isButtonPressed(Mouse::Left) && box.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
			tp_to++;
			onclick = true;
			if (tp_to > 4) {
				tp_to = 0;
			}
		}

	}

};

struct Floor_button : public Block {

	bool change = false; bool* target; int group;
	Text text = Text(::text);

	void setTextColor() {

		if (target == a) {
			text.setFillColor(Color::White); return;
		}
		if (target == b) {
			text.setFillColor(Color::Black); return;
		}
		if (target == c) {
			text.setFillColor(Color::Red); return;
		}
		if (target == barmode) {
			text.setFillColor(Color::Magenta); return;
		}
	}

	Floor_button(int _x, int _y, int _id, int rotation_, bool* target_, int group_, bool change_) {

		x = _x; y = _y; id = _id; group = group_; rotation = rotation_; layer = 1;
		box.setRotation(rotation);
		target = target_; init_AABB();
		change = change_;

		// TODO: box.setTexture(buttonblock);

		box.setTextureRect(IntRect(0, 0, 128, 128));
		box.setRotation(rotation);

		setTextColor();
		text.setString(to_string(group));
	}

	void cycle() {

		if (intersection(p,*this)) {
			box.setTextureRect(IntRect(128, 0, 128, 128));

			if (!target[group]) {
				open.play();
			}
			target[group] = true;

			return;
		}
		else {

			for (int k = 0; k < movables.size(); k++) {

				if (bx < movables[k]->ax || ax > movables[k]->bx || ay > movables[k]->by || by < movables[k]->ay) { continue; }
				if (abs(movables[k]->x - x) > 30 || abs(movables[k]->y - y) > 30) { continue; }

				box.setTextureRect(IntRect(128, 0, 128, 128));

				if (!target[group]) {
					open.play();
				}
				target[group] = true;

				return;

			}
		}

		if (target[group]) {
			open.play();
		}

		target[group] = false;
		box.setTextureRect(IntRect(0, 0, 128, 128));

	}

	void save(ofstream& save) {
		save << "[ ";
		save << id << ' ';
		save << x << ' ';
		save << y << ' ';
		save << rotation << ' ';

		if (target == a) {
			save << "dmode" << ' ';
		}
		if (target == b) {
			save << "crystal" << ' ';
		}
		if (target == c) {
			save << "lmode" << ' ';
		}
		if (target == barmode) {
			save << "barmode" << ' ';
		}
		save << group << ' ';
		save << int(change) << ' ';
		save << "]" << endl;
	}

	void editing() {

		text.setString(to_string(group));

		//edit();
		if (editor_mode != 4) { return; }

		E_rotate_block.box.setPosition(box.getPosition()); E_rotate_block.box.move(80 * scale, -80 * scale);
		E_rotate_block2.box.setPosition(box.getPosition()); E_rotate_block2.box.move(-80 * scale, -80 * scale);

		E_rotate_block.box.setScale(scale, scale);
		//E_rotate_block.bg_box.setScale(scale * 0.5, scale * 0.5);
		E_rotate_block2.box.setScale(scale, scale);
		//E_rotate_block2.bg_box.setScale(scale * 0.5, scale * 0.5);

		if (option_mode) {

			E_edit_block.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y - 40 * scale);
			E_edit_block.box.setScale(scale * 0.4, scale * 0.4);

			if (E_edit_block.if_click()) {
				option_mode = !option_mode;
			}

			E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 200 * scale);
			E_arrow[1].setPosition(box.getPosition().x + 200 * scale, box.getPosition().y);
			E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 200 * scale);
			E_arrow[3].setPosition(box.getPosition().x - 200 * scale, box.getPosition().y);

			E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);

			E_edit_color.box.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y + 40 * scale);
			E_edit_color.bg_box.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y + 40 * scale);
			E_edit_color.box.setScale(0.5 * scale, 0.5 * scale);
			E_edit_color.bg_box.setScale(0.45 * scale, 0.45 * scale);
			E_edit_color.bg_box.setColor(text.getFillColor());

			setTextColor();
			E_edit_color.bg_box.setColor(text.getFillColor());

			if (E_edit_color.if_click()) {

				if (target == a) {
					target = crystal; return;
				}
				if (target == b) {
					target = lmode; return;
				}
				if (target == c) {
					target = barmode; return;
				}
				if (target == barmode) {
					target = dmode; return;
				}
			}

			E_edit_number.box.setPosition(box.getPosition());
			E_edit_number.box.move(-40 * scale, 40 * scale);
			E_edit_number.box.setScale(scale * 0.5, scale * 0.5);
			E_edit_number.bg_box.setScale(scale * 0.5, scale * 0.5);

			if (E_edit_number.if_click()) {

				if (Mouse::isButtonPressed(Mouse::Left)) {
					group++; onclick = true;
					last_group = group;
				}
				if (Mouse::isButtonPressed(Mouse::Right)) {
					if (group > 0) {
						group--; onclick = true;
						last_group = group;
					}
				}

			}

			text.setPosition(E_edit_number.box.getPosition());
			text.setString(to_string(group));
			text.move(-25 * UI_scale, -30 * UI_scale);

			window.draw(text);

		}
		else {

			E_edit_block.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y - 40 * scale);
			E_edit_block.box.setScale(scale * 0.4, scale * 0.4);

			if (E_edit_block.if_click()) {
				option_mode = !option_mode;
			}

			if (!onclick && Mouse::isButtonPressed(Mouse::Left) && cursor.getGlobalBounds().intersects(box.getGlobalBounds())) {
				group++; onclick = true; last_group = group;
			}
			if (!onclick && Mouse::isButtonPressed(Mouse::Right) && cursor.getGlobalBounds().intersects(box.getGlobalBounds())) {
				group = 0; onclick = true; last_group = group;
			}

			E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 128 * scale);
			E_arrow[1].setPosition(box.getPosition().x + 128 * scale, box.getPosition().y);
			E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 128 * scale);
			E_arrow[3].setPosition(box.getPosition().x - 128 * scale, box.getPosition().y);

			E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);
		}
	}

	void editor_exist() {

		update_scrolling();
		window.draw(box);

		text.setPosition((x - scrollx + 20) * scale, (y - scrolly + 5) * scale);
		text.setCharacterSize(40 * scale);
		window.draw(text);
	}

	bool* getTarget() {

		if (target == a) {
			return dmode;
		}
		if (target == b) {
			return crystal;
		}
		if (target == c) {
			return lmode;
		}
		if (target == barmode) {
			return barmode;
		}

	}

	int getGroup() {
		return group;
	}

};

struct Door : public Block {

	int group; bool reversed; bool* target;
	Text text = ::text;

	void setTextColor() {

		if (target == a) {
			text.setFillColor(Color::White); return;
		}
		if (target == b) {
			text.setFillColor(Color::Black); return;
		}
		if (target == c) {
			text.setFillColor(Color::Red); return;
		}
		if (target == barmode) {
			text.setFillColor(Color::Magenta); return;
		}
	}

	bool* getTarget() {

		if (target == a) {
			return dmode;
		}
		if (target == b) {
			return crystal;
		}
		if (target == c) {
			return lmode;
		}
		if (target == barmode) {
			return barmode;
		}

	}

	int getGroup() {
		return group;
	}

	Door(int _x, int _y, int _id, int rotation_, bool* target_, int _group, bool reversed_) : Block(_x, _y, rotation_, _id)  {

		target = target_; group = _group; layer = 1;
		/*magnet = -0.15;*/

		box.setTexture(*MapFloorTextures[id]);
		box.setTextureRect(IntRect(0, 0, 128, 128));

		switch (id) {
			case 2:  reversed = false; box.setTextureRect(IntRect(0, 0, 128, 128)); break;
			case 3:  reversed = true; box.setTextureRect(IntRect(128, 0, 128, 128)); break;
			case 15: reversed = true; box.setTextureRect(IntRect(0, 0, 128, 128)); break;
			case 16: reversed = false; box.setTextureRect(IntRect(128, 0, 128, 128)); break;
			case 23: reversed = false; box.setTextureRect(IntRect(0, 0, 128, 128)); break;
			case 24: reversed = true; box.setTextureRect(IntRect(128, 0, 128, 128)); break;
			case 38: reversed = false; box.setTextureRect(IntRect(0, 0, 128, 128)); break;
			case 39: reversed = true; box.setTextureRect(IntRect(128, 0, 128, 128)); break;
			case 40: reversed = false; box.setTextureRect(IntRect(0, 0, 128, 128)); break;
			case 41: reversed = true; box.setTextureRect(IntRect(128, 0, 128, 128)); break;
		}

		reversed = reversed_;

		box.setRotation(rotation);
		setTextColor();
		text.setString(to_string(group));

	}

	void cycle() {
		if (target[group]) {
			if (reversed) {
				box.setTextureRect(IntRect(0, 0, 128, 128));
			}
			else {
				box.setTextureRect(IntRect(128, 0, 128, 128));
				if_collide();

				for (int k = 0; k < movables.size(); k++) {
					if (collide(*this, *movables[k], 0.5)) { // TODO: dt
						/*if (abs(movables[k]->x - x) < 3 || abs(movables[k]->y - y) < 3) {
							smoke_spawn("smoke", x, y);
							sound_b.play();
							movables[k]->x = -999999;
							return;
						}*/
					}
				}

			}
		}
		else {
			if (reversed) {
				box.setTextureRect(IntRect(128, 0, 128, 128));
				if_collide();

				for (int k = 0; k < movables.size(); k++) {
					if (collide(*this, *movables[k], 0.5)) { // TODO: dt
						//if (abs(movables[k]->x - x) < 3 || abs(movables[k]->y - y) < 3) {
						//	smoke_spawn("smoke", x, y);
						//	sound_b.play();
						//	movables[k]->x = -999999;
						//	return;
						//}
					}
				}
			}
			else {
				box.setTextureRect(IntRect(0, 0, 128, 128));
			}
		}
	}

	void save(ofstream& save) {
		save << "[ ";
		save << id << ' ';
		save << x << ' ';
		save << y << ' ';
		save << rotation << ' ';

		if (target == a) {
			save << "dmode" << ' ';
		}
		if (target == b) {
			save << "crystal" << ' ';
		}
		if (target == c) {
			save << "lmode" << ' ';
		}
		if (target == barmode) {
			save << "barmode" << ' ';
		}
		save << group << ' ';
		save << int(reversed) << ' ';
		save << "]" << endl;
	}

	void editing() {

		//edit();
		if (editor_mode != 4) { return; }

		text.setString(to_string(group));

		E_rotate_block.box.setPosition(box.getPosition()); E_rotate_block.box.move(80 * scale, -80 * scale);
		E_rotate_block2.box.setPosition(box.getPosition()); E_rotate_block2.box.move(-80 * scale, -80 * scale);

		E_rotate_block.box.setScale(scale, scale);
		//E_rotate_block.bg_box.setScale(scale * 0.5, scale * 0.5);
		E_rotate_block2.box.setScale(scale, scale);
		//E_rotate_block2.bg_box.setScale(scale * 0.5, scale * 0.5);

		if (option_mode) {

			E_edit_block.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y - 40 * scale);
			E_edit_block.box.setScale(scale * 0.4, scale * 0.4);

			if (E_edit_block.if_click()) {
				option_mode = !option_mode;
			}

			E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 200 * scale);
			E_arrow[1].setPosition(box.getPosition().x + 200 * scale, box.getPosition().y);
			E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 200 * scale);
			E_arrow[3].setPosition(box.getPosition().x - 200 * scale, box.getPosition().y);

			E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);

			E_edit_color.box.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y + 40 * scale);
			E_edit_color.bg_box.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y + 40 * scale);
			E_edit_color.box.setScale(0.5 * scale, 0.5 * scale);
			E_edit_color.bg_box.setScale(0.45 * scale, 0.45 * scale);
			E_edit_color.bg_box.setColor(text.getFillColor());

			setTextColor();
			E_edit_color.bg_box.setColor(text.getFillColor());

			if (E_edit_color.if_click()) {

				if (target == a) {
					target = crystal; return;
				}
				if (target == b) {
					target = lmode; return;
				}
				if (target == c) {
					target = barmode; return;
				}
				if (target == barmode) {
					target = dmode; return;
				}
			}

			E_edit_number.box.setPosition(box.getPosition());
			E_edit_number.box.move(-40 * scale, 40 * scale);
			E_edit_number.box.setScale(scale * 0.5, scale * 0.5);
			E_edit_number.bg_box.setScale(scale * 0.5, scale * 0.5);

			if (E_edit_number.if_click()) {

				if (Mouse::isButtonPressed(Mouse::Left)) {
					group++; onclick = true;
					last_group = group;
				}
				if (Mouse::isButtonPressed(Mouse::Right)) {
					if (group > 0) {
						group--; onclick = true;
						last_group = group;
					}
				}

			}

			text.setPosition(E_edit_number.box.getPosition());
			text.setString(to_string(group));
			text.move(-25 * UI_scale, -30 * UI_scale);

			window.draw(text);

		}
		else {

			E_edit_block.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y - 40 * scale);
			E_edit_block.box.setScale(scale * 0.4, scale * 0.4);

			if (E_edit_block.if_click()) {
				option_mode = !option_mode;
			}

			if (!onclick && Mouse::isButtonPressed(Mouse::Left) && cursor.getGlobalBounds().intersects(box.getGlobalBounds())) {
				group++; onclick = true; last_group = group;
			}
			if (!onclick && Mouse::isButtonPressed(Mouse::Right) && cursor.getGlobalBounds().intersects(box.getGlobalBounds())) {
				group = 0; onclick = true; last_group = group;
			}

			E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 128 * scale);
			E_arrow[1].setPosition(box.getPosition().x + 128 * scale, box.getPosition().y);
			E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 128 * scale);
			E_arrow[3].setPosition(box.getPosition().x - 128 * scale, box.getPosition().y);

			E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);
		}
	}

	void editor_exist() {

		update_scrolling();
		window.draw(box);

		text.setPosition((x - scrollx + 20) * scale, (y - scrolly + 5) * scale);
		text.setCharacterSize(40 * scale);
		window.draw(text);
	}

	bool getReverse() {
		return reversed;
	}

};

//Electricity

struct Electric : public Block {

	Sprite bg;
	int con[4] = {0,0,0,0}; int con_size = 0;
	int charge = 0, type = 0, group;

	Electric(int _x, int _y, int rotation, int _type, int _group)  {

		// TODO: bg.setTexture(BGel);
		x = _x; y = _y; init_AABB();
		layer = 1;
		box.setRotation(rotation);
		type = _type;
		group = _group;

	}
	Electric() { 
		// TODO: 
		//box.setTexture(void_el); 
		layer = 1; 
		bg.setOrigin(64, 64); 
		//bg.setTexture(BGel); 
		box.setTextureRect(IntRect(0, 0, 128, 128));
	}

	void set_connections(int* cons) {
		con[0] = cons[0];
		con[1] = cons[1];
		con[2] = cons[2];
		con[3] = cons[3];
	}

	void render() {

		update_scrolling();
		bg.setPosition(box.getPosition());
		bg.setScale(scale, scale);
		bg.setColor(Color(126 + charge * 2, 129 - charge * 2, 129 - charge * 2, 126 + charge * 2));
		window.draw(bg);
		window.draw(box);
	}
};

inline vector <Electric*> electric;

void rech(int a, int b);
void rech(Electric& a, Electric& b);
void rech(Electric& a, int c);
void rech_give_charge(int a);

struct Wire : public Electric {

	int type = 0;

	Wire(int _x, int _y, int rotation_, int _type) {

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

	void cycle() {

		if ((type == 32) && (rand() % 2 == 0)) { return; }

		for (int k = 0; k < con_size; k++) {
			rech(*this, con[k]);
		}

	}

	void save(ofstream& save) {
		save << "[ ";
		save << id << ' ';
		save << x << ' ';
		save << y << ' ';
		save << rotation << ' ';
		save << "]" << endl;
	}

};

struct Generator : public Electric {

	bool generator = true;

	Generator(int _x, int _y, int rotation_, int type, bool generator_) {
		electric = true;
		// TODO: bg.setTexture(BGel); 
		x = _x; y = _y; rotation = rotation_; id = type; init_AABB();
		box.setRotation(rotation);
		/*con[0] = con_;*/ box.setOrigin(64, 64);
		generator = generator_;

		box.setTexture(*MapFloorTextures[id]); 
		con_size = 1; 
	}

	void cycle() {

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

	void editor_exist() {

		update_scrolling();
		window.draw(box);

		text.setString(to_string(generator));
		text.setPosition(box.getPosition());

		window.draw(text);
	}

	void save(ofstream& save) {
		save << "[ ";
		save << id << ' ';
		save << x << ' ';
		save << y << ' ';
		save << rotation << ' ';
		save << int(generator) << ' ';
		save << "]" << endl;
	}

};

struct Switcher : public Electric {

	bool* target; int group;
	Text text = ::text;

	void setTextColor() {

		if (target == a) {
			text.setFillColor(Color::White); return;
		}
		if (target == b) {
			text.setFillColor(Color::Black); return;
		}
		if (target == c) {
			text.setFillColor(Color::Red); return;
		}
		if (target == barmode) {
			text.setFillColor(Color::Magenta); return;
		}
	}
	bool* getTarget() {

		if (target == a) {
			return dmode;
		}
		if (target == b) {
			return crystal;
		}
		if (target == c) {
			return lmode;
		}
		if (target == barmode) {
			return barmode;
		}

	}

	int getGroup() {
		return group;
	}
	Switcher(int x_, int y_, int rotation_, int type_, bool* target_, int group_) {
		x = x_; y = y_; rotation = rotation_;  init_AABB(); electric = true;
		target = target_;
		group = group_;
		//con[0] = cons[0];
		//con[1] = cons[1];
		//con[2] = cons[2];
		box.setRotation(rotation);
		box.setTexture(*MapFloorTextures[id]); 
		box.setOrigin(64, 64);
		type = type_;id = type;
		setTextColor();
		text.setString(to_string(group));
	}

	void cycle() {
		if (target[group]) {
			rech(con[1], con[2]);
			box.setTextureRect(IntRect(128, 0, 128, 128));
		}
		else {
			rech(con[0], con[1]);
			box.setTextureRect(IntRect(0, 0, 128, 128));
		}
	}

	void save(ofstream& save) {
		save << "[ ";
		save << id << ' ';
		save << x << ' ';
		save << y << ' ';
		save << rotation << ' ';

		if (target == a) {
			save << "dmode" << ' ';
		}
		if (target == b) {
			save << "crystal" << ' ';
		}
		if (target == c) {
			save << "lmode" << ' ';
		}
		if (target == barmode) {
			save << "barmode" << ' ';
		}
		save << group << ' ';

		save << "]" << endl;
	}

	void editing() {

		//edit();
		if (editor_mode != 4) { return; }

		E_rotate_block.box.setPosition(box.getPosition()); E_rotate_block.box.move(80 * scale, -80 * scale);
		E_rotate_block2.box.setPosition(box.getPosition()); E_rotate_block2.box.move(-80 * scale, -80 * scale);

		E_rotate_block.box.setScale(scale, scale);
		//E_rotate_block.bg_box.setScale(scale * 0.5, scale * 0.5);
		E_rotate_block2.box.setScale(scale, scale);
		//E_rotate_block2.bg_box.setScale(scale * 0.5, scale * 0.5);

		if (option_mode) {

			E_edit_block.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y - 40 * scale);
			E_edit_block.box.setScale(scale * 0.4, scale * 0.4);

			if (E_edit_block.if_click()) {
				option_mode = !option_mode;
			}

			E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 200 * scale);
			E_arrow[1].setPosition(box.getPosition().x + 200 * scale, box.getPosition().y);
			E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 200 * scale);
			E_arrow[3].setPosition(box.getPosition().x - 200 * scale, box.getPosition().y);

			E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);

			E_edit_color.box.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y + 40 * scale);
			E_edit_color.bg_box.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y + 40 * scale);
			E_edit_color.box.setScale(0.5 * scale, 0.5 * scale);
			E_edit_color.bg_box.setScale(0.45 * scale, 0.45 * scale);
			E_edit_color.bg_box.setColor(text.getFillColor());

			setTextColor();
			E_edit_color.bg_box.setColor(text.getFillColor());

			if (E_edit_color.if_click()) {

				if (target == a) {
					target = crystal; return;
				}
				if (target == b) {
					target = lmode; return;
				}
				if (target == c) {
					target = barmode; return;
				}
				if (target == barmode) {
					target = dmode; return;
				}
			}

			E_edit_number.box.setPosition(box.getPosition());
			E_edit_number.box.move(-40 * scale, 40 * scale);
			E_edit_number.box.setScale(scale * 0.5, scale * 0.5);
			E_edit_number.bg_box.setScale(scale * 0.5, scale * 0.5);

			if (E_edit_number.if_click()) {

				if (Mouse::isButtonPressed(Mouse::Left)) {
					group++; onclick = true;
					last_group = group;
				}
				if (Mouse::isButtonPressed(Mouse::Right)) {
					if (group > 0) {
						group--; onclick = true;
						last_group = group;
					}
				}

			}

			text.setPosition(E_edit_number.box.getPosition());
			text.setString(to_string(group));
			text.move(-25 * UI_scale, -30 * UI_scale);

			window.draw(text);

		}
		else {

			E_edit_block.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y - 40 * scale);
			E_edit_block.box.setScale(scale * 0.4, scale * 0.4);

			if (E_edit_block.if_click()) {
				option_mode = !option_mode;
			}

			if (!onclick && Mouse::isButtonPressed(Mouse::Left) && cursor.getGlobalBounds().intersects(box.getGlobalBounds())) {
				group++; onclick = true; last_group = group;
			}
			if (!onclick && Mouse::isButtonPressed(Mouse::Right) && cursor.getGlobalBounds().intersects(box.getGlobalBounds())) {
				group = 0; onclick = true; last_group = group;
			}

			E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 128 * scale);
			E_arrow[1].setPosition(box.getPosition().x + 128 * scale, box.getPosition().y);
			E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 128 * scale);
			E_arrow[3].setPosition(box.getPosition().x - 128 * scale, box.getPosition().y);

			E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);
		}
	}

	void editor_exist() {

		update_scrolling();
		window.draw(box);

		text.setString(to_string(group));

		text.setPosition((x - scrollx + 20) * scale, (y - scrolly + 5) * scale);
		text.setCharacterSize(40 * scale);
		window.draw(text);
	}

};

struct Switcher2 : public Electric {

	bool* target; bool reversed; int group;
	Text text = ::text;
	bool* getTarget() {

		if (target == a) {
			return dmode;
		}
		if (target == b) {
			return crystal;
		}
		if (target == c) {
			return lmode;
		}
		if (target == barmode) {
			return barmode;
		}

	}

	int getGroup() {
		return group;
	}
	void setTextColor() {

		if (target == a) {
			text.setFillColor(Color::White); return;
		}
		if (target == b) {
			text.setFillColor(Color::Black); return;
		}
		if (target == c) {
			text.setFillColor(Color::Red); return;
		}
		if (target == barmode) {
			text.setFillColor(Color::Magenta); return;
		}
	}

	Switcher2(int x_, int y_, int rotation_, int type_, bool* target_, int group_, bool reversed_) {
		x = x_; y = y_; rotation = rotation_;  init_AABB(); electric = true;
		target = target_;
		group = group_;
		reversed = reversed_;
		//con[0] = cons[0];
		//con[1] = cons[1];
		box.setRotation(rotation);
		box.setTexture(*MapFloorTextures[id]); 
		box.setOrigin(64, 64);
		type = type_; id = type;
		setTextColor();
		text.setString(to_string(group));
	}

	void cycle() {
		if (target[group] == reversed) {
			rech(con[0], con[1]);
			// TODO: box.setTexture(c_switch);
		}
		else {
			// TODO: box.setTexture(c_switch_off);
		}
	}

	void save(ofstream& save) {
		save << "[ ";
		save << id << ' ';
		save << x << ' ';
		save << y << ' ';
		save << rotation << ' ';

		if (target == a) {
			save << "dmode" << ' ';
		}
		if (target == b) {
			save << "crystal" << ' ';
		}
		if (target == c) {
			save << "lmode" << ' ';
		}
		if (target == barmode) {
			save << "barmode" << ' ';
		}
		save << group << ' ';

		save << int(reversed) << ' ';

		save << "]" << endl;
	}

	void editing() {

		//edit();
		if (editor_mode != 4) { return; }

		E_rotate_block.box.setPosition(box.getPosition()); E_rotate_block.box.move(80 * scale, -80 * scale);
		E_rotate_block2.box.setPosition(box.getPosition()); E_rotate_block2.box.move(-80 * scale, -80 * scale);

		E_rotate_block.box.setScale(scale, scale);
		//E_rotate_block.bg_box.setScale(scale * 0.5, scale * 0.5);
		E_rotate_block2.box.setScale(scale, scale);
		//E_rotate_block2.bg_box.setScale(scale * 0.5, scale * 0.5);

		if (option_mode) {

			E_edit_block.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y - 40 * scale);
			E_edit_block.box.setScale(scale * 0.4, scale * 0.4);

			if (E_edit_block.if_click()) {
				option_mode = !option_mode;
			}

			E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 200 * scale);
			E_arrow[1].setPosition(box.getPosition().x + 200 * scale, box.getPosition().y);
			E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 200 * scale);
			E_arrow[3].setPosition(box.getPosition().x - 200 * scale, box.getPosition().y);

			E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);

			E_edit_color.box.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y + 40 * scale);
			E_edit_color.bg_box.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y + 40 * scale);
			E_edit_color.box.setScale(0.5 * scale, 0.5 * scale);
			E_edit_color.bg_box.setScale(0.45 * scale, 0.45 * scale);
			E_edit_color.bg_box.setColor(text.getFillColor());

			setTextColor();
			E_edit_color.bg_box.setColor(text.getFillColor());

			if (E_edit_color.if_click()) {

				if (target == a) {
					target = crystal; return;
				}
				if (target == b) {
					target = lmode; return;
				}
				if (target == c) {
					target = barmode; return;
				}
				if (target == barmode) {
					target = dmode; return;
				}
			}

			E_edit_number.box.setPosition(box.getPosition());
			E_edit_number.box.move(-40 * scale, 40 * scale);
			E_edit_number.box.setScale(scale * 0.5, scale * 0.5);
			E_edit_number.bg_box.setScale(scale * 0.5, scale * 0.5);

			if (E_edit_number.if_click()) {

				if (Mouse::isButtonPressed(Mouse::Left)) {
					group++; onclick = true;
					last_group = group;
				}
				if (Mouse::isButtonPressed(Mouse::Right)) {
					if (group > 0) {
						group--; onclick = true;
						last_group = group;
					}
				}

			}

			text.setPosition(E_edit_number.box.getPosition());
			text.setString(to_string(group));
			text.move(-25 * UI_scale, -30 * UI_scale);

			window.draw(text);

		}
		else {

			if (E_edit_block.if_click()) {
				option_mode = !option_mode;
			}

			if (!onclick && Mouse::isButtonPressed(Mouse::Left) && cursor.getGlobalBounds().intersects(box.getGlobalBounds())) {
				group++; onclick = true; last_group = group;
			}
			if (!onclick && Mouse::isButtonPressed(Mouse::Right) && cursor.getGlobalBounds().intersects(box.getGlobalBounds())) {
				group = 0; onclick = true; last_group = group;
			}

			E_edit_block.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y - 40 * scale);
			E_edit_block.box.setScale(scale * 0.4, scale * 0.4);

			E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 128 * scale);
			E_arrow[1].setPosition(box.getPosition().x + 128 * scale, box.getPosition().y);
			E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 128 * scale);
			E_arrow[3].setPosition(box.getPosition().x - 128 * scale, box.getPosition().y);

			E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);
		}
	}

	void editor_exist() {

		update_scrolling();
		window.draw(box);

		text.setPosition((x - scrollx + 20) * scale, (y - scrolly + 5) * scale);
		text.setCharacterSize(40 * scale);
		text.setString(to_string(group));

		window.draw(text);
	}

};

struct Ac : public Electric {

	bool* target; int group; 
	Text text = ::text;
	bool* getTarget() {

		if (target == a) {
			return dmode;
		}
		if (target == b) {
			return crystal;
		}
		if (target == c) {
			return lmode;
		}
		if (target == barmode) {
			return barmode;
		}

	}

	int getGroup() {
		return group;
	}
	void setTextColor() {

		if (target == a) {
			text.setFillColor(Color::White); return;
		}
		if (target == b) {
			text.setFillColor(Color::Black); return;
		}
		if (target == c) {
			text.setFillColor(Color::Red); return;
		}
		if (target == barmode) {
			text.setFillColor(Color::Magenta); return;
		}
	}

	Ac(int x_, int y_, int rotation_, int type_, bool* target_, int group_) {
		x = x_; y = y_; rotation = rotation_; init_AABB(); electric = true;
		target = target_;
		group = group_;
		//con[0] = cons[0];
		//con[1] = cons[1];
		box.setRotation(rotation);
		box.setTexture(*MapFloorTextures[id]);
		box.setOrigin(64, 64);
		type = type_; id = type;
		setTextColor();
		text.setString(to_string(group));
	}

	void cycle() {

		if (target[group]) {

			rech_give_charge(con[0]);
			rech_give_charge(con[1]);

		}

	}

	void save(ofstream& save) {
		save << "[ ";
		save << id << ' ';
		save << x << ' ';
		save << y << ' ';
		save << rotation << ' ';

		if (target == a) {
			save << "dmode" << ' ';
		}
		if (target == b) {
			save << "crystal" << ' ';
		}
		if (target == c) {
			save << "lmode" << ' ';
		}
		if (target == barmode) {
			save << "barmode" << ' ';
		}
		save << group << ' ';

		save << "]" << endl;
	}

	void editing() {

		//edit();
		if (editor_mode != 4) { return; }

		E_rotate_block.box.setPosition(box.getPosition()); E_rotate_block.box.move(80 * scale, -80 * scale);
		E_rotate_block2.box.setPosition(box.getPosition()); E_rotate_block2.box.move(-80 * scale, -80 * scale);

		E_rotate_block.box.setScale(scale, scale);
		//E_rotate_block.bg_box.setScale(scale * 0.5, scale * 0.5);
		E_rotate_block2.box.setScale(scale, scale);
		//E_rotate_block2.bg_box.setScale(scale * 0.5, scale * 0.5);

		if (option_mode) {

			E_edit_block.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y - 40 * scale);
			E_edit_block.box.setScale(scale * 0.4, scale * 0.4);

			if (E_edit_block.if_click()) {
				option_mode = !option_mode;
			}

			E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 200 * scale);
			E_arrow[1].setPosition(box.getPosition().x + 200 * scale, box.getPosition().y);
			E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 200 * scale);
			E_arrow[3].setPosition(box.getPosition().x - 200 * scale, box.getPosition().y);

			E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);

			E_edit_color.box.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y + 40 * scale);
			E_edit_color.bg_box.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y + 40 * scale);
			E_edit_color.box.setScale(0.5 * scale, 0.5 * scale);
			E_edit_color.bg_box.setScale(0.45 * scale, 0.45 * scale);
			E_edit_color.bg_box.setColor(text.getFillColor());

			setTextColor();
			E_edit_color.bg_box.setColor(text.getFillColor());

			if (E_edit_color.if_click()) {

				if (target == a) {
					target = crystal; return;
				}
				if (target == b) {
					target = lmode; return;
				}
				if (target == c) {
					target = barmode; return;
				}
				if (target == barmode) {
					target = dmode; return;
				}
			}

			E_edit_number.box.setPosition(box.getPosition());
			E_edit_number.box.move(-40 * scale, 40 * scale);
			E_edit_number.box.setScale(scale * 0.5, scale * 0.5);
			E_edit_number.bg_box.setScale(scale * 0.5, scale * 0.5);

			if (E_edit_number.if_click()) {

				if (Mouse::isButtonPressed(Mouse::Left)) {
					group++; onclick = true;
					last_group = group;
				}
				if (Mouse::isButtonPressed(Mouse::Right)) {
					if (group > 0) {
						group--; onclick = true;
						last_group = group;
					}
				}

			}

			text.setPosition(E_edit_number.box.getPosition());
			text.setString(to_string(group));
			text.move(-25 * UI_scale, -30 * UI_scale);

			window.draw(text);

		}
		else {

			E_edit_block.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y - 40 * scale);
			E_edit_block.box.setScale(scale * 0.4, scale * 0.4);

			if (E_edit_block.if_click()) {
				option_mode = !option_mode;
			}

			if (!onclick && Mouse::isButtonPressed(Mouse::Left) && cursor.getGlobalBounds().intersects(box.getGlobalBounds())) {
				group++; onclick = true; last_group = group;
			}
			if (!onclick && Mouse::isButtonPressed(Mouse::Right) && cursor.getGlobalBounds().intersects(box.getGlobalBounds())) {
				group = 0; onclick = true; last_group = group;
			}

			E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 128 * scale);
			E_arrow[1].setPosition(box.getPosition().x + 128 * scale, box.getPosition().y);
			E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 128 * scale);
			E_arrow[3].setPosition(box.getPosition().x - 128 * scale, box.getPosition().y);

			E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);
		}
	}

	void editor_exist() {

		update_scrolling();
		window.draw(box);

		text.setPosition((x - scrollx + 20) * scale, (y - scrolly + 5) * scale);
		text.setCharacterSize(40 * scale);
		text.setString(to_string(group));

		window.draw(text);
	}

};

struct El_Detector : public Electric {

	bool* target; int group;
	Text text = ::text;

	void setTextColor() {

		if (target == a) {
			text.setFillColor(Color::White); return;
		}
		if (target == b) {
			text.setFillColor(Color::Black); return;
		}
		if (target == c) {
			text.setFillColor(Color::Red); return;
		}
		if (target == barmode) {
			text.setFillColor(Color::Magenta); return;
		}
	}
	bool* getTarget() {

		if (target == a) {
			return dmode;
		}
		if (target == b) {
			return crystal;
		}
		if (target == c) {
			return lmode;
		}
		if (target == barmode) {
			return barmode;
		}

	}

	int getGroup() {
		return group;
	}
	El_Detector(int x_, int y_, int rotation_, int type_, bool* target_, int group_) {
		x = x_; y = y_; rotation = rotation_;  init_AABB();
		target = target_;
		group = group_; electric = true;
		/*con[0] = con_;*/
		box.setTexture(*MapFloorTextures[id]);
		box.setRotation(rotation);
		box.setOrigin(64, 64);
		type = type_; id = type;
		text.setString(to_string(group));
		setTextColor();
	}

	void cycle() {

		rech(*this, con[0]);

		if (charge > 25) {
			// TODO: box.setTexture(c_sensor_on);
			target[group] = true;
		}
		else {
			// TODO: box.setTexture(c_sensor);
			target[group] = false;
		}

	}

	void save(ofstream& save) {
		save << "[ ";
		save << id << ' ';
		save << x << ' ';
		save << y << ' ';
		save << rotation << ' ';

		if (target == a) {
			save << "dmode" << ' ';
		}
		if (target == b) {
			save << "crystal" << ' ';
		}
		if (target == c) {
			save << "lmode" << ' ';
		}
		if (target == barmode) {
			save << "barmode" << ' ';
		}
		save << group << ' ';

		save << "]" << endl;
	}

	void editing() {

		//edit();
		if (editor_mode != 4) { return; }

		E_rotate_block.box.setPosition(box.getPosition()); E_rotate_block.box.move(80 * scale, -80 * scale);
		E_rotate_block2.box.setPosition(box.getPosition()); E_rotate_block2.box.move(-80 * scale, -80 * scale);

		E_rotate_block.box.setScale(scale, scale);
		//E_rotate_block.bg_box.setScale(scale * 0.5, scale * 0.5);
		E_rotate_block2.box.setScale(scale, scale);
		//E_rotate_block2.bg_box.setScale(scale * 0.5, scale * 0.5);

		if (option_mode) {

			E_edit_block.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y - 40 * scale);
			E_edit_block.box.setScale(scale * 0.4, scale * 0.4);

			if (E_edit_block.if_click()) {
				option_mode = !option_mode;
			}

			E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 200 * scale);
			E_arrow[1].setPosition(box.getPosition().x + 200 * scale, box.getPosition().y);
			E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 200 * scale);
			E_arrow[3].setPosition(box.getPosition().x - 200 * scale, box.getPosition().y);

			E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);

			E_edit_color.box.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y + 40 * scale);
			E_edit_color.bg_box.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y + 40 * scale);
			E_edit_color.box.setScale(0.5 * scale, 0.5 * scale);
			E_edit_color.bg_box.setScale(0.45 * scale, 0.45 * scale);
			E_edit_color.bg_box.setColor(text.getFillColor());

			setTextColor();
			E_edit_color.bg_box.setColor(text.getFillColor());

			if (E_edit_color.if_click()) {

				if (target == a) {
					target = crystal; return;
				}
				if (target == b) {
					target = lmode; return;
				}
				if (target == c) {
					target = barmode; return;
				}
				if (target == barmode) {
					target = dmode; return;
				}
			}

			E_edit_number.box.setPosition(box.getPosition());
			E_edit_number.box.move(-40 * scale, 40 * scale);
			E_edit_number.box.setScale(scale * 0.5, scale * 0.5);
			E_edit_number.bg_box.setScale(scale * 0.5, scale * 0.5);

			if (E_edit_number.if_click()) {

				if (Mouse::isButtonPressed(Mouse::Left)) {
					group++; onclick = true;
					last_group = group;
				}
				if (Mouse::isButtonPressed(Mouse::Right)) {
					if (group > 0) {
						group--; onclick = true;
						last_group = group;
					}
				}

			}

			text.setPosition(E_edit_number.box.getPosition());
			text.setString(to_string(group));
			text.move(-25 * UI_scale, -30 * UI_scale);

			window.draw(text);

		}
		else {

			if (!onclick && Mouse::isButtonPressed(Mouse::Left) && cursor.getGlobalBounds().intersects(box.getGlobalBounds())) {
				group++; onclick = true; last_group = group;
			}
			if (!onclick && Mouse::isButtonPressed(Mouse::Right) && cursor.getGlobalBounds().intersects(box.getGlobalBounds())) {
				group = 0; onclick = true; last_group = group;
			}

			E_edit_block.setPosition(box.getPosition().x + 40 * scale, box.getPosition().y - 40 * scale);
			E_edit_block.box.setScale(scale * 0.4, scale * 0.4);

			if (E_edit_block.if_click()) {
				option_mode = !option_mode;
			}

			E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 128 * scale);
			E_arrow[1].setPosition(box.getPosition().x + 128 * scale, box.getPosition().y);
			E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 128 * scale);
			E_arrow[3].setPosition(box.getPosition().x - 128 * scale, box.getPosition().y);

			E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
			E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);
		}
	}

	void editor_exist() {

		update_scrolling();
		window.draw(box);

		text.setPosition((x - scrollx + 20) * scale, (y - scrolly + 5) * scale);
		text.setCharacterSize(40 * scale);
		text.setString(to_string(group));

		window.draw(text);
	}

};

struct El_button : public Electric {

	bool reversed;

	El_button(int _x, int _y, int _rotation, bool _reversed) {
		x = _x; y = _y; size = 40; type = 46; id = 46; init_AABB(); rotation = _rotation; reversed = _reversed;
		box.setRotation(_rotation);
		box.setTexture(*MapFloorTextures[id]);
		box.setOrigin(64, 64); magnet = 0.3; electric = true;
	}

	void cycle() {

		for (int k = 0; k < movables.size(); k++) {
			if (intersection(*this,*movables[k])) {

				if (reversed) {
					if (charge < 63) {
						charge += 1;
						if (charge < 20) {
							charge += 10;
						}
					}
					return;
				}

				if (charge > 0) {
					charge -= 1;
					if (charge > 10) {
						charge -= 6;
					}
				}

				return;
			}
		}

		if (reversed) {
			if (intersection(*this, p)) {
				box.setTextureRect(IntRect(128,0,128,128));
				if (charge < 63) {
					charge += 1;
					if (charge < 20) {
						charge += 10;
					}
				} return;
			}
			else {

				box.setTextureRect(IntRect(0, 0, 128, 128));
				if (charge > 0) {
					charge -= 1;
					if (charge > 10) {
						charge -= 6;
					}
				}
			}
		}
		else {
			if (intersection(*this, p)) {
				box.setTextureRect(IntRect(128, 0, 128, 128));
				if (charge > 0) {
					charge -= 1;
					if (charge > 10) {
						charge -= 6;
					}
				} return;
			} 
			else {
				box.setTextureRect(IntRect(0, 0, 128, 128));
				if (charge < 63) {
					charge += 1;
					if (charge < 20) {
						charge += 10;
					}
				}
			}
		}

	}

	void save(ofstream& save) {
		save << "[ ";
		save << id << ' ';
		save << x << ' ';
		save << y << ' ';
		save << rotation << ' ';

		save << int(reversed) << ' ';

		save << "]" << endl;
	}

};

//Triggers

struct Trigger : public Block {

	bool once_flag = false, stop = false;

	Sprite zone_marker;

	virtual void trigger() {}

	void render() {
		update_scrolling();
		if (intersection(p, *this) && !stop) {
			stop = once_flag;
			trigger();
		}
	}

	void editor_exist() {

		update_scrolling();

		zone_marker.setPosition(box.getPosition());

		// TODO: zone_marker.setTexture(block_choose);

		zone_marker.setOrigin(64, 64);
		zone_marker.setScale(scale * size / 64, scale * size / 64);
		zone_marker.setColor(Color(255, 255, 255, 155 + 55 * sin(float(tick) / 40)));

		window.draw(zone_marker);

		window.draw(box);

	}

	void edit() {

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

	void save(ofstream& save) {
		save << "[ ";
		save << id << ' ';
		save << x << ' ';
		save << y << ' ';
		save << int(size) << ' ';
		save << "]" << endl;
	}

};

struct Camera_trigger : public Trigger {

	void trigger() {

		scroll_pinned = true;

		if (box.getPosition().x > screenw * 0.55) {
			scrollx += 1;
		}
		if (box.getPosition().x < screenw * 0.45) {
			scrollx -= 1;
		}
		if (box.getPosition().y > screenh * 0.55) {
			scrolly += 1;
		}
		if (box.getPosition().y < screenh * 0.45) {
			scrolly -= 1;
		}

		if (abs(box.getPosition().x - screenw * 0.5) > 20 || abs(box.getPosition().y - screenh * 0.5) > 20) {

			for (int auf = 0; auf < 3; auf++) {

				if (box.getPosition().x > screenw * 0.55) {
					scrollx += 14;
				}
				if (box.getPosition().x < screenw * 0.45) {
					scrollx -= 14;
				}
				if (box.getPosition().y > screenh * 0.55) {
					scrolly += 14;
				}
				if (box.getPosition().y < screenh * 0.45) {
					scrolly -= 14;
				}

				update_scrolling();

			}

		}
	}

	Camera_trigger(int id_, int x_, int y_, int size_) {
		id = id_; x = x_; y = y_; size = size_;
		magnet = 0;
		box.setOrigin(64, 64);
		init_AABB();
		box.setPosition((x - scrollx) * scale, (y - scrolly) * scale);
		box.setTexture(*MapFloorTextures[id]);
	}

};

struct Blind_trigger : public Trigger {

	int fade_time = 0;

	void render() {
		update_scrolling();
		if (intersection(p, *this) && !stop) {
			//stop = once_flag;
			//trigger();

			if (fade_time < 255) {
				fade_time++;
			}
			blend.setColor(Color(0, 0, 0, fade_time));
			window.draw(blend);

		}
		else {
			if (fade_time > 0) {
				fade_time--;
				blend.setColor(Color(0, 0, 0, fade_time));
				window.draw(blend);
			}
		}
	}

	Blind_trigger(int id_, int x_, int y_, int size_) {
		box.setTexture(*MapFloorTextures[id]);
		id = id_; x = x_; y = y_; size = size_;
		magnet = 0;
		box.setOrigin(64, 64);
		init_AABB();
		box.setPosition((x - scrollx) * scale, (y - scrolly) * scale);
	}
};

struct Portal_trigger : public Trigger {

	int delta_x = 200, delta_y = -500;
	Sprite zone_marker2, box2;


	void trigger() {
		scrollx += delta_x;
		scrolly += delta_y;

		p.move(delta_x, delta_y);

		last_coordinates[0][0] = scale * (p.x - scrollx);
		last_coordinates[1][0] = scale * (p.x - scrollx);
		last_coordinates[2][0] = scale * (p.x - scrollx);
		last_coordinates[3][0] = scale * (p.x - scrollx);
		last_coordinates[4][0] = scale * (p.x - scrollx);
		last_coordinates[5][0] = scale * (p.x - scrollx);

		last_coordinates[0][1] = scale * (p.y - scrolly);
		last_coordinates[1][1] = scale * (p.y - scrolly);
		last_coordinates[2][1] = scale * (p.y - scrolly);
		last_coordinates[3][1] = scale * (p.y - scrolly); 
		last_coordinates[4][1] = scale * (p.y - scrolly);
		last_coordinates[5][1] = scale * (p.y - scrolly);

		logg << "Teleport! Deltas: " << delta_x << " " << delta_y << endl;
	}

	Portal_trigger(int id_, int x_, int y_, int size_, int dx, int dy) {

		id = id_; x = x_; y = y_; size = size_;

		delta_x = dx; delta_y = dy;

		box.setTexture(*MapFloorTextures[id]);
		// TODO: box2.setTexture(t_portal2);

		box.setOrigin(64, 64);
		box2.setOrigin(64, 64);
		init_AABB();

		E_plus.is_checked = false;
		E_Rt.is_checked = false;
		E_M.is_checked = true;
		E_player.is_checked = false;
		E_multichoose.is_checked = false;
	}

	void edit() {

		if (editor_mode != 4) { return; }

		E_arrow[0].setPosition(box2.getPosition().x, box2.getPosition().y - 128 * scale);
		E_arrow[1].setPosition(box2.getPosition().x + 128 * scale, box2.getPosition().y);
		E_arrow[2].setPosition(box2.getPosition().x, box2.getPosition().y + 128 * scale);
		E_arrow[3].setPosition(box2.getPosition().x - 128 * scale, box2.getPosition().y);

		E_arrow[0].box.setScale(scale * 0.8, scale * 0.8);
		E_arrow[1].box.setScale(scale * 0.8, scale * 0.8);
		E_arrow[2].box.setScale(scale * 0.8, scale * 0.8);
		E_arrow[3].box.setScale(scale * 0.8, scale * 0.8);

		if (E_arrow[0].if_click()) {
			delta_y -= 128;
		}
		if (E_arrow[1].if_click()) {
			delta_x += 128;
		}
		if (E_arrow[2].if_click()) {
			delta_y += 128;
		}
		if (E_arrow[3].if_click()) {
			delta_x -= 128;
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			if (!on_keyboard_click) {
				if (Keyboard::isKeyPressed(Keyboard::LShift)) { move(0, 16); delta_y -= 16; }
				else { move(0, 128); delta_y -= 128; }
				on_keyboard_click = !Keyboard::isKeyPressed(Keyboard::LControl);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			if (!on_keyboard_click) {
				if (Keyboard::isKeyPressed(Keyboard::LShift)) { move(-16, 0);  delta_x += 16; }
				else { move(-128, 0); delta_x += 128; }
				on_keyboard_click = !Keyboard::isKeyPressed(Keyboard::LControl);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			if (!on_keyboard_click) {
				if (Keyboard::isKeyPressed(Keyboard::LShift)) { move(0, -16); delta_y += 16; }
				else { move(0, -128); delta_y += 128;}
				on_keyboard_click = !Keyboard::isKeyPressed(Keyboard::LControl);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			if (!on_keyboard_click) {
				if (Keyboard::isKeyPressed(Keyboard::LShift)) { move(16, 0); delta_x -= 16;}
				else { move(128, 0); delta_x -= 128;}
				on_keyboard_click = !Keyboard::isKeyPressed(Keyboard::LControl);
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::W)) {
			if (!on_keyboard_click) {
				if (Keyboard::isKeyPressed(Keyboard::LShift)) { move(0, 16); delta_y -= 16; }
				else { delta_y -= 128; }
				on_keyboard_click = !Keyboard::isKeyPressed(Keyboard::LControl);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			if (!on_keyboard_click) {
				if (Keyboard::isKeyPressed(Keyboard::LShift)) { move(-16, 0);  delta_x += 16; }
				else { delta_x += 128; }
				on_keyboard_click = !Keyboard::isKeyPressed(Keyboard::LControl);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			if (!on_keyboard_click) {
				if (Keyboard::isKeyPressed(Keyboard::LShift)) { move(0, -16); delta_y += 16; }
				else { delta_y += 128; }
				on_keyboard_click = !Keyboard::isKeyPressed(Keyboard::LControl);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			if (!on_keyboard_click) {
				if (Keyboard::isKeyPressed(Keyboard::LShift)) { move(16, 0); delta_x -= 16; }
				else { delta_x -= 128; }
				on_keyboard_click = !Keyboard::isKeyPressed(Keyboard::LControl);
			}
		}

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

		E_arrow[0].setPosition(box.getPosition().x, box.getPosition().y - 128 * scale);
		E_arrow[1].setPosition(box.getPosition().x + 128 * scale, box.getPosition().y);
		E_arrow[2].setPosition(box.getPosition().x, box.getPosition().y + 128 * scale);
		E_arrow[3].setPosition(box.getPosition().x - 128 * scale, box.getPosition().y);

		on_portal_trigger_edit = true;
	}

	void editor_exist() {

		update_scrolling();

		zone_marker.setPosition(box.getPosition());

		// TODO: zone_marker.setTexture(block_choose);

		zone_marker.setOrigin(64, 64);
		zone_marker.setScale(scale * size / 64, scale * size / 64);
		zone_marker.setColor(Color(255, 255, 255, 155 + 55 * sin(float(tick) / 40)));

		window.draw(zone_marker);

		box2.setPosition(box.getPosition());
		box2.move(scale * delta_x, scale * delta_y);
		box2.setScale(scale, scale);

		zone_marker2.setPosition(box2.getPosition());

		// TODO: zone_marker2.setTexture(block_choose);

		zone_marker2.setOrigin(64, 64);
		zone_marker2.setScale(scale * size / 64, scale * size / 64);
		zone_marker2.setColor(Color(255, 255, 255, 155 + 55 * sin(float(tick) / 40)));

		window.draw(zone_marker2);

		window.draw(box);
		window.draw(box2);

		Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(box.getPosition())),
			sf::Vertex(sf::Vector2f(box2.getPosition()))
		};

		window.draw(line, 2, sf::Lines);

	}

	void save(ofstream& save) {
		save << "[ ";
		save << id << ' ';
		save << x << ' ';
		save << y << ' ';
		save << int(size) << ' ';
		save << delta_x << ' ';
		save << delta_y << ' ';
		save << "]" << endl;
	}
};

struct Player_size_trigger : public Trigger {

	float player_scale_multiplier = 1.24;

	void trigger() {

		smoke_spawn("smoke", p.x, p.y);
		sound_b.play();

		player_scale *= player_scale_multiplier;
		p.size *= player_scale_multiplier;
		// TODO: изменение силы по размеру
		//p.repulsion /= player_scale_multiplier;
		//p.repulsion /= player_scale_multiplier;
		//p.repulsion /= player_scale_multiplier;
		p.init_AABB();
	}

	void edit() {

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

		if (!onclick && box.getGlobalBounds().intersects(cursor.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
			onclick = true;
			player_scale_multiplier *= 1.15;
		}
		if (!onclick && box.getGlobalBounds().intersects(cursor.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Right)) {
			onclick = true;
			player_scale_multiplier *= 0.95;
		}

		text.setPosition(box.getPosition());
		text.setString(to_string(player_scale_multiplier));

		window.draw(text);
	}

	Player_size_trigger(int id_, int x_, int y_, int size_, float _player_scale_multiplier) {

		id = id_; x = x_; y = y_; size = size_;
		once_flag = true;
		player_scale_multiplier = _player_scale_multiplier;

		magnet = 0;
		box.setOrigin(64, 64);
		init_AABB();
		box.setPosition((x - scrollx) * scale, (y - scrolly) * scale);
		box.setTexture(*MapFloorTextures[id]);
	}

	void save(ofstream& save) {
		save << "[ ";
		save << id << ' ';
		save << x << ' ';
		save << y << ' ';
		save << int(size) << ' ';
		save << player_scale_multiplier << ' ';
		save << "]" << endl;
	}

};

struct Text_Block : public Block {

	Text txt;
	string text;

	Text_Block(int id_, int x_, int y_, string str) {

		text = str;

		for (int i = 0; i < text.size(); i++) {
			if (text[i] == '_') {
				text[i] = ' ';
			}
		}

		txt.setString(text);
		x = x_;
		y = y_;
		id = id_;

		txt.setFont(font);
		txt.setFillColor(Color::Black);
		txt.setCharacterSize(30);
		txt.setOrigin(50, 50);

		box.setTexture(*MapFloorTextures[id]);
		box.setOrigin(64, 64);
		box.setTextureRect(IntRect(0, 0, 128, 128));
	}

	void render() {
		txt.setPosition((x - scrollx) * scale, (y - scrolly) * scale);
		txt.setScale(scale, scale);
		window.draw(txt);
	}

	void editor_exist() {

		update_scrolling();
		window.draw(box);

		txt.setString(text);
		txt.setPosition((x - scrollx) * scale, (y - scrolly) * scale);
		txt.setScale(scale, scale);
		window.draw(txt);
	}

	void edit() {

		while (!Keyboard::isKeyPressed(Keyboard::Enter) && window.isOpen()) {

			for (int i = 0; i < map_floor.size(); i++) {
				map_floor[i]->render();
			}

			for (int i = 0; i < ::electric.size(); i++) {
				::electric[i]->render();
			}

			for (int i = 0; i < movables.size(); i++) {
				window.draw(movables[i]->box);
			}

			for (int i = 0; i < map_basic.size(); i++) {
				map_basic[i]->render();
			}

			for (int i = 0; i < triggers.size(); i++) {
				if (triggers[i]->id == 104) { triggers[i]->render(); }
			}

			::text.setPosition(100, 100);
			::text.setFillColor(Color(255, 255, 255));
			::text.setCharacterSize(80 * UI_scale);
			::text.setString("Press enter to stop editing");
			window.draw(::text);

			::text.setPosition(100, screenh - 100);
			::text.setString("Arrows to move text");
			window.draw(::text);

			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				y -= 1; render();
			}
			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				y += 1; render();
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				x += 1; render();
			}
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				x -= 1; render();
			}

			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::TextEntered) {
					if (event.text.unicode < 128) {

						if (Keyboard::isKeyPressed(Keyboard::Enter)) { break; }

						if (Keyboard::isKeyPressed(Keyboard::Space)) {
							text += " "; continue;
						}
						if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
							text = text.substr(0, text.size() - 1);
						}
						else {
							text += static_cast<char>(event.text.unicode);
						}
						
					}
				}
			}

			txt.setString(text);

			if (tick % 70 > 34) {
				txt.setString(text + '|');
				window.draw(txt);
			}

			window.draw(box);
			window.draw(txt);

			window.display();
		
			sleep(milliseconds(10));
			
			window.clear();

		}

		chosen = map_basic[0];

		editor_mode = 1;
		E_plus.is_checked = true;
		E_Rt.is_checked = false;
		E_M.is_checked = false;
		E_player.is_checked = false;
		E_multichoose.is_checked = false;
		E_fill.is_checked = false;

	}

	void editing() {
		E_arrow[0].setPosition(-800, -800);
		E_arrow[1].setPosition(-800, -800);
		E_arrow[2].setPosition(-800, -800);
		E_arrow[3].setPosition(-800, -800);
	}

	void save(ofstream& save) {

		for (int i = 0; i < text.size(); i++) {
			if (text[i] == ' ') {
				text[i] = '_';
			}
		}

		save << "[ ";
		save << id << ' '; //40
		save << x << ' ';
		save << y << ' ';
		save << text << ' ';
		save << "]" << endl;
	}

};
