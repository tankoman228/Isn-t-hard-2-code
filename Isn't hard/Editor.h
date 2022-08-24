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
#include "Blocks.h"
#include "Editor_building.h"

void save_latest_changes(vector <Block*> *s_map_basic, vector <Block*> *s_map_floor, vector <Movable*> *s_movables, vector <Electric*> *s_electric, vector <Block*> *s_triggers) {

	s_map_basic[4] = s_map_basic[3];
	s_map_basic[3] = s_map_basic[2];
	s_map_basic[2] = s_map_basic[1];
	s_map_basic[1] = s_map_basic[0];
	s_map_basic[0] = map_basic;

	s_map_floor[4] = s_map_floor[3];
	s_map_floor[3] = s_map_floor[2];
	s_map_floor[2] = s_map_floor[1];
	s_map_floor[1] = s_map_floor[0];
	s_map_floor[0] = map_floor;

	s_movables[4] = s_movables[3];
	s_movables[3] = s_movables[2];
	s_movables[2] = s_movables[1];
	s_movables[1] = s_movables[0];
	s_movables[0] = movables;

	s_electric[4] = s_electric[3];
	s_electric[3] = s_electric[2];
	s_electric[2] = s_electric[1];
	s_electric[1] = s_electric[0];
	s_electric[0] = electric;

	s_triggers[4] = s_triggers[3];
	s_triggers[3] = s_triggers[2];
	s_triggers[2] = s_triggers[1];
	s_triggers[1] = s_triggers[0];
	s_triggers[0] = triggers;
	
}

void control_z(vector <Block*>* s_map_basic, vector <Block*>* s_map_floor, vector <Movable*>* s_movables, vector <Electric*>* s_electric, vector <Block*>* s_triggers) {

	map_basic.clear();
	map_floor.clear();
	movables.clear();
	electric.clear();
	triggers.clear();

	map_basic = s_map_basic[1];
	s_map_basic[0] = s_map_basic[1];
	s_map_basic[1] = s_map_basic[2];
	s_map_basic[2] = s_map_basic[3];
	s_map_basic[3] = s_map_basic[4];

	map_floor = s_map_floor[1];
	s_map_floor[0] = s_map_floor[1];
	s_map_floor[1] = s_map_floor[2];
	s_map_floor[2] = s_map_floor[3];
	s_map_floor[3] = s_map_floor[4];

	movables = s_movables[1];
	s_movables[0] = s_movables[1];
	s_movables[1] = s_movables[2];
	s_movables[2] = s_movables[3];
	s_movables[3] = s_movables[4];

	electric = s_electric[1];
	s_electric[0] = s_electric[1];
	s_electric[1] = s_electric[2];
	s_electric[2] = s_electric[3];
	s_electric[3] = s_electric[4];

	triggers = s_triggers[1];
	s_triggers[0] = s_triggers[1];
	s_triggers[1] = s_triggers[2];
	s_triggers[2] = s_triggers[3];
	s_triggers[3] = s_triggers[4];
}

