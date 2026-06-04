#include <Blocks.hpp>

Special_floor::Special_floor(int _x, int _y, int _id, int rotation_, int _look) {

	basic_init(_x, _y, rotation_, _id);
	look = _look;
	layer = 1;
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

void Special_floor::cycle() {
	switch (id) {
	case 6:
		break;
	case 18:
		//Fake block
		break;

	case 19:

		for (int j = 0; j < movables.size(); j++) {
			if (intersection(*movables[j], *this)) {
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

						smoke_spawn("tp", x, y); smoke_spawn("tp", map_floor[k]->x, map_floor[k]->y);
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

void Special_floor::render() {

	update_scrolling();
	float helper_s2 = 0;
	float helper_s[2];

	switch (id) {

	case 6:

		if (coins_gathered >= coins_required) {
			// TODO: box.setTexture(finon);
			if (intersection(p, *this)) {
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

void Special_floor::save(ofstream& save) {
	save << "[ ";
	save << id << ' ';
	save << x << ' ';
	save << y << ' ';
	save << rotation << ' ';
	save << look << ' ';
	save << "]" << endl;
}

void Special_floor::edit() {

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

void Special_floor::editor_exist() {

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