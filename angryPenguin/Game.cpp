#include "Game.h"
#include "Map.h"
#include "Walrus.h"
#include "Bar.h"

Game::Game(): player(&map, "cat.png"), pengy(&map, "penguin.png")
{
	map.load("tileset.png", 32, "map.txt");
	window = new RenderWindow(VideoMode(map.getTileSize() * map.getLevelSize().y * 2, map.getTileSize() * map.getLevelSize().y), "ANGRY PENGUIN | ESC to exit", Style::Titlebar | Style::Close);
	view = new View(FloatRect(0, 0, map.getTileSize() * map.getLevelSize().y * 2, map.getTileSize() * map.getLevelSize().y));
	window->setVerticalSyncEnabled(true);
	window->setMouseCursorGrabbed(true);
	window->setMouseCursorVisible(false);
	background.loadFromFile("clouds.jpg");
	background.setRepeated(true);
}

Game::~Game()
{
	delete window;
	delete view;
}

void Game::start(int speed)
{
	player.position.x = 32 * 5;
	player.position.y = 32 * 6;
	walrii.push_back(new Walrus(&map, "walrus.png", Vector2f(32 * 28, 32 * 5)));
	walrii.push_back(new Walrus(&map, "walrus.png", Vector2f(32 * 128, 32 * 5)));
	walrii.push_back(new Walrus(&map, "walrus.png", Vector2f(32 * 62, 32 * 1)));
	walrii.push_back(new Walrus(&map, "walrus.png", Vector2f(32 * 76, 32 * 6)));
	walrii.push_back(new Walrus(&map, "walrus.png", Vector2f(32 * 143, 32 * 5)));
	walrii.push_back(new Walrus(&map, "walrus.png", Vector2f(32 * 202, 32 * 6)));
	walrii.push_back(new Walrus(&map, "walrus.png", Vector2f(32 * 255, 32 * 6)));
	walrii.push_back(new Walrus(&map, "walrus.png", Vector2f(32 * 295, 32 * 6)));
	walrii.push_back(new Walrus(&map, "walrus.png", Vector2f(32 * 337, 32 * 5)));

	Sprite bgr_sprite; //Fon
	bgr_sprite.setTexture(background);
	bgr_sprite.setTextureRect(IntRect(0, 0, 10000, 500));
	
	Clock clock;
	Event event;
	Vector2f coords;
	Vector2f viewCoords;
	Vector2f mapCoords;
	int offset = view->getSize().x / 2;

	Bar bar("Bar.png", "Rubius.ttf", &player, view->getCenter().x - 350, view->getCenter().x + 250);
	bar.stopGame();
	bar.loadMsgFromFile("intro.txt");

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
				if (event.key.code == Keyboard::Space)
					player.jump();
				if (event.key.code == Keyboard::X)
					player.activateWalrus(walrii, pengy);
				if (event.key.code == Keyboard::Enter)
					bar.startGame();
				break;
			default:
				break;
			}
		}

		window->setView(*view);
		window->clear(); // очистка кадра
		window->draw(bgr_sprite);

		if (!bar.isStarted()) {
			bar.update(elapsed);
			window->draw(bar);
		}
		else {
			window->draw(map);
			//обработка списка моржей
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

			if (!player.getStateOfDeath()) {
				player.update(elapsed);
				player.move(elapsed);
				window->draw(player);

				pengy.update(elapsed);
				pengy.move(elapsed, &player);
				window->draw(pengy);

				bar.update(elapsed);
				window->draw(bar);
			}
			else {
				bar.stopGame();
				bar.setMsgPosition(window->mapPixelToCoords(Vector2i(10, 10), *view));
				bar.setMsg("THOU ART FAILED!\nBE GONE AT ONCE\nUNLESS THOU WISHEST\nTO INCUR OUR WRATH!");
			}

			//настройка области видимости карты
			if (player.position.x > view->getCenter().x) {
				//конвертирование координат окна в координаты карты
				viewCoords = window->mapPixelToCoords(Vector2i(view->getCenter()), *view);
				mapCoords = window->mapPixelToCoords(Vector2i(map.getLevelPixelSize()), *view);

				if (viewCoords.x < mapCoords.x - offset) {
					view->setCenter(round(player.position.x), view->getCenter().y);

					//установка позиции строк состояния.
					bar.setPosition(view->getCenter().x - 350);
					bar.setPointsPositions(view->getCenter().x + 250);
				}
			}
		}
		window->display(); // отрисовка кадра
	}
}
