#pragma once
#include "Values.h"
#include "Blocks.h"
#include "Voids.h"
#include "End.h"

string getType(int id, int layer) {

	if (layer == 1) {

		if (id == 1 || id == 4 || id == 5 || id == 9 || id == 10 || id == 11 || id == 12 || id == 13 || id == 14 || id == 20 || id == 21 || id == 22 || id == 42 || id == 44) {
			return "Basic_floor";
		}
		if (id == 2 || id == 3 || id == 15 || id == 16 || id == 23 || id == 24 || id == 38 || id == 39 || id == 40 || id == 41) {
			return "Door";
		}
		if (id == 6 || id == 18 || id == 19 || id == 43) {
			return "Special_floor";
		}
		if (id == 7 || id == 8) {
			return "Portal";
		}
		if (id == 17) {
			return "Floor_button";
		}

		if (id == 25 || id == 26 || id == 27 || id == 28 || id == 29 || id == 32) {
			return "Wire";
		}
		if (id == 30 || id == 31) {
			return "Generator";
		}
		if (id == 33) {
			return "Switcher";
		}
		if (id == 34 || id == 35) {
			return "Switcher2";
		}
		if (id == 36) {
			return "Ac";
		}
		if (id == 37) {
			return "El_detector";
		}
		if (id == 46) {
			return "El_button";
		}
		if (id == 100) {
			return "Camera_trigger";
		}
		if (id == 100) {
			return "Camera_trigger";
		}
		if (id == 101) {
			return "Blind_trigger";
		}
		if (id == 102) {
			return "Portal_trigger";
		}
		if (id == 103) {
			return "Player_size_trigger";
		}
		if (id == 104) {
			return "Text_Block";
		}
	}
	if (layer == 0) {

		if (id == 1 || id == 7 || id == 8 || id == 9 || id == 10 || id == 11 || id == 12 || id == 13 || id == 14 || id == 21 || id == 22 || id == 23 || id == 25) {
			return "Basic";
		}
		if (id == 2 || id == 15 || id == 24) {
			return "Activators";
		}
		if (id == 3 || id == 4 || id == 6 || id == 18 || id == 19 || id == 20 || id == 29) {
			return "Questions";
		}
		if (id == 5) {
			return "Movable_spawn";
		}
		if (id == 16 || id == 17 || id == 31) {
			return "Special";
		}
		if (id == 26 || id == 27) {
			return "Detector";
		}
		if (id == 28) {
			return "View_det";
		}
		if (id == 30) {
			return "Speed_det";
		}
		if (id == 100) {
			return "Camera_trigger";
		}
		if (id == 101) {
			return "Blind_trigger";
		}
		if (id == 102) {
			return "Portal_trigger";
		}
		if (id == 103) {
			return "Player_size_trigger";
		}
		if (id == 104) {
			return "Text_Block";
		}

	}

	logg << "Error : unknown ID " << id << endl;
	return "Error";
}

void save(string fname) {

	ofstream save;

	save.open(fname);
	current_filename = fname;

	logg << "Saving level: " << fname << endl;

	save << lvl_name << endl;
	save << "Map_basic" << endl;

	for (i = 0; i < map_basic.size(); i++) {

		if (map_basic[i]->id > 0) {
			map_basic[i]->save(save);
		}
	}

	save << "Movables" << endl;

	for (i = 0; i < movables.size(); i++) {
		movables[i]->save(save);
	}

	save << "Map_floor" << endl;

	for (i = 0; i < map_floor.size(); i++) {

		if (map_floor[i]->id > 0) {
			map_floor[i]->save(save);
		}

	}

	for (i = 0; i < triggers.size(); i++) {

		if (triggers[i]->id > 0) {
			triggers[i]->save(save);
		}

	}

	save << "Electric" << endl;

	for (i = 0; i < electric.size(); i++) {
		if (electric[i]->id > 0) {
			electric[i]->save(save);
		}
	}

	save << "PLayer ";
	save << px << " ";
	save << py;

	save.close();
	logg << "Saving finished" << endl;

}

