#include <Blocks.hpp>

Text_Block::Text_Block(int id_, int x_, int y_, string str) {

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

void Text_Block::render() {
	txt.setPosition((x - scrollx) * scale, (y - scrolly) * scale);
	txt.setScale(scale, scale);
	window.draw(txt);
}

void Text_Block::editor_exist() {

	update_scrolling();
	window.draw(box);

	txt.setString(text);
	txt.setPosition((x - scrollx) * scale, (y - scrolly) * scale);
	txt.setScale(scale, scale);
	window.draw(txt);
}

void Text_Block::edit() {

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

void Text_Block::editing() {
	E_arrow[0].setPosition(-800, -800);
	E_arrow[1].setPosition(-800, -800);
	E_arrow[2].setPosition(-800, -800);
	E_arrow[3].setPosition(-800, -800);
}

void Text_Block::save(ofstream& save) {

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