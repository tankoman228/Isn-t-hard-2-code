#include <Values.h>
#include <UI.h>
#include <Particles.h>
#include <Voids.h>
#include <Blocks.h>
#include <Loading.h>
#include <GlobalVoids.hpp>

using namespace std; 
using namespace sf; 

void InitWindow() {
	// TODO: нормальный определитель размеров окна, режимы окна, Screen.txt реализован слишком криво

	sf::VideoMode fullscreen = sf::VideoMode::getFullscreenModes()[0];

	//Auto screen
	window.create(fullscreen, "Isn't hard 2", sf::Style::Default);
	window.setFramerateLimit(60);

	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false); 

	// Глобальные параметры для рендера UI, 
	screenw = fullscreen.width - 60; // TODO: получить размер панели снизу 
	screenh = fullscreen.height;
	UI_scale = fullscreen.width / 1920.0;
}

void ProcessPollEvents() {

	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			save_options(); 
			close = true; window.close(); return;
		}

		if (event.type == sf::Event::Resized) {
			screenw = event.size.width;
			screenh = event.size.height;
			UI_scale = screenw / 1920.f;

			sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
			window.setView(sf::View(visibleArea));
		}
	}
}



int main() {

	logg.open("log.txt");

	InitWindow();
	logg << "Loading...\n";
	loading(); 
	logg << "Loading succesfully finished \n";
	ChangeScene("menu");

	sf::Clock clock;

	while (window.isOpen())
	{
		float dt = clock.restart().asSeconds(); 

		window.clear();
		SceneSelectorTick(dt); // отрисует картинку самой сцены
		tick++;

		cursor.setPosition(Mouse::getPosition().x - window.getPosition().x, (Mouse::getPosition().y) - window.getPosition().y);
		cursor.setScale(1.5, 1.5);
		window.draw(cursor); // отрисует курсор

		window.display();

		ProcessPollEvents();
		if (close) {
			window.close();
			logg.close();
			return 1;
		}
	}

	logg.close();
	return 0;
}
