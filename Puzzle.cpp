#include "Puzzle.h"
#include "ScreenManager.h"
#include "ResourceManager.h"

using namespace puz;

Puzzle::Puzzle() 
: 
_app(sf::RenderWindow(sf::VideoMode(800,600,32), "Puzzle"))
{}

int Puzzle::run() {

	ScreenManager::init(_app);
	ResourceManager::init();

	ScreenManager::TerminateCurrentScreenAndActivate("Intro");

	while (_app.IsOpened()) {
		_app.Clear();
		ScreenManager::runActiveScreen();
		if (_app.IsOpened())
			_app.Display();

		sf::Sleep(0.1f);
	}

	ScreenManager::cleanup();

	return EXIT_SUCCESS;
}