//#include <iostream>
//#include <SFML/Graphics.hpp>
//#include <math.h>
//#include <windows.h>
//#include <SFML/Audio.hpp>
//#include <fstream>

#include "Values.h"
#include "Classes.h"
#include "Voids.h"
#include "Game.h"
#include "Editor.h"
#include "Levels.h"
#include "Achievements.h"
#include "Blocks.h"
#include "Loading.h"
#include "Editor_menu.h"

using namespace std; //it's absolutely safe. I know what to do
using namespace sf; //Release x86. Install SFML to this project if doesn't work

int main() {

	HWND Stealth;
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth, 0);
	//Destroy console

	logg.open("log.txt");

	do {

	ifstream screensize("Screen.txt");
	screensize >> helper;

	if (helper > 0) {

		screenw = helper;
		screensize >> helper;
		screensize >> i;
		screensize >> UI_scale;  UI_scale /= 10;
		if (i == 0) { helper -= 80; }
		screenh = helper;
		screensize.close();

		window.close();
		window.create(sf::VideoMode(screenw, screenh), "Isn't hard 2");

		if (i == 1) {
			window.close();
			window.create(VideoMode(screenw, screenh), "Isn't hard 2", Style::Fullscreen);
			screenmode.is_checked = true;
		}
	}
	else {

		//Auto screen
		window.create(sf::VideoMode(1200, 720), "Isn't hard 2");

		helper_s[0] = GetSystemMetrics(0);
		helper_s[1] = GetSystemMetrics(1);

		UI_scale = helper_s[0] / 1920.0;

		ofstream file;
		file.open("Screen.txt");
		file << helper_s[0] << " ";
		file << helper_s[1] << " ";
		file << 1 << " ";
		file << int(UI_scale * 10) << " ";
		file.close();
		
		ofstream scr;
		scr.open("Screen.txt");
		UI_scale = helper_s[0] / 1920;
		scr << helper_s[0] << " " << helper_s[1] << " ";
		scr << 1 << " ";
		scr << int(UI_scale * 10) << " ";
		scr.close();

		continue;

	}

	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);

	std::thread physics(physics_processing);

	physics.detach();

	Sleep(100);

	loading(); logg << "Loading was succesfully finished \n";

	while (window.isOpen())
	{
		cursor.setScale(0.2, 0.2);
		music.setVolume(30);

		if (mode == "game") {
			//game_cycle();
			test_game();
		}

		if (mode == "editor_menu") {
			editor_menu_cycle();
		}

		if (mode == "editor") {
			/*editor_cycle();*/	
			test_editor();
		}

		if (mode == "achievements") {
			achievements_cycle();
		}

		if (mode == "menu") { 

			if (tick % 10 == 1) {
				if (!music.getStatus()) {
					music.openFromFile("Sounds\\menu.ogg");
					music.play();
				}
			}

			block.setTexture(bg); block.setOrigin(128, 128); block.setTextureRect(IntRect(0, 0, 256, 256)); block.setScale(1, 1);
			for (i = 0; i < 8; i++) {
				for (j = 0; j < 6; j++) {
					switch((i + j) % 4) {
					case 0: block.setRotation(0); break;
					case 1: block.setRotation(90); break;
					case 2: block.setRotation(180); break;
					case 3: block.setRotation(270); break;
					}
					block.setPosition(i * 256 + 128, j * 256 + 128);
					window.draw(block);
				}
			}

			text.setPosition(screenw / 2 - (352 * UI_scale), screenh / 20);
			text.setCharacterSize(150 * UI_scale);
			text.setFillColor(Color::Color(0, 0, 0, 255));
			text.setString("Isn't hard 2");

			window.draw(text);

			text.setPosition(screenw/2 - (350 * UI_scale), screenh / 20 + 2);
			text.setCharacterSize(150 * UI_scale);
			text.setFillColor(Color::Color(200,200,255,255));
			text.setString("Isn't hard 2");
			
			window.draw(text);

			text.setPosition(5, 5);
			text.setFillColor(Color::White);
			text.setCharacterSize(15 * UI_scale);
			text.setString("Beta 1.7");
			window.draw(text);

			b_levels.cycle();
			b_ach.cycle();
			b_exit.cycle();
			b_options.cycle();
			b_play.cycle();
			b_editor.cycle();

			if (click_button_menu) {
				logg << "click_button_menu \n";
				switch (int(helper_s2)) {
				case 0: mode = "levels"; level_scroll = (levels_opened * 300 - 800) * -1; break;
				case 1: mode = "game"; block.setScale(scale, scale); block.setOrigin(64, 64); music.stop(); if (levels_opened < 35) { build(levels_opened); } else { build(rand()%36); } break;
				case 2: mode = "editor_menu"; music.stop(); break;
				case 3: mode = "achievements"; break;
				case 4: mode = "options"; break;
				case 5: save_options(); close = true; window.close();  return 0;
				}
				click_button_menu = false;
			}

		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			if (!onclick) {
				/*mode = "menu"; */
				onclick = true;
				if ((lvlnum == -1)&&(!context_menu)) { lvlnum = 1; }
			}
			if (mode == "options") { mode = "menu"; }
			else { context_menu = true; onclick = false; }

		}

		if (mode == "levels") {
			levels_cycle();
		}

		if (mode == "options") {

			if (tick % 10 == 1) {
				if (!music.getStatus()) {
					music.openFromFile("Sounds\\menu.ogg");
					music.play();
				}
			}

			block.setColor(Color::Color(100, 100, 100, 255));
			block.setTexture(bg); block.setOrigin(128, 128); block.setTextureRect(IntRect(0, 0, 256, 256)); block.setScale(1, 1);
			for (i = 0; i < 8; i++) {
				for (j = 0; j < 6; j++) {
					switch ((i + j) % 4) {
					case 0: block.setRotation(0); break;
					case 1: block.setRotation(90); break;
					case 2: block.setRotation(180); break;
					case 3: block.setRotation(270); break;
					}
					block.setPosition(i * 256 + 128, j * 256 + 128);
					window.draw(block);
				}
			}
			block.setColor(Color::Color(255, 255, 255, 255));

			particles_option.cycle();
			bg_particles_option.cycle();

			text.setFillColor(Color::Color(0, 0, 200, 255));
			text.setCharacterSize(40 * UI_scale);
			text.setPosition(particles_option.middle.getPosition());
			text.move(-90 * UI_scale, 120 * UI_scale);
			text.setString("Particles density");
			window.draw(text);
			text.move(2, 2);
			text.setFillColor(Color::Color(0, 0, 0, 255));
			window.draw(text);

			text.setFillColor(Color::Color(0, 0, 200, 255));
			text.setPosition(bg_particles_option.middle.getPosition());
			text.move(-90 * UI_scale, 120 * UI_scale);
			text.setString("BG quality (0 is BG off). FPS depends on this \n value, especially on weak computers");
			window.draw(text);
			text.move(2, 2);
			text.setFillColor(Color::Color(0, 0, 0, 255));
			window.draw(text);

			reloader.cycle();
			auto_reloader.cycle();
			anti_progress.cycle();

			if (anti_progress.is_clicked) {

				if (Keyboard::isKeyPressed(Keyboard::F) && Keyboard::isKeyPressed(Keyboard::K)) {

					ofstream i_am_bored;

					i_am_bored.close();

					for (k = 0; k < 43; k++) {
						i_am_bored.open("Achievements\\" + to_string(ach_but[k].lvl) + " " + to_string(ach_but[k].n) + ".txt");

						i_am_bored << 0;
						i_am_bored << ' ';
						i_am_bored << 0;

						i_am_bored.close();
					}

					i_am_bored.open("Achievements\\-2 0.txt");

					i_am_bored << 1;
					i_am_bored << ' ';
					i_am_bored << 0;

					levels_opened = 1;

					save_options();

					mode = "menu";

				}
			}

			if (reloader.is_clicked) {
				for (i = 0; i < 2; i++) {
					if (res_but[i].is_picked) {
						helper_s[0] = res_but[i].W; helper_s[1] = res_but[i].H;
						switch (i) {
						case 0: UI_scale = 1; break;
						case 1: UI_scale = 0.5; break;
						}
					}
					ofstream scr;
					scr.open("Screen.txt");
					scr << helper_s[0] << " " << helper_s[1] << " ";
					if (screenmode.is_checked) {
						scr << 1 << " ";
					}
					else { scr << 0 << " "; }
					scr << UI_scale * 10 << " ";
					scr.close();
				}
				break;
			}

			if (auto_reloader.is_clicked) {
				ofstream scr;
				scr.open("Screen.txt");
				UI_scale = helper_s[0] / 1920;
				scr << helper_s[0] << " " << helper_s[1] << " ";
				scr << 1 << " ";
				scr << UI_scale * 10 << " ";
				scr.close();
				break;
			}

			screenmode.cycle();

			for (i = 0; i < 2; i++) {
				res_but[i].cycle();
				if (res_but[i].click) {
					for (j = 0; j < 2; j++) {
						if (i == j) {
							res_but[j].is_picked = true;
						}
						else {
							res_but[j].is_picked = false;
						}
					}
				}
			}

			if (Mouse::isButtonPressed(Mouse::Left)) {
				onclick = true;
			}
			else { onclick = false; }

		}
		
		//CuRsOr!!!
		if (true) {
			cursor.setPosition(Mouse::getPosition().x - window.getPosition().x, (Mouse::getPosition().y) - window.getPosition().y);
			cursor.setScale(1.5, 1.5);
			window.draw(cursor);
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				save_options(); mode = "menu";
				close = true; window.close(); return 1;
			}

		}

		tick++;
		window.display();
		Sleep(1);
		context_menu = false;
	}
	if (close) {
		window.close();
		return 1;
	}
	window.close();
	} while (true);

	return 3;

}
