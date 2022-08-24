#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <windows.h>
#include <SFML/Audio.hpp>
#include <fstream>
#include "Values.h"
#include "Classes.h"
#include "Voids.h"

using namespace sf; using namespace std;

void achievements_cycle() {

	Sleep(500);

	/*ach_text = text;*/

	logg << "achievements menu" << endl;

	if (lvlnum != -3) { achievements_scroll = 0; }

	ach_but[0].init(achievement_button_t, 300, 150, "achievement :)", 0);

	for (i = 0; i < 42; i++) {
		ach_but[i + 1].init(achievement_button_t, 300, (200 * i) + 450, "achievement :)", i + 1);
	}

	ach_but[0].update(-2, 0);
	ach_but[1].update(1, 0);
	ach_but[2].update(2, 0);
	ach_but[3].update(3, 0);
	ach_but[4].update(-3, 0);
	ach_but[5].update(5, 0);
	ach_but[6].update(5, 1);
	ach_but[7].update(6, 0);
	ach_but[8].update(-3, 1);
	ach_but[9].update(7, 0);
	ach_but[10].update(7, 1);
	ach_but[11].update(9, 0);
	ach_but[12].update(11, 0);
	ach_but[13].update(-3, 2);
	ach_but[14].update(12, 0);
	ach_but[15].update(-3, 3);
	ach_but[16].update(14, 0);
	ach_but[17].update(15, 0);
	ach_but[18].update(15, 1);
	ach_but[19].update(17, 0);
	ach_but[20].update(-3, 4);
	ach_but[21].update(19, 0);
	ach_but[22].update(-3, 5);
	ach_but[23].update(20, 0);
	ach_but[24].update(21, 0);
	ach_but[25].update(21, 1);
	ach_but[26].update(23, 0);
	ach_but[27].update(23, 1);
	ach_but[28].update(24, 0);
	ach_but[29].update(-3, 6);
	ach_but[30].update(25, 0);
	ach_but[31].update(-3, 7);
	ach_but[32].update(26, 0);
	ach_but[33].update(-3, 8);
	ach_but[34].update(29, 0);
	ach_but[35].update(-3, 9);
	ach_but[36].update(31, 0);
	ach_but[37].update(-3, 10);
	ach_but[38].update(33, 0);
	ach_but[39].update(-3, 11);
	ach_but[40].update(-3, 12);
	ach_but[41].update(35, 0);
	ach_but[42].update(-3, 13);

	do {

		block.setTexture(gray2); block.setOrigin(64, 64); block.setTextureRect(IntRect(0, 0, 128, 128)); block.setScale(1, 1);
		for (i = 0; i < 18; i++) {
			for (j = 0; j < 16; j++) {
				block.setColor(Color::Color(200, 200, 200, 255));
				switch ((i + j) % 4) {
				case 0: block.setRotation(0); break;
				case 1: block.setRotation(90); break;
				case 2: block.setRotation(180); break;
				case 3: block.setRotation(270); break;
				}
				block.setPosition(i * 128 + 64, j * 128 + 64);
				window.draw(block); block.setColor(Color::Color(255, 255, 255, 255));
			}
		}

		for (i = 0; i < 43; i++) {

			ach_but[i].box.setPosition(ach_but[i].box.getPosition().x, ach_but[i].y * UI_scale - achievements_scroll);
			ach_but[i].txt.setPosition(ach_but[i].box.getPosition().x + 70 * UI_scale, ach_but[i].y * UI_scale - achievements_scroll - 30 * UI_scale);

			if (ach_but[i].if_click()) {

				block.setScale(scale, scale); 
				block.setOrigin(64, 64); 
				music.stop(); 

				achievement_file[0] = ach_but[i].lvl;
				achievement_file[1] = ach_but[i].n;

				string newf = ach_but[i].txt.getString();

				for (j = 0; j < newf.size(); j++) {
					if (newf[j] == ' ') { newf[j] = '_'; }
				}

				for (j = 0; j < newf.size(); j++) {
					if (newf[j] == '?') { newf.erase(j); }
				}
				for (j = 0; j < newf.size(); j++) {
					if (newf[j] == '.') { newf.erase(j); }
				}

				if (i == 0) {
					newf = "Horosie_pelmeny_eto_ochen-ochen_vcusno.Na_samom_dele_retsept_prostoy_mnogo_myasa_malo_testa";
				}
				
				current_filename = "Levels\\Bonus levels\\" + newf;

				lvlnum = -3; mode = "game"; build(-2); return;

			}

		}

		cursor.setPosition(Mouse::getPosition().x - window.getPosition().x, (Mouse::getPosition().y) - window.getPosition().y);
		cursor.setScale(1.5, 1.5);
		window.draw(cursor);

		if (cursor.getPosition().y > screenh - 30) {
			achievements_scroll+=35;
		}
		if (cursor.getPosition().y < 30 && achievements_scroll > 0) {
			achievements_scroll-=35;
		}

		window.display();
		Sleep(1);
		window.clear();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				save_options(); mode = "menu";
				close = true; window.close(); mode = "close"; return;
			}

		}

		if (onclick && !Mouse::isButtonPressed(Mouse::Left)) {
			onclick = false;
		}

	}
	while (!Keyboard::isKeyPressed(Keyboard::Escape));

	mode = "menu";

}
