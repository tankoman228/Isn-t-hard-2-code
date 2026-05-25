#include <Values.h>
#include <Scenes.hpp>
#include <Voids.h>
#include <GlobalVoids.hpp>

// Указатель на функцию, которая циклически вызывается каждый тик
void (*CurrentScene)(float) = nullptr;


void ChangeScene(std::string sceneId) {

    if (sceneId == "game") {
        InitGame();
        CurrentScene = GameTick;
    }
    else if (sceneId == "editor_menu") {
        InitEditorMenu();
        CurrentScene = EditorMenuTick;
    }
    else if (sceneId == "editor") {
        InitEditor();
        CurrentScene = EditorTick;
    }
    else if (sceneId == "achievements") {
        InitAchievements();
        CurrentScene = AchievementsTick;
    }
    else if (sceneId == "menu") {
        InitMenu();
        CurrentScene = MenuTick;
    }
    else if (sceneId == "options") {
        InitOptions();
        CurrentScene = OptionsTick;
    }
    else if (sceneId == "levels") {
        InitLevels();
        CurrentScene = LevelsTick;
    }
}

void SceneSelectorTick(float dt) {

    if (CurrentScene == nullptr) CurrentScene = MenuTick;
    CurrentScene(dt);

    if (sf::Keyboard::isKeyPressed(Keyboard::Escape) && CurrentScene != EditorTick && CurrentScene != GameTick) {
        ChangeScene("menu");
        while (sf::Keyboard::isKeyPressed(Keyboard::Escape)) { }
    }

    if (!music.getStatus()) {
        reset_music();
    }
}