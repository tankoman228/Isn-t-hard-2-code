#pragma once

#include "Values.h"

class ButtonRes {
public:
	Sprite _box; Text _text; Texture _t;
	bool is_picked = false, click = false;
	int W, H;
	void init(int w, int h) {
		W = w, H = h;
		helper_string = to_string(w) + " : " + to_string(h);
		_text.setString(helper_string);
		_box.setScale(UI_scale / 1.5, UI_scale);
		_t.loadFromFile("Textures\\ResBut.png");
		_box.setTexture(_t);
		_box.setPosition(50 + i * 200, 750 * UI_scale);
		_text.setPosition(50 + i * 200, 770 * UI_scale);
		_text.setFont(font); _text.setFillColor(Color::Black);
		_text.setCharacterSize(UI_scale * 30);
	}
	void cycle() {
		click = false;
		if (_box.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
			_box.setTextureRect(IntRect(0, 64, 256, 64));
			if (!onclick && (Mouse::isButtonPressed(Mouse::Left))) {
				click = true;
			}
		}
		else {
			_box.setTextureRect(IntRect(0, 0, 256, 64));
		}
		if (is_picked) {
			_box.setTextureRect(IntRect(0, 64, 256, 64));
		}
		window.draw(_box);
		window.draw(_text);
	}

};
ButtonRes res_but[2];
//Button of screen resolution

class Checkbox {
public:
	Sprite box_;
	Text text_;
	Texture texture_;
	string text__ = "Fullscreen";
	int type = 0;
	bool is_checked = false;

	void init(int x, int y) {
		text_.setFont(font);
		text_.setCharacterSize(30);
		text_.setFillColor(Color::Blue);
		text_.setPosition(x, y);
		texture_.loadFromFile("Textures\\Check_Box.png");
		box_.setScale(UI_scale / 2, UI_scale / 2);
		box_.setTexture(texture_);
		box_.setPosition(x, y);
		text_.setPosition(x + 72 * UI_scale, y + 10 * UI_scale);
		text_.setString(text__);
	}

	void cycle() {
		if (is_checked) {
			box_.setTextureRect(IntRect(0, 128, 128, 128));
		}
		else {
			box_.setTextureRect(IntRect(0, 0, 128, 128));
		}
		if (cursor.getGlobalBounds().intersects(box_.getGlobalBounds())) {
			if (!onclick) {
				if (Mouse::isButtonPressed(Mouse::Left)) {
					if (is_checked) {
						is_checked = false;
					}
					else {
						is_checked = true;
					}
					switch (type) {
					case 0: break;
					}
				}
			}
		}
		window.draw(box_); window.draw(text_);
	}
};
Checkbox screenmode;

class Option_Button {
public:

	//Bad code!!! Don't touch it, please;
	//I was really bad programmer when i did it

	Sprite button_;
	string text_ = "The first button";
	Texture texture_;
	Text txt_;
	int type = 0;
	bool is_clicked = false;
	void init() {
		txt_.setFont(font);
		txt_.setString(text_);
		button_.setScale(1 * UI_scale, 0.7 * UI_scale);
		texture_.loadFromFile("Textures\\ContextMenuB.png");
		button_.setTexture(texture_);
		button_.setPosition((type) * 600 * UI_scale, 200 * UI_scale);
		txt_.setPosition((type) * 600 * UI_scale + 10, 210 * UI_scale);
		txt_.setCharacterSize(40 * UI_scale);
		txt_.setFillColor(Color::Black);
	}
	void cycle() {
		is_clicked = false;
		if (cursor.getGlobalBounds().intersects(button_.getGlobalBounds())) {
			button_.setTextureRect(IntRect(0, 128, 512, 128));
			if (!onclick) {
				if (Mouse::isButtonPressed(Mouse::Left)) {
					switch (type) {
					case 0:
						if (true) {
							helper_s[0] = 1920;
							helper_s[1] = 1080;
							ofstream file;
							file.open("Screen.txt");
							file << helper_s[0] << " ";
							file << helper_s[1] << " ";
							if (screenmode.is_checked) {
								file << 1 << " ";
							}
							else {
								file << 0 << " ";
							}
							file << UI_scale * 10 << " ";
							file.close();
						}
						break;
					case 1:

						if (true) {

							helper_s[0] = GetSystemMetrics(0);
							helper_s[1] = GetSystemMetrics(1);

							UI_scale = helper_s[0] / 1920.0;

							ofstream file;
							file.open("Screen.txt");
							file << helper_s[0] << " ";
							file << helper_s[1] << " ";
							file << 1 << " ";
							file << UI_scale * 10 << " ";
							file.close();

						}
						break;
					case 2:
						break;
					}
					is_clicked = true;
				}
			}
		}
		else {
			button_.setTextureRect(IntRect(0, 0, 512, 128));
		}
		window.draw(button_);
		window.draw(txt_);
	}
};
Option_Button reloader, auto_reloader, anti_progress;

