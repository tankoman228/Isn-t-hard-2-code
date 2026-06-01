#include <Values.h>
#include <UI.h>
#include <Particles.h>
#include <Voids.h>
#include <Blocks.h>
#include <Level_building.h>
#include <Scenes.hpp>
#include <GlobalVoids.hpp>
#include <System/FileLib.hpp>

int mouseHolding = 0;
Button5 adder;
int renamed = 0;
int levelsCount = 0;
bool isRenaming = false;
Button5 higher , lower;
Texture up, down;
BtnEditorMenuLevel* cheese;
std::string ex_file;
Sprite bg;

void InitEditorMenu() {

    srand(tick * 909);

	ofstream saves;
	saves.open("saves.txt");
    renamed = 0; 
    isRenaming = false; // TODO: что ругается то?

    saves.close();
	logg << "Searching for levels incomplete, create list of files then \n";
	
	auto levels = FilesList("Saves");
	levelsCount = levels.size();

	cheese = new BtnEditorMenuLevel[levels.size()];

	int j = 0;
	for (auto level : levels) {
		cheese[j] = BtnEditorMenuLevel(level.path().filename().u8string(), j);
		j++;
	}

	up.loadFromFile("Textures/Editor_UI/Up.png");
	down.loadFromFile("Textures/Editor_UI/Down.png");

	adder.init(EM_add, 100 * UI_scale, 100 * UI_scale, "", 666);
	higher.init(up, 100 * UI_scale, screenh - 600 * UI_scale, "", 0);
	lower.init(down, 100 * UI_scale, screenh - 300 * UI_scale, "", 0);

	text.setFillColor(Color(0, 0, 128, 255));

	bg.setTexture(Textures["BG"]);
	bg.setTextureRect(IntRect(0, 0, screenw, screenh));

    mouseHolding = 0;
}

