#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <SFML/Audio.hpp>
#include <fstream>

#include <Values.h>
#include <UI.h>
#include <Particles.h>
#include <Voids.h>
#include <Blocks.h>
#include <Player.h>
#include <Physics_processing.h>
#include <Context_menu.h>
#include <Level_building.h>
#include <Scenes.hpp>
#include <GlobalVoids.hpp>

#define px p.x
#define py p.y
#define sx p.sx
#define sy p.sy

static int i, j, k, helper;
static float helper_s[2] = { 0,0 };
static float helper_s2 = 0;

static int cursor_fade = 0;
static int last_x = 0, last_y = 0;

void InitGame() {
    teleport_to = -1;
	on_teleport = false;

    cursor_fade = 0;
    last_x = 0; last_y = 0;

    music.setVolume(100);

	s1.setVolume(30);
	sound_p.setVolume(12);
	sound_c.setVolume(30);
	sound_b.setVolume(30);
	_break.setVolume(30);
	ach_s.setVolume(30);
	electro.setVolume(30);
	sound_ab.setVolume(30);
	tp1.setVolume(30);
	tp2.setVolume(30);
	push2.setVolume(30);
	open.setVolume(30);


	// TODO: block.setTexture(corn);
	block.setOrigin(64, 64);
	
	logg << "The game start!\n";

	eyes.setScale(scale, scale);
    blink.setScale(scale, scale);
	playerS.setScale(scale, scale);
}



