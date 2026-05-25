// Это все функции, которые могут вызываться из многих частей программы и влияют на глобальный стейт машин, переход между сценами...

#include <string>

// Смена сцены на следующую
void ChangeScene(std::string sceneId);

// Тик сцены, реализацию см. в SceneManager
void SceneSelectorTick(float dt);