void EditorMenuTick(float dt) {
    if (onclick && !Mouse::isButtonPressed(Mouse::Left)) {
        onclick = false;
    }

    if (mouseHolding > 0 && !Mouse::isButtonPressed(Mouse::Left)) { mouseHolding = 0; }

		window.draw(bg);

		if (adder.if_click() && !onclick) {

			onclick = true;

			if (isRenaming) {
				isRenaming = false;
				
				if (ex_file == cheese[renamed].filename) {
					return;
				}

				std::ofstream ofs("Saves/" + cheese[renamed].filename);

				helper_string = "Saves/" + ex_file;
				const char* chr = helper_string.c_str();
				logg << "Delete: " << chr << endl;
				std::remove(chr);
			}

			std::ifstream ifs("Levels/" + rand() % 30);
			std::ofstream ofs("Saves/" + to_string(rand()));

			std::string str;

			while (std::getline(ifs, str)) {
				ofs << str << ' ';
			}
			ifs.close(); ofs.close();

			return;

		}

		for (int i = 0; i < levelsCount; i++) {

			if (cheese[i].chooser.if_click() && !onclick) {

				if (isRenaming) {
					isRenaming = false;
					if (ex_file == cheese[renamed].filename) {
						return;
					}
					std::ifstream ifs("Saves/" + ex_file);
					std::ofstream ofs("Saves/" + cheese[renamed].filename);

					std::string str;

					while (std::getline(ifs, str)) {
						ofs << str << '\n';
					}
					ifs.close(); ofs.close();

					helper_string = "Saves/" + ex_file;
					const char* chr = helper_string.c_str();
					logg << "Delete: " << chr << endl;
					std::remove(chr);
				}

				current_filename = "Saves/" + cheese[i].filename;

				logg << "Custom level play: ";
				logg << cheese[i].filename << endl;

				lvlnum = -2;
				InitGameSceneLevel(-2);
				ChangeScene("game");
				
				return;
			}

			if (cheese[i].deleter.if_click()) {
				if (isRenaming) {
					isRenaming = false;
					if (ex_file == cheese[renamed].filename) {
						return;
					}
					std::ifstream ifs("Saves/" + ex_file);
					std::ofstream ofs("Saves/" + cheese[renamed].filename);

					std::string str;

					while (std::getline(ifs, str)) {
						ofs << str << '\n';
					}
					ifs.close(); ofs.close();

					helper_string = "Saves/" + ex_file;
					const char* chr = helper_string.c_str();
					logg << "Delete: " << chr << endl;
					std::remove(chr);
				}

				mouseHolding += 4;
				onclick = false;

				cheese[i].deleter.box.setColor(Color(255 - mouseHolding, 255 - mouseHolding, 255 - mouseHolding, 255));
				text.setPosition(cheese[i].deleter.box.getPosition());
				text.setString("Hold to delete");
				text.move(- 31 * UI_scale, - 35 * UI_scale);
				text.setCharacterSize(UI_scale * 30);
				window.draw(text);

				if (mouseHolding > 255) {
					helper_string = "Saves/" + cheese[i].filename;
					const char* chr = helper_string.c_str();
					logg << "Delete: " << chr << endl;
					std::remove(chr);
					mouseHolding = 0;
					return;
				}
			}

			if (cheese[i].renamer.if_click() && !onclick) {

				onclick = true;

				if (isRenaming) {
					isRenaming = false;

					if (ex_file == cheese[renamed].filename) {
						return;
					}

					std::ifstream ifs("Saves/" + ex_file);
					std::ofstream ofs("Saves/" + cheese[renamed].filename);

					std::string str;

					while (std::getline(ifs, str)) {
						ofs << str << '\n';
					}
					ifs.close(); ofs.close();

					helper_string = "Saves/" + ex_file;
					const char* chr = helper_string.c_str();
					logg << "Delete: " << chr << endl;
					std::remove(chr);
				}

				isRenaming = true;
				renamed = i;
				ex_file = cheese[i].filename;
			}

			if (cheese[i].editor.if_click()) {
				if (isRenaming) {
					isRenaming = false;
					if (ex_file == cheese[renamed].filename) {
						return;
					}
					std::ifstream ifs("Saves/" + ex_file);
					std::ofstream ofs("Saves/" + cheese[renamed].filename);

					lvl_name = cheese[renamed].filename;

					std::string str;

					while (std::getline(ifs, str)) {
						ofs << str << '\n';
					}
					ifs.close(); ofs.close();

					helper_string = "Saves/" + ex_file;
					const char* chr = helper_string.c_str();
					logg << "Delete: " << chr << endl;
					std::remove(chr);
				}
				current_filename = "Saves/" + cheese[i].filename;
				lvlnum = -2;
				InitGameSceneLevel(-2);
				ChangeScene("editor");
				Sleep(300);
				return;
			}

			text.setPosition(cheese[i].chooser.box.getPosition());
			text.move(UI_scale * 30, UI_scale * 20);
			text.setCharacterSize(UI_scale * 60);

			if (i == renamed && isRenaming) {
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
			for (int i = 0; i < levelsCount; i++) {

				cheese[i].chooser.box.move(0, 19 * UI_scale);
				cheese[i].deleter.box.move(0, 19 * UI_scale);
				cheese[i].renamer.box.move(0, 19 * UI_scale);
				cheese[i].editor.box.move(0, 19 * UI_scale);

				onclick = false;
			}
		}
		if (lower.if_click()) {
			for (int i = 0; i < levelsCount; i++) {

				cheese[i].chooser.box.move(0, -19 * UI_scale);
				cheese[i].renamer.box.move(0, -19 * UI_scale);
				cheese[i].deleter.box.move(0, -19 * UI_scale);
				cheese[i].editor.box.move(0, -19 * UI_scale);

				onclick = false;
			}
		}

	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::TextEntered && isRenaming) {
			if (event.text.unicode < 128) {
				if (Keyboard::isKeyPressed(Keyboard::Space)) {
					cheese[renamed].filename += "_"; continue;
				}
				if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
					cheese[renamed].filename = cheese[renamed].filename.substr(0, cheese[renamed].filename.size() - 1); continue;
				}
				if (Keyboard::isKeyPressed(Keyboard::Enter)) {
					isRenaming = false;

					std::ifstream ifs("Saves/" + ex_file);
					std::ofstream ofs("Saves/" + cheese[renamed].filename);

					std::string str;

					while (std::getline(ifs, str)) {
						ofs << str << '\n';
					}
					ifs.close(); ofs.close();

					helper_string = "Saves/" + ex_file;
					const char* chr = helper_string.c_str();
					logg << "Delete: " << chr << endl;
					std::remove(chr);

					return;

				}
				cheese[renamed].filename += static_cast<char>(event.text.unicode);
			}
		}
	}

	if (onclick && !Mouse::isButtonPressed(Mouse::Left)) {
		onclick = false;
	}
}

