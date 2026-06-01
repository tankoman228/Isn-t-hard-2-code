#include <Loading.h>
#include <UI.h>
#include <Particles.h>
#include <Voids.h>

void loadTexture(const std::string key, const std::string& path) {
    Textures[key] = Texture();
    Textures[key].loadFromFile(path);
	Textures[key].setSmooth(true);
}

Texture* getTexture(const std::string& path) {
    auto t = new Texture();
    t->loadFromFile(path);
	return t;
}

void loading() {

	logg << "Loading \n";

	//Screen	

	float helper_s2;

	ifstream options;
	options.open("Options.txt");
	options >> partnum;
	options >> levels_opened;
	options >> helper_s2;
	options >> BG_particles_number;
	options.close();

	//loading some textures
	if ("textures" == "textures") {

		font.loadFromFile("Textures/Text.ttf");
		text.setFont(font);

		//somethings
		loadTexture("Eyes",   "Textures/Eyes.png");
		loadTexture("Player", "Textures/Player.png");
		loadTexture("Coin",   "Textures/Coin.png");
		loadTexture("Smoke",  "Textures/Smoke.png");
		loadTexture("Broken", "Textures/Broken.png");
		loadTexture("Choose", "Textures/Choose.png");
		loadTexture("Dark",   "Textures/Dark.png");
		loadTexture("cursor", "Textures/Choose.png");

		loadTexture("BG", "Textures/BG.png");
		Textures["BG"].setRepeated(true);

		loadTexture("Gray2", "Textures/Gray2.png"); // для текстуры в меню ачивок
		Textures["Gray2"].setRepeated(true);

		cursor.setTexture(Textures["cursor"]);
		cursor.setOrigin(8, 8);

		loadTexture("spiral", "Textures/Spiral.png");
		for (int i = 0; i < 5; i++) {
			spiral[i].setTexture(Textures["spiral"]);
			spiral[i].setOrigin(128, 128);
			spiral[i].setTextureRect(IntRect(0, 0, 256, 256));
			spiral[i].setRotation(rand() % 360);
		}
		spiral[0].setColor(Color::Blue);
		spiral[1].setColor(Color::Red);
		spiral[2].setColor(Color::Magenta);
		spiral[3].setColor(Color::Green);
		spiral[4].setColor(Color::White);
		loadTexture("int", "Textures/Int.png");
		blend.setPosition(0, 0);
		blend.setTexture(Textures["cursor"]);
		blend.setTextureRect(IntRect(0, 0, screenw, screenh));
		loadTexture("lev",  "Textures/Levels.png");

		loadTexture("b_ach", "Textures/Ach.png");
		loadTexture("b_editor", "Textures/Editor.png");
		loadTexture("b_exit", "Textures/Exit.png");
		loadTexture("b_levels", "Textures/Lvls.png");
		loadTexture("b_options", "Textures/Options.png");
		loadTexture("b_play", "Textures/Play.png");

		loadTexture("eb_chooser", "Textures/Editor_UI/Lvl_name.png");
		loadTexture("eb_editor",  "Textures/Editor_UI/Lvl_edit.png");
		loadTexture("eb_renamer", "Textures/Editor_UI/Lvl_rename.png");
		loadTexture("eb_deleter", "Textures/Editor_UI/Trash.png");

		//blocks
		block.setOrigin(64, 64);

		Texture empty;

		// TODO: имена текстур соотнести с ID
		std::vector<std::string> texturesFilenames = {
			"Textures/NULL.png", // TODO: файл загадочного нуля
			"Textures/Blue.png", // 1
			"Textures/switch.png", // 2
			"Textures/Something.png", // 3
			"Textures/Something2.png", // 4
			"Textures/Box.png", // 5
			"Textures/Something.png", // 6
			"Textures/Wall.png", // 7
			"Textures/Gr.png", // 8
			"Textures/Grb.png", // 9
			"Textures/Green.png", // 10
			"Textures/GreenWall.png", // 11
			"Textures/RoseBricks.png", // 12
			"Textures/RB.png", // 13
			"Textures/Flowers.png", // 14
			"Textures/Crystal.png", // 15
			"Textures/grav.png", // 16
			"Textures/Glass.png", // 17
			"Textures/Something.png", // 18
			"Textures/Something.png", // 19
			"Textures/Something.png", // 20
			"Textures/Something3.png", // 21
			"Textures/White.png", // 22
			"Textures/White_wall.png", // 23
			"Textures/RoseBut.png", // 24
			"Textures/RoseBricks2.png", // 25
			"Textures/Player_detector.png", // 26
			"Textures/Player_detector_inv.png", // 27
			"Textures/View_detector.png", // 28
			"Textures/Pusher.png", // 29
			"Textures/Speed_detector.png", // 30
			"Textures/Glass.png", // 31
			"Textures/NULL.png", // 32
			"Textures/NULL.png", // 33
			"Textures/NULL.png", // 34
			"Textures/NULL.png", // 35
			"Textures/NULL.png", // 36
			"Textures/NULL.png", // 37
			"Textures/NULL.png", // 38
			"Textures/NULL.png", // 39
			"Textures/NULL.png", // 40
			"Textures/NULL.png", // 41
			"Textures/NULL.png", // 42
			"Textures/NULL.png", // 43
			"Textures/NULL.png", // 44
			"Textures/NULL.png", // 45
			"Textures/NULL.png", // 46
			"Textures/NULL.png", // 47
			"Textures/NULL.png", // 48
			"Textures/NULL.png", // 49
			"Textures/NULL.png", // 50
			"Textures/NULL.png", // 51
			"Textures/NULL.png", // 52
			"Textures/NULL.png", // 53
			"Textures/NULL.png", // 54
			"Textures/NULL.png", // 55
			"Textures/NULL.png", // 56
			"Textures/NULL.png", // 57
			"Textures/NULL.png", // 58
			"Textures/NULL.png", // 59
			"Textures/NULL.png", // 60
			"Textures/NULL.png", // 61
			"Textures/NULL.png", // 62
			"Textures/NULL.png", // 63
			"Textures/NULL.png", // 64
			"Textures/NULL.png", // 65
			"Textures/NULL.png", // 66
			"Textures/NULL.png", // 67
			"Textures/NULL.png", // 68
			"Textures/NULL.png", // 69
			"Textures/NULL.png", // 70
			"Textures/NULL.png", // 71
			"Textures/NULL.png", // 72
			"Textures/NULL.png", // 73
			"Textures/NULL.png", // 74
			"Textures/NULL.png", // 75
			"Textures/NULL.png", // 76
			"Textures/NULL.png", // 77
			"Textures/NULL.png", // 78
			"Textures/NULL.png", // 79
			"Textures/NULL.png", // 80
			"Textures/NULL.png", // 81
			"Textures/NULL.png", // 82
			"Textures/NULL.png", // 83
			"Textures/NULL.png", // 84
			"Textures/NULL.png", // 85
			"Textures/NULL.png", // 86
			"Textures/NULL.png", // 87
			"Textures/NULL.png", // 88
			"Textures/NULL.png", // 89
			"Textures/NULL.png", // 90
			"Textures/NULL.png", // 91
			"Textures/NULL.png", // 92
			"Textures/NULL.png", // 93
			"Textures/NULL.png", // 94
			"Textures/NULL.png", // 95
			"Textures/NULL.png", // 96
			"Textures/NULL.png", // 97
			"Textures/NULL.png", // 98
			"Textures/NULL.png", // 99
			"Textures/Editor_UI/T_camera.png", // 100
			"Textures/Editor_UI/T_darkness.png", // 101
			"Textures/Editor_UI/T_portal.png", // 102
			"Textures/Editor_UI/T_player.png", // 103
			"Textures/text.png", // 104
			"Textures/NULL.png", // 105
		};

		// А далее задаём по ID блоков их текстуры
		for (int i = 0; i < sizeof(MapBasicTextures) / sizeof(MapBasicTextures[0]); i++) {
			MapBasicTextures[i] = &empty;
			if (i >= texturesFilenames.size()) continue;

			MapBasicTextures[i] = getTexture(texturesFilenames[i]);
		}

		texturesFilenames = {
			"Textures/NULL.png", // TODO: файл загадочного нуля
			"Textures/Floor.png.png", // 1
			"Textures/Electric trap.png", // 2
			"Textures/Electric trap.png", // 3
			"Textures/Stripes.png", // 4
			"Textures/Corner.png", // 5
			"Textures/finoff.png", // 6
			"Textures/Portal.png", // 7
			"Textures/Portal_out.png", // 8
			"Textures/.png", // 9
			"Textures/StripesP.png", // 10
			"Textures/GreenFloor.png", // 11
			"Textures/Different.png", // 12
			"Textures/Rose.png", // 13
			"Textures/GreenFloor2.png", // 14
			"Textures/GreenSwitch.png", // 15
			"Textures/GreenSwitch.png", // 16
			"Textures/NULL.png", // 17
			"Textures/Glass.png", // 18
			"Textures/Arrow.png", // 19
			"Textures/Blue_floor2.png", // 20
			"Textures/Rosefloor2.png", // 21
			"Textures/Gray2.png", // 22
			"Textures/Rose_door.png", // 23
			"Textures/Rose_door.png", // 24
			"Textures/Electricity/C 1.png", // 25
			"Textures/Electricity/C linear.png", // 26
			"Textures/Electricity/C corner.png", // 27
			"Textures/Electricity/C cross 3.png", // 28
			"Textures/Electricity/C cross 4.png", // 29
			"Textures/Electricity/+.png", // 30
			"Textures/Electricity/-.png", // 31
			"Textures/Electricity/Resistor.png", // 32
			"Textures/Electricity/Switcher_main.png", // 33
			"Textures/Electricity/Switch_off.png", // 34
			"Textures/Electricity/Switch_on.png", // 35
			"Textures/Electricity/Acc.png", // 36
			"Textures/Electricity/Sensor_off.png", // 37
			"Textures/Lamp_blue.png", // 38
			"Textures/Lamp_blue.png", // 39
			"Textures/Lamp_barrier.png", // 40
			"Textures/Lamp_barrier.png", // 41
			"Textures/Electricity/void.png", // 42
			"Textures/Portal2.png", // 43
			"Textures/Some_help.png", // 44
			"Textures/Position_detector.png", // 45
			"Textures/Electricity/Button.png", // 46
			"Textures/NULL.png", // 47
			"Textures/NULL.png", // 48
			"Textures/NULL.png", // 49
			"Textures/NULL.png", // 50
			"Textures/NULL.png", // 51
			"Textures/NULL.png", // 52
			"Textures/NULL.png", // 53
			"Textures/NULL.png", // 54
			"Textures/NULL.png", // 55
			"Textures/NULL.png", // 56
			"Textures/NULL.png", // 57
			"Textures/NULL.png", // 58
			"Textures/NULL.png", // 59
			"Textures/NULL.png", // 60
			"Textures/NULL.png", // 61
			"Textures/NULL.png", // 62
			"Textures/NULL.png", // 63
			"Textures/NULL.png", // 64
			"Textures/NULL.png", // 65
			"Textures/NULL.png", // 66
			"Textures/NULL.png", // 67
			"Textures/NULL.png", // 68
			"Textures/NULL.png", // 69
			"Textures/NULL.png", // 70
			"Textures/NULL.png", // 71
			"Textures/NULL.png", // 72
			"Textures/NULL.png", // 73
			"Textures/NULL.png", // 74
			"Textures/NULL.png", // 75
			"Textures/NULL.png", // 76
			"Textures/NULL.png", // 77
			"Textures/NULL.png", // 78
			"Textures/NULL.png", // 79
			"Textures/NULL.png", // 80
			"Textures/NULL.png", // 81
			"Textures/NULL.png", // 82
			"Textures/NULL.png", // 83
			"Textures/NULL.png", // 84
			"Textures/NULL.png", // 85
			"Textures/NULL.png", // 86
			"Textures/NULL.png", // 87
			"Textures/NULL.png", // 88
			"Textures/NULL.png", // 89
			"Textures/NULL.png", // 90
			"Textures/NULL.png", // 91
			"Textures/NULL.png", // 92
			"Textures/NULL.png", // 93
			"Textures/NULL.png", // 94
			"Textures/NULL.png", // 95
			"Textures/NULL.png", // 96
			"Textures/NULL.png", // 97
			"Textures/NULL.png", // 98
			"Textures/NULL.png", // 99
			"Textures/Editor_UI/T_camera.png", // 100
			"Textures/Editor_UI/T_darkness.png", // 101
			"Textures/Editor_UI/T_portal.png", // 102
			"Textures/Editor_UI/T_player.png", // 103
			"Textures/text.png", // 104
			"Textures/NULL.png", // 105
		};

		// А далее задаём по ID блоков их текстуры
		for (int i = 0; i < sizeof(MapFloorTextures) / sizeof(MapFloorTextures[0]); i++) {
			MapFloorTextures[i] = &empty;
			if (i >= texturesFilenames.size()) continue;

			MapFloorTextures[i] = getTexture(texturesFilenames[i]);
		}

		//sounds
		scl.loadFromFile("Sounds/S1.ogg");
		push.loadFromFile("Sounds/Push.ogg");
		coin_s.loadFromFile("Sounds/Coin.ogg");
		boom.loadFromFile( "Sounds/Boom.ogg");
		cryst.loadFromFile( "Sounds/crys.ogg");
		s1.setBuffer(scl); sound_p.setBuffer(push); sound_c.setBuffer(coin_s); sound_b.setBuffer(boom); _break.setBuffer(cryst);
		telep.loadFromFile( "Sounds/Tp.ogg"); tp_s.setBuffer(telep);
		arpush.loadFromFile( "Sounds/Arrow_move.ogg");
		sound_ab.setBuffer(arpush);
		elbuf.loadFromFile( "Sounds/Electro.ogg");
		electro.setBuffer(elbuf);

		tp1_buf.loadFromFile( "Sounds/tp1.ogg"); tp1.setBuffer(tp1_buf);
		tp2_buf.loadFromFile( "Sounds/tp2.ogg"); tp2.setBuffer(tp2_buf);
		push2_buf.loadFromFile( "Sounds/push2.ogg"); push2.setBuffer(push2_buf);
		open_buf.loadFromFile( "Sounds/Open.ogg"); open.setBuffer(open_buf);

		playerS.setTexture(*getTexture("Textures/Player.png"));
		eyes.setTexture(*getTexture("Textures/Eyes.png"));
		blink.setTexture(*getTexture("Textures/Blink.png"));

		playerS.setOrigin(37.5, 37.5); 
		eyes.setOrigin(37.5, 37.5);
		blink.setOrigin(37.5, 37.5);
	} 

	playerS.setPosition(0, 0);

	//UI
	box.setTexture(*getTexture("Textures/Context_menu.png")); 
	box_but.setTexture(*getTexture("Textures/ContextMenuB.png"));
	box.setScale(UI_scale, UI_scale); box_but.setScale(UI_scale, UI_scale * 0.8);
	box.setOrigin(320, 0); box.setPosition(screenw / 2, 50 * UI_scale);
	box_but.setOrigin(256, 64);

	particles_option = ThreeBut(0, 20, 50, 400, 0);
	particles_option.currentval = partnum;

	bg_particles_option = ThreeBut(0,20,1000,400,1);
	bg_particles_option.currentval = BG_particles_number;

	anti_progress.type = 2;
	anti_progress.text_ = " Destroy your progress (!!!)\n \n (press F, K and this button)";
	anti_progress.init();

	ach_text.setFont(font);

	ach_bg.loadFromFile("Textures/AchievementBG.png");


	ach_BG.setTexture(ach_bg);
	ach_complete.loadFromFile("Textures/Achievement_try.png");
	ach_BG.setOrigin(700,0);
	ach_BG.setScale(UI_scale / 1.5, UI_scale / 1.5);
	ach_text.setCharacterSize(UI_scale * 100);

	//editor UI
	if (true) {

		e_B.loadFromFile("Textures/Editor_UI/B.png");
		e_E.loadFromFile("Textures/Editor_UI/E.png");
		e_Gr.loadFromFile( "Textures/Editor_UI/G.png");
		e_Gy.loadFromFile( "Textures/Editor_UI/Gy.png");
		e_L.loadFromFile( "Textures/Editor_UI/Layers.png");
		e_L2.loadFromFile("Textures/Editor_UI/Layers2.png");
		e_load.loadFromFile("Textures/Editor_UI/Load.png");
		e_M.loadFromFile( "Textures/Editor_UI/M.png");
		e_Mech.loadFromFile( "Textures/Editor_UI/Mech.png");
		e_next.loadFromFile( "Textures/Editor_UI/Next.png");
		e_play.loadFromFile( "Textures/Editor_UI/Play.png");
		e_player.loadFromFile( "Textures/Editor_UI/Player.png");
		e_plus.loadFromFile( "Textures/Editor_UI/Plus.png");
		e_prev.loadFromFile( "Textures/Editor_UI/Previous.png");
		e_Q.loadFromFile( "Textures/Editor_UI/Q.png");
		e_R.loadFromFile("Textures/Editor_UI/R.png");
		e_Rt.loadFromFile("Textures/Editor_UI/Rotate.png");
		e_grid.loadFromFile("Textures/Editor_UI/Grid.png");
		e_save.loadFromFile( "Textures/Editor_UI/Save.png");
		trash.loadFromFile("Textures/Editor_UI/Trash.png");
		editor_num.loadFromFile("Textures/Editor_UI/Number.png");
		editor_option.loadFromFile( "Textures/Editor_UI/Option.png");
		editor_col.loadFromFile("Textures/Editor_UI/Color_choose.png");
		e_rotate__.loadFromFile( "Textures/Editor_UI/Rotate2.png");
		EM_add.loadFromFile( "Textures/Editor_UI/Add.png");
		e_multichoose.loadFromFile( "Textures/Editor_UI/Choose.png");
		e_copy.loadFromFile( "Textures/Editor_UI/Copy.png");
		e_fill.loadFromFile( "Textures/Editor_UI/Fill.png");

		E_copy.init(e_copy,0,0,"",0);
		E_plus.init(e_plus, 0, 0, " ", 0);
		E_Rt.init(e_Rt, 128 * UI_scale, 0, " ", 1);
		E_M.init(e_M, 256 * UI_scale, 0, " ", 2);
		E_player.init(e_player, 768 * UI_scale, 0, " ", 3);
		E_multichoose.init(e_multichoose, 512 * UI_scale, 0, " ",3);
		E_fill.init(e_fill, 640 * UI_scale,0,"",22);
		E_grid.init(e_grid, 384 * UI_scale, 0, "", 4);
		E_play.init(e_play, screenw - 384 * UI_scale, 0, " ", 5);
		E_save.init(e_save, screenw - 256 * UI_scale, 0, " ", 6);
		E_load.init(e_load, screenw - 128 * UI_scale, 0, " ", 7);

		E_prev.init(e_prev, 0, screenh - 128 * UI_scale, " ", 8);
		E_next.init(e_next, 128 * UI_scale, screenh - 128 * UI_scale, " ", 9);
		E_L.init(e_L, 0, screenh - 256 * UI_scale, " ", 10);
		E_L2.init(e_L2, 128 * UI_scale, screenh - 256 * UI_scale, " ", 11);
		E_B.init(e_B, 256 * UI_scale, screenh - 256 * UI_scale, " ", 12);
		E_R.init(e_R, 384 * UI_scale, screenh - 256 * UI_scale, " ", 13);
		E_Gr.init(e_Gr, 512 * UI_scale, screenh - 256 * UI_scale, " ", 14);
		E_Gy.init(e_Gy, 640 * UI_scale, screenh - 256 * UI_scale, " ", 15);
		E_Mech.init(e_Mech, 768 * UI_scale, screenh - 256 * UI_scale, " ", 16);
		E_Q.init(e_Q, 896 * UI_scale, screenh - 256 * UI_scale, " ", 17);
		E_E.init(e_E, 1024 * UI_scale, screenh - 256 * UI_scale, " ", 18);
		E_trash.init(trash, 0, 0, "", 19);
		E_next_page.init(e_next, screenw / 2 + UI_scale * 190, screenh * 0.75, " ", 19); E_next_page.box.scale(0.75, 0.75);
		E_prev_page.init(e_prev, screenw / 2 - UI_scale * 285, screenh * 0.75, " ", 20); E_prev_page.box.scale(0.75, 0.75);

		t_plus.loadFromFile("Textures/Editor_UI/T_plus.png");
		t_minus.loadFromFile("Textures/Editor_UI/T_minus.png");

		T_plus.init(t_plus,0,0,"",69);
		T_minus.init(t_minus, 0, 0, "", 69);

		E_plus.is_checked = true;
		E_L.is_checked = true;
		E_B.is_checked = true;
	}

	//achievements UI
	if (true) {
		achievement_button_t.loadFromFile("Textures/Bonus_button.png");
	}

	arrow_editor_t.loadFromFile("Textures/Editor_UI/Arrow_editor.png");
	E_arrow[0].init(arrow_editor_t, 0, 0, "", 99); E_arrow[0].box.setOrigin(64, 64); E_arrow[0].box.rotate(-90);
	E_arrow[1].init(arrow_editor_t, 0, 0, "", 99); E_arrow[1].box.setOrigin(64, 64); E_arrow[1].box.rotate(0);
	E_arrow[2].init(arrow_editor_t, 0, 0, "", 99); E_arrow[2].box.setOrigin(64, 64); E_arrow[2].box.rotate(90);
	E_arrow[3].init(arrow_editor_t, 0, 0, "", 99); E_arrow[3].box.setOrigin(64, 64); E_arrow[3].box.rotate(180);
}
