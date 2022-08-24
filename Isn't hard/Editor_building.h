#pragma once

#include "Values.h"
#include "Blocks.h"
#include "Level_building.h"

int getLook() {

	if (editor_layer == 0) {

		if (editor_block == 1) {
			return rand() % 6;
		}

		if (editor_block == 5) {
			if (E_B.is_checked) {
				return 2;
			}
			if (E_R.is_checked) {
				return 0;
			}
			if (E_Gr.is_checked) {
				return 1;
			}
			if (E_Gy.is_checked) {
				return 3;
			}
		}

		if (getType(editor_block, 0) == "Questions") {

			if (editor_block == 29) {
				return 0;
			}

			if (E_B.is_checked) {
				return 1;
			}
			if (E_R.is_checked) {
				return 3;
			}
			if (E_Gr.is_checked) {
				return 2;
			}
			if (E_Gy.is_checked) {
				return 0;
			}

		}

	}

	if (editor_layer == 1) {
		if (editor_block == 9 || editor_block == 12) {
			return rand() % 6;
		}
		if (editor_block == 18) {
			return last_group;
		}
	}

	return 0;

}

bool* getTarget() {

	if (editor_layer == 1) {

		if (editor_block == 2 || editor_block == 3 || editor_block == 17) {
			return dmode;
		}
		if (editor_block == 15 || editor_block == 16) {
			return crystal;
		}
		if (editor_block == 23 || editor_block == 24) {
			return lmode;
		}
		if (editor_block == 38 || editor_block == 39 || editor_block == 40 || editor_block == 41) {
			return barmode;
		}

		return lmode;

	}
	if (editor_layer == 0) {

		if (editor_block == 2 || editor_block == 26 || editor_block == 27) {
			return dmode;
		}
		if (editor_block == 15) {
			return crystal;
		}
		if (editor_block == 24) {
			return lmode;
		}		
		if (editor_block == 28 || editor_block == 30) {
			return barmode;
		}

	}

	return dmode;
}

bool getReverse() {

	if (editor_layer == 0) {
		
	}

	if (editor_layer == 1) {
		if (editor_block == 2) { return false; }
		if (editor_block == 3) { return true; }
		if (editor_block == 15) { return false; }
		if (editor_block == 16) { return true; }
		if (editor_block == 23) { return false; }
		if (editor_block == 24) { return true; }
		if (editor_block == 38) { return false; }
		if (editor_block == 39) { return true; }
		if (editor_block == 40) { return false; }
		if (editor_block == 41) { return true; }
	}

	return false;
}

