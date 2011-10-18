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
	_app->Draw(_pressKeyLabel);
}

int IntroScreen::onInit() {
	_logoSprite.SetImage(ResourceManager::getImage("logo.png"));
	ScreenManager::getLayout().alignSprite(_logoSprite, utl::Direction::center, utl::Direction::center);
	
	_pressKeyLabel = sf::String("press a key to start ..", ResourceManager::getFont(), 20.0f);
	ScreenManager::getLayout().alignString(_pressKeyLabel, utl::Direction::center, utl::Direction::none);
	
	_pressKeyLabel.SetY(_logoSprite.GetPosition().y + _logoSprite.GetSize().y + 30);

	return EXIT_SUCCESS;
}