Texture thbtexture_;
class ThreeBut {
public:
	int minval = 10, maxval = 40, currentval, x = 50, y = 400, option = 0;
	Sprite lower, middle, more;
	Text value;

	/*void init() {
		lower.setPosition(x, y);
		lower.setTexture(thbtexture_);
		lower.setTextureRect(IntRect(0, 0, 128, 128));
		lower.setScale(UI_scale, UI_scale);
		middle.setPosition(x + 128 * UI_scale, y);
		middle.setTexture(thbtexture_);
		middle.setTextureRect(IntRect(128, 0, 128, 128));
		middle.setScale(UI_scale, UI_scale);
		more.setPosition(x + 256 * UI_scale, y);
		more.setTexture(thbtexture_);
		more.setTextureRect(IntRect(256, 0, 128, 128));
		more.setScale(UI_scale, UI_scale);
		thbtexture_.loadFromFile("Textures\\Opt.png");
		value.setPosition(x + 168 * UI_scale, y + UI_scale * 38);
		value.setFont(font);
		value.setCharacterSize(40 * UI_scale);
		value.setFillColor(Color::Black);

	}*/
	void cycle() {
		if (lower.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
			lower.setColor(Color::Color(200, 200, 200, 255));
			if (!onclick) {
				if (Mouse::isButtonPressed(Mouse::Left)) {
					onclick = true;
					if (currentval > minval) {
						currentval -= 1;
					}
					switch (option) {
					case 0: partnum = currentval;
						break;
					case 1: BG_particles_number = currentval;
						break;
					}
				}
			}
		}
		else
		{
			lower.setColor(Color::Color(255, 255, 255, 255));
		}

		if (more.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
			more.setColor(Color::Color(200, 200, 200, 255));
			if (!onclick) {
				if (Mouse::isButtonPressed(Mouse::Left)) {
					onclick = true;
					if (currentval < maxval) {
						currentval += 1;
					}
					switch (option) {
					case 0: partnum = currentval;
						break;
					case 1: BG_particles_number = currentval;
						break;
					}
				}
			}
		}
		else
		{
			more.setColor(Color::Color(255, 255, 255, 255));
		}

		if (!Mouse::isButtonPressed(Mouse::Left)) { onclick = false; }

		value.setString(to_string(currentval));

		window.draw(lower);
		window.draw(middle);
		window.draw(more);
		window.draw(value);
	}

	ThreeBut(int min, int max, int x_, int y_, int option_r) {

		minval = min; maxval = max; option = option_r;
		x = x_; y = y_;

		thbtexture_.loadFromFile("Textures\\Opt.png");

		lower.setPosition(x * UI_scale, y * UI_scale);
		lower.setTexture(thbtexture_);
		lower.setTextureRect(IntRect(0, 0, 128, 128));
		lower.setScale(UI_scale, UI_scale);

		middle.setPosition((x + 128) * UI_scale, y * UI_scale);
		middle.setTexture(thbtexture_);
		middle.setTextureRect(IntRect(128, 0, 128, 128));
		middle.setScale(UI_scale, UI_scale);

		more.setPosition((x + 256) * UI_scale, y * UI_scale);
		more.setTexture(thbtexture_);
		more.setTextureRect(IntRect(256, 0, 128, 128));
		more.setScale(UI_scale, UI_scale);

		value.setPosition((x + 168) * UI_scale, y * UI_scale + UI_scale * 38);
		value.setFont(font);
		value.setCharacterSize(40 * UI_scale);
		value.setFillColor(Color::Black);
	}
	ThreeBut() {}
};
ThreeBut particles_option, bg_particles_option;
//For non-boolean values

