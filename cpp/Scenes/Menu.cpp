#include <Values.h>
#include <UI.h>
#include <Particles.h>
#include <Voids.h>
#include <Blocks.h>
#include <Loading.h>
#include <Scenes.hpp>
#include <GlobalVoids.hpp>
#include <Level_building.h>

void InitMenu() {

}


void MenuTick(float dt) {

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

    b_levels.cycle();
    b_ach.cycle();
    b_exit.cycle();
    b_options.cycle();
    b_play.cycle();
    b_editor.cycle();

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


