#include <Blocks.hpp>

void Questions::update() {
	if (id != 29) {
		id = 4;
		box.setTexture(*MapBasicTextures[id]);
	}
	init_AABB();
}


Questions::Questions(int _x, int _y, int _id, int rotation_, int _look) {

	basic_init(_x, _y, rotation_, _id);

	look = _look;
	layer = 0;

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

void Questions::cycle() {

	// TODO: что за хрень, которая ещё и дублируется?!
	if (look == -1 && id == 29) {

		float dx = (x - px);
		float dy = (y - py);

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
			case 18: open.play(); spawn_movable(x, y, look); smoke_spawn("mech", x, y, look); x = -99999; y = -99999; break;
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

void Questions::editor_exist() {

	render();

	txt.setCharacterSize(UI_scale * scale * 40);
	txt.setPosition((x - scrollx - UI_scale * 50) * scale, (y - scrolly - UI_scale * 30) * scale);

	window.draw(txt);
}