class UI {
public:
	Sprite box; Text txt;
	int x, y, id;
	virtual void init(Texture& _t, int _x, int _y, string _text, int _id) {
		box.setTexture(_t);
		x = _x; y = _y;
		txt.setFont(font);
		txt.setString(_text);
		id = _id;
		box.setPosition(x, y);

		txt.setFillColor(Color::White);
		txt.setPosition(x + 65 * UI_scale, y - 35 * UI_scale);
		txt.setCharacterSize(UI_scale * 40);

		box.setOrigin(128, 128);
		box.setScale(UI_scale, UI_scale);
		box.setTextureRect(IntRect(0, 0, 128, 128));
	}

	void setPosition(int _x, int _y) {
		x = _x; y = _y;
		box.setPosition(x, y);	
		txt.setPosition(x + 65 * UI_scale, y - 35 * UI_scale);
	}
};

class Button : public UI {
public:
	void cycle() {
		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (box.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
				if (!onclick) {
					onclick = true;
					click_button_menu = true;
					helper_s2 = id;
				}
			}
		}
		else { onclick = false; }

		if (box.getGlobalBounds().intersects(cursor.getGlobalBounds())) { box.setTextureRect(IntRect(256, 0, 256, 256)); }
		else { box.setTextureRect(IntRect(0, 0, 256, 256)); }

		window.draw(box);
	}
};
Button b_play, b_levels, b_editor, b_ach, b_options, b_exit;
//Like in menu

class Button2 : public UI {
public:
	bool is_checked = false;

	void init(Texture& _t, int _x, int _y, string _text, int _id) {
		box.setTexture(_t);
		x = _x; y = _y;
		txt.setFont(font);
		txt.setString(_text);
		id = _id;
		box.setPosition(x, y);

		txt.setFillColor(Color::White);
		txt.setPosition(x + 65 * UI_scale, y - 35 * UI_scale);
		txt.setCharacterSize(UI_scale * 40);

		box.setOrigin(0, 0);
		box.setScale(UI_scale, UI_scale);
		box.setTextureRect(IntRect(0, 0, 128, 128));
	}

	bool if_click() {
		if (box.getGlobalBounds().intersects(cursor.getGlobalBounds())) {

			button_overlapped = true;

			if (Mouse::isButtonPressed(Mouse::Left)) {
				if (!onclick) {
					onclick = true;
					return true;
				}
			}

			if (is_checked) {
				box.setTextureRect(IntRect(0, 0, 128, 128));
			}
			else { box.setTextureRect(IntRect(128, 0, 128, 128)); }

		}
		else {
			if (is_checked) {
				box.setTextureRect(IntRect(128, 0, 128, 128));
			}
			else { box.setTextureRect(IntRect(0, 0, 128, 128)); }

		}
		window.draw(box);
		return false;
	}

};
Button2 E_B, E_E, E_Gr, E_Gy, E_L, E_L2, E_M, E_Mech, E_next, E_prev, E_play, E_player, E_plus, E_Q, E_R, E_Rt, E_save, E_load, E_trash, E_next_page, E_prev_page, E_grid;
Button2 E_multichoose, E_fill;
//Editor_buttons

class Button3 : public UI {

public:

	Sprite box2; Text txt2;

	int lvl, n;

	bool unlocked = false, finished = false;
	bool wisdom = false;

