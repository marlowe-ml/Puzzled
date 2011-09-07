#include "MainMenuScreen.h"
#include "ScreenManager.h"
#include "ResourceManager.h"

using namespace puz;


void MainMenuScreen::handleEvent(const sf::Event& e) {
	if (e.Type == sf::Event::KeyPressed) {
		ScreenManager::activateScreen("Game");
		terminate();
	}
}

void MainMenuScreen::update() {

}

void MainMenuScreen::present() {
	_app->Clear(sf::Color(0,0,0));

	for (vLabels::iterator it = _menuButtons.begin(); it!=_menuButtons.end(); it++) {
		_app->Draw(*it);
	}
}

int MainMenuScreen::onInit() {

	sf::String newGame;
	newGame.SetText("New Game");
	newGame.SetFont(ResourceManager::getFont());
	newGame.SetColor(sf::Color(255,255,255));

	_menuButtons.push_back(Label(newGame));
	
	sf::String exit;

	exit.SetText("Exit");
	exit.SetFont(ResourceManager::getFont());
	exit.SetColor(sf::Color(255,255,255));
	_menuButtons.push_back(Label(exit));

	const Layout & layout = ScreenManager::getLayout();
	for (vLabels::iterator it = _menuButtons.begin(); it!=_menuButtons.end(); it++) {
		layout.alignLabel((*it), utl::Direction::center, utl::Direction::center);
	}
	
	
	return EXIT_SUCCESS;
}

