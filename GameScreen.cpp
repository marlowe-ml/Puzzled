#include "GameScreen.h"
#include "ScreenManager.h"
#include "ResourceManager.h"
#include <iostream>
#include <boost/utility/typed_in_place_factory.hpp>
#include <boost/lexical_cast.hpp>
#include <math.h>


using namespace puz;

GameScreen::GameScreen() 
	: _gameStarted(false), _showMenu(false), _isSolved(false), _defaultGridSpacing(3), 
	_timeLastPaused(0), _totalTimePaused(0)
{}

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
	_mainMenu.setInGame(false);

	if (!setupBoard())
		return EXIT_FAILURE;

	showMenu();

	return EXIT_SUCCESS;
}

void GameScreen::update() {
	if (!_showMenu && !_isSolved)
		checkUpdateTimeTaken();
}

void GameScreen::present() {

	if (_gameStarted) {
		for (vpLabels::iterator it = _allLabels.begin(); it!=_allLabels.end(); it++) {
			_app->Draw(*(*it));
		}
		if (!_showMenu || _isSolved) {
			_app->Draw(*_boardGrid);
		}
	}

	if (_showMenu) {
		_app->Draw(_mainMenu);
	}

}

void GameScreen::startGame() {
	_isSolved = false;
	_numMovesTaken = 0;
	_secondsTaken = 0;
	_showMenu = false;

	_mainMenu.setInGame(true);

	_stopWatch.Reset();
	_timeLastPaused = 0;
	_totalTimePaused = 0;

	//_boardGrid->randomize();
	_boardGrid->reset();
	_boardGrid->setGridSpacing(_defaultGridSpacing);

	_labelMovesTaken.SetText("0");
	_labelTimeTaken.SetText("00:00:00");
	_labelStatus.SetText("");

	const Layout & layout = ScreenManager::getLayout();
	layout.alignString(_labelMovesTaken, utl::Direction::right, utl::Direction::top);
	layout.alignString(_labelTimeTaken, utl::Direction::center, utl::Direction::top);

	_gameStarted = true;
}

void GameScreen::hideMenu() {
	_showMenu = false;
	_totalTimePaused += _stopWatch.GetElapsedTime() - _timeLastPaused;
}

void GameScreen::showMenu() {
	_showMenu = true;
	_timeLastPaused = _stopWatch.GetElapsedTime();
	_mainMenu.selectFirst();
}

void GameScreen::handleEvent(const sf::Event& e) {
	
	if (_showMenu) {
		_mainMenu.handleEvent(e);

		if (_mainMenu.checkWasClosed()) {
			hideMenu();
		}

		switch (_mainMenu.checkLastActivatedButton()) {
			case MainMenu::btnNewGame:
				startGame();
				break;
			case MainMenu::btnResumeGame:
				hideMenu();
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
				showMenu();
				break;
		}
	}
}

void GameScreen::move(int offsetX, int offsetY) {

	if (_boardGrid->moveEmptyTileBy(offsetX,offsetY)) {
		// move was made
		_numMovesTaken++;

		_labelMovesTaken.SetText(boost::lexical_cast<std::string>(_numMovesTaken));
		ScreenManager::getLayout().alignString(_labelMovesTaken, utl::Direction::right, utl::Direction::top);

		checkIsSolved();
	}
}

void GameScreen::checkIsSolved() {
	_isSolved = _boardGrid->isSolved();
	if (_isSolved) {
		_labelStatus.SetText("Solved!");
		_boardGrid->setGridSpacing(0);
		_boardGrid->removeEmptyTile();
		_mainMenu.setInGame(false);
	}
}

void GameScreen::checkUpdateTimeTaken() {

	float newSecondsTaken = _stopWatch.GetElapsedTime() - _totalTimePaused;
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
	sf::Vector2f pos = layout.getAlignedPosition(_boardGrid->getSize(), utl::Direction::center, utl::Direction::center);
	_boardGrid->SetPosition(pos);
}
