#pragma once

#include "Values.h"
#include "Voids.h"
#include "Level_building.h"

void game_context_menu() {

	while (context_menu) {

		stop_physics = false;

		box_but.setScale(UI_scale, UI_scale * 0.75);
		window.draw(box);
		text.setFillColor(Color::Black); text.setCharacterSize(UI_scale * 50);
		for (i = 0; i < 6; i++) {
			box_but.setPosition(screenw / 2, 150 * UI_scale + 130 * i * UI_scale);
			if (cursor.getGlobalBounds().intersects(box_but.getGlobalBounds())) {
				box_but.setTextureRect(IntRect(0, 128, 512, 128));
				if (Mouse::isButtonPressed(Mouse::Left)) {
					onclick = true;

					switch (i) {
					case 0: context_menu = false; break;
					case 1: checkpoint(); context_menu = false; break;
					case 2: context_menu = false; load_checkpoint(); break;
					case 3: build(lvlnum); context_menu = false; break;
					case 4: checkpoint(); context_menu = false; stop_physics = true; Sleep(100); mode = "menu"; break;
					case 5: context_menu = false; stop_physics = true; Sleep(100); mode = "menu"; break;
					}
				}
			}
			else { box_but.setTextureRect(IntRect(0, 0, 512, 128)); }
			window.draw(box_but);
			text.setPosition(box_but.getPosition());
			text.move(UI_scale * -200, UI_scale * -35);
			switch (i) {
			case 0: text.setString("Resume"); break;
			case 1: text.setString("Save (F5)"); break;
			case 2: text.setString("Back to save"); break;
			case 3: text.setString("Try again (TAB)"); break;
			case 4: text.setString("Save and exit"); break;
			case 5: text.setString("Exit (no saving)"); break;
			}
			window.draw(text);
		}
		cursor.setPosition(Mouse::getPosition().x - window.getPosition().x, (Mouse::getPosition().y) - window.getPosition().y);
		cursor.setScale(1.5, 1.5);
		window.draw(cursor);

		text.setFillColor(Color::White);
		text.setPosition(50, 50);
		text.setString("level: " + to_string(lvlnum));
		window.draw(text);

		window.display();
		window.clear();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				mode = "menu";
				save_options();
				close = true; 
				stop_physics = true;
				window.close();
				return;
			}
		}
	}

}
