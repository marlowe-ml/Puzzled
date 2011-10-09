#include "GameScreen.h"
#include "ScreenManager.h"
#include "ResourceManager.h"
#include <iostream>
#include <boost/utility/typed_in_place_factory.hpp>
#include <boost/lexical_cast.hpp>
#include <math.h>


using namespace puz;

GameScreen::GameScreen() : _gameStarted(false), _showMenu(false), _isSolved(false), _defaultGridSpacing(3) {}

bool GameScreen::setupBoard() {
	if (!_boardImage.LoadFromFile("puzzle.jpg"))
		return false;

	_boardGrid = boost::in_place<BoardGrid>(3, 3, _boardImage); 
	centerBoard();

	return true;
}

void GameScreen::addLabels() {
	_allLabels.push_back(&_labelStatus);
	_allLabels.push_back(&_labelMovesTaken);
	_allLabels.push_back(&_labelTimeTaken);

	for (vpLabels::iterator it = _allLabels.begin(); it!=_allLabels.end(); it++) {
		(*it)->SetFont(ResourceManager::getFont());
		(*it)->SetColor(sf::Color(255,0,0));
	}
}

int GameScreen::onInit() {
	addLabels();

	if (!setupBoard())
		return EXIT_FAILURE;

	_showMenu = true;

	return EXIT_SUCCESS;
}

void GameScreen::update() {
	checkUpdateTimeTaken();
}

void GameScreen::present() {

	if (_gameStarted) {
		for (vpLabels::iterator it = _allLabels.begin(); it!=_allLabels.end(); it++) {
			_app->Draw(*(*it));
		}
		_app->Draw(*_boardGrid);
	}

	if (_showMenu) {
		_app->Draw(_mainMenu);
	}

}

void GameScreen::startGame() {
	_showMenu = false;
	_isSolved = false;
	_numMovesTaken = 0;
	_secondsTaken = 0;

	_stopWatch.Reset();	
	//_boardGrid->randomize();
	_boardGrid->reset();
	_boardGrid->setGridSpacing(_defaultGridSpacing);

	_labelMovesTaken.SetText("0");
	_labelTimeTaken.SetText("00:00:00");
	_labelStatus.SetText("");

	const Layout & layout = ScreenManager::getLayout();
	layout.alignLabel(_labelMovesTaken, utl::Direction::right, utl::Direction::top);
	layout.alignLabel(_labelTimeTaken, utl::Direction::center, utl::Direction::top);

	_gameStarted = true;
}

void GameScreen::resumeGame() {
	_showMenu = false;
}

void GameScreen::handleEvent(const sf::Event& e) {
	
	if (_showMenu) {
		_mainMenu.handleEvent(e);

		switch (_mainMenu.checkLastActivatedButton()) {
			case MainMenu::btnNewGame:
				startGame();
				break;
			case MainMenu::btnResumeGame:
				resumeGame();
				break;
			case MainMenu::btnAbout:
				// todo
				break;
			case MainMenu::btnExit:
				ResourceManager::getApp()->Close();
				break;
		}

		return;
	}


	if (e.Type == sf::Event::KeyPressed) {
		switch(e.Key.Code) {
			case sf::Key::Up:
				move(0,1);
				break;
			case sf::Key::Down:
				move(0,-1);
				break;
			case sf::Key::Left:
				move(1,0);
				break;
			case sf::Key::Right:
				move(-1,0);
				break;
			case sf::Key::Escape:
				_showMenu = true;
				break;
		}
	}
}

void GameScreen::move(int offsetX, int offsetY) {

	if (_boardGrid->moveEmptyTileBy(offsetX,offsetY)) {
		// move was made
		_numMovesTaken++;

		_labelMovesTaken.SetText(boost::lexical_cast<std::string>(_numMovesTaken));
		ScreenManager::getLayout().alignLabel(_labelMovesTaken, utl::Direction::right, utl::Direction::top);

		checkIsSolved();
	}
}

void GameScreen::checkIsSolved() {
	_isSolved = _boardGrid->isSolved();
	if (_isSolved) {
		_labelStatus.SetText("Solved!");
		_boardGrid->setGridSpacing(0);
		_boardGrid->removeEmptyTile();
	}
}

void GameScreen::checkUpdateTimeTaken() {

	float newSecondsTaken = _stopWatch.GetElapsedTime();
	if (newSecondsTaken != _secondsTaken) {
		int totalSeconds = static_cast<int>(newSecondsTaken);

		int hours = totalSeconds / 3600;
		totalSeconds -= (hours * 3600);

		int minutes = totalSeconds / 60;
		totalSeconds -= (minutes * 60);

		int seconds = totalSeconds;

		std::string sSeconds = boost::lexical_cast<std::string>(seconds);
		if (sSeconds.size() == 1)
			sSeconds = "0" + sSeconds;

		std::string sMinutes = boost::lexical_cast<std::string>(minutes);
		if (sMinutes.size() == 1)
			sMinutes = "0" + sMinutes;

		std::string sHours = boost::lexical_cast<std::string>(hours);
		if (sHours.size() == 1)
			sHours = "0" + sHours;

		_secondsTaken = newSecondsTaken;

		_labelTimeTaken.SetText(sHours + ":" + sMinutes + ":" + sSeconds);

	}
}


void GameScreen::centerBoard() {
	const Layout& layout = ScreenManager::getLayout();
	sf::Vector2f pos = layout.getAlignedPosition(_boardGrid->getRect(), utl::Direction::center, utl::Direction::center);
	_boardGrid->SetPosition(pos);
}
