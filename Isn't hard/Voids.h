#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <windows.h>
#include <SFML/Audio.hpp>
#include <fstream>
#include "Values.h"
#include "Classes.h"
#include "Player.h"

#define px p.x
#define py p.y
#define sx p.sx
#define sy p.sy

using namespace sf; using namespace std;

void reset_music() {
	switch (rand() % 5) {
	case 0: music.openFromFile("Sounds\\2.ogg"); music.setVolume(100); break;
	case 1: music.openFromFile("Sounds\\3.ogg"); music.setVolume(100); break;
	case 2: music.openFromFile("Sounds\\4.ogg"); music.setVolume(100); break;
	case 3: music.openFromFile("Sounds\\5.ogg"); music.setVolume(100); break;
	case 4: music.openFromFile("Sounds\\music1.ogg"); music.setVolume(30); break;
	}
	if (lvlnum == 1 || lvlnum == 15 || lvlnum == 23 || lvlnum > 30 || ((lvlnum == -3) && tick%3 == 1)) {
		switch (rand() % 3) {
		case 0: music.openFromFile("Sounds\\Music of music.ogg"); music.setVolume(40); break;
		case 1: music.openFromFile("Sounds\\1.ogg"); music.setVolume(100); break;
		case 2: music.openFromFile("Sounds\\1.ogg"); music.setVolume(100); break;
		}
	}
	music.play();
	logg << "Music reset \n";
}

void save_options() {
	logg << "Options are being saved \n";
	ofstream options;
	options.open("Options.txt");
	options << partnum << " " << levels_opened << " ";
	for (i = 0; i < 2; i++) {
		if (res_but[i].is_picked) {
			options << i << " ";
			break;
		}
	}
	options << BG_particles_number << " ";
	options.close();
	logg << "Options are saved\n";
}

#include <filesystem>

void check_saves() {

	logg << "Searching for levels... \n";

	ofstream saves;
	saves.open("saves.txt");

	j = 0;

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

	saves.close();
	logg << "Searching for levels complete \n";
}

void achievement(int _lvl, int _n) {

	helper = 0;

	ifstream ach;
	ach.open("Achievements\\" + to_string(_lvl) + " " + to_string(_n) + ".txt");

	ach >> helper;
	if (helper > 0) { ach.close(); return; }
	
	ach.close();

	//ach_t.loadFromFile("Achievements\\Textures\\" + to_string(_lvl) + " " + to_string(_n) + ".png");
	ach_t.loadFromFile("Achievements\\Textures\\Achievement.png");

	ach_box.setTexture(ach_t);
	//ach_text.setString(helper_string);

	ach_text.setFillColor(Color::Black);
	ach_text.setOutlineColor(Color(0, 255, 255));
	ach_text.setOutlineThickness(3 * UI_scale);
	ach_text.setFont(font);

	for (s = 0; s < 43; s++) {
		if (ach_but[s].lvl == _lvl && ach_but[s].n == _n) {
			break;
		}
	}

#define txt ach_text

	switch (s) {
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
	case 32: txt.setString("Hard. This is hard."); break;
	case 33: txt.setString("Nani?!?!"); break;
	case 34: txt.setString("Incredible mechanics"); break;
	case 35: txt.setString("Superliminal"); break;
	case 36: txt.setString("The end?"); break;
	case 37: txt.setString("Minecart"); break;
	case 38: txt.setString("Fake fakes... Where you are?"); break;
	case 39: txt.setString("Portal"); break;
	case 40: txt.setString("Portal 2"); break;
	case 41: txt.setString("The end."); break;
	case 42: txt.setString("The final countdown"); break;
	}

#undef txt
	
	ach_b.loadFromFile("Achievements\\Sounds\\" + to_string(_lvl) + " " + to_string(_n) + ".ogg");
	ach_b.loadFromFile("Achievements\\Sounds\\-2 0.ogg");
	ach_s.setBuffer(ach_b);

	if (ach_text.getString().getSize() < 20) {
		ach_text.setCharacterSize(UI_scale * 100);
	}
	else {
		ach_text.setCharacterSize(UI_scale * 50);
		if (ach_text.getString().getSize() > 60) {
			ach_text.setCharacterSize(UI_scale * 35);
		}
	}

	ofstream achr;
	achr.open("Achievements\\" + to_string(_lvl) + " " + to_string(_n) + ".txt");

	achr << 1;
	achr << " ";
	achr << 0;
	achr.close();

	achieve_fade = 1400;
	ach_s.play();

}