void checkpoint() {

	logg << "	Checkpoint \n";

	ofstream save;

	save.open("checkpoint");



	save << lvl_name << endl;
	save << "Map_basic" << endl;

	for (i = 0; i < map_basic.size(); i++) {
		map_basic[i]->save(save);
	}

	save << "Movables" << endl;

	for (i = 0; i < movables.size(); i++) {
		movables[i]->save(save);
	}

	save << "Map_floor" << endl;

	for (i = 0; i < map_floor.size(); i++) {
		map_floor[i]->save(save);
	}

	for (i = 0; i < triggers.size(); i++) {

		triggers[i]->save(save);

	}

	save << "Electric" << endl;

	for (i = 0; i < electric.size(); i++) {
		electric[i]->save(save);
	}

	save << "PLayer ";
	save << px << " ";
	save << py << endl;

	for (i = 0; i < 999; i++) {
		save << int(dmode[i]) << ' ';
		save << int(crystal[i]) << ' ';
		save << int(lmode[i]) << ' ';
		save << int(barmode[i]) << ' ';
	}

	save << player_scale << ' ';
	save << lvlnum << ' ';
	save << current_filename << ' ';

	logg << "	Checkpoint is succesfully set \n";
}

void load_checkpoint() {

	logg << "	loading checkpoint \n";

	stop_physics = true;

	Sleep(100);

	helper = 0;
	coins_gathered = 0;
	coins_required = 0;
	helper_s[0] = 0;
	helper_s[1] = 0;
	alpha = 255;

	map_basic.clear();
	map_floor.clear();
	movables.clear();
	electric.clear();
	triggers.clear();

	for (i = 0; i < 5; i++) {
		tx[i] = -20000; ty[i] = -20000;
		spiral[i].setPosition(-30000, -30000);
	}

	int id, rotation, look, group;
	float x, y;
	bool* target = dmode; bool something_else;
	
	ifstream save;
	save.open("checkpoint");

	save >> lvl_name;
	save >> helper_string;

	while (true) {

		save >> helper_string;

		while (true) {

			save >> id;
			save >> x;
			save >> y;

			helper_string = getType(id, 0);

			if (helper_string == "Basic") {

				save >> rotation;
				save >> look;

				Basic* add = new Basic(x, y, id, rotation, look);

				add[0].box.setOrigin(64, 64);

				map_basic.push_back(add);
			}
			if (helper_string == "Activators") {

				save >> rotation;
				save >> helper_string;

				if (helper_string == "dmode") {
					target = dmode;
				}
				if (helper_string == "crystal") {
					target = crystal;
				}
				if (helper_string == "lmode") {
					target = lmode;
				}
				if (helper_string == "barmode") {
					target = barmode;
				}

				save >> group;

				save >> something_else;

				Activators* add = new Activators(x, y, id, rotation, target, group, something_else);

				add[0].box.setOrigin(64, 64);

				map_basic.push_back(add);
			}
			if (helper_string == "Questions") {

				save >> rotation;
				save >> look;

				Questions* add = new Questions(x, y, id, rotation, look);

				add[0].box.setOrigin(64, 64);

				map_basic.push_back(add);
			}
			if (helper_string == "Special") {

				save >> rotation;
				save >> look;

				Special* add = new Special(x, y, id, rotation, look);

				add[0].box.setOrigin(64, 64);

				map_basic.push_back(add);

			}
			if (helper_string == "Detector") {

				save >> rotation;
				save >> helper_string;

				if (helper_string == "dmode") {
					target = dmode;
				}
				if (helper_string == "crystal") {
					target = crystal;
				}
				if (helper_string == "lmode") {
					target = lmode;
				}
				if (helper_string == "barmode") {
					target = barmode;
				}

				save >> group;

				save >> something_else;

				Detector* add = new Detector(x, y, id, rotation, target, group, something_else);

				add[0].box.setOrigin(64, 64);

				map_basic.push_back(add);

			}
			if (helper_string == "View_det") {

				save >> rotation;
				save >> helper_string;

				if (helper_string == "dmode") {
					target = dmode;
				}
				if (helper_string == "crystal") {
					target = crystal;
				}
				if (helper_string == "lmode") {
					target = lmode;
				}
				if (helper_string == "barmode") {
					target = barmode;
				}

				save >> group;

				View_det* add = new View_det(x, y, id, rotation, target, group);

				add[0].box.setOrigin(64, 64);

				map_basic.push_back(add);

			}
			if (helper_string == "Speed_det") {

				save >> rotation;
				save >> helper_string;

				if (helper_string == "dmode") {
					target = dmode;
				}
				if (helper_string == "crystal") {
					target = crystal;
				}
				if (helper_string == "lmode") {
					target = lmode;
				}
				if (helper_string == "barmode") {
					target = barmode;
				}

				save >> group;

				Speed_det* add = new Speed_det(x, y, id, rotation, target, group);

				add[0].box.setOrigin(64, 64);

				map_basic.push_back(add);

			}
			if (helper_string == "Error") {
				while (helper_string != "Movables") {
					save >> helper_string;
				}
				break;
			}

			save >> helper_string;

			save >> helper_string;

			if (helper_string != "[") { break; }

		}
		logg << "Map_Basic has been loaded" << endl;

		save >> helper_string;

		while (true) {

			if (helper_string != "[") { break; }

			save >> x;
			save >> y;
			save >> look;

			Movable* add = new Movable(x, y, look);

			movables.push_back(add);

			save >> helper_string;
			save >> helper_string;

		}
		logg << "Movables has been loaded" << endl;

		save >> helper_string;

		while (true) {

			if (helper_string != "[") { break; }

			save >> id;
			save >> x;
			save >> y;

			helper_string = getType(id, 1);

			if (helper_string == "Basic_floor") {

				save >> rotation;
				save >> look;

				Basic_floor* add = new Basic_floor(x, y, id, rotation, look);

				add[0].box.setOrigin(64, 64);

				map_floor.push_back(add);

			}
			if (helper_string == "Door") {

				save >> rotation;
				save >> helper_string;

				if (helper_string == "dmode") {
					target = dmode;
				}
				if (helper_string == "crystal") {
					target = crystal;
				}
				if (helper_string == "lmode") {
					target = lmode;
				}
				if (helper_string == "barmode") {
					target = barmode;
				}

				save >> group;

				save >> something_else;

				Door* add = new Door(x, y, id, rotation, target, group, something_else);

				add[0].box.setOrigin(64, 64);

				map_floor.push_back(add);
			}
			if (helper_string == "Portal") {
				save >> helper;

				Portal* add = new Portal(x, y, id, helper);

				map_floor.push_back(add);
			}
			if (helper_string == "Floor_button") {

				save >> rotation;
				save >> helper_string;

				if (helper_string == "dmode") {
					target = dmode;
				}
				if (helper_string == "crystal") {
					target = crystal;
				}
				if (helper_string == "lmode") {
					target = lmode;
				}
				if (helper_string == "barmode") {
					target = barmode;
				}

				save >> group;
				bool biba; int boba;
				save >> boba;
				biba = bool(boba);

				Floor_button* add = new Floor_button(x, y, id, rotation, target, group, biba);

				add[0].box.setOrigin(64, 64);

				map_floor.push_back(add);
			}
			if (helper_string == "Special_floor") {

				save >> rotation;
				save >> look;

				Special_floor* add = new Special_floor(x, y, id, rotation, look);

				add[0].box.setOrigin(64, 64);

				map_floor.push_back(add);

			}

			if (helper_string == "Camera_trigger") {

				int size = 128;
				save >> size;

				Camera_trigger* add = new Camera_trigger(id, x, y, size);
				/*map_floor.push_back(add);*/
				triggers.push_back(add);
			}
			if (helper_string == "Blind_trigger") {

				int size = 128;
				save >> size;

				Blind_trigger* add = new Blind_trigger(id, x, y, size);
				/*map_floor.push_back(add);*/
				triggers.push_back(add);
			}
			if (helper_string == "Portal_trigger") {

				int size = 128, dx = 0, dy = 0;
				save >> size;

				save >> dx;
				save >> dy;

				Portal_trigger* add = new Portal_trigger(id, x, y, size, dx, dy);
				triggers.push_back(add);
			}
			if (helper_string == "Player_size_trigger") {

				int size = 128; float ds = 0;
				save >> size;

				save >> ds;

				Player_size_trigger* add = new Player_size_trigger(id, x, y, size, ds);
				triggers.push_back(add);
			}
			if (helper_string == "Text_Block") {

				string teeext;
				save >> teeext;

				Text_Block* add = new Text_Block(id,x,y,teeext);
				triggers.push_back(add);
			}

			if (helper_string == "Error") {
				while (helper_string != "Electric") {
					save >> helper_string;
				}
				break;
			}

			save >> helper_string;
			save >> helper_string;

		}
		logg << "Map_floor has been loaded" << endl;

		save >> helper_string;

		while (true) {

			if (helper_string != "[") { break; }

			save >> id;
			save >> x;
			save >> y;
			save >> rotation;

			helper_string = getType(id, 1);

			if (helper_string == "Wire") {
				Wire* add = new Wire(x, y, rotation, id);

				electric.push_back(add);
			}
			if (helper_string == "Generator") {
				save >> something_else;
				Generator* add = new Generator(x, y, rotation, id, something_else);

				electric.push_back(add);
			}
			if (helper_string == "Switcher") {

				save >> helper_string;

				if (helper_string == "dmode") {
					target = dmode;
				}
				if (helper_string == "crystal") {
					target = crystal;
				}
				if (helper_string == "lmode") {
					target = lmode;
				}
				if (helper_string == "barmode") {
					target = barmode;
				}

				save >> group;

				Switcher* add = new Switcher(x, y, rotation, id, target, group);

				electric.push_back(add);
			}
			if (helper_string == "Switcher2") {
				save >> helper_string;

				if (helper_string == "dmode") {
					target = dmode;
				}
				if (helper_string == "crystal") {
					target = crystal;
				}
				if (helper_string == "lmode") {
					target = lmode;
				}
				if (helper_string == "barmode") {
					target = barmode;
				}

				save >> group;

				save >> something_else;

				Switcher2* add = new Switcher2(x, y, rotation, id, target, group, something_else);

				electric.push_back(add);
			}
			if (helper_string == "Ac") {
				save >> helper_string;

				if (helper_string == "dmode") {
					target = dmode;
				}
				if (helper_string == "crystal") {
					target = crystal;
				}
				if (helper_string == "lmode") {
					target = lmode;
				}
				if (helper_string == "barmode") {
					target = barmode;
				}

				save >> group;

				Ac* add = new Ac(x, y, rotation, id, target, group);

				electric.push_back(add);
			}
			if (helper_string == "El_detector") {

				save >> helper_string;

				if (helper_string == "dmode") {
					target = dmode;
				}
				if (helper_string == "crystal") {
					target = crystal;
				}
				if (helper_string == "lmode") {
					target = lmode;
				}
				if (helper_string == "barmode") {
					target = barmode;
				}

				save >> group;

				El_Detector* add = new El_Detector(x, y, rotation, id, target, group);

				electric.push_back(add);
			}
			if (helper_string == "El_button") {

				save >> something_else;

				El_button* add = new El_button(x, y, rotation, something_else);

				electric.push_back(add);
			}
			if (helper_string == "Error") {
				while (helper_string != "PLayer") {
					save >> helper_string;
				}
				break;
			}

			save >> helper_string;
			save >> helper_string;

		}

		break;
	}

	save >> px;
	save >> py;

	for (i = 0; i < 999; i++) {
		save >> (dmode[i]);
		save >> (crystal[i]);
		save >> (lmode[i]);
		save >> (barmode[i]);
	}

	save >> player_scale;

	save >> lvlnum;
	save >> current_filename;

	p.unset_player();
	p.size *= player_scale;
	p.repulsion /= player_scale;
	p.repulsion /= player_scale;
	p.repulsion /= player_scale;
	p.init_AABB();

	logg << "	Success! \n";

	stop_physics = false;

	save.close();

}

