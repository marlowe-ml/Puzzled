#include "MainMenu.h"
#include "Layout.h"
#include "ScreenManager.h"
#include "ResourceManager.h"

using namespace puz;

MainMenu::MainMenu() {
	_buttonList.addButton("New Game");
	_buttonList.addButton("About");
	_buttonList.addButton("Exit");

	const Layout & layout = ScreenManager::getLayout();
	sf::Vector2f centerPos = layout.getAlignedPosition(_buttonList.GetRect(), utl::Direction::center, utl::Direction::center);
	_buttonList.SetPosition(centerPos);
	_buttonList.setSelectedButton(0);
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
		}		
	}
}

void MainMenu::activateSelectedButton() {
	switch (_buttonList.getSelectedButton()) {
	case MainMenu::btnNewGame:
		ScreenManager::activateScreen("Game");
		break;
	case MainMenu::btnAbout:
		// todo
		break;
	case MainMenu::btnExit:
		// todo
		//terminate();
		ResourceManager::getApp()->Close();
		break;
	}
}