void set_achievement_complete() {

	ofstream ach;
	ach.open("Achievements\\" + to_string(achievement_file[0]) + " " + to_string(achievement_file[1]) + ".txt");

	ach << 1 << ' ' << 1;

	ach.close();

}

void reload_textures() {

	blue.loadFromFile("Textures\\Blue.png");
	el.loadFromFile("Textures\\Floor.png");
	switch_t.loadFromFile("Textures\\switch.png");
	door.loadFromFile("Textures\\Electric trap.png");
	smth.loadFromFile("Textures\\Something.png");
	smth2.loadFromFile("Textures\\Something2.png");
	smth3.loadFromFile("Textures\\Something3.png");
	str.loadFromFile("Textures\\Stripes.png");
	corn.loadFromFile("Textures\\Corner.png");
	movable.loadFromFile("Textures\\Box.png");
	finon.loadFromFile("Textures\\Finish(ON).png");
	finoff.loadFromFile("Textures\\Finish(OFF).png");
	wall.loadFromFile("Textures\\Wall.png");
	bg.loadFromFile("Textures\\BG.png");
	port_in.loadFromFile("Textures\\Portal.png");
	port_o.loadFromFile("Textures\\Portal_out.png");
	gray.loadFromFile("Textures\\Gray.png");
	gr.loadFromFile("Textures\\Gr.png");
	grb.loadFromFile("Textures\\Grb.png");
	strp.loadFromFile("Textures\\StripesP.png");
	differ.loadFromFile("Textures\\Different.png");
	rb.loadFromFile("Textures\\RB.png");
	rose.loadFromFile("Textures\\Rose.png");
	green.loadFromFile("Textures\\Green.png");
	greenf.loadFromFile("Textures\\GreenFloor.png");
	greenw.loadFromFile("Textures\\GreenWall.png");
	roseb.loadFromFile("Textures\\RoseBricks.png");
	greenf2.loadFromFile("Textures\\GreenFloor2.png");
	fl.loadFromFile("Textures\\Flowers.png");
	crys.loadFromFile("Textures\\Crystal.png");
	act.loadFromFile("Textures\\GreenSwitch.png");
	gravs.loadFromFile("Textures\\gravS.png");
	grav.loadFromFile("Textures\\grav.png");
	buttonblock.loadFromFile("Textures\\Button.png");
	noth.loadFromFile("Textures\\Nothing.png");
	glass.loadFromFile("Textures\\Glass.png");
	_arrow.loadFromFile("Textures\\Arrow.png");
	white.loadFromFile("Textures\\White.png");
	rosebut.loadFromFile("Textures\\RoseBut.png");
	whitewall.loadFromFile("Textures\\White_wall.png");
	rose_door.loadFromFile("Textures\\Rose_door.png");
	gray2.loadFromFile("Textures\\Gray2.png");
	rosefloor2.loadFromFile("Textures\\Blue_floor2.png");
	blue_floor2.loadFromFile("Textures\\Rosefloor2.png");
	rosebricks.loadFromFile("Textures\\RoseBricks2.png");
	lamp_blue.loadFromFile("Textures\\Lamp_blue.png");
	lamp_green.loadFromFile("Textures\\Lamp_barrier.png");
	speed_det.loadFromFile("Textures\\Speed_detector.png");
	portal2.loadFromFile("Textures\\Portal2.png");
	view_det.loadFromFile("Textures\\View_detector.png");
	player_det.loadFromFile("Textures\\Player_detector.png");
	player_det_inv.loadFromFile("Textures\\Player_detector_inv.png");
	pusher.loadFromFile("Textures\\Pusher.png");
	some_help.loadFromFile("Textures\\Some_help.png");
	tp_p.loadFromFile("Textures\\tp.png");
	position_detector.loadFromFile("Textures\\Position_detector.png");
	textblock.loadFromFile("Textures\\text.png");

	c_minus.loadFromFile("Textures\\Electricity\\-.png");
	c_plus.loadFromFile("Textures\\Electricity\\+.png");
	c_ac.loadFromFile("Textures\\Electricity\\Acc.png");
	BGel.loadFromFile("Textures\\Electricity\\BG.png");
	c_corner.loadFromFile("Textures\\Electricity\\C corner.png");
	c_cross3.loadFromFile("Textures\\Electricity\\C cross 3.png");
	c_cross4.loadFromFile("Textures\\Electricity\\C cross 4.png");
	c_one.loadFromFile("Textures\\Electricity\\C 1.png");
	c_line.loadFromFile("Textures\\Electricity\\C linear.png");
	c_resist.loadFromFile("Textures\\Electricity\\Resistor.png");
	c_sensor.loadFromFile("Textures\\Electricity\\Sensor_off.png");
	c_sensor_on.loadFromFile("Textures\\Electricity\\Sensor_on.png");
	c_switch.loadFromFile("Textures\\Electricity\\Switch_on.png");
	c_switch_off.loadFromFile("Textures\\Electricity\\Switch_off.png");
	c_switcher3.loadFromFile("Textures\\Electricity\\Switcher_main.png");
	c_button.loadFromFile("Textures\\Electricity\\Button.png");
	void_el.loadFromFile("Textures\\Electricity\\void.png");

	t_camera.loadFromFile("Textures\\Editor_UI\\T_camera.png");
	block_choose.loadFromFile("Textures\\Editor_UI\\BlockChoose.png");
	t_darkness.loadFromFile("Textures\\Editor_UI\\T_darkness.png");
	t_portal.loadFromFile("Textures\\Editor_UI\\T_portal.png");
	t_portal2.loadFromFile("Textures\\Editor_UI\\T_portal_2.png");
	t_player_size.loadFromFile("Textures\\Editor_UI\\T_player.png");

}

