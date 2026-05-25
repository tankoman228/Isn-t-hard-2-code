// Это функции для перехода и отрисовки каждой из сцен, см. в глобальных методах переключение между ними
// Реализация в cpp сцен

// Указатель будет указывать на один из этих методов, будет верная часть цикла без if-else
void AchievementsTick(float dt);
void EditorMenuTick(float dt);
void LevelsTick(float dt);
void OptionsTick(float dt);
void EditorTick(float dt);
void GameTick(float dt);
void MenuTick(float dt);

// Вызываются в момент перехода на сцену, инициализация спрайтов, переменных
void InitAchievements();
void InitEditorMenu();
void InitLevels();
void InitOptions();
void InitEditor();
void InitGame();
void InitMenu();

