#pragma once

#include "Values.h"

void end() {

	int fade = 0;
	int scroll = 0;

	music.stop();

	while (window.isOpen() && (!Keyboard::isKeyPressed(Keyboard::Escape))) {

		if (fade < 230) {
			fade++;
		}

		if (scroll * UI_scale < 70) {
			scroll+= 2;
		}

		text.setString("Isn't hard 2");
		text.setPosition(screenw / 2 - UI_scale * 400, scroll - UI_scale * 70);
		text.setCharacterSize(UI_scale * 145);
		text.setFillColor(Color(128,255,255,fade));

		window.draw(text);

		text.setString("by tank228");
		text.setPosition(screenw / 2 - UI_scale * 50, scroll + UI_scale * 70);
		text.setCharacterSize(UI_scale * 70);
		text.setFillColor(Color(128, 255, 255, fade));

		window.draw(text);

		text.setString("Thanks for testing");
		text.setPosition(screenw / 2 - UI_scale * 400, scroll + UI_scale * 240);
		text.setCharacterSize(UI_scale * 100);
		text.setFillColor(Color(128, 255, 255, fade));

		window.draw(text);

		text.setString("POTHETIV");
		text.setPosition(screenw / 2 - UI_scale * 330, scroll + UI_scale * 380);
		text.setCharacterSize(UI_scale * 60);
		text.setFillColor(Color(128, 255, 255, fade));

		window.draw(text);

		text.setString("Gla????? Ni????");
		text.setPosition(screenw / 2 - UI_scale * 330, scroll + UI_scale * 460);
		text.setCharacterSize(UI_scale * 60);
		text.setFillColor(Color(128, 255, 255, fade));

		window.draw(text);

		text.setString("Anime_Lord");
		text.setPosition(screenw / 2 - UI_scale * 330, scroll + UI_scale * 540);
		text.setCharacterSize(UI_scale * 60);
		text.setFillColor(Color(128, 255, 255, fade));

		window.draw(text);

		text.setString("Fht??");
		text.setPosition(screenw / 2 - UI_scale * 330, scroll + UI_scale * 620);
		text.setCharacterSize(UI_scale * 60);
		text.setFillColor(Color(128, 255, 255, fade));

		window.draw(text);

		text.setString("Krakozyabra 5");
		text.setPosition(screenw / 2 - UI_scale * 330, scroll + UI_scale * 700);
		text.setCharacterSize(UI_scale * 60);
		text.setFillColor(Color(128, 255, 255, fade));

		window.draw(text);

		text.setString("Gahub");
		text.setPosition(screenw / 2 - UI_scale * 330, scroll + UI_scale * 780);
		text.setCharacterSize(UI_scale * 60);
		text.setFillColor(Color(128, 255, 255, fade));

		window.draw(text);

		text.setString("Morkovka [?]");
		text.setPosition(screenw / 2 - UI_scale * 330, scroll + UI_scale * 860);
		text.setCharacterSize(UI_scale * 60);
		text.setFillColor(Color(128, 255, 255, fade));

		window.draw(text);

		if (Mouse::isButtonPressed(Mouse::Left)) {
			fade -= 30;
			if (fade < 0 && scroll > 30) {
				break;
			}
		}


		//CuRsOr!!!
		cursor.setPosition(Mouse::getPosition().x - window.getPosition().x, (Mouse::getPosition().y) - window.getPosition().y);
		cursor.setScale(1.25, 1.25);
		cursor.setRotation(0);
		window.draw(cursor);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				save_options(); mode = "menu";
				close = true; window.close();
			}

		}

		tick++;
		window.display();
		Sleep(10);
		window.clear();

	}

	mode = "menu";
}