void place_block(int x, int  y) {

	int rotation = last_angle;
	int group = last_group;

	int id = editor_block;
	int look = getLook();

	helper_string = getType(editor_block, editor_layer);

	if (helper_string == "Basic") {

		if (id == 1) {
			rotation = (rand() % 4) * 90;
		}

		Basic* add = new Basic(x, y, id, rotation, look);

		add[0].box.setOrigin(64, 64);

		map_basic.push_back(add);
		chosen = add;
	}
	if (helper_string == "Activators") {

		bool if_crystal = (id == 15);

		Activators* add = new Activators(x, y, id, rotation, getTarget(), group, if_crystal);

		add[0].box.setOrigin(64, 64);

		map_basic.push_back(add);
		chosen = add;
	}
	if (helper_string == "Questions") {

		Questions* add = new Questions(x, y, id, 0, look);

		add[0].box.setOrigin(64, 64);

		map_basic.push_back(add);
		chosen = add;
	}
	if (helper_string == "Special") {

		Special* add = new Special(x, y, id, rotation, look);

		add[0].box.setOrigin(64, 64);

		map_basic.push_back(add);
		chosen = add;
	}
	if (helper_string == "Detector") {

		bool if_change = (id == 27);

		Detector* add = new Detector(x, y, id, rotation, getTarget(), group, if_change);

		add[0].box.setOrigin(64, 64);

		map_basic.push_back(add);
		chosen = add;
	}
	if (helper_string == "View_det") {

		View_det* add = new View_det(x, y, id, rotation, getTarget(), group);

		add[0].box.setOrigin(64, 64);

		map_basic.push_back(add);
		chosen = add;
	}
	if (helper_string == "Speed_det") {

		Speed_det* add = new Speed_det(x, y, id, rotation, getTarget(), group);

		add[0].box.setOrigin(64, 64);

		map_basic.push_back(add);
		chosen = add;
	}
	if (helper_string == "Movable_spawn") {
		Movable* add = new Movable(x, y, look);

		add[0].box.setOrigin(64, 64);

		movables.push_back(add); chosen = add;
		Sleep(10);
	}

	if (helper_string == "Basic_floor") {

		if (id == 1) {
			rotation = (rand() % 4) * 90;
		}

		Basic_floor* add = new Basic_floor(x, y, id, rotation, look);

		add[0].box.setOrigin(64, 64);

		map_floor.push_back(add);
		chosen = add;

	}
	if (helper_string == "Door") {

		Door* add = new Door(x, y, id, rotation, getTarget(), group, getReverse());

		add[0].box.setOrigin(64, 64);

		map_floor.push_back(add);
		chosen = add;
	}
	if (helper_string == "Portal") {

		Portal* add = new Portal(x, y, id, 0);

		map_floor.push_back(add); chosen = add;
	}
	if (helper_string == "Floor_button") {

		Floor_button* add = new Floor_button(x, y, id, rotation, getTarget(), group, false);

		add[0].box.setOrigin(64, 64);

		map_floor.push_back(add); chosen = add;
	}
	if (helper_string == "Special_floor") {

		Special_floor* add = new Special_floor(x, y, id, rotation, look);

		add[0].box.setOrigin(64, 64);

		map_floor.push_back(add); chosen = add;

	}

	if (helper_string == "Camera_trigger") {

		Camera_trigger* add = new Camera_trigger(id, x, y, last_size);

		/*map_floor.push_back(add);*/
		triggers.push_back(add); chosen = add;
	}
	if (helper_string == "Blind_trigger") {

		Blind_trigger* add = new Blind_trigger(id, x, y, last_size);
		/*map_floor.push_back(add);*/
		triggers.push_back(add); chosen = add;
	}
	if (helper_string == "Portal_trigger") {

		Portal_trigger* add = new Portal_trigger(id, x, y, 256,512,128);
		triggers.push_back(add); chosen = add;
	}
	if (helper_string == "Player_size_trigger") {

		Player_size_trigger* add = new Player_size_trigger(id, x, y, last_size, 1.2);
		triggers.push_back(add);
	}
	if (helper_string == "Text_Block") {

		Text_Block* add = new Text_Block(id, x, y, "Text");
		triggers.push_back(add); chosen = add; editor_mode = 4;
	}

	if (helper_string == "Wire") {
		Wire* add = new Wire(x, y, rotation, id);

		electric.push_back(add); chosen = add;
	}
	if (helper_string == "Generator") {

		Generator* add = new Generator(x, y, rotation, id, id == 30);

		electric.push_back(add); chosen = add;
	}
	if (helper_string == "Switcher") {

		Switcher* add = new Switcher(x, y, rotation, id, getTarget(), group);

		electric.push_back(add); chosen = add;
	}
	if (helper_string == "Switcher2") {

		Switcher2* add = new Switcher2(x, y, rotation, id, getTarget(), group, id == 35);

		electric.push_back(add); chosen = add;
	}
	if (helper_string == "Ac") {

		Ac* add = new Ac(x, y, rotation, id, getTarget(), group);

		electric.push_back(add); chosen = add;
	}
	if (helper_string == "El_detector") {

		El_Detector* add = new El_Detector(x, y, rotation, id, getTarget(), group);

		electric.push_back(add); chosen = add;
	}
	if (helper_string == "El_button") {

		//save >> something_else;

		El_button* add = new El_button(x, y, rotation, false);

		electric.push_back(add); chosen = add;
	}

	if (helper_string == "Error") {
		Basic* add = new Basic(x, y, 1, rotation, look);

		add[0].box.setOrigin(64, 64);

		map_basic.push_back(add); chosen = add;

		logg << "Error : can't place unknown blocktype" << endl;
	}
	//error

}
