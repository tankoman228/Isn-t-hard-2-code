#include <Values.h>
#include <UI.h>
#include <Particles.h>
#include <Voids.h>
#include <Blocks.h>
#include <Loading.h>
#include <Scenes.hpp>

void InitOptions() {

}

void OptionsTick(float dt) {
    // TODO: фон
    particles_option.cycle();
    bg_particles_option.cycle();

    text.setFillColor(Color(0, 0, 200, 255));
    text.setCharacterSize(40 * UI_scale);
    text.setPosition(particles_option.middle.getPosition());
    text.move(-90 * UI_scale, 120 * UI_scale);
    text.setString("Particles density");
    window.draw(text);
    text.move(2, 2);
    text.setFillColor(Color(0, 0, 0, 255));
    window.draw(text);

    text.setFillColor(Color(0, 0, 200, 255));
    text.setPosition(bg_particles_option.middle.getPosition());
    text.move(-90 * UI_scale, 120 * UI_scale);
    text.setString("BG quality (0 is BG off). FPS depends on this \n value, especially on weak computers");
    window.draw(text);
    text.move(2, 2);
    text.setFillColor(Color(0, 0, 0, 255));
    window.draw(text);

    anti_progress.cycle();

    if (anti_progress.is_clicked) {

        if (Keyboard::isKeyPressed(Keyboard::F) && Keyboard::isKeyPressed(Keyboard::K)) {

            ofstream i_am_bored;

            i_am_bored.close();

            for (int k = 0; k < 43; k++) {

                // TODO: просто открыть каждый файл и перезаписать его содержимое

                /*i_am_bored.open("Achievements/" + to_string(ach_but[k].lvl) + " " + to_string(ach_but[k].n) + ".txt");

                i_am_bored << 0;
                i_am_bored << ' ';
                i_am_bored << 0;

                i_am_bored.close();*/
            }

            i_am_bored.open("Achievements/-2 0.txt");

            i_am_bored << 1;
            i_am_bored << ' ';
            i_am_bored << 0;

            levels_opened = 1;

            save_options();
        }
    }

    float helper_s[2];

    if (Mouse::isButtonPressed(Mouse::Left)) {
        onclick = true;
    }
    else { onclick = false; }
}
