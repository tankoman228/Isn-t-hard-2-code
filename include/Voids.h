#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <SFML/Audio.hpp>
#include <fstream>
#include <Values.h>
#include <UI.h>
#include <Particles.h>
#include <Player.h>

#define px p.x
#define py p.y
#define sx p.sx
#define sy p.sy

using namespace sf; using namespace std;

inline void reset_music() {
	switch (rand() % 5) {
	case 0: music.openFromFile("Sounds/2.ogg"); music.setVolume(100); break;
	case 1: music.openFromFile("Sounds/3.ogg"); music.setVolume(100); break;
	case 2: music.openFromFile("Sounds/4.ogg"); music.setVolume(100); break;
	case 3: music.openFromFile("Sounds/5.ogg"); music.setVolume(100); break;
	case 4: music.openFromFile("Sounds/music1.ogg"); music.setVolume(30); break;
	}
	if (lvlnum == 1 || lvlnum == 15 || lvlnum == 23 || lvlnum > 30 || ((lvlnum == -3) && tick%3 == 1)) {
		switch (rand() % 3) {
		case 0: music.openFromFile("Sounds/Music of music.ogg"); music.setVolume(40); break;
		case 1: music.openFromFile("Sounds/1.ogg"); music.setVolume(100); break;
		case 2: music.openFromFile("Sounds/1.ogg"); music.setVolume(100); break;
		}
	}
	music.play();
	logg << "Music reset \n";
}

inline void save_options() {
	logg << "Options are being saved \n";
	ofstream options;
	options.open("Options.txt");
	options << partnum << " " << levels_opened << " ";
	options << 1 << " ";
	options << BG_particles_number << " ";
	options.close();
	logg << "Options are saved\n";
}

#include <filesystem>

inline void check_saves() {

	logg << "Searching for levels... \n";

	ofstream saves;
	saves.open("saves.txt");
	
	/*
	TODO:
	
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	hf = FindFirstFile(TEXT("Saves/*"), &FindFileData);
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
	
	*/
	saves.close();
	logg << "Searching for levels complete \n";
}

void achievement(int _lvl, int _n);

inline void set_achievement_complete() {
	ofstream ach;
	ach.open("Achievements/" + to_string(CurrentAchievementData[0]) + " " + to_string(CurrentAchievementData[1]) + ".txt");
	ach << 1 << ' ' << 1;
	ach.close();
}

int get_ID(int num);
void render_block_UI(int screenh, int ID, int i);