int get_ID(int num) {
	if (editor_layer == 0) {
		if (editor_choose == 1) {
			switch (num) {
			case 1: return 5;
			case 2: return 1;
			case 3: return 2;
			case 4: return 7;
			case 5: return 26;
			case 6: return 27;
			case 7: return 28;
			case 8: return 29;
			case 9: return 3;
			case 10: return 6;
			case 11: return 18;
			case 12: return 19;
			case 13: return 20;
			case 14: return 4;
			}
		}
		if (editor_choose == 2) {
			switch (num) {
			case 1: return 5;
			case 2: return 12;
			case 3: return 13;
			case 4: return 22;
			case 5: return 23;
			case 6: return 24;
			case 7: return 25;
			case 8: return 3;
			case 9: return 6;
			case 10: return 18;
			case 11: return 19;
			case 12: return 20;
			case 13: return 4;
			}
		}
		if (editor_choose == 3) {
			switch (num) {
			case 1: return 5;
			case 2: return 10;
			case 3: return 11;
			case 4: return 15;
			case 5: return 30;
			case 6: return 3;
			case 7: return 6;
			case 8: return 18;
			case 9: return 19;
			case 10: return 20;
			case 11: return 4;
			}
		}
		if (editor_choose == 4) {
			switch (num) {
			case 1: return 5;
			case 2: return 8;
			case 3: return 9;
			case 4: return 14;
			case 5: return 16;
			case 6: return 17;
			case 7: return 3;
			case 8: return 22;
			case 9: return 23;
			case 10: return 6;
			case 11: return 18;
			case 12: return 19;
			case 13: return 20;
			case 14: return 4;
			case 15: return 21;
			}
		}
		if (editor_choose == 5) {
			switch (num) {
			case 1: return 2;
			case 2: return 3;
			case 3: return 5;
			case 4: return 6;
			case 5: return 15;
			case 6: return 16;
			case 7: return 17;
			case 8: return 18;
			case 9: return 19;
			case 10: return 20;
			case 11: return 24;
			case 12: return 26;
			case 13: return 27;
			case 14: return 28;
			case 15: return 29;
			case 16: return 30;
			case 17: return 31;
			}
		}
		if (editor_choose == 6) {
			switch (num) {
			case 1: return 3;
			case 2: return 4;
			case 3: return 6;
			case 4: return 18;
			case 5: return 19;
			case 6: return 20;
			case 7: return 29;
			}
		}
		if (editor_choose == 7) {
			switch (num) {
			case 1: return 24;
			case 2: return 100;
			case 3: return 101;
			case 4: return 102;
			case 5: return 103;
			case 6: return 104;
			case 7: return 31;		
			}
		} 
		return 17;
	}
	if (editor_choose == 1) {
		switch (num) {
		case 1: return 1;
		case 2: return 2;
		case 3: return 3;
		case 4: return 10;
		case 5: return 17;
		case 6: return 18;
		case 7: return 21;
		case 8: return 38;
		case 9: return 39;
		}
	}
	if (editor_choose == 2) {
		switch (num) {
		case 1: return 10;
		case 2: return 13;
		case 3: return 18;
		case 4: return 20;
		case 5: return 23;
		case 6: return 24;
		case 7: return 25;
		case 8: return 26;
		case 9: return 27;
		case 10: return 28;
		case 11: return 29;
		case 12: return 30;
		case 13: return 31;
		case 14: return 32;
		case 15: return 33;
		case 16: return 34;
		case 17: return 35;
		case 18: return 36;
		case 19: return 37;
		case 20: return 42;
		case 21: return 46;
		}
	}
	if (editor_choose == 3) {
		switch (num) {
		case 1: return 11;
		case 2: return 14;
		case 3: return 15;
		case 4: return 16;
		case 5: return 18;
		case 6: return 21;
		case 7: return 40;
		case 8: return 41;
		case 9: return 43;
		case 10: return 45;
		}
	}
	if (editor_choose == 4) {
		switch (num) {
		case 1: return 4;
		case 2: return 5;
		case 3: return 6;
		case 4: return 7;
		case 5: return 8;
		case 6: return 9;
		case 7: return 10;
		case 8: return 12;
		case 9: return 18;
		case 10: return 19;
		case 11: return 22;
		}
	}
	if (editor_choose == 5) {
		switch (num) {
		case 1: return 2;
		case 2: return 3;
		case 3: return 6;
		case 4: return 7;
		case 5: return 8;
		case 6: return 15;
		case 7: return 16;
		case 8: return 17;
		case 9: return 19;
		case 10: return 23;
		case 11: return 24;
		case 12: return 38;
		case 13: return 39;
		case 14: return 40;
		case 15: return 41;
		case 16: return 43;
		case 17: return 45;
		}
	}
	if (editor_choose == 6) {
		if (num == 1) { return 44; }
		return 18;
	}
	if (editor_choose == 7) {
		switch (num) {
		case 1: return 23;
		case 2: return 24;
		case 3: return 25;
		case 4: return 26;
		case 5: return 27;
		case 6: return 28;
		case 7: return 29;
		case 8: return 30;
		case 9: return 31;
		case 10: return 32;
		case 11: return 33;
		case 12: return 34;
		case 13: return 35;
		case 14: return 36;
		case 15: return 37;
		case 16: return 42;
		case 17: return 46;
		}
	}
	return 22;
}

