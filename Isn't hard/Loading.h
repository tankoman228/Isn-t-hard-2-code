#pragma once

#include "Classes.h"
#include "Voids.h"

void loading() {

	logg << "Loading \n";

	//Screen	

	ifstream options;
	options.open("Options.txt");
	options >> partnum;
	options >> levels_opened;
	options >> helper_s2;
	options >> BG_particles_number;
	options.close();

	//loading some textures
	if ("textures" == "textures") {

		//somethings
		eyes_t.loadFromFile("Textures\\Eyes.png");
		body_t.loadFromFile("Textures\\Player.png");
		font.loadFromFile("Textures\\Text.ttf");
		text.setFont(font);
		Coin.loadFromFile("Textures\\Coin.png");
		smoke.loadFromFile("Textures\\Smoke.png");
		broken.loadFromFile("Textures\\Broken.png");
		cur.loadFromFile("Textures\\Choose.png");
		dark.loadFromFile("Textures\\Dark.png");

		cursor.setTexture(cur);
		cursor.setOrigin(8, 8);

		spir.loadFromFile("Textures\\Spiral.png");
		for (i = 0; i < 5; i++) {
			spiral[i].setTexture(spir);
			spiral[i].setOrigin(128, 128);
			spiral[i].setTextureRect(IntRect(0, 0, 256, 256));
			spiral[i].setRotation(rand() % 360);
		}
		spiral[0].setColor(Color::Blue);
		spiral[1].setColor(Color::Red);
		spiral[2].setColor(Color::Magenta);
		spiral[3].setColor(Color::Green);
		spiral[4].setColor(Color::White);
		inter.loadFromFile("Textures\\Int.png");
		blend.setPosition(0, 0);
		blend.setTexture(cur);
		blend.setTextureRect(IntRect(0, 0, screenw, screenh));
		lev.loadFromFile("Textures\\Levels.png");
		lvl_but.setTexture(lev); lvl_but.setOrigin(64, 64);

		t_ach.loadFromFile("Textures\\Ach.png");
		t_editor.loadFromFile("Textures\\Editor.png");
		t_exit.loadFromFile("Textures\\Exit.png");
		t_levels.loadFromFile("Textures\\Lvls.png");
		t_options.loadFromFile("Textures\\Options.png");
		t_play.loadFromFile("Textures\\Play.png");

		b_levels.init(t_levels, screenw / 4, screenh / 2, " ", 0);
		b_play.init(t_play, screenw / 2, screenh / 2, " ", 1);
		b_editor.init(t_editor, screenw / 4 * 3, screenh / 2, " ", 2);
		b_ach.init(t_ach, screenw / 4, screenh / 3.7 * 3, " ", 3);
		b_options.init(t_options, screenw / 2, screenh / 3.7 * 3, " ", 4);
		b_exit.init(t_exit, screenw / 4 * 3, screenh / 3.7 * 3, " ", 5);


		//blocks
		block.setOrigin(64, 64);
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

		//sounds
		scl.loadFromFile("Sounds\\S1.ogg");
		push.loadFromFile("Sounds\\Push.ogg");
		coin_s.loadFromFile("Sounds\\Coin.ogg");
		boom.loadFromFile("Sounds\\Boom.ogg");
		cryst.loadFromFile("Sounds\\crys.ogg");
		s1.setBuffer(scl); sound_p.setBuffer(push); sound_c.setBuffer(coin_s); sound_b.setBuffer(boom); _break.setBuffer(cryst);
		telep.loadFromFile("Sounds\\Tp.ogg"); tp_s.setBuffer(telep);
		arpush.loadFromFile("Sounds\\Arrow_move.ogg");
		sound_ab.setBuffer(arpush);
		elbuf.loadFromFile("Sounds\\Electro.ogg");
		electro.setBuffer(elbuf);

		tp1_buf.loadFromFile("Sounds\\tp1.ogg"); tp1.setBuffer(tp1_buf);
		tp2_buf.loadFromFile("Sounds\\tp2.ogg"); tp2.setBuffer(tp2_buf);
		push2_buf.loadFromFile("Sounds\\push2.ogg"); push2.setBuffer(push2_buf);
		open_buf.loadFromFile("Sounds\\Open.ogg"); open.setBuffer(open_buf);

		playerS.setTexture(body_t);
		body_t.setSmooth(true);
		eyes_t.setSmooth(true);
		eyes.setTexture(eyes_t);
		playerS.setOrigin(37.5, 37.5); eyes.setOrigin(37.5, 37.5);
		blink.loadFromFile("Textures\\Blink.png");

	} 

	playerS.setPosition(0, 0);

	//UI

	box_t.loadFromFile("Textures\\Context_menu.png"); box_but_t.loadFromFile("Textures\\ContextMenuB.png");
	box.setTexture(box_t); box_but.setTexture(box_but_t);
	box.setScale(UI_scale, UI_scale); box_but.setScale(UI_scale, UI_scale * 0.8);
	box.setOrigin(320, 0); box.setPosition(screenw / 2, 50 * UI_scale);
	box_but.setOrigin(256, 64);

	particles_option = ThreeBut(0, 20, 50, 400, 0);
	particles_option.currentval = partnum;

	bg_particles_option = ThreeBut(0,20,1000,400,1);
	bg_particles_option.currentval = BG_particles_number;

	reloader.type = 0;
	reloader.text_ = " Change screen resolution";
	reloader.init();

	auto_reloader.type = 1;
	auto_reloader.text_ = " Auto screen setting";
	auto_reloader.init();

	anti_progress.type = 2;
	anti_progress.text_ = " Destroy your progress (!!!)\n \n (press F, K and this button)";
	anti_progress.init();

	screenmode.init(600 * UI_scale, 100 * UI_scale);

	//"i" is gloabal, but not everywhere. I need to do this class better, but not now
	i = 0;
	res_but[0].init(1920, 1080);
	i = 1;
	res_but[1].init(1280, 720);

	res_but[int(helper_s2)].is_picked = true;

	ach_text.setFont(font);
	ach_bg.loadFromFile("Textures\\AchievementBG.png");
	ach_BG.setTexture(ach_bg);
	ach_complete.loadFromFile("Textures\\Achievement_try.png");
	ach_BG.setOrigin(700,0);
	ach_BG.setScale(UI_scale / 1.5, UI_scale / 1.5);
	ach_text.setCharacterSize(UI_scale * 100);

	//editor UI
	if (true) {

		e_B.loadFromFile("Textures\\Editor_UI\\B.png");
		e_E.loadFromFile("Textures\\Editor_UI\\E.png");
		e_Gr.loadFromFile("Textures\\Editor_UI\\G.png");
		e_Gy.loadFromFile("Textures\\Editor_UI\\Gy.png");
		e_L.loadFromFile("Textures\\Editor_UI\\Layers.png");
		e_L2.loadFromFile("Textures\\Editor_UI\\Layers2.png");
		e_load.loadFromFile("Textures\\Editor_UI\\Load.png");
		e_M.loadFromFile("Textures\\Editor_UI\\M.png");
		e_Mech.loadFromFile("Textures\\Editor_UI\\Mech.png");
		e_next.loadFromFile("Textures\\Editor_UI\\Next.png");
		e_play.loadFromFile("Textures\\Editor_UI\\Play.png");
		e_player.loadFromFile("Textures\\Editor_UI\\Player.png");
		e_plus.loadFromFile("Textures\\Editor_UI\\Plus.png");
		e_prev.loadFromFile("Textures\\Editor_UI\\Previous.png");
		e_Q.loadFromFile("Textures\\Editor_UI\\Q.png");
		e_R.loadFromFile("Textures\\Editor_UI\\R.png");
		e_Rt.loadFromFile("Textures\\Editor_UI\\Rotate.png");
		e_grid.loadFromFile("Textures\\Editor_UI\\Grid.png");
		e_save.loadFromFile("Textures\\Editor_UI\\Save.png");
		trash.loadFromFile("Textures\\Editor_UI\\Trash.png");
		editor_num.loadFromFile("Textures\\Editor_UI\\Number.png");
		editor_option.loadFromFile("Textures\\Editor_UI\\Option.png");
		editor_col.loadFromFile("Textures\\Editor_UI\\Color_choose.png");
		e_rotate__.loadFromFile("Textures\\Editor_UI\\Rotate2.png");
		e_choose.loadFromFile("Textures\\Editor_UI\\Lvl_name.png");
		e_edit.loadFromFile("Textures\\Editor_UI\\Lvl_edit.png");
		e_rename.loadFromFile("Textures\\Editor_UI\\Lvl_rename.png");
		EM_add.loadFromFile("Textures\\Editor_UI\\Add.png");
		e_multichoose.loadFromFile("Textures\\Editor_UI\\Choose.png");
		e_copy.loadFromFile("Textures\\Editor_UI\\Copy.png");
		e_fill.loadFromFile("Textures\\Editor_UI\\Fill.png");

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

		t_plus.loadFromFile("Textures\\Editor_UI\\T_plus.png");
		t_minus.loadFromFile("Textures\\Editor_UI\\T_minus.png");

		T_plus.init(t_plus,0,0,"",69);
		T_minus.init(t_minus, 0, 0, "", 69);

		E_plus.is_checked = true;
		E_L.is_checked = true;
		E_B.is_checked = true;
	}

	//achievements UI
	if (true) {
		achievement_button_t.loadFromFile("Textures\\Bonus_button.png");

		ach_but[0].init(achievement_button_t, 300, 150, "achievement :)", 0);

		for (i = 0; i < 42; i++) {
			ach_but[i + 1].init(achievement_button_t, 300, (200 * i) + 450, "achievement :)", i + 1);
		}

		ach_but[0].update(-2, 0);
		ach_but[1].update(1, 0);
		ach_but[2].update(2, 0);
		ach_but[3].update(3, 0);
		ach_but[4].update(-3, 0);
		ach_but[5].update(5, 0);
		ach_but[6].update(5, 1);
		ach_but[7].update(6, 0);
		ach_but[8].update(-3, 1);
		ach_but[9].update(7, 0);
		ach_but[10].update(7, 1);
		ach_but[11].update(9, 0);
		ach_but[12].update(11, 0);
		ach_but[13].update(-3, 2);
		ach_but[14].update(12, 0);
		ach_but[15].update(-3, 3);
		ach_but[16].update(14, 0);
		ach_but[17].update(15, 0);
		ach_but[18].update(15, 1);
		ach_but[19].update(17, 0);
		ach_but[20].update(-3, 4);
		ach_but[21].update(19, 0);
		ach_but[22].update(-3, 5);
		ach_but[23].update(20, 0);
		ach_but[24].update(21, 0);
		ach_but[25].update(21, 1);
		ach_but[26].update(23, 0);
		ach_but[27].update(23, 1);
		ach_but[28].update(24, 0);
		ach_but[29].update(-3, 6);
		ach_but[30].update(25, 0);
		ach_but[31].update(-3, 7);
		ach_but[32].update(26, 0);
		ach_but[33].update(-3, 8);
		ach_but[34].update(29, 0);
		ach_but[35].update(-3, 9);
		ach_but[36].update(31, 0);
		ach_but[37].update(-3, 10);
		ach_but[38].update(33, 0);
		ach_but[39].update(-3, 11);
		ach_but[40].update(-3, 12);
		ach_but[41].update(35, 0);
		ach_but[42].update(-3, 13);
	}

	arrow_editor_t.loadFromFile("Textures\\Editor_UI\\Arrow_editor.png");
	E_arrow[0].init(arrow_editor_t, 0, 0, "", 99); E_arrow[0].box.setOrigin(64, 64); E_arrow[0].box.rotate(-90);
	E_arrow[1].init(arrow_editor_t, 0, 0, "", 99); E_arrow[1].box.setOrigin(64, 64); E_arrow[1].box.rotate(0);
	E_arrow[2].init(arrow_editor_t, 0, 0, "", 99); E_arrow[2].box.setOrigin(64, 64); E_arrow[2].box.rotate(90);
	E_arrow[3].init(arrow_editor_t, 0, 0, "", 99); E_arrow[3].box.setOrigin(64, 64); E_arrow[3].box.rotate(180);
}