	void update(int _lvl, int _n) {

		lvl = _lvl; n = _n; wisdom = false;

		box.setScale(UI_scale * 1.2, UI_scale * 1.2);
		box.setPosition(box.getPosition() * UI_scale);
		txt.setPosition(txt.getPosition() * UI_scale);
		box.setOrigin(64, 64);

		txt2.setFont(font);
		txt2.setCharacterSize(UI_scale * 40);

		box2 = box;
		box2.setTexture(ach_complete);

		ifstream ach;
		ach.open("Achievements\\" + to_string(_lvl) + " " + to_string(_n) + ".txt");

		ach >> helper;
		if (helper > 0) {
			unlocked = true;
			box.setTextureRect(IntRect(128, 0, 128, 128));
		}
		else {
			box.setTextureRect(IntRect(0, 0, 128, 128));
			unlocked = false;
		}

		ach >> helper;

		if (helper > 0) {
			finished = true;
			box2.setTextureRect(IntRect(128, 0, 128, 128));
			ach.close();
		}
		else {
			box2.setTextureRect(IntRect(0, 0, 128, 128));
			finished = false;
			ach.close();
		}

		switch (id) {
		case 0: txt.setString("Get achievements to unlock bonus levels!"); break;
		case 1: txt.setString("Welcome to the hard zone"); break;
		case 2: txt.setString("Knot the grawks"); break;
		case 3: txt.setString("Critical mistake"); break;
		case 4: txt.setString("There are no accidents"); break;
		case 5: txt.setString("Move and set"); break;
		case 6: txt.setString("Snail Bob"); break;
		case 7: txt.setString("Logic"); break;
		case 8: txt.setString("We are number one!"); break;
		case 9: txt.setString("Fakes everywhere"); break;
		case 10: txt.setString("Turn the lights off"); break;
		case 11: txt.setString("I like to move it, move it"); break;
		case 12: txt.setString("Automatic"); break;
		case 13: txt.setString("Press start"); break;
		case 14: txt.setString("Have a look"); break;
		case 15: txt.setString("Don't spy!"); break;
		case 16: txt.setString("Hippotomonstrosesquipedaliophobia"); break;
		case 17: txt.setString("I'm blue..."); break;
		case 18: txt.setString("Roses are red, violets are blue..."); break;
		case 19: txt.setString("Electroman adventures"); break;
		case 20: txt.setString("Antichamber"); break;
		case 21: txt.setString("Love is"); break;
		case 22: txt.setString("Friendship is the miracle"); break;
		case 23: txt.setString("Yesterday is history, tomorrow is a mystery"); break;
		case 24: txt.setString("Come on, let's go!"); break;
		case 25: txt.setString("Isn't hard?!?!"); break;
		case 26: txt.setString("No elecric"); break;
		case 27: txt.setString("Greeeeeen"); break;
		case 28: txt.setString("No way back"); break;
		case 29: txt.setString("Escape from the prison"); break;
		case 30: txt.setString("Have a break;"); break;
		case 31: txt.setString("Continue;"); break;
		case 32: txt.setString("Hard. This is hard"); break;
		case 33: txt.setString("Nani?!?!"); break;
		case 34: txt.setString("Incredible mechanics"); break;
		case 35: txt.setString("Superliminal"); break;
		case 36: txt.setString("The end?"); break;
		case 37: txt.setString("Minecart"); break;
		case 38: txt.setString("Fake fakes... Where you are?"); break;
		case 39: txt.setString("Portal"); break;
		case 40: txt.setString("Portal 2"); break;
		case 41: txt.setString("[ The end ]"); break;
		case 42: txt.setString("The final countdown"); break;
		}

		txt2.setString(" ");
	}

