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
#include "Player.h"
#include "Physics_processing.h"
#include "Context_menu.h"
#include "Level_building.h"

#define px p.x
#define py p.y
#define sx p.sx
#define sy p.sy

void test_game() {

	int i, j, k, helper;
	float helper_s[2] = { 0,0 };
	float helper_s2 = 0;

	int cursor_fade = 0;
	int last_x = 0, last_y = 0;

	teleport_to = -1;
	on_teleport = false;
	/*teleport_frame = 0;*/

	music.setVolume(100);

	s1.setVolume(30);
	sound_p.setVolume(12);
	sound_c.setVolume(30);
	sound_b.setVolume(30);
	_break.setVolume(30);
	ach_s.setVolume(30);
	electro.setVolume(30);
	sound_ab.setVolume(30);
	tp1.setVolume(30);
	tp2.setVolume(30);
	push2.setVolume(30);
	open.setVolume(30);

	player_at_button = -1;

	block.setTexture(corn);
	block.setOrigin(64, 64);

	/*build(lvlnum);*/

	/*load_new(3);*/
	
	logg << "	The game start!\n";

	stop_physics = false;

	player_processing(); render_player();

	eyes.setScale(scale, scale);
	playerS.setScale(scale, scale);

	//Portal_trigger* add = new Portal_trigger(1200,1200,400);
	//map_basic.push_back(add);

	while (mode == "game") {

		//управление
		while (true) {

			//if (Keyboard::isKeyPressed(Keyboard::F5)) {
			//	checkpoint();
			//	alpha = 40;
			//	Sleep(200);
			//}

			if (Keyboard::isKeyPressed(Keyboard::Tab) && !onclick) {

				onclick = true;

				stop_physics = true;
				
				Sleep(100);
				

				build(lvlnum);

				return;
			}

			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				music.stop(); tick += rand() % 10;
			}

			if (Keyboard::isKeyPressed(Keyboard::F5)) {
				stop_physics = true; Sleep(200);
				checkpoint(); stop_physics = false;
			}

			break; //не ругайтесь, я так делаю, чтобы свернуть можно было(
		}

		for (i = 0; i < BG_particles_number; i++) {
			bg_particles[i].cycle();
		}

		if (colint > 0) { colint--; }

		for (i = 0; i < map_floor.size(); i++) {
			map_floor[i]->render();
		}

		for (i = 0; i < electric.size(); i++) {
			electric[i]->render();
		}

		for (i = 0; i < movables.size(); i++) {
			movables[i]->render();
		}

		for (i = 0; i < 5; i++) {
			spiral[i].rotate(3.2);
			if (i == teleport_to) { spiral[i].setScale((teleport_frame * 0.01 + 0.25) * scale, (teleport_frame * 0.01 + 0.25) * scale); }
			else { spiral[i].setScale(0.25 * scale, 0.25 * scale); }
			window.draw(spiral[i]);
			spiral[i].scale(2, 2);
			window.draw(spiral[i]);
			spiral[i].scale(0.5, 0.5);
			window.draw(spiral[i]);
			if (i == teleport_to) { spiral[i].setScale((teleport_frame * 0.01 + 0.25) * scale, (teleport_frame * 0.01 + 0.25) * scale); }
			else { spiral[i].setScale(0.25 * scale, 0.25 * scale); }
			spiral[i].setPosition((tx[i] - scrollx) * scale, (ty[i] - scrolly) * scale);
			window.draw(spiral[i]);
			spiral[i].scale(2, 2);
			window.draw(spiral[i]);
			spiral[i].scale(0.5, 0.5);
			window.draw(spiral[i]);
			spiral[i].setPosition(-200, -200);
		}

		for (i = 0; i < map_basic.size(); i++) {
			map_basic[i]->render();
		}

		//zoom
		if (Mouse::isButtonPressed(Mouse::Right)) {
			if (scale > 0.5 * UI_scale) {
				scale *= 0.99;
				eyes.setScale(scale, scale);
				playerS.setScale(scale, scale);

				if (!scroll_pinned) {
					if (playerS.getPosition().x > screenw / 2) {
						scrollx += 5;
					}
					else {
						scrollx -= 5;
					}
					if (playerS.getPosition().y > screenh / 2) {
						scrolly += 5;
					}
					else {
						scrollx -= 5;
					}
				}

				for (i = 0; i < map_floor.size(); i++) {
					map_floor[i]->render();
				}
				for (i = 0; i < electric.size(); i++) {
					electric[i]->render();
				}
				for (i = 0; i < movables.size(); i++) {
					movables[i]->render();
				}
				for (i = 0; i < 5; i++) {
					spiral[i].rotate(3.2);
					if (i == teleport_to) { spiral[i].setScale((teleport_frame * 0.01 + 0.25) * scale, (teleport_frame * 0.01 + 0.25) * scale); }
					else { spiral[i].setScale(0.25 * scale, 0.25 * scale); }
					window.draw(spiral[i]);
					spiral[i].scale(2, 2);
					window.draw(spiral[i]);
					spiral[i].scale(0.5, 0.5);
					window.draw(spiral[i]);
					if (i == teleport_to) { spiral[i].setScale((teleport_frame * 0.01 + 0.25) * scale, (teleport_frame * 0.01 + 0.25) * scale); }
					else { spiral[i].setScale(0.25 * scale, 0.25 * scale); }
					spiral[i].setPosition((tx[i] - scrollx) * scale, (ty[i] - scrolly) * scale);
					window.draw(spiral[i]);
					spiral[i].scale(2, 2);
					window.draw(spiral[i]);
					spiral[i].scale(0.5, 0.5);
					window.draw(spiral[i]);
					spiral[i].setPosition(-200, -200);
				}
				for (i = 0; i < map_basic.size(); i++) {
					map_basic[i]->render();
				}
			}
		}
		else {
			if (Mouse::isButtonPressed(Mouse::Left)) {
				scale *= 1.01;
				eyes.setScale(scale, scale);
				playerS.setScale(scale, scale);

				if (!scroll_pinned) {
					if (playerS.getPosition().x > screenw / 2) {
						scrollx += 5;
					}
					else {
						scrollx -= 5;
					}
					if (playerS.getPosition().y > screenh / 2) {
						scrolly += 5;
					}
					else {
						scrollx -= 5;
					}
				}

				for (i = 0; i < map_floor.size(); i++) {
					map_floor[i]->render();
				}
				for (i = 0; i < electric.size(); i++) {
					electric[i]->render();
				}
				for (i = 0; i < movables.size(); i++) {
					movables[i]->render();
				}
				for (i = 0; i < 5; i++) {
					spiral[i].rotate(3.2);
					if (i == teleport_to) { spiral[i].setScale((teleport_frame * 0.01 + 0.25) * scale, (teleport_frame * 0.01 + 0.25) * scale); }
					else { spiral[i].setScale(0.25 * scale, 0.25 * scale); }
					window.draw(spiral[i]);
					spiral[i].scale(2, 2);
					window.draw(spiral[i]);
					spiral[i].scale(0.5, 0.5);
					window.draw(spiral[i]);
					if (i == teleport_to) { spiral[i].setScale((teleport_frame * 0.01 + 0.25) * scale, (teleport_frame * 0.01 + 0.25) * scale); }
					else { spiral[i].setScale(0.25 * scale, 0.25 * scale); }
					spiral[i].setPosition((tx[i] - scrollx) * scale, (ty[i] - scrolly) * scale);
					window.draw(spiral[i]);
					spiral[i].scale(2, 2);
					window.draw(spiral[i]);
					spiral[i].scale(0.5, 0.5);
					window.draw(spiral[i]);
					spiral[i].setPosition(-200, -200);
				}
				for (i = 0; i < map_basic.size(); i++) {
					map_basic[i]->render();
				}

			}
		}

		for (i = 0; i < triggers.size(); i++) {
			triggers[i]->render();
		}

		//scrolling
		if (!scroll_pinned) {

			if (last_x != cursor.getPosition().x && last_y != cursor.getPosition().y) {
				last_x = cursor.getPosition().x;
				last_y = cursor.getPosition().y;
				cursor_fade = 0;
			}
			else {
				cursor_fade++;
			}

			if (last_x > screenw - 20) { scrollx += 5 / scale; }
			if (last_x < 20) { scrollx -= 5 / scale; }
			if (last_y < 20) { scrolly -= 5 / scale; }
			if (last_y > screenh - 20) { scrolly += 5 / scale; }

			int x = playerS.getPosition().x;
			int y = playerS.getPosition().y;

			if (x > screenw * 0.6) {
				scrollx += 1;
			}
			if (x < screenw * 0.4) {
				scrollx -= 1;
			}
			if (y > screenh * 0.6) {
				scrolly += 1;
			}
			if (y < screenh * 0.4) {
				scrolly -= 1;
			}

			if (x > screenw - 400 * UI_scale) {
				scrollx += 1;
			}
			if (x < 400 * UI_scale) {
				scrollx -= 1;
			}
			if (y > screenh - 280 * UI_scale) {
				scrolly += 1;
			}
			if (y < 280 * UI_scale) {
				scrolly -= 1;
			}

			if (x > screenw - 200 * UI_scale) {
				scrollx += 11;
				if (playerS.getPosition().x > screenw) {
					scrollx += 9;/* sx = 0;*/
				}
			}
			if (x < 200 * UI_scale) {
				scrollx -= 11;
				if (playerS.getPosition().x < 0) {
					scrollx -= 9;/* sx = 0;*/
				}
			}
			if (y > screenh - 100 * UI_scale) {
				scrolly += 11;
				if (playerS.getPosition().y > screenh) {
					scrolly += 9;/* sy = 0;*/
				}
			}
			if (y < 100 * UI_scale) {
				scrolly -= 11;
				if (playerS.getPosition().y < 0) {
					scrolly -= 9;/* sy = 0;*/
				}
			}
		}
		
		render_player();

		scroll_pinned = false;

		if (Keyboard::isKeyPressed(Keyboard::Add) || Keyboard::isKeyPressed(Keyboard::Equal)) {
			scale *= 1.01;

			eyes.setScale(scale, scale);
			playerS.setScale(scale, scale);
		}
		if ((Keyboard::isKeyPressed(Keyboard::Subtract) || Keyboard::isKeyPressed(Keyboard::Hyphen)) && (scale > 0.8 * UI_scale)) {

			if (scale > 0.5 * UI_scale) {
				scale *= 0.99;
			}

			eyes.setScale(scale, scale);
			playerS.setScale(scale, scale);
		}	

		if (!on_teleport && (teleport_frame > 0)) {
			teleport_frame -= 3; spiral[teleport_to].rotate(-4);

			playerS.setColor(Color::Color(255, 255, 255, 260 - teleport_frame * 4));
			eyes.setColor(Color::Color(255, 255, 255, 260 - teleport_frame * 4));

			if (teleport_frame < 0) {
				teleport_frame = 0;
				playerS.setColor(Color::Color(255, 255, 255, 255));
				eyes.setColor(Color::Color(255, 255, 255, 255));
			}
		}

		for (i = 0; i < 3; i++) {
			if (particle[i][0].enabled) {
				for (j = 0; j < partnum; j++) {
					particle[i][j].render();
				}
			}
		}

		if (abs(alpha) > 0) {
			alpha -= 5;
			if (alpha > 0) {
				blend.setColor(Color::Color(0, 0, 0, abs(alpha)));
			}
			if (alpha < 0) {
				blend.setColor(Color::Color(0, 0, 0, abs(alpha)));
				if (alpha < -253) {

					stop_physics = true; Sleep(300);

					if (levels_opened == lvlnum) {
						levels_opened++; lvlnum++;

						checkpoint();
						Sleep(200);
						build(lvlnum);

						return;
					}
					if (lvlnum == -2) {
						mode = "editor"; stop_physics = true; Sleep(100); lvlnum = -2; build(-2); return;
					}
					if (lvlnum == -3) {

						set_achievement_complete();
						mode = "achievements"; stop_physics = true; Sleep(100); build(-2); 

						return;

					}
					else {
						if (lvlnum == -1) {
							stop_physics = true; Sleep(100);
							mode = "menu";
							lvlnum = 1;
						}
						else { lvlnum++; build(lvlnum); stop_physics = true; Sleep(100); checkpoint(); return; }
					}

					build(lvlnum);
				}
			}
			window.draw(blend);
		}

		if (!music.getStatus()) {
			reset_music();
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			if (!onclick) {
				/*mode = "menu"; */
				onclick = true;
				context_menu = true;
			}
		}
		else {
			onclick = false;
		}

		if (context_menu) { game_context_menu(); }

		if (tp_rech > 0) { tp_rech -= 1; }

		if (achieve_fade > 0) {

			if (achieve_fade > 1145) {
				ach_text.setFillColor(Color::Color(0, 0, 0, 1400 - achieve_fade));					/*ach_box.setPosition(screenw - (1512 - achieve_fade) * UI_scale, 0);*/
				ach_BG.setColor(Color::Color(255, 255, 255, 1400 - achieve_fade));
				ach_text.setOutlineColor(Color(255, 255, 255, 1400 - achieve_fade));
				ach_BG.setPosition(screenw, 0);
				ach_text.setPosition(38 * UI_scale, 20 * UI_scale);
				achieve_fade -= 7;
			}

			if (achieve_fade < 128) {
				/*ach_box.setColor(Color::Color(255, 255, 255, achieve_fade * 2));*/
				ach_BG.setColor(Color::Color(255, 255, 255, achieve_fade * 2));
				ach_text.setFillColor(Color::Color(0, 0, 0, achieve_fade * 2));
				ach_text.setOutlineColor(Color(255, 255, 255, achieve_fade * 2));
			}

			achieve_fade -= 3;

			window.draw(ach_BG); /*window.draw(ach_box);*/ window.draw(ach_text);
		}

		//CuRsOr!!!
		cursor.setPosition(Mouse::getPosition().x - window.getPosition().x, (Mouse::getPosition().y) - window.getPosition().y);
		cursor.setScale(1.25, 1.25);
		cursor.setRotation(0);
		if (cursor_fade < 100) { window.draw(cursor); }

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				save_options(); mode = "menu";
				close = true; window.close();
			}
		}

		if (block_collision) { colint += 4; block_collision = false; }

		tick++;
		window.display();
		Sleep(1);
		window.clear();
	}
}