void GameTick(float dt) {

    physics_processing();

    if (Keyboard::isKeyPressed(Keyboard::Tab) && !onclick) {

        onclick = true;
        InitGameSceneLevel(lvlnum);

        return;
    }

    if (Keyboard::isKeyPressed(Keyboard::Q)) {
        music.stop(); tick += rand() % 10;
    }

    if (Keyboard::isKeyPressed(Keyboard::F5)) {
        sleep(milliseconds(200));
        checkpoint();
        while (Keyboard::isKeyPressed(Keyboard::F5)) {}
    }

    for (i = 0; i < BG_particles_number; i++) {
        bg_particles[i].cycle();
    }

    if (colint > 0) { colint--; }

    for (i = 0; i < map_floor.size(); i++) {
        map_floor[i]->render();
    }

    for (i = 0; i < electric.size(); i++) {
        electric[i]->render();
    }

    for (i = 0; i < movables.size(); i++) {
        movables[i]->render();
    }

    for (i = 0; i < 5; i++) {
        spiral[i].rotate(3.2);
        if (i == teleport_to) { spiral[i].setScale((teleport_frame * 0.01 + 0.25) * scale, (teleport_frame * 0.01 + 0.25) * scale); }
        else { spiral[i].setScale(0.25 * scale, 0.25 * scale); }
        window.draw(spiral[i]);
        spiral[i].scale(2, 2);
        window.draw(spiral[i]);
        spiral[i].scale(0.5, 0.5);
        window.draw(spiral[i]);
        if (i == teleport_to) { spiral[i].setScale((teleport_frame * 0.01 + 0.25) * scale, (teleport_frame * 0.01 + 0.25) * scale); }
        else { spiral[i].setScale(0.25 * scale, 0.25 * scale); }
        spiral[i].setPosition((tx[i] - scrollx) * scale, (ty[i] - scrolly) * scale);
        window.draw(spiral[i]);
        spiral[i].scale(2, 2);
        window.draw(spiral[i]);
        spiral[i].scale(0.5, 0.5);
        window.draw(spiral[i]);
        spiral[i].setPosition(-200, -200);
    }

    for (i = 0; i < map_basic.size(); i++) {
        map_basic[i]->render();
    }

    //zoom
    if (Mouse::isButtonPressed(Mouse::Right)) {
        if (scale > 0.5 * UI_scale) {
            scale *= 0.99;
            eyes.setScale(scale, scale);
            playerS.setScale(scale, scale);

            if (!scroll_pinned) {
                if (playerS.getPosition().x > screenw / 2) {
                    scrollx += 5;
                }
                else {
                    scrollx -= 5;
                }
                if (playerS.getPosition().y > screenh / 2) {
                    scrolly += 5;
                }
                else {
                    scrollx -= 5;
                }
            }

            for (i = 0; i < map_floor.size(); i++) {
                map_floor[i]->render();
            }
            for (i = 0; i < electric.size(); i++) {
                electric[i]->render();
            }
            for (i = 0; i < movables.size(); i++) {
                movables[i]->render();
            }
            for (i = 0; i < 5; i++) {
                spiral[i].rotate(3.2);
                if (i == teleport_to) { spiral[i].setScale((teleport_frame * 0.01 + 0.25) * scale, (teleport_frame * 0.01 + 0.25) * scale); }
                else { spiral[i].setScale(0.25 * scale, 0.25 * scale); }
                window.draw(spiral[i]);
                spiral[i].scale(2, 2);
                window.draw(spiral[i]);
                spiral[i].scale(0.5, 0.5);
                window.draw(spiral[i]);
                if (i == teleport_to) { spiral[i].setScale((teleport_frame * 0.01 + 0.25) * scale, (teleport_frame * 0.01 + 0.25) * scale); }
                else { spiral[i].setScale(0.25 * scale, 0.25 * scale); }
                spiral[i].setPosition((tx[i] - scrollx) * scale, (ty[i] - scrolly) * scale);
                window.draw(spiral[i]);
                spiral[i].scale(2, 2);
                window.draw(spiral[i]);
                spiral[i].scale(0.5, 0.5);
                window.draw(spiral[i]);
                spiral[i].setPosition(-200, -200);
            }
            for (i = 0; i < map_basic.size(); i++) {
                map_basic[i]->render();
            }
        }
    }
    else {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            scale *= 1.01;
            eyes.setScale(scale, scale);
            playerS.setScale(scale, scale);

            if (!scroll_pinned) {
                if (playerS.getPosition().x > screenw / 2) {
                    scrollx += 5;
                }
                else {
                    scrollx -= 5;
                }
                if (playerS.getPosition().y > screenh / 2) {
                    scrolly += 5;
                }
                else {
                    scrollx -= 5;
                }
            }

            for (i = 0; i < map_floor.size(); i++) {
                map_floor[i]->render();
            }
            for (i = 0; i < electric.size(); i++) {
                electric[i]->render();
            }
            for (i = 0; i < movables.size(); i++) {
                movables[i]->render();
            }
            for (i = 0; i < 5; i++) {
                spiral[i].rotate(3.2);
                if (i == teleport_to) { spiral[i].setScale((teleport_frame * 0.01 + 0.25) * scale, (teleport_frame * 0.01 + 0.25) * scale); }
                else { spiral[i].setScale(0.25 * scale, 0.25 * scale); }
                window.draw(spiral[i]);
                spiral[i].scale(2, 2);
                window.draw(spiral[i]);
                spiral[i].scale(0.5, 0.5);
                window.draw(spiral[i]);
                if (i == teleport_to) { spiral[i].setScale((teleport_frame * 0.01 + 0.25) * scale, (teleport_frame * 0.01 + 0.25) * scale); }
                else { spiral[i].setScale(0.25 * scale, 0.25 * scale); }
                spiral[i].setPosition((tx[i] - scrollx) * scale, (ty[i] - scrolly) * scale);
                window.draw(spiral[i]);
                spiral[i].scale(2, 2);
                window.draw(spiral[i]);
                spiral[i].scale(0.5, 0.5);
                window.draw(spiral[i]);
                spiral[i].setPosition(-200, -200);
            }
            for (i = 0; i < map_basic.size(); i++) {
                map_basic[i]->render();
            }

        }
    }

    for (i = 0; i < triggers.size(); i++) {
        triggers[i]->render();
    }

    //scrolling
    if (!scroll_pinned) {

        if (last_x != cursor.getPosition().x && last_y != cursor.getPosition().y) {
            last_x = cursor.getPosition().x;
            last_y = cursor.getPosition().y;
            cursor_fade = 0;
        }
        else {
            cursor_fade++;
        }

        if (last_x > screenw - 20) { scrollx += 5 / scale; }
        if (last_x < 20) { scrollx -= 5 / scale; }
        if (last_y < 20) { scrolly -= 5 / scale; }
        if (last_y > screenh - 20) { scrolly += 5 / scale; }

        int x = playerS.getPosition().x;
        int y = playerS.getPosition().y;

        if (x > screenw * 0.6) {
            scrollx += 1;
        }
        if (x < screenw * 0.4) {
            scrollx -= 1;
        }
        if (y > screenh * 0.6) {
            scrolly += 1;
        }
        if (y < screenh * 0.4) {
            scrolly -= 1;
        }

        if (x > screenw - 400 * UI_scale) {
            scrollx += 1;
        }
        if (x < 400 * UI_scale) {
            scrollx -= 1;
        }
        if (y > screenh - 280 * UI_scale) {
            scrolly += 1;
        }
        if (y < 280 * UI_scale) {
            scrolly -= 1;
        }

        if (x > screenw - 200 * UI_scale) {
            scrollx += 11;
            if (playerS.getPosition().x > screenw) {
                scrollx += 9;/* sx = 0;*/
            }
        }
        if (x < 200 * UI_scale) {
            scrollx -= 11;
            if (playerS.getPosition().x < 0) {
                scrollx -= 9;/* sx = 0;*/
            }
        }
        if (y > screenh - 100 * UI_scale) {
            scrolly += 11;
            if (playerS.getPosition().y > screenh) {
                scrolly += 9;/* sy = 0;*/
            }
        }
        if (y < 100 * UI_scale) {
            scrolly -= 11;
            if (playerS.getPosition().y < 0) {
                scrolly -= 9;/* sy = 0;*/
            }
        }
    }
    
    render_player();

    scroll_pinned = false;

    if (Keyboard::isKeyPressed(Keyboard::Add) || Keyboard::isKeyPressed(Keyboard::Equal)) {
        scale *= 1.01;

        eyes.setScale(scale, scale);
        playerS.setScale(scale, scale);
    }
    if ((Keyboard::isKeyPressed(Keyboard::Subtract) || Keyboard::isKeyPressed(Keyboard::Hyphen)) && (scale > 0.8 * UI_scale)) {

        if (scale > 0.5 * UI_scale) {
            scale *= 0.99;
        }

        eyes.setScale(scale, scale);
        playerS.setScale(scale, scale);
    }	

    if (!on_teleport && (teleport_frame > 0)) {
        teleport_frame -= 3; spiral[teleport_to].rotate(-4);

        playerS.setColor(Color(255, 255, 255, 260 - teleport_frame * 4));
        eyes.setColor(Color(255, 255, 255, 260 - teleport_frame * 4));

        if (teleport_frame < 0) {
            teleport_frame = 0;
            playerS.setColor(Color(255, 255, 255, 255));
            eyes.setColor(Color(255, 255, 255, 255));
        }
    }

    for (i = 0; i < 3; i++) {
        if (particle[i][0].enabled) {
            for (j = 0; j < partnum; j++) {
                particle[i][j].render();
            }
        }
    }

    if (abs(alpha) > 0) {
        alpha -= 5;
        if (alpha > 0) {
            blend.setColor(Color(0, 0, 0, abs(alpha)));
        }
        if (alpha < 0) {
            blend.setColor(Color(0, 0, 0, abs(alpha)));
            if (alpha < -253) {
                if (levels_opened == lvlnum) {
                    levels_opened++; lvlnum++;

                    checkpoint();
                    sleep(milliseconds((200)));
                    InitGameSceneLevel(lvlnum);

                    return;
                }
                if (lvlnum == -2) {
                    lvlnum = -2; InitGameSceneLevel(-2); 
                    
                    ChangeScene("editor");
                    return;
                }
                if (lvlnum == -3) {

                    set_achievement_complete();
                    InitGameSceneLevel(-2); 

                    ChangeScene("achievements");
                    return;

                }
                else {
                    if (lvlnum == -1) {			
                        ChangeScene("menu");
                        lvlnum = 1;
                    }
                    else { lvlnum++; InitGameSceneLevel(lvlnum); checkpoint(); return; }
                }

                InitGameSceneLevel(lvlnum);
            }
        }
        window.draw(blend);
    }

    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        if (!onclick) {
            /*mode = "menu"; */
            onclick = true;
            context_menu = true;
        }
    }
    else {
        onclick = false;
    }

    if (context_menu) { game_context_menu(); }

    if (tp_rech > 0) { tp_rech -= 1; }

    if (achieve_fade > 0) {

        if (achieve_fade > 1145) {
            ach_text.setFillColor(Color(0, 0, 0, 1400 - achieve_fade));					/*ach_box.setPosition(screenw - (1512 - achieve_fade) * UI_scale, 0);*/
            ach_BG.setColor(Color(255, 255, 255, 1400 - achieve_fade));
            ach_text.setOutlineColor(Color(255, 255, 255, 1400 - achieve_fade));
            ach_BG.setPosition(screenw, 0);
            ach_text.setPosition(38 * UI_scale, 20 * UI_scale);
            achieve_fade -= 7;
        }

        if (achieve_fade < 128) {
            /*ach_box.setColor(Color::Color(255, 255, 255, achieve_fade * 2));*/
            ach_BG.setColor(Color(255, 255, 255, achieve_fade * 2));
            ach_text.setFillColor(Color(0, 0, 0, achieve_fade * 2));
            ach_text.setOutlineColor(Color(255, 255, 255, achieve_fade * 2));
        }

        achieve_fade -= 3;

        window.draw(ach_BG); /*window.draw(ach_box);*/ window.draw(ach_text);
    }

    if (block_collision) { colint += 4; block_collision = false; }
}