	bool if_click() {

		box2.setPosition(box.getPosition());
		box2.move(UI_scale * 160, 0);
		txt.setPosition(box.getPosition());
		txt.move(UI_scale * 290, - UI_scale * 30);
		
		txt2.setPosition(box.getPosition());
		txt2.move(UI_scale * 290, -UI_scale * 30);

		window.draw(box2);

		if (box2.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
			box2.setColor(Color(200, 200, 200));

			#define txt txt2

			if (finished && Mouse::isButtonPressed(Mouse::Left)) {
				txt.setFillColor(Color(0, 0, 80));
				wisdom = !wisdom;
				switch (id) {
				case 0: txt.setString("There are 43 bonus levels"); break;
				case 1: txt.setString("But this one isn't difficult"); break;
				case 2: txt.setString("What do you mean?"); break;
				case 3: txt.setString("Don't afraid of mistakes. Afraid not to solve the problem"); break;
				case 4: txt.setString("But if you don't know anything, there are accidents only"); break;
				case 5: txt.setString("This pattern is well-known. But here it's a bit harder"); break;
				case 6: txt.setString("Do you remember this puzzle?"); break;
				case 7: txt.setString("Brain is the best thing you can use"); break;
				case 8: txt.setString("Do you never be alone..."); break;
				case 9: txt.setString("What about reading/whatching some news?"); break;
				case 10: txt.setString("Don't play with light!"); break;
				case 11: txt.setString("We like to... MOVE IT!"); break;
				case 12: txt.setString("Like in supermarkets"); break;
				case 13: txt.setString("Rub-Rub wasn't here"); break;
				case 14: txt.setString("Your view is matter for them"); break;
				case 15: txt.setString("Run!"); break;
				case 16: txt.setString("The best is enemy for good"); break;
				case 17: txt.setString("Da bu dee, da bu dae..."); break;
				case 18: txt.setString("O mae oh mou, shienderu"); break;
				case 19: txt.setString("Or theory of everything?"); break;
				case 20: txt.setString("Also try antichamber. It's much better than my game"); break;
				case 21: txt.setString("The best thing you can feel and the worst thing you can lose"); break;
				case 22: txt.setString("But nothing can be eternal..."); break;
				case 23: txt.setString("Mystery must be explored!"); break;
				case 24: txt.setString("Sorry for what?"); break;
				case 25: txt.setString("There are no difficult questions. There are complex answers"); break;
				case 26: txt.setString("Mistake) Year, I'm particularly dumb"); break;
				case 27: txt.setString("Tea"); break;
				case 28: txt.setString("History is in the past. You always run to the mystery"); break;
				case 29: txt.setString("But what if prison exists in our minds only?"); break;
				case 30: txt.setString("do_some_magic();"); break;
				case 31: txt.setString("for (i = 0; i < 300; i++) { give_player(''You're cute''); }"); break;
				case 32: txt.setString("Our brain has it's own limits"); break;
				case 33: txt.setString("N-no, let it go"); break;
				case 34: txt.setString("Our life is too various. Unique patterns are everywhere"); break;
				case 35: txt.setString("East or West, home is best"); break;
				case 36: txt.setString("Our life is not infinite, but why we always feel it so? Are there other things after that?"); break;
				case 37: txt.setString("Weeeeeeeeeeeeeeeeee..."); break;
				case 38: txt.setString("Information is so various and unlogic... Internet? No, just a game"); break;
				case 39: txt.setString("Sample text"); break;
				case 40: txt.setString("txet elpmaS"); break;
				case 41: txt.setString("Sometimes we expect more than get as a result \n Don't worry, this game may contain infinite number of levels... \n					Just create them"); break;
				case 42: txt.setString("It's the final brain cell!"); break;
				}

				while (Mouse::isButtonPressed(Mouse::Left)) { };
			}

			#undef txt

		}
		else { box2.setColor(Color::White); }

		if (box.getGlobalBounds().intersects(cursor.getGlobalBounds())) {

			button_overlapped = true;
			box.setColor(Color(200, 200, 200));

			if (Mouse::isButtonPressed(Mouse::Left)) {

				if (!onclick) {

					if (!unlocked) {
						onclick = true;
						return false;
					}

					onclick = true;
					return true;

				}
			}

		}
		else { box.setColor(Color::White); }

		window.draw(box); 
		
		if (!wisdom) { window.draw(txt); }
		else { window.draw(txt2); }

		return false;
	}

};
Button3 ach_but[43];
//Buttons in achievements' menu

class Button4 : public UI {

public:

	Sprite bg_box;

