#include "MainMenu.h"
#include "Layout.h"
#include "ScreenManager.h"
#include "ResourceManager.h"

using namespace puz;

MainMenu::MainMenu() : _wasClosed(false) {
	_buttonList.addButton("New Game", MainMenu::btnNewGame);
	_buttonList.addButton("Resume Game", MainMenu::btnResumeGame);
	_buttonList.addButton("About", MainMenu::btnAbout);
	_buttonList.addButton("Exit", MainMenu::btnExit);

	const Layout & layout = ScreenManager::getLayout();
	sf::Vector2f centerPos = layout.getAlignedPosition(_buttonList.GetRect(), utl::Direction::center, utl::Direction::center);
	_buttonList.SetPosition(centerPos);
	_buttonList.selectFirstButton();
}


void MainMenu::Render(sf::RenderTarget& target) const {
	target.Draw(_buttonList);
}

void MainMenu::handleEvent(const sf::Event& e) {
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
		case sf::Key::Escape:
			_wasClosed = true;
			break;
		}		
	}
}

MainMenu::MenuSelection MainMenu::checkLastActivatedButton() {
	MenuSelection last = _lastActivatedButton;
	_lastActivatedButton = MainMenu::btnNone;
	return last;
}

bool MainMenu::checkWasClosed() {
	bool closed = _wasClosed;
	_wasClosed = false;
	return closed;
}

void MainMenu::activateSelectedButton() {
	_lastActivatedButton = static_cast<MainMenu::MenuSelection>(_buttonList.getSelectedButton());
}

void MainMenu::setInGame(bool inGame) {
	_buttonList.showButton(MainMenu::btnResumeGame, inGame);
	_buttonList.showButton(MainMenu::btnNewGame, !inGame);
}

void MainMenu::selectFirst() {
	_buttonList.selectFirstButton();
}