void render_block_UI(int screenh, int ID) {
	block.setTexture(cur);
	block.setPosition(128 * UI_scale * i + editor_scroll * UI_scale, screenh - 128 * UI_scale);
	if (editor_layer == 0) {
		switch (ID) {
		case 1:
			block.setTexture(blue);
			break;
		case 2:
			block.setTexture(switch_t);
			break;
		case 3:
			//the secret coin
			block.setTexture(smth);
			switch (editor_choose) {
			case 1: block.setTextureRect(IntRect(128, 0, 128, 128)); break;
			case 2: block.setTextureRect(IntRect(384, 0, 128, 128)); break;
			case 3: block.setTextureRect(IntRect(256, 0, 128, 128)); break;
			case 4: block.setTextureRect(IntRect(0, 0, 128, 128)); break;
			}
			break;
		case 4:
			//the secret (gathered)
			block.setTexture(smth2);
			switch (editor_choose) {
			case 1: block.setTextureRect(IntRect(128, 0, 128, 128)); break;
			case 2: block.setTextureRect(IntRect(384, 0, 128, 128)); break;
			case 3: block.setTextureRect(IntRect(256, 0, 128, 128)); break;
			case 4: block.setTextureRect(IntRect(0, 0, 128, 128)); break;
			}
			break;
		case 5:
			//movable
			block.setTexture(movable);
			switch (editor_choose) {
			case 1: block.setTextureRect(IntRect(256, 0, 128, 128)); break;
			case 2: block.setTextureRect(IntRect(0, 0, 128, 128)); break;
			case 3: block.setTextureRect(IntRect(128, 0, 128, 128)); break;
			case 4: block.setTextureRect(IntRect(384, 0, 128, 128)); break;
			}
			break;
		case 6:
			//the secret (smoke)
			block.setTexture(smth);
			switch (editor_choose) {
			case 1: block.setTextureRect(IntRect(128, 0, 128, 128)); break;
			case 2: block.setTextureRect(IntRect(384, 0, 128, 128)); break;
			case 3: block.setTextureRect(IntRect(256, 0, 128, 128)); break;
			case 4: block.setTextureRect(IntRect(0, 0, 128, 128)); break;
			}
			break;
		case 7:
			//the wall
			block.setTexture(wall);
			break;
		case 8:
			//gray
			block.setTexture(gr);
			break;
		case 9:
			//gray_wall
			block.setTexture(grb);
			break;
		case 10:
			//greenn
			block.setTexture(green);
			break;
		case 11:
			//green_wall
			block.setTexture(greenw);
			break;
		case 12:
			block.setTexture(roseb);
			break;
		case 13:
			block.setTexture(rb);
			break;
		case 14:
			block.setTexture(fl);
			break;
		case 15:
			block.setTexture(crys); break;
		case 16:
			block.setTexture(gravs);
			window.draw(block);
			block.setTexture(grav);
			break;
		case 17:
			block.setTexture(glass); break;
		case 18:
			//hidden block
			block.setTexture(smth);
			switch (editor_choose) {
			case 1: block.setTextureRect(IntRect(128, 0, 128, 128)); break;
			case 2: block.setTextureRect(IntRect(384, 0, 128, 128)); break;
			case 3: block.setTextureRect(IntRect(256, 0, 128, 128)); break;
			case 4: block.setTextureRect(IntRect(0, 0, 128, 128)); break;
			}
			break;
		case 19:
			//Closer
			block.setTexture(smth);
			switch (editor_choose) {
			case 1: block.setTextureRect(IntRect(128, 0, 128, 128)); break;
			case 2: block.setTextureRect(IntRect(384, 0, 128, 128)); break;
			case 3: block.setTextureRect(IntRect(256, 0, 128, 128)); break;
			case 4: block.setTextureRect(IntRect(0, 0, 128, 128)); break;
			}
			break;
		case 20:
			//Opener
			block.setTexture(smth);
			switch (editor_choose) {
			case 1: block.setTextureRect(IntRect(128, 0, 128, 128)); break;
			case 2: block.setTextureRect(IntRect(384, 0, 128, 128)); break;
			case 3: block.setTextureRect(IntRect(256, 0, 128, 128)); break;
			case 4: block.setTextureRect(IntRect(0, 0, 128, 128)); break;
			}
			break;
		case 21:
			block.setTexture(smth3); break;
		case 22:
			block.setTexture(white); break;
		case 23:
			block.setTexture(whitewall); break;
		case 24:
			block.setTexture(rosebut); break;
		case 25:
			block.setTexture(rosebricks); break;
		case 26:
			block.setTexture(player_det); break;
		case 27:
			block.setTexture(player_det_inv); break;
		case 28:
			block.setTexture(view_det); break;
		case 29:
			block.setTexture(pusher); break;
		case 30:
			block.setTexture(speed_det); break;
		case 100:
			block.setTexture(t_camera); break;
		case 101:
			block.setTexture(t_darkness); break;
		case 102:
			block.setTexture(t_portal); break;
		case 103:
			block.setTexture(t_player_size); break;		
		case 104:
			block.setTexture(textblock); break;
		}

	}
	else {
		switch (ID) {
		case 1:
			block.setTexture(el);
			break;
		case 2:
			block.setTexture(door);
			block.setTextureRect(IntRect(0, 0, 128, 128));
			break;
		case 3:
			block.setTexture(door);
			block.setTextureRect(IntRect(128, 0, 128, 128));
			break;
		case 4:
			block.setTexture(str);
			break;
		case 5:
			block.setTexture(corn);
			break;
		case 6:
			block.setTexture(finon);
			break;
		case 7:
			block.setTexture(port_in);
			break;
		case 8:
			block.setTexture(port_o);
			break;
		case 9:
			block.setTexture(gray); break;
		case 10:
			block.setTexture(strp);
			if (editor_choose == 2) {
				block.setTextureRect(IntRect(0, 0, 128, 128));
			}
			break;
		case 11:
			block.setTexture(greenf); break;
		case 12:
			block.setTexture(differ);
			break;
		case 13:
			block.setTexture(rose); break;
		case 14:
			block.setTexture(greenf2); break;
		case 15:
			block.setTexture(act); break;
		case 16:
			block.setTextureRect(IntRect(128, 0, 128, 128));
			block.setTexture(act); break;
		case 17:
			block.setTexture(buttonblock); block.setTextureRect(IntRect(0, 0, 128, 128)); break;
		case 18:
			block.setTexture(noth); break;
		case 19:
			block.setTexture(_arrow); break;
		case 20:
			block.setTexture(blue_floor2);
			break;
		case 21:
			block.setTexture(rosefloor2);
			break;
		case 22:
			block.setTexture(gray2);
			break;
		case 23:
			block.setTexture(rose_door); break;
		case 24:
			block.setTexture(rose_door);
			block.setTextureRect(IntRect(128, 0, 128, 128)); break;

		case 25:
			block.setTexture(c_one);
			break;
		case 26:
			block.setTexture(c_line);
			break;
		case 27:
			block.setTexture(c_corner);
			break;
		case 28:
			block.setTexture(c_cross3);
			break;
		case 29:
			block.setTexture(c_cross4);
			break;
		case 30:
			block.setTexture(c_plus);
			break;
		case 31:
			block.setTexture(c_minus);
			break;
		case 32:
			block.setTexture(c_resist);
			break;
		case 33:
			block.setTexture(c_switcher3);
			break;
		case 34:
			block.setTexture(c_switch);
			break;
		case 35:
			block.setTexture(c_switch_off);
			break;
		case 36:
			block.setTexture(c_ac);
			break;
		case 37:
			block.setTexture(c_sensor);
			break;
		case 38:
			block.setTexture(lamp_blue); block.setTextureRect(IntRect(0, 0, 128, 128)); break;
		case 39:
			block.setTexture(lamp_blue); block.setTextureRect(IntRect(128, 0, 128, 128)); break;
		case 40:
			block.setTexture(lamp_green); block.setTextureRect(IntRect(0, 0, 128, 128)); break;
		case 41:
			block.setTexture(lamp_green); block.setTextureRect(IntRect(128, 0, 128, 128)); break;
		case 42:
			block.setTexture(void_el);
			break;
		case 43:
			block.setTexture(portal2);
			break;
		case 45:
			block.setTexture(position_detector);
			break;
		case 46:
			block.setTexture(c_button);
			break;
		}
	}
	if (get_ID(i) == editor_block) { block.scale(0.8, 0.8); block.move(7, 7); }
	else { block.setScale(UI_scale / 1.1, UI_scale / 1.1); }
	window.draw(block);
	block.setTextureRect(IntRect(0, 0, 128, 128));
}