	Button4(Texture& _t, int _x, int _y, int _id) {
		box.setTexture(_t);
		x = _x; y = _y;
		id = _id;
		box.setPosition(x, y);

		bg_box.setOrigin(64, 64);
		box.setOrigin(64, 64);
		box.setTextureRect(IntRect(0, 0, 128, 128));
		box.setTexture(_t);
		bg_box.setTexture(editor_col);
		bg_box.setTextureRect(IntRect(128, 0, 128, 128));

		if (id == 2) {
			box.setTextureRect(IntRect(128, 0, 128, 128));
		}
		if (id == 3) {
			box.setTextureRect(IntRect(0, 0, 128, 128));
		}
	}

	bool if_click() {

		if (box.getGlobalBounds().intersects(cursor.getGlobalBounds())) {

			box.setColor(Color::Color(128, 128, 128, 255));

			button_overlapped = true;

			if (Mouse::isButtonPressed(Mouse::Left) || Mouse::isButtonPressed(Mouse::Right)) {
				if (!onclick) {
					window.draw(box);
					onclick = true;
					return true;
				}
			}

		}
		else {
			box.setColor(Color::Color(255, 255, 255, 255));
		}
		if (id == 1) {
			window.draw(bg_box);
		}
		if (id < 2) {
			window.draw(box);
		}
		return false;
	}

};
Button4 E_edit_block = Button4(editor_option,0,0,0), E_edit_color = Button4(editor_col, 0, 0, 1), E_edit_number = Button4(editor_num, 0, 0, 0);
Button4 E_rotate_block = Button4(e_rotate__, 0, 0, 2);
Button4 E_rotate_block2 = Button4(e_rotate__, 0, 0, 3);

class Button5 : public UI {
public:
	bool is_checked = false;

	void init(Texture& _t, int _x, int _y, string _text, int _id) {
		box.setTexture(_t);
		x = _x; y = _y;
		txt.setFont(font);
		txt.setString(_text);
		id = _id;
		box.setPosition(x, y);

		txt.setFillColor(Color::Blue);
		txt.setPosition(x + 200 * UI_scale, y + 40 * UI_scale);
		txt.setCharacterSize(UI_scale * 40);

		box.setOrigin(0, 0);
		box.setScale(UI_scale, UI_scale);

		if (id == 99) {
			box.setTextureRect(IntRect(0, 0, 128, 128));
		}
		if (id == 69) {
			box.setOrigin(64, 64);
		}
	}

	bool if_click() {
		if (box.getGlobalBounds().intersects(cursor.getGlobalBounds())) {

			button_overlapped = true;

			if (Mouse::isButtonPressed(Mouse::Left)) {
				if (!onclick) {
					/*onclick = true;*/
					window.draw(box);
					return true;
				}
			}

			if (is_checked) {
				box.setColor(Color::Color(255, 255, 255, 255));
			}
			else { box.setColor(Color::Color(128, 128, 128, 255)); }

		}
		else {
			if (is_checked) {
				box.setColor(Color::Color(128, 128, 128, 255));
			}
			else { box.setColor(Color::Color(255, 255, 255, 255)); }

		}
		window.draw(box);
		return false;
	}

};
Button5 E_arrow[4], E_copy, T_plus, T_minus;

Texture e_choose, e_edit, e_rename;
class Custom_Level_choose {
public:

	Button5 chooser, editor, renamer, deleter;
	string filename = "does not exist";

	Custom_Level_choose() { }

	Custom_Level_choose(string file, int number) {

		filename = file;

		chooser.init(e_choose, screenw / 2 - UI_scale * 500, (100 + number * 200) * UI_scale, filename, number);
		editor.init(e_edit, screenw / 2 + UI_scale * 340, (100 + number * 200) * UI_scale, " ", number);
		renamer.init(e_rename, screenw / 2 + UI_scale * 480, (100 + number * 200) * UI_scale, " ", number);
		deleter.init(trash, screenw / 2 + UI_scale * 620, (100 + number * 200) * UI_scale, " ", number);
	}

};