void test_editor() {

	int changes_number = -1;

	vector <Block*> s_map_basic[5], s_map_floor[5];
	vector <Movable*> s_movables[5];
	vector <Electric*> s_electric[5];
	vector <Block*> s_triggers[5];

	helper = 1; text.setCharacterSize(50 * scale);
	E_grid.is_checked = true;

	logg << "Editor_start" << endl;

	chosen = map_basic[0];

	float ch_x, ch_y/*, ch_size = 0*/, m_x = 0, m_y = 0;
	RectangleShape choose;

	vector <Sq*> choosed;

	bool onchoose = false;

	editor_mode = 1;
	E_plus.is_checked = true;
	E_Rt.is_checked = false;
	E_M.is_checked = false;
	E_player.is_checked = false;
	E_multichoose.is_checked = false;
	E_fill.is_checked = false;

	save_latest_changes(s_map_basic, s_map_floor, s_movables, s_electric, s_triggers);

	do {

		if (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::Z)) {
			if (changes_number > 0) { changes_number--; control_z(s_map_basic, s_map_floor, s_movables, s_electric, s_triggers); }
			while ((Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::Z))) {}
		}

		if (!music.getStatus()) {
			reset_music();
		}

		/*if ((Keyboard::isKeyPressed(Keyboard::Tab))) {
			for (i = 0; i < wid; i++) {
				for (j = 0; j < hei; j++) {
					for (helper = 0; helper < 2; helper++) {
						for (int oo = 0; oo < 3; oo++) {
							level[i][j][helper][oo] = 0;
						}
					}
				}
			}
			helper = 0;
		}*/

		//zoom
		if (Mouse::isButtonPressed(Mouse::Middle)) {
			if (Mouse::isButtonPressed(Mouse::Right)) {
				scale *= 0.99;
			}
			if (Mouse::isButtonPressed(Mouse::Left)) {
				scale *= 1.01;
			}
			block.setScale(scale, scale);
			text.setCharacterSize(50 * scale);

			if (cursor.getPosition().x > screenw / 2) {
				scrollx += 6 / scale;
			}
			else {
				scrollx -= 6 / scale;
			}
			if (cursor.getPosition().y > screenh / 2) {
				scrolly += 6 / scale;
			}
			else {
				scrolly -= 6 / scale;
			}

		}
		if (Keyboard::isKeyPressed(Keyboard::Add) || Keyboard::isKeyPressed(Keyboard::Equal)) {
			scale *= 1.01;

			if (cursor.getPosition().x > screenw / 2) {
				scrollx += 6 / scale;
			}
			else {
				scrollx -= 6 / scale;
			}
			if (cursor.getPosition().y > screenh / 2) {
				scrolly += 6 / scale;
			}
			else {
				scrolly -= 6 / scale;
			}

			eyes.setScale(scale, scale);
			block.setScale(scale, scale);
			playerS.setScale(scale, scale);
			text.setCharacterSize(50 * scale);
		}
		if (Keyboard::isKeyPressed(Keyboard::Subtract) || Keyboard::isKeyPressed(Keyboard::Hyphen)) {
			scale *= 0.99;

			if (cursor.getPosition().x > screenw / 2) {
				scrollx += 6 / scale;
			}
			else {
				scrollx -= 6 / scale;
			}
			if (cursor.getPosition().y > screenh / 2) {
				scrolly += 6 / scale;
			}
			else {
				scrolly -= 6 / scale;
			}

			eyes.setScale(scale, scale);
			block.setScale(scale, scale);
			playerS.setScale(scale, scale);
			text.setCharacterSize(50 * scale);
		}

		cursor.setPosition(Mouse::getPosition().x - window.getPosition().x, (Mouse::getPosition().y) - window.getPosition().y);
		cursor.setScale(1, 1);

		if (cursor.getPosition().x > screenw - 20) { scrollx += 10 / scale; }
		if (cursor.getPosition().x < 20) { scrollx -= 10 / scale; }
		if (cursor.getPosition().y < 20) { scrolly -= 10 / scale; }
		if (cursor.getPosition().y > screenh - 20) { scrolly += 10 / scale; }

		/*if (Keyboard::isKeyPressed(Keyboard::Tab)) { mode = "game"; }*/

		block.setTexture(editor_col);
		block.setTextureRect(IntRect(0, 0, 128, 128));

		helper = 0;

		for (i = 0; i < 17.0 / scale; i++) {
			for (j = 0; j < 11.0 / scale; j++) {

				block.setPosition((i * 128 - scrollx % 128 - 128) * scale, (j * 128 - scrolly % 128 - 128) * scale);

				if (E_grid.is_checked) {
					window.draw(block);
				}

					if (helper == 1 || cursor.getPosition().y < 128 * UI_scale || cursor.getPosition().y > screenh - 130 * UI_scale) {
						continue;
					}

					if (!button_overlapped && editor_mode == 1 && block.getGlobalBounds().intersects(cursor.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && (!onclick || ((editor_block != 5) && Keyboard::isKeyPressed(Keyboard::LControl)))) {
						onclick = true;

						int x = floor((block.getPosition().x / scale) + scrollx);
						int y = floor((block.getPosition().y / scale) + scrolly);

						if (editor_layer == 0) {
							if (editor_block < 100) {
								for (k = 0; k < map_basic.size(); k++) {
									map_basic[k]->box.scale(0.9, 0.9);
									if (map_basic[k]->box.getGlobalBounds().intersects(block.getGlobalBounds())) {
										map_basic.erase(map_basic.begin() + k);
										chosen = map_basic[0];
									}
								}
								for (k = 0; k < movables.size(); k++) {
									movables[k]->box.scale(0.9, 0.9);
									if (movables[k]->box.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
										movables.erase(movables.begin() + k);
										chosen = map_basic[0];
									}
								}
							}
						}
						if (editor_layer == 1) {
							for (k = 0; k < map_floor.size(); k++) {
								map_floor[k]->box.scale(0.9, 0.9);
								if (map_floor[k]->box.getGlobalBounds().intersects(block.getGlobalBounds())) {
									map_floor.erase(map_floor.begin() + k);
									chosen = map_floor[0];
								}
							}
							for (k = 0; k < electric.size(); k++) {
								electric[k]->box.scale(0.9, 0.9);
								if (electric[k]->box.getGlobalBounds().intersects(block.getGlobalBounds())) {
									electric.erase(electric.begin() + k);
									chosen = map_floor[0];
								}
							}
						}

						place_block(x, y);

						if (changes_number < 4) { changes_number++; }
						save_latest_changes(s_map_basic, s_map_floor, s_movables, s_electric, s_triggers);

						helper = 1;

					}

				}
		}

		if (editor_mode == 1 && Mouse::isButtonPressed(Mouse::Right)) {

			if (editor_layer == 0) {

				helper = -4;

				for (i = 0; i < triggers.size(); i++) {
					if (triggers[i]->box.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
						triggers.erase(triggers.begin() + i); helper = 309;
						while (Mouse::isButtonPressed(Mouse::Right)) {}
					}
				}

				if (helper < 0) {

					for (i = 0; i < map_basic.size(); i++) {
						if (map_basic[i]->box.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
							map_basic.erase(map_basic.begin() + i); helper = 0;
						}
					}
					for (i = 0; i < movables.size(); i++) {
						if (movables[i]->box.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
							movables.erase(movables.begin() + i); helper = 0;
						}
					}
				}
			}
			if (editor_layer == 1) {
				for (i = 0; i < map_floor.size(); i++) {
					if (map_floor[i]->box.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
						map_floor.erase(map_floor.begin() + i); helper = 0;
					}
				}
				for (i = 0; i < electric.size(); i++) {
					if (electric[i]->box.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
						electric.erase(electric.begin() + i); helper = 0;
					}
				}
			}

			if (helper >= 0) {
				if (changes_number < 4) { changes_number++; }
				save_latest_changes(s_map_basic, s_map_floor, s_movables, s_electric, s_triggers);
			}
		}

		if (!onclick && editor_mode == 2 && Mouse::isButtonPressed(Mouse::Left)) {
			if (editor_layer == 0) {
				for (i = 0; i < map_basic.size(); i++) {
					if (map_basic[i]->box.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
						map_basic[i]->rotate(90); onclick = true; continue;
					}
				}
				//for (i = 0; i < movables.size(); i++) {
				//	if (movables[i]->box.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
				//		movables[i]->rotate(90); onclick = true; break;
				//	}
				//}
			}
			if (editor_layer == 1) {
				for (i = 0; i < map_floor.size(); i++) {
					if (map_floor[i]->box.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
						map_floor[i]->rotate(90); onclick = true; continue;
					}
				}
				for (i = 0; i < electric.size(); i++) {
					if (electric[i]->box.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
						electric[i]->rotate(90); onclick = true; continue;
					}
				}
			}
		}

		on_portal_trigger_edit = false;

		chosen->edit();

		if (editor_mode == 4) {
			/*chosen->editing();*/
			if (!onclick) {

				E_arrow[0].box.scale(0.5, 0.5);
				E_arrow[1].box.scale(0.5, 0.5);
				E_arrow[2].box.scale(0.5, 0.5);
				E_arrow[3].box.scale(0.5, 0.5);

				E_rotate_block.box.scale(0.35, 0.35);
				E_rotate_block2.box.scale(0.335, 0.35);

				if (E_arrow[0].if_click()) {
					if (!on_keyboard_click) {
						if (Keyboard::isKeyPressed(Keyboard::LShift)) { chosen->move(0, -16); }
						else { chosen->move(0, -128); }
						onclick = true;
						on_keyboard_click = !Keyboard::isKeyPressed(Keyboard::LControl);
					}
				}
				if (E_arrow[1].if_click()) {
					if (!on_keyboard_click) {
						if (Keyboard::isKeyPressed(Keyboard::LShift)) { chosen->move(16, 0); }
						else { chosen->move(128, 0); }
						onclick = true;
						on_keyboard_click = !Keyboard::isKeyPressed(Keyboard::LControl);
					}
				}
				if (E_arrow[2].if_click()) {
					if (!on_keyboard_click) {
						if (Keyboard::isKeyPressed(Keyboard::LShift)) { chosen->move(0, 16); }
						else { chosen->move(0, 128); }
						onclick = true;
						on_keyboard_click = !Keyboard::isKeyPressed(Keyboard::LControl);
					}
				}
				if (E_arrow[3].if_click()) {
					if (!on_keyboard_click) {
						if (Keyboard::isKeyPressed(Keyboard::LShift)) { chosen->move(-16, 0); }
						else { chosen->move(-128, 0); }
						onclick = true;
						on_keyboard_click = !Keyboard::isKeyPressed(Keyboard::LControl);
					}
				}
				if (E_rotate_block.if_click()) {
					if (!on_keyboard_click) {
						chosen->rotate(-90);
						onclick = true;
					}
				}
				if (E_rotate_block2.if_click()) {
					if (!on_keyboard_click) {
						chosen->rotate(90);
						onclick = true;
					}
				}


				E_arrow[0].box.scale(2, 2);
				E_arrow[1].box.scale(2, 2);
				E_arrow[2].box.scale(2, 2);
				E_arrow[3].box.scale(2, 2);

				E_rotate_block.box.scale(2, 2);
				E_rotate_block2.box.scale(2, 2);
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Q)) {
			if (!on_keyboard_click) {
				chosen->rotate(-90);
				onclick = true;
				on_keyboard_click = true;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::E)) {
			if (!on_keyboard_click) {
				chosen->rotate(90);
				onclick = true;
				on_keyboard_click = true;
			}
		}

		if (!on_portal_trigger_edit && editor_mode < 6) {
			if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {
				if (!on_keyboard_click) {
					if (Keyboard::isKeyPressed(Keyboard::LShift)) { chosen->move(0, -16); }
					else { chosen->move(0, -128); }
					onclick = true;
					on_keyboard_click = !Keyboard::isKeyPressed(Keyboard::LControl);
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
				if (!on_keyboard_click) {
					if (Keyboard::isKeyPressed(Keyboard::LShift)) { chosen->move(16, 0); }
					else { chosen->move(128, 0); }
					onclick = true;
					on_keyboard_click = !Keyboard::isKeyPressed(Keyboard::LControl);
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {
				if (!on_keyboard_click) {
					if (Keyboard::isKeyPressed(Keyboard::LShift)) { chosen->move(0, 16); }
					else { chosen->move(0, 128); }
					onclick = true;
					on_keyboard_click = !Keyboard::isKeyPressed(Keyboard::LControl);
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
				if (!on_keyboard_click) {
					if (Keyboard::isKeyPressed(Keyboard::LShift)) { chosen->move(-16, 0); }
					else { chosen->move(-128, 0); }
					onclick = true;
					on_keyboard_click = !Keyboard::isKeyPressed(Keyboard::LControl);
				}
			}
		}

		//blocks
		for (i = 0; i < triggers.size(); i++) {
			if (!onclick && !button_overlapped && editor_mode == 4 && editor_layer == 0 && Mouse::isButtonPressed(Mouse::Left) && triggers[i]->box.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
				chosen = triggers[i]; onclick = true;
			}
		}

		for (i = 0; i < map_floor.size(); i++) {
			map_floor[i]->editor_exist();			
			if (!onclick && !button_overlapped && editor_mode == 4 && editor_layer == 1 && map_floor[i] != chosen && Mouse::isButtonPressed(Mouse::Left) && map_floor[i]->box.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
				chosen = map_floor[i]; onclick = true;
			}
		}
		for (i = 0; i < electric.size(); i++) {
			electric[i]->editor_exist();
			if (!onclick && !button_overlapped && editor_mode == 4 && editor_layer == 1 && electric[i] != chosen && Mouse::isButtonPressed(Mouse::Left) && electric[i]->box.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
				chosen = electric[i]; onclick = true;
			}
		}
		for (i = 0; i < movables.size(); i++) {
			movables[i]->editor_behave();
			if (!onclick && !button_overlapped && editor_mode == 4 && editor_layer == 0 && movables[i] != chosen && Mouse::isButtonPressed(Mouse::Left) && movables[i]->box.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
				chosen = movables[i]; onclick = true;
			}
		}
		for (i = 0; i < map_basic.size(); i++) {
			map_basic[i]->editor_exist();
			if (!onclick && !button_overlapped && editor_mode == 4 && editor_layer == 0 && map_basic[i] != chosen && Mouse::isButtonPressed(Mouse::Left) && map_basic[i]->box.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
				chosen = map_basic[i]; onclick = true;
			}
		}

		for (i = 0; i < triggers.size(); i++) {
			triggers[i]->editor_exist();
		}
		//!blocks

		chosen->edit();

		if (editor_mode == 4) {

			chosen->editing();

			window.draw(E_arrow[0].box);
			window.draw(E_arrow[1].box);
			window.draw(E_arrow[2].box);
			window.draw(E_arrow[3].box);

			E_rotate_block.box.scale(0.8, 0.8);
			E_rotate_block2.box.scale(0.8, 0.8);

			window.draw(E_rotate_block.box);
			window.draw(E_rotate_block2.box);
		}

		window.draw(cursor);

		//UI
		block.setOrigin(0, 0);
		block.setTexture(grb);
		for (i = 1; i < 50; i++) {
			render_block_UI(screenh, get_ID(i));
		}
		block.setScale(scale, scale);
		block.setOrigin(64, 64);

		/*if (onclick) {
			if ((!Mouse::isButtonPressed(Mouse::Left)) && (!Mouse::isButtonPressed(Mouse::Right)) && (!Keyboard::isKeyPressed(Keyboard::W)) && (!Keyboard::isKeyPressed(Keyboard::A)) && (!Keyboard::isKeyPressed(Keyboard::S)) && (!Keyboard::isKeyPressed(Keyboard::D)) && (!Keyboard::isKeyPressed(Keyboard::Up)) && (!Keyboard::isKeyPressed(Keyboard::Right)) && (!Keyboard::isKeyPressed(Keyboard::Down)) && (!Keyboard::isKeyPressed(Keyboard::Left))) { onclick = false; }
		}*/

		if (editor_mode != 6 && editor_mode != 7) { 

			button_overlapped = false; 

			if (onclick) {
				if (!Mouse::isButtonPressed(Mouse::Left)) {
					onclick = false;
				}
			}

		}
		else {

			if (Mouse::isButtonPressed(Mouse::Right) == Mouse::isButtonPressed(Mouse::Left)) {
				onclick = false;
			}

			if (!onclick && !button_overlapped && (Mouse::isButtonPressed(Mouse::Left) || Mouse::isButtonPressed(Mouse::Right)) && cursor.getPosition().y > 128 * UI_scale) {
				onclick = true;
				onchoose = true;

				ch_x = cursor.getPosition().x;
				ch_y = cursor.getPosition().y;

				choose.setPosition(ch_x, ch_y);

				choose.setOutlineThickness(3);

				if (editor_mode == 6) {
					choose.setFillColor(Color::Color(0, 255, 0, 99));
					choose.setOutlineColor(sf::Color(0, 255, 80));
					deleting = false;
				}
				else {
					if (Mouse::isButtonPressed(Mouse::Left)) {
						choose.setFillColor(Color::Color(0, 0, 255, 99));
						choose.setOutlineColor(sf::Color(0, 80, 255));
						deleting = false;
					}
					else {
						choose.setFillColor(Color::Color(255, 0, 0, 99));
						choose.setOutlineColor(sf::Color(255, 0, 0));
						deleting = true;
					}
				}

			}
			//Begin
			if (onclick && !button_overlapped && (Mouse::isButtonPressed(Mouse::Left) || Mouse::isButtonPressed(Mouse::Right))) {
				choose.setSize({ cursor.getPosition().x - ch_x, cursor.getPosition().y - ch_y });
				window.draw(choose); onclick = true;
			}
			//Choosing
			if (onchoose && editor_mode == 6 && !button_overlapped && !(Mouse::isButtonPressed(Mouse::Left) || Mouse::isButtonPressed(Mouse::Right))) {

				onchoose = false;

				choosed.clear();

				m_x = 0; m_y = 0; k = 0;

				for (i = 0; i < map_floor.size(); i++) {
					map_floor[i]->choosen = false;
					map_floor[i]->editor_exist();
					if (map_floor[i]->box.getGlobalBounds().intersects(choose.getGlobalBounds())) {
						choosed.push_back(map_floor[i]);
						m_x += map_floor[i]->x;
						m_y += map_floor[i]->y;
						map_floor[i]->choosen = true;
						k++;
					}
				}
				for (i = 0; i < electric.size(); i++) {
					electric[i]->editor_exist();
					electric[i]->choosen = false;
					if (electric[i]->box.getGlobalBounds().intersects(choose.getGlobalBounds())) {
						choosed.push_back(electric[i]);
						m_x += electric[i]->x;
						m_y += electric[i]->y;
						electric[i]->choosen = true;
						k++;
					}
				}
				for (i = 0; i < movables.size(); i++) {
					movables[i]->editor_behave();
					movables[i]->choosen = false;
					if (movables[i]->box.getGlobalBounds().intersects(choose.getGlobalBounds())) {
						choosed.push_back(movables[i]);
						m_x += movables[i]->x;
						m_y += movables[i]->y;
						movables[i]->choosen = true;
						k++;
					}
				}
				for (i = 0; i < map_basic.size(); i++) {
					map_basic[i]->editor_exist();
					map_basic[i]->choosen = false;
					if (map_basic[i]->box.getGlobalBounds().intersects(choose.getGlobalBounds())) {
						choosed.push_back(map_basic[i]);
						m_x += map_basic[i]->x;
						m_y += map_basic[i]->y;
						map_basic[i]->choosen = true;
						k++;
					}
				}

				if (k != 0) {
					m_x /= k;
					m_y /= k;
				}
			}
			//Selecting

			if (!onclick && onchoose && editor_mode == 7 && !button_overlapped && (!Mouse::isButtonPressed(Mouse::Left) && !Mouse::isButtonPressed(Mouse::Right))) {

				/*choose.setSize({ cursor.getPosition().x - ch_x, cursor.getPosition().y - ch_y });*/

				if (changes_number < 4) { changes_number++; }

				if (!deleting) {

					logg << "Filling with block: " << editor_block << endl;

					for (i = 0; i < 17.0 / scale; i++) {
						for (j = 0; j < 11.0 / scale; j++) {

							if (cursor.getPosition().y < 128 * UI_scale || cursor.getPosition().y > screenh - 130 * UI_scale) {
								continue;
							}

							block.setPosition((i * 128 - scrollx % 128 - 128) * scale, (j * 128 - scrolly % 128 - 128) * scale);

							if (block.getGlobalBounds().intersects(choose.getGlobalBounds())) {
								onclick = true;

								int x = floor((block.getPosition().x / scale) + scrollx);
								int y = floor((block.getPosition().y / scale) + scrolly);

								if (editor_layer == 0) {
									if (editor_block < 100) {
										for (k = 0; k < map_basic.size(); k++) {
											map_basic[k]->box.scale(0.9, 0.9);
											if (map_basic[k]->box.getGlobalBounds().intersects(block.getGlobalBounds())) {
												map_basic.erase(map_basic.begin() + k);
												chosen = map_basic[0];
											}
										}
										for (k = 0; k < movables.size(); k++) {
											movables[k]->box.scale(0.9, 0.9);
											if (movables[k]->box.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
												movables.erase(movables.begin() + k);
												chosen = map_basic[0];
											}
										}
									}
								}
								if (editor_layer == 1) {
									for (k = 0; k < map_floor.size(); k++) {
										map_floor[k]->box.scale(0.9, 0.9);
										if (map_floor[k]->box.getGlobalBounds().intersects(block.getGlobalBounds())) {
											map_floor.erase(map_floor.begin() + k);
											chosen = map_floor[0];
										}
									}
									for (k = 0; k < electric.size(); k++) {
										electric[k]->box.scale(0.9, 0.9);
										if (electric[k]->box.getGlobalBounds().intersects(block.getGlobalBounds())) {
											electric.erase(electric.begin() + k);
											chosen = map_floor[0];
										}
									}
								}

								place_block(x, y);
							}
						}
					}
				}
				else {

					logg << "Unfilling" << endl;

					if (editor_layer == 0) {

						helper = -4;

						if (helper < 0) {

							for (i = 0; i < map_basic.size(); i++) {
								if (map_basic[i]->box.getGlobalBounds().intersects(choose.getGlobalBounds())) {
									map_basic.erase(map_basic.begin() + i);
									i = 0;
								}
							}
							for (i = 0; i < movables.size(); i++) {
								if (movables[i]->box.getGlobalBounds().intersects(choose.getGlobalBounds())) {
									movables.erase(movables.begin() + i);
									i = 0;
								}
							}
						}
					}
					if (editor_layer == 1) {
						for (i = 0; i < map_floor.size(); i++) {
							if (map_floor[i]->box.getGlobalBounds().intersects(choose.getGlobalBounds())) {
								map_floor.erase(map_floor.begin() + i);
								i = 0;
							}
						}
						for (i = 0; i < electric.size(); i++) {
							if (electric[i]->box.getGlobalBounds().intersects(choose.getGlobalBounds())) {
								electric.erase(electric.begin() + i);
								i = 0;
							}
						}
					}

				}

				save_latest_changes(s_map_basic, s_map_floor, s_movables, s_electric, s_triggers);

				onchoose = false;

			}

			if (!on_keyboard_click) {

				if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
					for (i = 0; i < choosed.size(); i++) {
						if (Keyboard::isKeyPressed(Keyboard::LShift)) { choosed[i]->move(-16, 0); }
						else { choosed[i]->move(-128, 0); }
					}

				}
				if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
					for (i = 0; i < choosed.size(); i++) {
						if (Keyboard::isKeyPressed(Keyboard::LShift)) { choosed[i]->move(16, 0); }
						else { choosed[i]->move(128, 0); }
					}

				}
				if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {
					for (i = 0; i < choosed.size(); i++) {
						if (Keyboard::isKeyPressed(Keyboard::LShift)) { choosed[i]->move(0, -16); }
						else { choosed[i]->move(0, -128); }
					}

				}
				if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {
					for (i = 0; i < choosed.size(); i++) {
						if (Keyboard::isKeyPressed(Keyboard::LShift)) { choosed[i]->move(0, 16); }
						else { choosed[i]->move(0, 128); }
					}

				}

				on_keyboard_click = !Keyboard::isKeyPressed(Keyboard::LControl);
			}

			for (i = 0; i < choosed.size(); i++) {
				choosed[i]->do_some_magic();
			}

			button_overlapped = false;

			if (editor_mode == 6) {

				m_x = 0; m_y = 0;
				for (i = 0; i < choosed.size(); i++) {
					m_x += choosed[i]->x;
					m_y += choosed[i]->y;
				}

				if (choosed.size() != 0) {
					m_x /= choosed.size();
					m_y /= choosed.size();
				}
				else {
					m_x = -1000; m_y = -1000;
				}

				E_copy.box.setPosition((m_x - scrollx - 50)* scale, (m_y - scrolly - 50)* scale);
				E_copy.box.setScale(scale * 0.7, scale * 0.7);

				E_arrow[0].box.setPosition((m_x - scrollx) * scale, (m_y - scrolly) * scale); E_arrow[0].box.move(0, -scale *100);
				E_arrow[1].box.setPosition((m_x - scrollx) * scale, (m_y - scrolly) * scale); E_arrow[1].box.move(scale * 100, 0);
				E_arrow[2].box.setPosition((m_x - scrollx) * scale, (m_y - scrolly) * scale); E_arrow[2].box.move(0, scale *100);
				E_arrow[3].box.setPosition((m_x - scrollx) * scale, (m_y - scrolly) * scale); E_arrow[3].box.move(-scale *100, 0);

				E_arrow[0].box.setScale(scale * 0.7, scale * 0.7);
				E_arrow[1].box.setScale(scale * 0.7, scale * 0.7);
				E_arrow[2].box.setScale(scale * 0.7, scale * 0.7);
				E_arrow[3].box.setScale(scale * 0.7, scale * 0.7);

				if (E_arrow[0].if_click()) {
					if (!onclick) {
						for (i = 0; i < choosed.size(); i++) {
							if (Keyboard::isKeyPressed(Keyboard::LShift)) { choosed[i]->move(0, -16); }
							else { choosed[i]->move(0, -128); }
						}
						onclick = true;
					}
				}
				if (E_arrow[1].if_click()) {
					if (!onclick) {
						for (i = 0; i < choosed.size(); i++) {
							if (Keyboard::isKeyPressed(Keyboard::LShift)) { choosed[i]->move(16, 0); }
							else { choosed[i]->move(128, 0); }
						}
						onclick = true;
					}
				}
				if (E_arrow[2].if_click()) {
					if (!onclick) {
						for (i = 0; i < choosed.size(); i++) {
							if (Keyboard::isKeyPressed(Keyboard::LShift)) { choosed[i]->move(0, 16); }
							else { choosed[i]->move(0, 128); }
						}
						onclick = true;
					}
				}
				if (E_arrow[3].if_click()) {
					if (!onclick) {
						for (i = 0; i < choosed.size(); i++) {
							if (Keyboard::isKeyPressed(Keyboard::LShift)) { choosed[i]->move(-16, 0); }
							else { choosed[i]->move(-128, 0); }
						}
						onclick = true;
					}
				}

				if (E_copy.if_click()) {
					if (!onclick) {
						Sleep(150);

						logg << "copy! {" << endl;

						choosed.clear();

						int g = map_basic.size();

						logg << "	Preparing finished;" << endl;

						for (i = 0; i < g; i++) {
							if (map_basic[i]->choosen) {

								map_basic[i]->choosen = false;

								helper_string = getType(map_basic[i]->id, 0);

								int x = map_basic[i]->x, y = map_basic[i]->y, rotation = map_basic[i]->rotation;
								int id = map_basic[i]->id, look = (map_basic[i]->box.getTextureRect().left) / 128;


								if (helper_string == "Basic") {

									Basic* add = new Basic(x, y, id, rotation, look);

									add[0].box.setOrigin(64, 64);
									add->move(128, -128);
									add->choosen = true;

									map_basic.push_back(add);
								}
								if (helper_string == "Activators") {

									bool if_crystal = (id == 15);

									Activators* add = new Activators(x, y, id, rotation, map_basic[i]->getTarget(), map_basic[i]->getGroup(), if_crystal);

									add[0].box.setOrigin(64, 64);
									add->move(128, -128);
									add->choosen = true;

									map_basic.push_back(add);
								}
								if (helper_string == "Questions") {

									Questions* add = new Questions(x, y, id, 0, look);

									add[0].box.setOrigin(64, 64);
									add->move(128, -128);
									add->choosen = true;

									map_basic.push_back(add);
								}
								if (helper_string == "Special") {

									Special* add = new Special(x, y, id, rotation, look);

									add[0].box.setOrigin(64, 64);
									add->move(128, -128);
									add->choosen = true;

									map_basic.push_back(add);
								}
								if (helper_string == "Detector") {

									bool if_change = (id == 27);

									Detector* add = new Detector(x, y, id, rotation, map_basic[i]->getTarget(), map_basic[i]->getGroup(), if_change);

									add[0].box.setOrigin(64, 64);
									add->move(128, -128);
									add->choosen = true;

									map_basic.push_back(add);
								}
								if (helper_string == "View_det") {

									View_det* add = new View_det(x, y, id, rotation, map_basic[i]->getTarget(), map_basic[i]->getGroup());

									add[0].box.setOrigin(64, 64);
									add->move(128, -128);
									add->choosen = true;

									map_basic.push_back(add);
								}
								if (helper_string == "Speed_det") {

									Speed_det* add = new Speed_det(x, y, id, rotation, map_basic[i]->getTarget(), map_basic[i]->getGroup());

									add[0].box.setOrigin(64, 64);
									add->move(128, -128);
									add->choosen = true;

									map_basic.push_back(add);
								}
								if (helper_string == "Movable_spawn") {
									Movable* add = new Movable(x, y, look);

									add[0].box.setOrigin(64, 64);
									add->move(128, -128);
									add->choosen = true;

									movables.push_back(add);
								}

							}
						}
						for (i = g; i < map_basic.size(); i++) {
							choosed.push_back(map_basic[i]);
						}

						g = movables.size();

						for (i = 0; i < g; i++) {
							if (movables[i]->choosen) {
								Movable* copy = new Movable(*movables[i]);

								movables[i]->choosen = false;

								copy->move(128, -128);
								copy->choosen = true;

								movables.push_back(copy);
							}
						}
						for (i = g; i < movables.size(); i++) {
							choosed.push_back(movables[i]);
						}

						g = map_floor.size();

						for (i = 0; i < g; i++) {
							if (map_floor[i]->choosen) {

								helper_string = getType(map_floor[i]->id, 1);
								map_floor[i]->choosen = false;

								int x = map_floor[i]->x, y = map_floor[i]->y, rotation = map_floor[i]->rotation;
								int id = map_floor[i]->id, look = (map_floor[i]->box.getTextureRect().left) / 128;

								if (helper_string == "Basic_floor") {

									Basic_floor* add = new Basic_floor(x, y, id, rotation, look);

									add[0].box.setOrigin(64, 64);
									add->move(128, -128);
									add->choosen = true;

									map_floor.push_back(add);
								}
								if (helper_string == "Door") {

									Door* add = new Door(x, y, id, rotation, map_floor[i]->getTarget(), map_floor[i]->getGroup(), map_floor[i]->getReverse());

									add[0].box.setOrigin(64, 64);
									add->move(128, -128);
									add->choosen = true;

									map_floor.push_back(add);
								}
								if (helper_string == "Portal") {

									Portal* add = new Portal(x, y, id, 0);
									add->move(128, -128);
									add->choosen = true;

									map_floor.push_back(add);
								}
								if (helper_string == "Floor_button") {

									Floor_button* add = new Floor_button(x, y, id, rotation, map_floor[i]->getTarget(), map_floor[i]->getGroup(), false);

									add[0].box.setOrigin(64, 64);
									add->move(128, -128);
									add->choosen = true;

									map_floor.push_back(add);
								}
								if (helper_string == "Special_floor") {

									Special_floor* add = new Special_floor(x, y, id, rotation, look);

									add[0].box.setOrigin(64, 64);
									add->move(128, -128);
									add->choosen = true;

									map_floor.push_back(add);

								}

							}
						}
						for (i = g; i < map_floor.size(); i++) {
							choosed.push_back(map_floor[i]);
						}

						g = electric.size();

						for (i = 0; i < g; i++) {
							if (electric[i]->choosen) {

								helper_string = getType(electric[i]->id, 1);

								int x = electric[i]->x, y = electric[i]->y, rotation = electric[i]->rotation;
								int id = electric[i]->id, look = (electric[i]->box.getTextureRect().left) / 128;

								electric[i]->choosen = false;

								if (helper_string == "Wire") {
									Wire* add = new Wire(x, y, rotation, id);

									add->move(128, -128);
									add->choosen = true;

									electric.push_back(add);
								}
								if (helper_string == "Generator") {

									Generator* add = new Generator(x, y, rotation, id, id == 30);

									add->move(128, -128);
									add->choosen = true;

									electric.push_back(add);
								}
								if (helper_string == "Switcher") {

									Switcher* add = new Switcher(x, y, rotation, id, electric[i]->getTarget(), electric[i]->getGroup());

									add->move(128, -128);
									add->choosen = true;

									electric.push_back(add);
								}
								if (helper_string == "Switcher2") {

									Switcher2* add = new Switcher2(x, y, rotation, id, electric[i]->getTarget(), electric[i]->getGroup(), electric[i]->id == 35);

									add->move(128, -128);
									add->choosen = true;

									electric.push_back(add);
								}
								if (helper_string == "Ac") {

									Ac* add = new Ac(x, y, rotation, id, electric[i]->getTarget(), electric[i]->getGroup());

									add->move(128, -128);
									add->choosen = true;

									electric.push_back(add); 
								}
								if (helper_string == "El_detector") {

									El_Detector* add = new El_Detector(x, y, rotation, id, electric[i]->getTarget(), electric[i]->getGroup());

									add->move(128, -128);
									add->choosen = true;

									electric.push_back(add); 
								}
								if (helper_string == "El_button") {

									//save >> something_else;

									El_button* add = new El_button(x, y, rotation, false);

									add->move(128, -128);
									add->choosen = true;

									electric.push_back(add);
								}

							}
						}
						for (i = g; i < electric.size(); i++) {
							choosed.push_back(electric[i]);
						}

						logg << "	Copy process finished;" << endl;

						if (changes_number < 4) { changes_number++; }
						save_latest_changes(s_map_basic, s_map_floor, s_movables, s_electric, s_triggers);

						logg << "}" << endl;

					}
					onclick = true;
				}
			}

		}


		if (on_keyboard_click) {
			if (!Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::S) && !Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::Up) && !Keyboard::isKeyPressed(Keyboard::Down) && !Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Q) && !Keyboard::isKeyPressed(Keyboard::E)) {
				on_keyboard_click = false;
			}
		}

		if (E_plus.if_click() || Keyboard::isKeyPressed(Keyboard::Num1)) {
			editor_mode = 1;
			E_plus.is_checked = true;
			E_Rt.is_checked = false;
			E_M.is_checked = false;
			E_player.is_checked = false;
			E_multichoose.is_checked = false;
			E_fill.is_checked = false;
		}

		if (E_Rt.if_click() || Keyboard::isKeyPressed(Keyboard::Num2)) {
			editor_mode = 2;
			E_plus.is_checked = false;
			E_Rt.is_checked = true;
			E_M.is_checked = false;
			E_player.is_checked = false;
			E_multichoose.is_checked = false;
			E_fill.is_checked = false;
		}

		if (E_M.if_click() || Keyboard::isKeyPressed(Keyboard::Num3)) {
			editor_mode = 4;
			E_plus.is_checked = false;
			E_Rt.is_checked = false;
			E_M.is_checked = true;
			E_player.is_checked = false;
			E_multichoose.is_checked = false;
			E_fill.is_checked = false;
		}

		if (E_player.if_click() || Keyboard::isKeyPressed(Keyboard::Num7)) {
			editor_mode = 5;
			E_plus.is_checked = false;
			E_Rt.is_checked = false;
			E_M.is_checked = false;
			E_player.is_checked = true;
			E_multichoose.is_checked = false;
			E_fill.is_checked = false;
		}

		if (E_multichoose.if_click() || Keyboard::isKeyPressed(Keyboard::Num5)) {
			editor_mode = 6;
			E_plus.is_checked = false;
			E_Rt.is_checked = false;
			E_M.is_checked = false;
			E_player.is_checked = false;
			E_multichoose.is_checked = true;
			E_fill.is_checked = false;
		}

		if (E_fill.if_click() || Keyboard::isKeyPressed(Keyboard::Num6)) {
			editor_mode = 7;
			E_plus.is_checked = false;
			E_Rt.is_checked = false;
			E_M.is_checked = false;
			E_player.is_checked = false;
			E_multichoose.is_checked = false;
			E_fill.is_checked = true;
		}

		if (E_play.if_click()) {
			mode = "game"; /*lvl_name = helper_string;*/ lvlnum = -2; save(current_filename); build(-2); break;
		}

		if (E_L.if_click()) {
			editor_layer = 0;
			E_L.is_checked = true;
			E_L2.is_checked = false;

			for (i = 0; i < map_basic.size(); i++) {
				map_basic[i]->setOpacity(255);
			}
			for (i = 0; i < movables.size(); i++) {
				movables[i]->box.setColor(Color(255,255,255,255));
			}
		}

		if (E_grid.if_click() || Keyboard::isKeyPressed(Keyboard::Num4)) {
			E_grid.is_checked = !E_grid.is_checked;
			while (Keyboard::isKeyPressed(Keyboard::Num4)) {}
		}

		if (E_L2.if_click()) {
			editor_layer = 1;
			E_L.is_checked = false;
			E_L2.is_checked = true;

			for (i = 0; i < map_basic.size(); i++) {
				map_basic[i]->setOpacity(75);
			}
			for (i = 0; i < movables.size(); i++) {
				movables[i]->box.setColor(Color(255, 255, 255, 129));
			}
		}

		if (E_save.if_click()) {
			save(current_filename);
			Sleep(300);
		}

		if (E_load.if_click()) {
			/*saveornot = false;
			context_menu = true;*/
			save(current_filename);
			mode = "editor_menu";
		}

		if (E_prev.if_click()) {
			editor_scroll += 128;
			onclick = true;
		}

		if (E_next.if_click()) {
			editor_scroll -= 128;
			onclick = true;
		}

		if (E_B.if_click()) {
			editor_choose = 1;
			E_B.is_checked = true;
			E_R.is_checked = false;
			E_Gr.is_checked = false;
			E_Gy.is_checked = false;
			E_Mech.is_checked = false;
			E_Q.is_checked = false;
			E_E.is_checked = false;
		}

		if (E_R.if_click()) {
			editor_choose = 2;
			E_B.is_checked = false;
			E_R.is_checked = true;
			E_Gr.is_checked = false;
			E_Gy.is_checked = false;
			E_Mech.is_checked = false;
			E_Q.is_checked = false;
			E_E.is_checked = false;
		}

		if (E_Gr.if_click()) {
			editor_choose = 3;
			E_B.is_checked = false;
			E_R.is_checked = false;
			E_Gr.is_checked = true;
			E_Gy.is_checked = false;
			E_Mech.is_checked = false;
			E_Q.is_checked = false;
			E_E.is_checked = false;
		}

		if (E_Gy.if_click()) {
			editor_choose = 4;
			E_B.is_checked = false;
			E_R.is_checked = false;
			E_Gr.is_checked = false;
			E_Gy.is_checked = true;
			E_Mech.is_checked = false;
			E_Q.is_checked = false;
			E_E.is_checked = false;
		}

		if (E_Mech.if_click()) {
			editor_choose = 5;
			E_B.is_checked = false;
			E_R.is_checked = false;
			E_Gr.is_checked = false;
			E_Gy.is_checked = false;
			E_Mech.is_checked = true;
			E_Q.is_checked = false;
			E_E.is_checked = false;
		}

		if (E_Q.if_click()) {
			editor_choose = 6;
			E_B.is_checked = false;
			E_R.is_checked = false;
			E_Gr.is_checked = false;
			E_Gy.is_checked = false;
			E_Mech.is_checked = false;
			E_Q.is_checked = true;
			E_E.is_checked = false;
		}

		if (E_E.if_click()) {
			editor_choose = 7;
			E_B.is_checked = false;
			E_R.is_checked = false;
			E_Gr.is_checked = false;
			E_Gy.is_checked = false;
			E_Mech.is_checked = false;
			E_Q.is_checked = false;
			E_E.is_checked = true;
		}

		if (Keyboard::isKeyPressed(Keyboard::L)) {

			E_L.is_checked = !E_L.is_checked;
			E_L2.is_checked = !E_L.is_checked;

			if (editor_layer == 0) { editor_layer = 1; }
			else { editor_layer = 0; }

			while (Keyboard::isKeyPressed(Keyboard::L)) {}
		}

		if (editor_mode == 5) {
			if (Mouse::isButtonPressed(Mouse::Right)) {
				px = (Mouse::getPosition().x) / scale + scrollx;
				py = (Mouse::getPosition().y) / scale + scrolly;
			}
			playerS.setPosition((px - scrollx) * scale, (py - scrolly) * scale);
			playerS.setScale(scale, scale);
			eyes.setScale(scale, scale);
			eyes.setPosition(playerS.getPosition());
			eyes.setRotation(playerS.getRotation());
			window.draw(playerS); window.draw(eyes);
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			if (!onclick) {
				onclick = true;

				save(current_filename);
				mode = "editor_menu";

				Sleep(100);
			}
		}

		block.setOrigin(0, 0);
		block.setTexture(grb);
		for (i = 1; i < 50; i++) {
			render_block_UI(screenh, get_ID(i));
			if (block.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
				button_overlapped = true;
				if (!onclick && Mouse::isButtonPressed(Mouse::Left)) {
					editor_block = get_ID(i);

					if (editor_mode != 7) { editor_mode = 1; }
					E_plus.is_checked = true;
					E_Rt.is_checked = false;
					E_M.is_checked = false;
					E_player.is_checked = false;
					E_multichoose.is_checked = false;

					onclick = true;
				}
			}
		}
		block.setOrigin(64, 64);
		block.setScale(scale, scale);

		if (E_prev.if_click()) {}

		if (E_next.if_click()) {}

		window.draw(cursor);

		tick++;
		window.display();
		Sleep(1);
		window.clear();

		sf::Event event;
		while (window.pollEvent(event))
		{
			// "запрос закрытия" событие: мы закрываем окно
			if (event.type == sf::Event::Closed) {
				save_options();
				close = true; window.close(); mode = "menu";
			}

		}

	} while (mode == "editor" && window.isOpen());
}
