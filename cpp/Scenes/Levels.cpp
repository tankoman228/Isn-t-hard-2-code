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
#include <Level_building.h>
#include <Scenes.hpp>

void InitLevels() {
	while(Mouse::isButtonPressed(Mouse::Left)){}
	logg << "Level cycle begin \n";
	onclick = false;
	level_scroll = 400;
}

void LevelsTick(float dt) {

    block.setTexture(Textures["BG"]); block.setScale(2, 2);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 6; j++) {
            block.setPosition(i * 256 + level_scroll % 256 - 128, j * 256);
            window.draw(block);
        }
    }

    for (int i = 0; i < 35; i++) {
        text.setCharacterSize(UI_scale * 100);
        lvl_but.setScale(UI_scale * 2, UI_scale * 2);
        lvl_but.setPosition(level_scroll + (300 * (i + 1)) * UI_scale, screenh / 2);
        if (lvl_but.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
            lvl_but.scale(1.08, 1.08); text.setCharacterSize(UI_scale * 108);
        }
        if (i + 1 <= levels_opened) {
            lvl_but.setTextureRect(IntRect(0, 0, 128, 128));
            if (lvl_but.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    if (!onclick) {
                        lvlnum = i + 1;
                        music.stop();
                        block.setOrigin(64, 64);
                        InitGameSceneLevel(lvlnum);
                        ChangeScene("game");
                        block.setScale(scale, scale);
                    }
                }
            }
        }
        else { lvl_but.setTextureRect(IntRect(128, 0, 128, 128)); }
        text.setFillColor(Color(50, 50, 20, 255));
        text.setPosition(lvl_but.getPosition().x - UI_scale * 72, lvl_but.getPosition().y - UI_scale * 70);
        if (i < 9) { text.move(UI_scale * 42, 0); }
        helper_string = to_string(i + 1);
        text.setString(helper_string);
        window.draw(lvl_but);
        window.draw(text);
    }

    if (cursor.getPosition().x > screenw * 0.9) {
        level_scroll-=60;
    }
    if (cursor.getPosition().x < screenw * 0.1) {
        level_scroll+=60;
    }
}

