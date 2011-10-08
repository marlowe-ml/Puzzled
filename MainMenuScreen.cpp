#include "MainMenuScreen.h"
#include "ScreenManager.h"
#include "ResourceManager.h"

using namespace puz;

MainMenuScreen::~MainMenuScreen() {}

void MainMenuScreen::handleEvent(const sf::Event& e) {
	_mainMenu.handleEvent(e);
}

void MainMenuScreen::update() {}

void MainMenuScreen::present() {
	_app->Clear(sf::Color(0,0,0));
	_app->Draw(_mainMenu);
}
