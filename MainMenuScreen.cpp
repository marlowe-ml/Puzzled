#include "MainMenuScreen.h"
#include "ScreenManager.h"
#include "ResourceManager.h"

using namespace puz;

MainMenuScreen::~MainMenuScreen() {
}


void MainMenuScreen::handleEvent(const sf::Event& e) {
	if (e.Type == sf::Event::KeyPressed) {
		switch(e.Key.Code) {
			case sf::Key::Up:
				_buttonList.selectPreviousButton();
				break;
			case sf::Key::Down:
				_buttonList.selectNextButton();
				break;
			case sf::Key::Return:
			case sf::Key::Space:
				activateSelectedButton();
				break;
		}		
		
	}
}


void MainMenuScreen::activateSelectedButton() {
	switch (_buttonList.getSelectedButton()) {
		case MainMenuScreen::btnNewGame:
			ScreenManager::TerminateCurrentScreenAndActivate("Game");
			break;
		case MainMenuScreen::btnExit:
			terminate();
			_app->Close();
			break;
	}
}



void MainMenuScreen::update() {

}

void MainMenuScreen::present() {
	_app->Clear(sf::Color(0,0,0));
	_app->Draw(_buttonList);
}

int MainMenuScreen::onInit() {	
	_buttonList.addButton("New Game");
	_buttonList.addButton("Exit");
	
	const Layout & layout = ScreenManager::getLayout();
	sf::Vector2f centerPos = layout.getAlignedPosition(_buttonList.GetRect(), utl::Direction::center, utl::Direction::center);
	_buttonList.SetPosition(centerPos);
	_buttonList.setSelectedButton(0);

	return EXIT_SUCCESS;
}