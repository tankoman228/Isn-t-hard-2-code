#pragma once

#include <string>
using namespace std;

std::string getType(int id, int layer);

void save(string fname);

void checkpoint();

void load_checkpoint();

void clear_lvl();

void InitGameSceneLevel(int l);
