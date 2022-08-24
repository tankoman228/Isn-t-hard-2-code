#pragma once

#include "Values.h"
#include "Classes.h"
#include "Voids.h"
#include "Blocks.h"
#include "Level_building.h"

void editor_menu_cycle() {

	srand(tick * 909);

	logg << "Editor menu opened!" << endl;
	
	logg << "Searching for levels... \n";

	ofstream saves;
	saves.open("saves.txt");

	int j = 0, renamed = 0;
	bool rename = false;
	string ex;

	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	hf = FindFirstFile(TEXT("Saves\\*"), &FindFileData);
	if (hf != INVALID_HANDLE_VALUE)
	{
		while (FindNextFile(hf, &FindFileData) != 0)
		{
			wstring ws = (FindFileData.cFileName);

			saves << string(ws.begin(), ws.end()) << endl;
			logg << string(ws.begin(), ws.end()) << endl;

			j++;

		}
		FindClose(hf);
	}
	j -= 1;
	logg << j << endl;



	saves.close();
	logg << "Searching for levels complete \n";
	

	Custom_Level_choose* cheese = new Custom_Level_choose[j];
	Button5 adder;
	adder.init(EM_add, 100 * UI_scale, 100 * UI_scale, "", 666);

	ifstream levels;
	levels.open("saves.txt");

	levels >> helper_string;

	for (int i = 0; i < j; i++) {
		levels >> helper_string;
		cheese[i] = Custom_Level_choose(helper_string,i);
	}

	levels.close();

	Button5 higher , lower;
	Texture up, down;

	up.loadFromFile("Textures\\Editor_UI\\Up.png");
	down.loadFromFile("Textures\\Editor_UI\\Down.png");

	higher.init(up, 100 * UI_scale, screenh - 600 * UI_scale, "", 0);
	lower.init(down, 100 * UI_scale, screenh - 300 * UI_scale, "", 0);

	text.setFillColor(Color::Color(0, 0, 128, 255));

	block.setRotation(0); block.setTexture(bg); block.setTextureRect(IntRect(0, 0, 256, 256)); block.setScale(1, 1);
	block.setOrigin(128, 128);

	while (mode == "editor_menu") {

		if (onclick && !Mouse::isButtonPressed(Mouse::Left)) {
			onclick = false;
		}

		if (helper_s2 > 0 && !Mouse::isButtonPressed(Mouse::Left)) { helper_s2 = 0; }

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 8; j++) {
				switch ((i + j) % 4) {
				case 0: block.setRotation(0); break;
				case 1: block.setRotation(90); break;
				case 2: block.setRotation(180); break;
				case 3: block.setRotation(270); break;
				}
				block.setPosition(i * 256 - 128, j * 256 - 128);
				window.draw(block);
			}
		}

		if (adder.if_click() && !onclick) {

			onclick = true;

			if (rename) {
				rename = false;
				
				if (ex == cheese[renamed].filename) {
					return;
				}

				std::ifstream ifs("Saves\\" + ex);
				std::ofstream ofs("Saves\\" + cheese[renamed].filename);

				std::string str;

				while (std::getline(ifs, str)) {
					ofs << str << '\n';
				}
				ifs.close(); ofs.close();

				helper_string = "Saves\\" + ex;
				const char* chr = helper_string.c_str();
				logg << "Delete: " << chr << endl;
				std::remove(chr);
			}

			std::ifstream ifs("Levels\\3");
			std::ofstream ofs("Saves\\" + to_string(rand()));

			std::string str;

			while (std::getline(ifs, str)) {
				ofs << str << ' ';
			}
			ifs.close(); ofs.close();

			return;

		}

		for (int i = 0; i < j; i++) {

			if (cheese[i].chooser.if_click() && !onclick) {

				if (rename) {
					rename = false;
					if (ex == cheese[renamed].filename) {
						return;
					}
					std::ifstream ifs("Saves\\" + ex);
					std::ofstream ofs("Saves\\" + cheese[renamed].filename);

					std::string str;

					while (std::getline(ifs, str)) {
						ofs << str << '\n';
					}
					ifs.close(); ofs.close();

					helper_string = "Saves\\" + ex;
					const char* chr = helper_string.c_str();
					logg << "Delete: " << chr << endl;
					std::remove(chr);
				}

				current_filename = "Saves\\" + cheese[i].filename;

				logg << "Custom level play: ";
				logg << cheese[i].filename << endl;

				lvlnum = -2;
				mode = "game";
				build(-2);
				return;
			}

			if (cheese[i].deleter.if_click()) {
				if (rename) {
					rename = false;
					if (ex == cheese[renamed].filename) {
						return;
					}
					std::ifstream ifs("Saves\\" + ex);
					std::ofstream ofs("Saves\\" + cheese[renamed].filename);

					std::string str;

					while (std::getline(ifs, str)) {
						ofs << str << '\n';
					}
					ifs.close(); ofs.close();

					helper_string = "Saves\\" + ex;
					const char* chr = helper_string.c_str();
					logg << "Delete: " << chr << endl;
					std::remove(chr);
				}

				helper_s2 += 4;
				onclick = false;

				cheese[i].deleter.box.setColor(Color::Color(255 - helper_s2, 255 - helper_s2, 255 - helper_s2, 255));
				text.setPosition(cheese[i].deleter.box.getPosition());
				text.setString("Hold to delete");
				text.move(- 31 * UI_scale, - 35 * UI_scale);
				text.setCharacterSize(UI_scale * 30);
				window.draw(text);

				if (helper_s2 > 255) {
					helper_string = "Saves\\" + cheese[i].filename;
					const char* chr = helper_string.c_str();
					logg << "Delete: " << chr << endl;
					std::remove(chr);
					helper_s2 = 0;
					return;
				}
			}

			if (cheese[i].renamer.if_click() && !onclick) {

				onclick = true;

				if (rename) {
					rename = false;

					if (ex == cheese[renamed].filename) {
						return;
					}

					std::ifstream ifs("Saves\\" + ex);
					std::ofstream ofs("Saves\\" + cheese[renamed].filename);

					std::string str;

					while (std::getline(ifs, str)) {
						ofs << str << '\n';
					}
					ifs.close(); ofs.close();

					helper_string = "Saves\\" + ex;
					const char* chr = helper_string.c_str();
					logg << "Delete: " << chr << endl;
					std::remove(chr);
				}

				rename = true;
				renamed = i;
				ex = cheese[i].filename;

			}

			if (cheese[i].editor.if_click()) {
				if (rename) {
					rename = false;
					if (ex == cheese[renamed].filename) {
						return;
					}
					std::ifstream ifs("Saves\\" + ex);
					std::ofstream ofs("Saves\\" + cheese[renamed].filename);

					lvl_name = cheese[renamed].filename;

					std::string str;

					while (std::getline(ifs, str)) {
						ofs << str << '\n';
					}
					ifs.close(); ofs.close();

					helper_string = "Saves\\" + ex;
					const char* chr = helper_string.c_str();
					logg << "Delete: " << chr << endl;
					std::remove(chr);
				}
				current_filename = "Saves\\" + cheese[i].filename;
				lvlnum = -2;
				mode = "editor";
				build(-2);
				Sleep(300);
				return;
			}

			text.setPosition(cheese[i].chooser.box.getPosition());
			text.move(UI_scale * 30, UI_scale * 20);
			text.setCharacterSize(UI_scale * 60);

			if (i == renamed && rename) {
				if (tick % 80 > 40) {
					text.setString(cheese[i].filename + "|");
				}
				else {
					text.setString(cheese[i].filename);
				}
			}
			else {
				text.setString(cheese[i].filename);
			}

			window.draw(text);

		}

		if (higher.if_click()) {
			for (int i = 0; i < j; i++) {

				cheese[i].chooser.box.move(0, 19 * UI_scale);
				cheese[i].deleter.box.move(0, 19 * UI_scale);
				cheese[i].renamer.box.move(0, 19 * UI_scale);
				cheese[i].editor.box.move(0, 19 * UI_scale);

				onclick = false;
			}
		}
		if (lower.if_click()) {
			for (int i = 0; i < j; i++) {

				cheese[i].chooser.box.move(0, -19 * UI_scale);
				cheese[i].renamer.box.move(0, -19 * UI_scale);
				cheese[i].deleter.box.move(0, -19 * UI_scale);
				cheese[i].editor.box.move(0, -19 * UI_scale);

				onclick = false;
			}
		}

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::TextEntered && rename) {
				if (event.text.unicode < 128) {
					if (Keyboard::isKeyPressed(Keyboard::Space)) {
						cheese[renamed].filename += "_"; continue;
					}
					if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
						cheese[renamed].filename = cheese[renamed].filename.substr(0, cheese[renamed].filename.size() - 1); continue;
					}
					if (Keyboard::isKeyPressed(Keyboard::Enter)) {
						rename = false;

						std::ifstream ifs("Saves\\" + ex);
						std::ofstream ofs("Saves\\" + cheese[renamed].filename);

						std::string str;

						while (std::getline(ifs, str)) {
							ofs << str << '\n';
						}
						ifs.close(); ofs.close();

						helper_string = "Saves\\" + ex;
						const char* chr = helper_string.c_str();
						logg << "Delete: " << chr << endl;
						std::remove(chr);

						return;

					}
					cheese[renamed].filename += static_cast<char>(event.text.unicode);
				}
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			mode = "menu";
			if (rename) {
				if (ex == cheese[renamed].filename) {
					return;
				}
				rename = false;

				std::ifstream ifs("Saves\\" + ex);
				std::ofstream ofs("Saves\\" + cheese[renamed].filename);

				std::string str;

				while (std::getline(ifs, str)) {
					ofs << str << '\n';
				}
				ifs.close(); ofs.close();

				helper_string = "Saves\\" + ex;
				const char* chr = helper_string.c_str();
				logg << "Delete: " << chr << endl;
				std::remove(chr);

				return;
			}
			return;
		}

		//CuRsOr!!!
		if (true) {
			cursor.setPosition(Mouse::getPosition().x - window.getPosition().x, (Mouse::getPosition().y) - window.getPosition().y);
			cursor.setScale(1.5, 1.5);
			window.draw(cursor);
		}

		if (onclick && !Mouse::isButtonPressed(Mouse::Left)) {
			onclick = false;
		}

		while (window.pollEvent(event))
		{
			// "запрос закрытия" событие: мы закрываем окно
			if (event.type == sf::Event::Closed) {
				mode = "menu";
				save_options();
				if (rename) {
					rename = false;

					std::ifstream ifs("Saves\\" + ex);
					std::ofstream ofs("Saves\\" + cheese[renamed].filename);

					std::string str;

					while (std::getline(ifs, str)) {
						ofs << str << '\n';
					}
					ifs.close(); ofs.close();

					helper_string = "Saves\\" + ex;
					const char* chr = helper_string.c_str();
					logg << "Delete: " << chr << endl;
					std::remove(chr);
				}
				close = true; window.close();
			}

		}

		window.display();
		tick++;
		Sleep(1);
		window.clear();
	}

}
