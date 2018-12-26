#include "Game.h"
#include "Map.h"
#include "Walrus.h"

Game::Game(): player(&map, "cat.png"), pengy(&map, "penguin.png")
{
	map.load("tileset.png", 32, "map.txt");
	window = new RenderWindow(VideoMode(map.getTileSize() * map.getLevelSize().y * 2, map.getTileSize() * map.getLevelSize().y), "ANGRY PENGUIN | ESC to exit", Style::Titlebar | Style::Close);
	view = new View(FloatRect(0, 0, map.getTileSize() * map.getLevelSize().y * 2, map.getTileSize() * map.getLevelSize().y));
	window->setVerticalSyncEnabled(true);
	viewOffset = 0;
	viewStart = view->getCenter().x;
	viewEnd = map.getLevelSize().x * map.getTileSize() - viewStart;
}

Game::~Game()
{
	delete window;
	delete view;
}

void Game::start(int speed, int fast, float reload)
{
	player.position.x = 32 * 5;
	player.position.y = 32 * 6;
	walrii.push_back(new Walrus(&map, "walrus.png", Vector2f(32*18, 32*5)));
	
	//==================
	Clock clock;
	Event event;
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
				if (event.key.code == Keyboard::Up)
					player.jump();
				if (event.key.code == Keyboard::Space)
					player.activateWalrus(walrii, pengy);
				break;
			case Event::MouseMoved:
				coords = window->mapPixelToCoords(Vector2i(event.mouseMove.x, event.mouseMove.y), *view);
				//cout << coords.x << " " << coords.y << endl;
				break;
			default:
				break;
			}
		}
		window->setView(*view);
		window->clear(); // очистка кадра

		window->draw(map);

		for (auto i = walrii.begin(); i != walrii.end(); i++) {
			if ((*i)->isActive()) {
				(*i)->update(elapsed);
				(*i)->move(elapsed);
				window->draw(**i);
			}
		}

		for (auto iter = walrii.begin(); iter != walrii.end(); iter++) {
			if ((*iter)->isActive()) {
				(*iter)->update(elapsed);
				(*iter)->move(elapsed);
				window->draw(**iter);
			}
			else {
				delete *iter;
				iter = walrii.erase(iter);
			}
		}

		player.update(elapsed);
		player.move(elapsed);
		window->draw(player);

		pengy.update(elapsed);
		pengy.move(elapsed, &player);
		window->draw(pengy);

		window->display(); // отрисовка кадра

		if(player.position.x > view->getCenter().x)
			view->setCenter(round(player.position.x), view->getCenter().y);
	}
}
