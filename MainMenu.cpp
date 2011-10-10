#include "MainMenu.h"
#include "Layout.h"
#include "ScreenManager.h"
#include "ResourceManager.h"

using namespace puz;

MainMenu::MainMenu() : _wasClosed(false), _initialMenu(true) {
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
	sf::FloatRect rect = _buttonList.GetRect();
	float x = _buttonList.GetPosition().x;
	float y = _buttonList.GetPosition().y;

	float x1 = x - 20;
	float y1 = y - 20;
	float x2 = x + rect.Right + 20;
	float y2 = y + rect.Bottom + 20;

	sf::Shape background = sf::Shape::Rectangle(x1, y1, x2, y2, sf::Color(128,0,0,128), 1.0f, sf::Color(255,255,255,128));
	target.Draw(background);
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
			if (!_initialMenu) {
				_wasClosed = true;
			}
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
	if (inGame)
		_initialMenu = false;

	_buttonList.showButton(MainMenu::btnResumeGame, inGame);
	_buttonList.showButton(MainMenu::btnNewGame, !inGame);
}

void MainMenu::selectFirst() {
	_buttonList.selectFirstButton();
}