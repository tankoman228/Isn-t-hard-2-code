
#include <Values.h>
#include <Blocks.h>
#include <Level_building.h>
#include <Editor_building.h>
#include <Voids.h>

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

	if (helper_string == "Wall") {

		if (id == 1) {
			rotation = (rand() % 4) * 90;
		}

		Wall* add = new Wall(x, y, id, rotation, look);

		add[0].box.setOrigin(64, 64);

		map_basic.push_back(add);
		chosen = add;
	}
	if (helper_string == "Switcher") {

		bool if_crystal = (id == 15);

		Switcher* add = new Switcher(x, y, id, rotation, getTarget(), group, if_crystal);

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
	if (helper_string == "ElectricSwitcher") {

		ElectricSwitcher* add = new ElectricSwitcher(x, y, rotation, id, getTarget(), group);

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
		Wall* add = new Wall(x, y, 1, rotation, look);

		add[0].box.setOrigin(64, 64);

		map_basic.push_back(add); chosen = add;

		logg << "Error : can't place unknown blocktype" << endl;
	}
	//error

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

void render_block_UI(int screenh, int ID, int i) {
	// TODO: // TODO: block.setTexture(cur);
	block.setPosition(128 * UI_scale * i + editor_scroll * UI_scale, screenh - 128 * UI_scale);
	if (editor_layer == 0) {
		switch (ID) {
		case 1:
			// TODO: // TODO: block.setTexture(blue);
			break;
		case 2:
			// TODO: // TODO: block.setTexture(switch_t);
			break;
		case 3:
			//the secret coin
			// TODO: // TODO: block.setTexture(smth);
			switch (editor_choose) {
				case 1: // TODO: block.setTextureRect(IntRect(128, 0, 128, 128)); break;
				case 2: // TODO: block.setTextureRect(IntRect(384, 0, 128, 128)); break;
				case 3: // TODO: block.setTextureRect(IntRect(256, 0, 128, 128)); break;
				case 4: // TODO: block.setTextureRect(IntRect(0, 0, 128, 128)); 
				
				default: break;
			}
			break;
		case 4:
			//the secret (gathered)
			// TODO: // TODO: block.setTexture(smth2);
			switch (editor_choose) {
			case 1: // TODO: block.setTextureRect(IntRect(128, 0, 128, 128)); break;
			case 2: // TODO: block.setTextureRect(IntRect(384, 0, 128, 128)); break;
			case 3: // TODO: block.setTextureRect(IntRect(256, 0, 128, 128)); break;
			case 4: // TODO: block.setTextureRect(IntRect(0, 0, 128, 128)); break;
		default: break;	
		}
			break;
		case 5:
			//movable
			// TODO: // TODO: block.setTexture(movable);
			switch (editor_choose) {
			case 1: // TODO: block.setTextureRect(IntRect(256, 0, 128, 128)); break;
			case 2: // TODO: block.setTextureRect(IntRect(0, 0, 128, 128)); break;
			case 3: // TODO: block.setTextureRect(IntRect(128, 0, 128, 128)); break;
			case 4: // TODO: block.setTextureRect(IntRect(384, 0, 128, 128)); break;
		default: break;	
		}
			break;
		case 6:
			//the secret (smoke)
			// TODO: // TODO: block.setTexture(smth);
			switch (editor_choose) {
			case 1: // TODO: block.setTextureRect(IntRect(128, 0, 128, 128)); break;
			case 2: // TODO: block.setTextureRect(IntRect(384, 0, 128, 128)); break;
			case 3: // TODO: block.setTextureRect(IntRect(256, 0, 128, 128)); break;
			case 4: // TODO: block.setTextureRect(IntRect(0, 0, 128, 128)); break;
		default: break;	
		}
			break;
		case 7:
			//the wall
			// TODO: // TODO: block.setTexture(wall);
			break;
		case 8:
			//gray
			// TODO: block.setTexture(gr);
			break;
		case 9:
			//gray_wall
			// TODO: block.setTexture(grb);
			break;
		case 10:
			//greenn
			// TODO: block.setTexture(green);
			break;
		case 11:
			//green_wall
			// TODO: block.setTexture(greenw);
			break;
		case 12:
			// TODO: block.setTexture(roseb);
			break;
		case 13:
			// TODO: block.setTexture(rb);
			break;
		case 14:
			// TODO: block.setTexture(fl);
			break;
		case 15:
			// TODO: block.setTexture(crys); break;
		case 16:
			// TODO: block.setTexture(gravs);
			window.draw(block);
			// TODO: block.setTexture(grav);
			break;
		case 17:
			// TODO: block.setTexture(glass); break;
		case 18:
			//hidden block
			// TODO: block.setTexture(smth);
			switch (editor_choose) {
			case 1: // TODO: block.setTextureRect(IntRect(128, 0, 128, 128)); break;
			case 2: // TODO: block.setTextureRect(IntRect(384, 0, 128, 128)); break;
			case 3: // TODO: block.setTextureRect(IntRect(256, 0, 128, 128)); break;
			case 4: // TODO: block.setTextureRect(IntRect(0, 0, 128, 128)); break;
		default: break;	
		}
			break;
		case 19:
			//Closer
			// TODO: block.setTexture(smth);
			switch (editor_choose) {
			case 1: // TODO: block.setTextureRect(IntRect(128, 0, 128, 128)); break;
			case 2: // TODO: block.setTextureRect(IntRect(384, 0, 128, 128)); break;
			case 3: // TODO: block.setTextureRect(IntRect(256, 0, 128, 128)); break;
			case 4: // TODO: block.setTextureRect(IntRect(0, 0, 128, 128)); break;
		default: break;	
		}
			break;
		case 20:
			//Opener
			// TODO: block.setTexture(smth);
			switch (editor_choose) {
			case 1: // TODO: block.setTextureRect(IntRect(128, 0, 128, 128)); break;
			case 2: // TODO: block.setTextureRect(IntRect(384, 0, 128, 128)); break;
			case 3: // TODO: block.setTextureRect(IntRect(256, 0, 128, 128)); break;
			case 4: // TODO: block.setTextureRect(IntRect(0, 0, 128, 128)); break;
		default: break;	
		}
			break;
		case 21:
			// TODO: block.setTexture(smth3); break;
		case 22:
			// TODO: block.setTexture(white); break;
		case 23:
			// TODO: block.setTexture(whitewall); break;
		case 24:
			// TODO: block.setTexture(rosebut); break;
		case 25:
			// TODO: block.setTexture(rosebricks); break;
		case 26:
			// TODO: block.setTexture(player_det); break;
		case 27:
			// TODO: block.setTexture(player_det_inv); break;
		case 28:
			// TODO: block.setTexture(view_det); break;
		case 29:
			// TODO: block.setTexture(pusher); break;
		case 30:
			// TODO: block.setTexture(speed_det); break;
		case 100:
			// TODO: block.setTexture(t_camera); break;
		case 101:
			// TODO: block.setTexture(t_darkness); break;
		case 102:
			// TODO: block.setTexture(t_portal); break;
		case 103:
			// TODO: block.setTexture(t_player_size); break;		
		case 104:

		default: break;
			// TODO: block.setTexture(textblock); break;
		}

	}
	else {
		switch (ID) {
		case 1:
			// TODO: block.setTexture(el);
			break;
		case 2:
			// TODO: block.setTexture(door);
			// TODO: block.setTextureRect(IntRect(0, 0, 128, 128));
			break;
		case 3:
			// TODO: block.setTexture(door);
			// TODO: block.setTextureRect(IntRect(128, 0, 128, 128));
			break;
		case 4:
			// TODO: block.setTexture(str);
			break;
		case 5:
			// TODO: block.setTexture(corn);
			break;
		case 6:
			// TODO: block.setTexture(finon);
			break;
		case 7:
			// TODO: block.setTexture(port_in);
			break;
		case 8:
			// TODO: block.setTexture(port_o);
			break;
		case 9:
			// TODO: block.setTexture(gray); break;
		case 10:
			// TODO: block.setTexture(strp);
			if (editor_choose == 2) {
				// TODO: block.setTextureRect(IntRect(0, 0, 128, 128));
			}
			break;
		case 11:
			// TODO: block.setTexture(greenf); break;
		case 12:
			// TODO: block.setTexture(differ);
			break;
		case 13:
			// TODO: block.setTexture(rose); break;
		case 14:
			// TODO: block.setTexture(greenf2); break;
		case 15:
			// TODO: block.setTexture(act); break;
		case 16:
			// TODO: block.setTextureRect(IntRect(128, 0, 128, 128));
			// TODO: block.setTexture(act); break;
		case 17:
			// TODO: block.setTexture(buttonblock); // TODO: block.setTextureRect(IntRect(0, 0, 128, 128)); break;
		case 18:
			// TODO: block.setTexture(noth); break;
		case 19:
			// TODO: block.setTexture(_arrow); break;
		case 20:
			// TODO: block.setTexture(blue_floor2);
			break;
		case 21:
			// TODO: block.setTexture(rosefloor2);
			break;
		case 22:
			// TODO: block.setTexture(gray2);
			break;
		case 23:
			// TODO: block.setTexture(rose_door); break;
		case 24:
			// TODO: block.setTexture(rose_door);
			// TODO: block.setTextureRect(IntRect(128, 0, 128, 128)); break;

		case 25:
			// TODO: block.setTexture(c_one);
			break;
		case 26:
			// TODO: block.setTexture(c_line);
			break;
		case 27:
			// TODO: block.setTexture(c_corner);
			break;
		case 28:
			// TODO: block.setTexture(c_cross3);
			break;
		case 29:
			// TODO: block.setTexture(c_cross4);
			break;
		case 30:
			// TODO: block.setTexture(c_plus);
			break;
		case 31:
			// TODO: block.setTexture(c_minus);
			break;
		case 32:
			// TODO: block.setTexture(c_resist);
			break;
		case 33:
			// TODO: block.setTexture(c_switcher3);
			break;
		case 34:
			// TODO: block.setTexture(c_switch);
			break;
		case 35:
			// TODO: block.setTexture(c_switch_off);
			break;
		case 36:
			// TODO: block.setTexture(c_ac);
			break;
		case 37:
			// TODO: block.setTexture(c_sensor);
			break;
		case 38:
			// TODO: block.setTexture(lamp_blue); // TODO: block.setTextureRect(IntRect(0, 0, 128, 128)); break;
		case 39:
			// TODO: block.setTexture(lamp_blue); // TODO: block.setTextureRect(IntRect(128, 0, 128, 128)); break;
		case 40:
			// TODO: block.setTexture(lamp_green); // TODO: block.setTextureRect(IntRect(0, 0, 128, 128)); break;
		case 41:
			// TODO: block.setTexture(lamp_green); // TODO: block.setTextureRect(IntRect(128, 0, 128, 128)); break;
		case 42:
			// TODO: block.setTexture(void_el);
			break;
		case 43:
			// TODO: block.setTexture(portal2);
			break;
		case 45:
			// TODO: block.setTexture(position_detector);
			break;
		case 46:
			// TODO: block.setTexture(c_button);
			break;
		}
	}
	if (get_ID(i) == editor_block) { block.scale(0.8, 0.8); block.move(7, 7); }
	else { block.setScale(UI_scale / 1.1, UI_scale / 1.1); }
	window.draw(block);
	// TODO: block.setTextureRect(IntRect(0, 0, 128, 128));
}
