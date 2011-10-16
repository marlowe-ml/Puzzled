#include "AboutScreen.h"
#include "ScreenManager.h"
#include "ResourceManager.h"

using namespace puz;

void AboutScreen::handleEvent(const sf::Event& e) {
	if (e.Type == sf::Event::KeyPressed) {
		ScreenManager::activateScreen("Game");
	}
}

void AboutScreen::update() {

}

void AboutScreen::present() {
	_app->Clear(sf::Color(0,0,0));
	_app->Draw(_labelAbout);
}

int AboutScreen::onInit() {
	std::string about = 
		"Puzzled - Copyright (c) 2011 by jvb\n\n"
		"Open source licensed under the MIT license\n\n"
		"Sources: https://github.com/marlowe-ml/Puzzled";
	_labelAbout = sf::String(about, ResourceManager::getFont(), 20.0f);
	ScreenManager::getLayout().alignString(_labelAbout, utl::Direction::center, utl::Direction::center);
	return EXIT_SUCCESS;
}

