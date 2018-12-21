#include "Game.h"
#include "Map.h"

Game::Game()
{
//	map = new Map();
	map.load("tileset.png", 32, "map.txt");
	//window = new RenderWindow(VideoMode(900, 500), "ANGRY PENGUIN | ESC to exit", Style::Titlebar | Style::Close);
	window = new RenderWindow (VideoMode(map.getTileSize() * map.getLevelSize().y * 2, map.getTileSize() * map.getLevelSize().y), "MAP WINDOW", Style::Titlebar | Style::Close);
	window->setVerticalSyncEnabled(true);
	window->setMouseCursorGrabbed(false);  // установка курсора в окно игры
	window->setMouseCursorVisible(false);  //скрытие курсора в области окна игры
	
}

Game::~Game()
{
	//delete map;
	window->setMouseCursorGrabbed(false);
	window->setMouseCursorVisible(true);
	delete window;
}

void Game::start(int speed, int fast, float reload)
{

	// окно размером в высоту карты и шириной=высота*2
	View view(FloatRect(0, 0, map.getTileSize() * map.getLevelSize().y * 2, map.getTileSize() * map.getLevelSize().y));
	float reloadSeconds = reload;
	window->setVerticalSyncEnabled(true);
	Clock clock;
	Event event;
	int x, y;
	Vector2f coords;
	while (window->isOpen()) {
		Time elapsed = clock.restart();
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
		window->setView(view);
		window->clear();
		window->draw(map);
		window->display();

		// прокрутка карты
		if (Keyboard::isKeyPressed(Keyboard::Right))
			view.move(Vector2f(elapsed.asSeconds() * (Keyboard::isKeyPressed(Keyboard::Space) ? speed * fast : speed), 0));
		if (Keyboard::isKeyPressed(Keyboard::Left))
			view.move(Vector2f(elapsed.asSeconds() * (Keyboard::isKeyPressed(Keyboard::Space) ? -speed * fast : -speed), 0));

		// перезагрузка карты
		reloadSeconds -= elapsed.asSeconds();
		if (reloadSeconds <= 0) {
			reloadSeconds = reload;
			map.load("tileset.png", 32, "map.txt");
		}
	}
}
