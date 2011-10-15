#include "IntroScreen.h"
#include "ScreenManager.h"
#include "ResourceManager.h"

using namespace puz;

void IntroScreen::handleEvent(const sf::Event& e) {
	if (e.Type == sf::Event::KeyPressed) {
		terminate();
		ScreenManager::activateScreen("Game");
	}
}

void IntroScreen::update() {
	
}

void IntroScreen::present() {
	_app->Clear(sf::Color(0,0,0));
	_app->Draw(_logoSprite);
}

int IntroScreen::onInit() {
	_logoSprite.SetImage(ResourceManager::getImage("logo.png"));
	ScreenManager::getLayout().alignDrawable(_logoSprite, _logoSprite.GetSize(), utl::Direction::center, utl::Direction::center);
	return EXIT_SUCCESS;
}