void clear_lvl() {

	stop_physics = true;
	Sleep(150 + 150);

	map_basic.clear();
	map_floor.clear();
	movables.clear();
	electric.clear();

	stop_physics = false;

	logg << "LEVEL CLEARED" << endl;
}

void build(int l) {

	stop_physics = true;

	Sleep(100);

	logg << "	Level building " + to_string(l) << "...\n";

	reload_textures();

	helper = 0;
	coins_gathered = 0;
	coins_required = 0;
	helper_s[0] = 0;
	helper_s[1] = 0;
	player_scale = 1;
	save_options();
	alpha = 255;
	p.unset_player();

	if (l == 36) {
		end();
	}

	for (i = 0; i < 999; i++) {
		dmode[i] = false;
		crystal[i] = false;
		lmode[i] = false;
		barmode[i] = false;
	}

	map_basic.clear();
	map_floor.clear();
	movables.clear();
	electric.clear();
	triggers.clear();

	for (i = 0; i < 5; i++) {
		tx[i] = -20000; ty[i] = -20000;
		spiral[i].setPosition(-300, -300);
	}

	helper_string = lvl_name;

	if (l > 0) { helper_string = "Levels\\" + to_string(l); }
	if (l == -2 || l == -3) {
		helper_string = current_filename;
	}
	if (l == -1) {
		helper_string = "Levels\\1";
	}
	if (l == 2) { music.stop(); }

	int id, rotation, look, group;
	bool* target = dmode; bool something_else;
	float x, y;

	current_filename = helper_string;

	ifstream save;
	save.open(helper_string);

	save >> lvl_name;
	save >> helper_string;

	while (true) {

		save >> helper_string;

		while (true) {

			save >> id;
			save >> x;
			save >> y;

			helper_string = getType(id, 0);

			if (helper_string == "Basic") {

				save >> rotation;
				save >> look;

				Basic* add = new Basic(x, y, id, rotation, look);

				add[0].box.setOrigin(64, 64);

				map_basic.push_back(add);
			}
			if (helper_string == "Activators") {

				save >> rotation;
				save >> helper_string;

				if (helper_string == "dmode") {
					target = dmode;
				}
				if (helper_string == "crystal") {
					target = crystal;
				}
				if (helper_string == "lmode") {
					target = lmode;
				}
				if (helper_string == "barmode") {
					target = barmode;
				}

				save >> group;

				save >> something_else;

				Activators* add = new Activators(x, y, id, rotation, target, group, something_else);

				add[0].box.setOrigin(64, 64);

				map_basic.push_back(add);
			}
			if (helper_string == "Questions") {

				save >> rotation;
				save >> look;

				Questions* add = new Questions(x, y, id, rotation, look);

				add[0].box.setOrigin(64, 64);

				map_basic.push_back(add);
			}
			if (helper_string == "Special") {

				save >> rotation;
				save >> look;

				Special* add = new Special(x, y, id, rotation, look);

				add[0].box.setOrigin(64, 64);

				map_basic.push_back(add);

			}
			if (helper_string == "Detector") {

				save >> rotation;
				save >> helper_string;

				if (helper_string == "dmode") {
					target = dmode;
				}
				if (helper_string == "crystal") {
					target = crystal;
				}
				if (helper_string == "lmode") {
					target = lmode;
				}
				if (helper_string == "barmode") {
					target = barmode;
				}

				save >> group;

				save >> something_else;

				Detector* add = new Detector(x, y, id, rotation, target, group, something_else);

				add[0].box.setOrigin(64, 64);

				map_basic.push_back(add);

			}
			if (helper_string == "View_det") {

				save >> rotation;
				save >> helper_string;

				if (helper_string == "dmode") {
					target = dmode;
				}
				if (helper_string == "crystal") {
					target = crystal;
				}
				if (helper_string == "lmode") {
					target = lmode;
				}
				if (helper_string == "barmode") {
					target = barmode;
				}

				save >> group;

				View_det* add = new View_det(x, y, id, rotation, target, group);

				add[0].box.setOrigin(64, 64);

				map_basic.push_back(add);

			}
			if (helper_string == "Speed_det") {

				save >> rotation;
				save >> helper_string;

				if (helper_string == "dmode") {
					target = dmode;
				}
				if (helper_string == "crystal") {
					target = crystal;
				}
				if (helper_string == "lmode") {
					target = lmode;
				}
				if (helper_string == "barmode") {
					target = barmode;
				}

				save >> group;

				Speed_det* add = new Speed_det(x, y, id, rotation, target, group);

				add[0].box.setOrigin(64, 64);

				map_basic.push_back(add);

			}

			if (helper_string == "Error") {
				while (helper_string != "Movables") {
					save >> helper_string;
				}
				break;
			}

			save >> helper_string;

			save >> helper_string;

			if (helper_string != "[") { break; }

		}
		logg << "Map_Basic has been loaded" << endl;

		save >> helper_string;

		while (true) {

			if (helper_string != "[") { break; }

			save >> x;
			save >> y;
			save >> look;

			Movable* add = new Movable(x, y, look);

			movables.push_back(add);

			save >> helper_string;
			save >> helper_string;

		}
		logg << "Movables has been loaded" << endl;

		save >> helper_string;

		while (true) {

			if (helper_string != "[") { break; }

			save >> id;
			save >> x;
			save >> y;

			helper_string = getType(id, 1);

			if (helper_string == "Basic_floor") {

				save >> rotation;
				save >> look;

				Basic_floor* add = new Basic_floor(x, y, id, rotation, look);

				add[0].box.setOrigin(64, 64);

				map_floor.push_back(add);

			}
			if (helper_string == "Door") {

				save >> rotation;
				save >> helper_string;

				if (helper_string == "dmode") {
					target = dmode;
				}
				if (helper_string == "crystal") {
					target = crystal;
				}
				if (helper_string == "lmode") {
					target = lmode;
				}
				if (helper_string == "barmode") {
					target = barmode;
				}

				save >> group;

				save >> something_else;

				Door* add = new Door(x, y, id, rotation, target, group, something_else);

				add[0].box.setOrigin(64, 64);

				map_floor.push_back(add);
			}
			if (helper_string == "Portal") {
				save >> helper;

				Portal* add = new Portal(x, y, id, helper);

				map_floor.push_back(add);
			}
			if (helper_string == "Floor_button") {

				save >> rotation;
				save >> helper_string;

				if (helper_string == "dmode") {
					target = dmode;
				}
				if (helper_string == "crystal") {
					target = crystal;
				}
				if (helper_string == "lmode") {
					target = lmode;
				}
				if (helper_string == "barmode") {
					target = barmode;
				}

				save >> group;
				bool biba; int boba;
				save >> boba;
				biba = bool(boba);

				Floor_button* add = new Floor_button(x, y, id, rotation, target, group, biba);

				add[0].box.setOrigin(64, 64);

				map_floor.push_back(add);
			}
			if (helper_string == "Special_floor") {

				save >> rotation;
				save >> look;

				Special_floor* add = new Special_floor(x, y, id, rotation, look);

				add[0].box.setOrigin(64, 64);

				map_floor.push_back(add);

			}

			if (helper_string == "Camera_trigger") {

				int size = 128;
				save >> size;

				Camera_trigger* add = new Camera_trigger(id, x, y, size);
				//map_floor.push_back(add);
				triggers.push_back(add);
			}
			if (helper_string == "Blind_trigger") {

				int size = 128;
				save >> size;

				Blind_trigger* add = new Blind_trigger(id, x, y, size);
				/*map_floor.push_back(add);*/
				triggers.push_back(add);
			}
			if (helper_string == "Portal_trigger") {

				int size = 128, dx = 0, dy = 0;
				save >> size;

				save >> dx;
				save >> dy;

				Portal_trigger* add = new Portal_trigger(id, x, y, size, dx, dy);
				triggers.push_back(add);
			}
			if (helper_string == "Player_size_trigger") {

				int size = 128; float ds = 0;
				save >> size;

				save >> ds;

				Player_size_trigger* add = new Player_size_trigger(id, x, y, size, ds);
				triggers.push_back(add);
			}
			if (helper_string == "Text_Block") {

				string teeext;
				save >> teeext;

				Text_Block* add = new Text_Block(id, x, y, teeext);
				triggers.push_back(add);
			}

			if (helper_string == "Error") {
				while (helper_string != "Electric") {
					save >> helper_string;
				}
				break;
			}

			save >> helper_string;
			save >> helper_string;

		}
		logg << "Map_floor has been loaded" << endl;

		save >> helper_string;

		while (true) {

			if (helper_string != "[") { break; }

			save >> id;
			save >> x;
			save >> y;
			save >> rotation;

			helper_string = getType(id, 1);

			if (helper_string == "Wire") {
				Wire* add = new Wire(x, y, rotation, id);

				electric.push_back(add);
			}
			if (helper_string == "Generator") {
				save >> something_else;
				Generator* add = new Generator(x, y, rotation, id, something_else);

				electric.push_back(add);
			}
			if (helper_string == "Switcher") {

				save >> helper_string;

				if (helper_string == "dmode") {
					target = dmode;
				}
				if (helper_string == "crystal") {
					target = crystal;
				}
				if (helper_string == "lmode") {
					target = lmode;
				}
				if (helper_string == "barmode") {
					target = barmode;
				}

				save >> group;

				Switcher* add = new Switcher(x, y, rotation, id, target, group);

				electric.push_back(add);
			}
			if (helper_string == "Switcher2") {
				save >> helper_string;

				if (helper_string == "dmode") {
					target = dmode;
				}
				if (helper_string == "crystal") {
					target = crystal;
				}
				if (helper_string == "lmode") {
					target = lmode;
				}
				if (helper_string == "barmode") {
					target = barmode;
				}

				save >> group;

				save >> something_else;

				Switcher2* add = new Switcher2(x, y, rotation, id, target, group, something_else);

				electric.push_back(add);
			}
			if (helper_string == "Ac") {
				save >> helper_string;

				if (helper_string == "dmode") {
					target = dmode;
				}
				if (helper_string == "crystal") {
					target = crystal;
				}
				if (helper_string == "lmode") {
					target = lmode;
				}
				if (helper_string == "barmode") {
					target = barmode;
				}

				save >> group;

				Ac* add = new Ac(x, y, rotation, id, target, group);

				electric.push_back(add);
			}
			if (helper_string == "El_detector") {

				save >> helper_string;

				if (helper_string == "dmode") {
					target = dmode;
				}
				if (helper_string == "crystal") {
					target = crystal;
				}
				if (helper_string == "lmode") {
					target = lmode;
				}
				if (helper_string == "barmode") {
					target = barmode;
				}

				save >> group;

				El_Detector* add = new El_Detector(x, y, rotation, id, target, group);

				electric.push_back(add);
			}
			if (helper_string == "El_button") {

				save >> something_else;

				El_button* add = new El_button(x, y, rotation, something_else);

				electric.push_back(add);
			}
			if (helper_string == "Error") {
				while (helper_string != "PLayer") {
					save >> helper_string;
				}
				break;
			}

			save >> helper_string;
			save >> helper_string;

		}

		break;
	}

	save >> px;
	save >> py;

	scrollx = px - screenw / 2;
	scrolly = py - screenh / 2;

	p.init_AABB();

	playerS.setPosition(scale * (px - scrollx), scale * (py - scrolly));

	save.close();

	for (i = 0; i < electric.size(); i++) {

		Sq a;
		a.size = 40;
		a.x = electric[i]->x; a.y = electric[i]->y;
		a.init_AABB();

		int x = a.x; int y = a.y; int rotation = electric[i]->box.getRotation();
		int* connections = new int[4];
		int group = electric[i]->group;

		connections[0] = 0; connections[1] = 0; connections[2] = 0; connections[3] = 0;

		switch (electric[i]->id) {

		case 25:

			for (j = 0; j < electric.size(); j++) {
				if (i == j) { continue; }
				a.x = electric[i]->x; a.y = electric[i]->y;
				switch (rotation) {
				case 0:

					a.x -= 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}

					break;

				case 90:

					a.y -= 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}
					break;

				case 180:

					a.x += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}
					break;

				case 270:

					a.y += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}
					break;

				}
			}

			electric[i]->set_connections(connections);

			break;

		case 26:

			for (j = 0; j < electric.size(); j++) {
				if (i == j) { continue; }
				a.x = electric[i]->x; a.y = electric[i]->y;

				if (rotation % 180 == 90) {

					a.y += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}

					a.y -= 100;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[1] = j;
					}

				}
				else {

					a.x += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}

					a.x -= 100;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[1] = j;
					}

				}

			}

			electric[i]->set_connections(connections);

			break;

		case 27:

			for (j = 0; j < electric.size(); j++) {
				if (i == j) { continue; }
				a.x = electric[i]->x; a.y = electric[i]->y;

				switch (rotation) {
				case 0:

					a.x -= 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}

					a.y -= 50; a.x += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[1] = j;
					}

					break;

				case 90:

					a.x += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}

					a.y -= 50; a.x -= 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[1] = j;
					}

					break;

				case 180:

					a.x += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}

					a.y += 50; a.x -= 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[1] = j;
					}
					break;

				case 270:

					a.x -= 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}

					a.y += 50; a.x += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[1] = j;
					}
					break;

				}
			}

			electric[i]->set_connections(connections);

			break;

		case 28:

			for (j = 0; j < electric.size(); j++) {
				if (i == j) { continue; }
				a.x = electric[i]->x; a.y = electric[i]->y;

				switch (rotation) {
				case 0:

					a.x -= 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}

					a.y -= 50; a.x += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[1] = j;
					}

					a.y += 50; a.x += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[2] = j;
					}

					break;

				case 90:

					a.y += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}

					a.y -= 50; a.x += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[1] = j;
					}

					a.y -= 50; a.x -= 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[2] = j;
					}

					break;

				case 180:

					a.x -= 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}

					a.y += 50; a.x += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[1] = j;
					}

					a.y -= 50; a.x += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[2] = j;
					}

					break;

				case 270:

					a.y += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}

					a.y -= 50; a.x -= 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[1] = j;
					}

					a.y -= 50; a.x += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[2] = j;
					}

					break;

				}

			}

			electric[i]->set_connections(connections);

			break;

		case 29:

			for (j = 0; j < electric.size(); j++) {
				if (i == j) { continue; }
				a.x = electric[i]->x; a.y = electric[i]->y;

				a.x -= 50;
				a.init_AABB();

				if (intersection(a, *electric[j])) {
					connections[0] = j;
				}

				a.y -= 50; a.x += 50;
				a.init_AABB();

				if (intersection(a, *electric[j])) {
					connections[1] = j;
				}

				a.x += 50; a.y += 50;
				a.init_AABB();

				if (intersection(a, *electric[j])) {
					connections[2] = j;
				}

				a.y += 50; a.x -= 50;

				if (intersection(a, *electric[j])) {
					connections[3] = j;
				}
			}

			electric[i]->set_connections(connections);

			break;

		case 30:

			for (j = 0; j < electric.size(); j++) {
				if (i == j) { continue; }
				a.x = electric[i]->x; a.y = electric[i]->y;

				switch (rotation) {
				case 0:

					a.x -= 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}
					break;

				case 90:

					a.y -= 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}
					break;

				case 180:

					a.x += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}
					break;

				case 270:

					a.y += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}
					break;

				}
			}

			electric[i]->set_connections(connections);

			break;

		case 31:

			for (j = 0; j < electric.size(); j++) {
				if (i == j) { continue; }
				a.x = electric[i]->x; a.y = electric[i]->y;

				switch (rotation) {
				case 0:

					a.x -= 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}

					break;

				case 90:

					a.y -= 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}
					break;

				case 180:

					a.x += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}
					break;

				case 270:

					a.y += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}
					break;

				}
			}


			electric[i]->set_connections(connections);

			break;

		case 32:

			for (j = 0; j < electric.size(); j++) {
				if (i == j) { continue; }
				a.x = electric[i]->x; a.y = electric[i]->y;

				if (rotation % 180 == 90) {

					a.y += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}

					a.y -= 100;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[1] = j;
					}

				}
				else {

					a.x += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}

					a.x -= 100;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[1] = j;
					}

				}

			}

			electric[i]->set_connections(connections);

			break;

		case 33:

			for (j = 0; j < electric.size(); j++) {
				if (i == j) { continue; }
				a.x = electric[i]->x; a.y = electric[i]->y;

				switch (rotation) {
				case 0:

					a.x -= 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}

					a.y -= 50; a.x += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[1] = j;
					}

					a.y += 50; a.x += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[2] = j;
					}

					break;

				case 90:

					a.y += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[2] = j;
					}

					a.y -= 50; a.x += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[1] = j;
					}

					a.y -= 50; a.x -= 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}

					break;

				case 180:

					a.x -= 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[2] = j;
					}

					a.y += 50; a.x += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[1] = j;
					}

					a.y -= 50; a.x += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}

					break;

				case 270:

					a.y += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}

					a.y -= 50; a.x -= 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[1] = j;
					}

					a.y -= 50; a.x += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[2] = j;
					}

					break;

				}

			}

			electric[i]->set_connections(connections);

			break;

		case 34:

			for (j = 0; j < electric.size(); j++) {
				if (i == j) { continue; }
				a.x = electric[i]->x; a.y = electric[i]->y;

				if (rotation % 180 == 90) {

					a.y += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}

					a.y -= 100;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[1] = j;
					}

				}
				else {

					a.x += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}

					a.x -= 100;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[1] = j;
					}

				}

			}

			electric[i]->set_connections(connections);

			break;

		case 35:

			for (j = 0; j < electric.size(); j++) {
				if (i == j) { continue; }
				a.x = electric[i]->x; a.y = electric[i]->y;

				if (rotation % 180 == 90) {

					a.y += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}

					a.y -= 100;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[1] = j;
					}

				}
				else {

					a.x += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}

					a.x -= 100;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[1] = j;
					}

				}

			}

			electric[i]->set_connections(connections);

			break;

		case 36:

			for (j = 0; j < electric.size(); j++) {
				if (i == j) { continue; }
				a.x = electric[i]->x; a.y = electric[i]->y;

				if (rotation % 180 == 90) {

					a.y += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}

					a.y -= 100;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[1] = j;
					}

				}
				else {

					a.x += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}

					a.x -= 100;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[1] = j;
					}

				}

			}

			electric[i]->set_connections(connections);

			break;

		case 37:

			for (j = 0; j < electric.size(); j++) {
				if (i == j) { continue; }
				a.x = electric[i]->x; a.y = electric[i]->y;
				switch (rotation) {
				case 0:

					a.x -= 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}

					break;

				case 90:

					a.y -= 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}
					break;

				case 180:

					a.x += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}
					break;

				case 270:

					a.y += 50;
					a.init_AABB();

					if (intersection(a, *electric[j])) {
						connections[0] = j;
					}
					break;

				}
			}

			electric[i]->set_connections(connections);

			break;

		case 46:

			electric[i]->set_connections(connections);

			break;

		}

	}

	helper = 0;

	helper_string = lvl_name;

	if ((!onclick) && (lvlnum == 1 || lvlnum == 2 || lvlnum == 15 || lvlnum == 16 || lvlnum == 23 || lvlnum == 24 || lvlnum == 31)) {
		music.stop();
	}

	if (lvlnum != -3) { lvlnum = l; }

	stop_physics = (mode != "game");

	logg << "	The level was built \n";

}
