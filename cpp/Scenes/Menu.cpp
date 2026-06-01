#include <Values.h>
#include <UI.h>
#include <Particles.h>
#include <Voids.h>
#include <Blocks.h>
#include <Loading.h>
#include <Scenes.hpp>
#include <GlobalVoids.hpp>
#include <Level_building.h>

MainMenuButton b_play, b_levels, b_editor, b_ach, b_options, b_exit;
Sprite background;

void InitMenu() {
    b_levels .init(Textures["b_levels"],     screenw / 4,     screenh / 2,       " ", 0);
    b_play   .init(Textures["b_play"],         screenw / 2,     screenh / 2,       " ", 1);
    b_editor .init(Textures["b_editor"],     screenw / 4 * 3, screenh / 2,       " ", 2);
    b_ach    .init(Textures["b_ach"],           screenw / 4,     screenh / 3.7 * 3, " ", 3);
    b_options.init(Textures["b_options"],   screenw / 2,     screenh / 3.7 * 3, " ", 4);
    b_exit   .init(Textures["b_exit"],         screenw / 4 * 3, screenh / 3.7 * 3, " ", 5);

    background.setTexture(Textures["BG"]);
}

void MenuTick(float dt) {

    background.setTextureRect(IntRect(0, 0, screenw, screenh));
    window.draw(background);

    text.setPosition(screenw / 2 - (352 * UI_scale), screenh / 20);
    text.setCharacterSize(150 * UI_scale);
    text.setFillColor(Color(0, 0, 0, 255));
    text.setString("Isn't hard 2");

    window.draw(text);

    text.setPosition(screenw/2 - (350 * UI_scale), screenh / 20 + 2);
    text.setCharacterSize(150 * UI_scale);
    text.setFillColor(Color(200,200,255,255));
    text.setString("Isn't hard 2");
    
    window.draw(text);

    text.setPosition(5, 5);
    text.setFillColor(Color::White);
    text.setCharacterSize(15 * UI_scale);
    text.setString("Beta 1.7");
    window.draw(text);

    b_levels .cycle(screenw / 4    , screenh / 2      );
    b_play   .cycle(screenw / 2    , screenh / 2      );
    b_editor .cycle(screenw / 4 * 3, screenh / 2      );
    b_ach    .cycle(screenw / 4    , screenh / 3.7 * 3);
    b_options.cycle(screenw / 2    , screenh / 3.7 * 3);
    b_exit   .cycle(screenw / 4 * 3, screenh / 3.7 * 3);

    if (click_button_menu) {
        logg << "click_button_menu \n";
        switch (btnCLICK_KOSTIL) {
            case 0: 
                ChangeScene("levels"); 
                level_scroll = (levels_opened * 300 - 800) * -1; 
                break;
        
            case 1: ChangeScene("game"); block.setScale(scale, scale); block.setOrigin(64, 64); music.stop(); 
            
                if (levels_opened < 35) {   
                    InitGameSceneLevel(levels_opened); 
                } else { 
                    InitGameSceneLevel(rand() + tick % 36); 
                } 
                break;
        
            case 2: ChangeScene("editor_menu"); music.stop(); 
                break;
        
            case 3: ChangeScene("achievements"); 
                break;
        
        
            case 4: ChangeScene("options"); 
                break;
        
            case 5: save_options(); close = true; window.close(); 
        }
        click_button_menu = false;
    }
}


