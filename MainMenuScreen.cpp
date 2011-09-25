#include "MainMenuScreen.h"
#include "ScreenManager.h"
#include "ResourceManager.h"

using namespace puz;


void MainMenuScreen::handleEvent(const sf::Event& e) {
	if (e.Type == sf::Event::KeyPressed) {
		switch(e.Key.Code) {
			case sf::Key::Up:
				selectPreviousButton();
				break;
			case sf::Key::Down:
				selectNextButton();
				break;
			case sf::Key::Return:
			case sf::Key::Space:
				activateSelectedButton();
				break;
		}		
		
	}
}

void MainMenuScreen::activateSelectedButton() {
	switch (_selectedButtonIndex) {
		case MainMenuScreen::btnNewGame:
			ScreenManager::TerminateCurrentScreenAndActivate("Game");
			break;
		case MainMenuScreen::btnExit:
			terminate();
			_app->Close();
			break;
	}

}

void MainMenuScreen::selectPreviousButton() {
	if (_selectedButtonIndex > 0)
		setSelectedButton((MenuSelection)(_selectedButtonIndex-1));

}

void MainMenuScreen::selectNextButton() {
	if (_selectedButtonIndex+1 < MainMenuScreen::btnLength)
		setSelectedButton((MenuSelection)(_selectedButtonIndex+1));
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
	_menuButtons.push_back(Label(sf::String("New Game")));
	_menuButtons.push_back(Label(sf::String("Exit")));

	const Layout & layout = ScreenManager::getLayout();
	float previousY = 0;
	float previousHeight = 0;
	for (vLabels::iterator it = _menuButtons.begin(); it!=_menuButtons.end(); it++) {
		(*it).SetFont(ResourceManager::getFont());
		(*it).SetColor(sf::Color(255,255,255));

		layout.alignLabel((*it), utl::Direction::center, utl::Direction::none);
		float newY = previousY + previousHeight + 10;
		(*it).SetY(newY);
		previousY = newY;
		previousHeight = (*it).GetRect().GetHeight();
	}
	
	setSelectedButton(MainMenuScreen::btnNewGame);

	return EXIT_SUCCESS;
}

void MainMenuScreen::setSelectedButton(MenuSelection selectedButton) {
	_selectedButtonIndex = selectedButton;
	int index = 0;
	for (int i=0; i<MainMenuScreen::btnLength;i++) {
		if (i == _selectedButtonIndex)
			_menuButtons[i].SetColor(sf::Color(255,0,0));
		else
			_menuButtons[i].SetColor(sf::Color(255,255,255));
	}

}



