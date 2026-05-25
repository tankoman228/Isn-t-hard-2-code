#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <SFML/Audio.hpp>
#include <fstream>
#include <Values.h>
#include <UI.h>
#include <Particles.h>
#include <Voids.h>
#include <GlobalVoids.hpp>
#include <Scenes.hpp>

Sprite BG;
ButtonInAchievementMenu MenuItem[43];

const float ScrollSpeed = 70;
float achievements_scroll = 0;

void InitAchievements() {

	logg << "achievements menu" << endl;

	// Сброс скролла не надо, если игрок только прошёл бонус, он и вернётся сюда
	if (lvlnum != -3) { achievements_scroll = 0; }

	BG.setTexture(Textures["Gray2"]);
	BG.setColor(Color(200, 200, 200)); // чуть темнее
	
	// Инициализация расположения UI, заполнение данных
	MenuItem[0].init(achievement_button_t, 300, 150, "achievement :)", 0);
	for (int i = 0; i < 42; i++) {
		MenuItem[i + 1].init(achievement_button_t, 300, (200 * i) + 450, "achievement :)", i + 1);
	}

	// Считывает из файлов, проверяет, выполнена ли ачивка, обновляет UI
	MenuItem[0].updateCheckAchievement(-2, 0);
	MenuItem[1].updateCheckAchievement(1, 0);
	MenuItem[2].updateCheckAchievement(2, 0);
	MenuItem[3].updateCheckAchievement(3, 0);
	MenuItem[4].updateCheckAchievement(-3, 0);
	MenuItem[5].updateCheckAchievement(5, 0);
	MenuItem[6].updateCheckAchievement(5, 1);
	MenuItem[7].updateCheckAchievement(6, 0);
	MenuItem[8].updateCheckAchievement(-3, 1);
	MenuItem[9].updateCheckAchievement(7, 0);
	MenuItem[10].updateCheckAchievement(7, 1);
	MenuItem[11].updateCheckAchievement(9, 0);
	MenuItem[12].updateCheckAchievement(11, 0);
	MenuItem[13].updateCheckAchievement(-3, 2);
	MenuItem[14].updateCheckAchievement(12, 0);
	MenuItem[15].updateCheckAchievement(-3, 3);
	MenuItem[16].updateCheckAchievement(14, 0);
	MenuItem[17].updateCheckAchievement(15, 0);
	MenuItem[18].updateCheckAchievement(15, 1);
	MenuItem[19].updateCheckAchievement(17, 0);
	MenuItem[20].updateCheckAchievement(-3, 4);
	MenuItem[21].updateCheckAchievement(19, 0);
	MenuItem[22].updateCheckAchievement(-3, 5);
	MenuItem[23].updateCheckAchievement(20, 0);
	MenuItem[24].updateCheckAchievement(21, 0);
	MenuItem[25].updateCheckAchievement(21, 1);
	MenuItem[26].updateCheckAchievement(23, 0);
	MenuItem[27].updateCheckAchievement(23, 1);
	MenuItem[28].updateCheckAchievement(24, 0);
	MenuItem[29].updateCheckAchievement(-3, 6);
	MenuItem[30].updateCheckAchievement(25, 0);
	MenuItem[31].updateCheckAchievement(-3, 7);
	MenuItem[32].updateCheckAchievement(26, 0);
	MenuItem[33].updateCheckAchievement(-3, 8);
	MenuItem[34].updateCheckAchievement(29, 0);
	MenuItem[35].updateCheckAchievement(-3, 9);
	MenuItem[36].updateCheckAchievement(31, 0);
	MenuItem[37].updateCheckAchievement(-3, 10);
	MenuItem[38].updateCheckAchievement(33, 0);
	MenuItem[39].updateCheckAchievement(-3, 11);
	MenuItem[40].updateCheckAchievement(-3, 12);
	MenuItem[41].updateCheckAchievement(35, 0);
	MenuItem[42].updateCheckAchievement(-3, 13);
}

void AchievementsTick(float dt) {

	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		ChangeScene("menu");
	}

	for (int i = 0; i < 43; i++) {

		MenuItem[i].box.setPosition(MenuItem[i].box.getPosition().x, MenuItem[i].y * UI_scale - achievements_scroll);
		MenuItem[i].txt.setPosition(MenuItem[i].box.getPosition().x + 70 * UI_scale, MenuItem[i].y * UI_scale - achievements_scroll - 30 * UI_scale);

		if (MenuItem[i].if_click()) {

			block.setScale(scale, scale); 
			block.setOrigin(64, 64); 
			music.stop(); 

			CurrentAchievementData[0] = MenuItem[i].lvl;
			CurrentAchievementData[1] = MenuItem[i].n;

			string newf = MenuItem[i].txt.getString();

			for (int j = 0; j < newf.size(); j++) {
				if (newf[j] == ' ') { newf[j] = '_'; }
			}

			for (int j = 0; j < newf.size(); j++) {
				if (newf[j] == '?') { newf.erase(j); }
			}
			for (int j = 0; j < newf.size(); j++) {
				if (newf[j] == '.') { newf.erase(j); }
			}

			if (i == 0) {
				newf = "Horosie_pelmeny_eto_ochen-ochen_vcusno.Na_samom_dele_retsept_prostoy_mnogo_myasa_malo_testa";
			}
			
			// Эти параметры при старте игры должны заставить его загрузить уровень из этого файла
			current_filename = "Levels/Bonus levels/" + newf;
			lvlnum = -3; 

			ChangeScene("game");

			return;
		}
	}

	if (cursor.getPosition().y > screenh - 30) {
		achievements_scroll += ScrollSpeed * dt;
	}
	if (cursor.getPosition().y < 30 && achievements_scroll > 0) {
		achievements_scroll -= ScrollSpeed * dt;
	}
}

void achievement(int _lvl, int _n) {

	int helper = 0;

	ifstream ach;
	ach.open("Achievements/" + to_string(_lvl) + " " + to_string(_n) + ".txt");

	ach >> helper;
	if (helper > 0) { ach.close(); return; }
	
	ach.close();

	//ach_t.loadFromFile("Achievements/Textures/" + to_string(_lvl) + " " + to_string(_n) + ".png");
	ach_t.loadFromFile("Achievements/Textures/Achievement.png");

	ach_box.setTexture(ach_t);
	//ach_text.setString(helper_string);

	ach_text.setFillColor(Color::Black);
	ach_text.setOutlineColor(Color(0, 255, 255));
	ach_text.setOutlineThickness(3 * UI_scale);
	ach_text.setFont(font);

	int s = 0;
	for (s = 0; s < 43; s++) {
		if (MenuItem[s].lvl == _lvl && MenuItem[s].n == _n) {
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
	
	ach_b.loadFromFile("Achievements/Sounds/" + to_string(_lvl) + " " + to_string(_n) + ".ogg");
	ach_b.loadFromFile("Achievements/Sounds/-2 0.ogg");
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
	achr.open("Achievements/" + to_string(_lvl) + " " + to_string(_n) + ".txt");

	achr << 1;
	achr << " ";
	achr << 0;
	achr.close();

	achieve_fade = 1400;
	ach_s.play();
}
