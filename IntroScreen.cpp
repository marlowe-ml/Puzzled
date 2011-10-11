#include "IntroScreen.h"
#include "ScreenManager.h"

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
	_logo.LoadFromFile("logo.png");
	_logoSprite.SetImage(_logo);
	float w = _logoSprite.GetSize().x;
	float h = _logoSprite.GetSize().y;
	sf::Vector2f centerPos = ScreenManager::getLayout().getAlignedPosition(sf::FloatRect(0,0,w,h), utl::Direction::center, utl::Direction::center);
	_logoSprite.SetPosition(centerPos);
	return EXIT_SUCCESS;
}

