#include "Game.h"

Game::Game()
{
	window = new RenderWindow(VideoMode(900, 500), "ANGRY PENGUIN | ESC to exit", Style::Titlebar | Style::Close);
	window->setVerticalSyncEnabled(true);
	window->setMouseCursorGrabbed(false);  // установка курсора в окно игры
	window->setMouseCursorVisible(false);  //скрытие курсора в области окна игры
}

Game::~Game()
{
	window->setMouseCursorGrabbed(false);
	window->setMouseCursorVisible(true);
	delete window;
}

void Game::start()
{
	Clock clock;
	Event event;

	while (window->isOpen()) {
		// время кадра
		Time elapsed = clock.restart();

		// обработка событий окна
		while (window->pollEvent(event)) {
			switch (event.type) {
			case Event::Closed:
				window->close();
				break;

			case Event::KeyPressed:
				if (event.key.code == Keyboard::Escape)
					window->close();
				break;

			default:
				break;
			}
		}
		window->clear(); // очистка кадра
		window->display(); // отрисовка кадра
	}
}
