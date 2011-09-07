#include "IntroScreen.h"
#include "ScreenManager.h"

using namespace puz;


void IntroScreen::handleEvent(const sf::Event& e) {
	if (e.Type == sf::Event::KeyPressed) {
		ScreenManager::activateScreen("MainMenu");
		terminate();
	}
}

void IntroScreen::update() {
	
}

void IntroScreen::present() {
	_app->Clear(sf::Color(255,0,0));
}

int IntroScreen::onInit() {
	return EXIT_SUCCESS;
}

