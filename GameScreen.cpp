#include "GameScreen.h"
#include "ScreenManager.h"
#include "ResourceManager.h"
#include <iostream>
#include <boost/utility/typed_in_place_factory.hpp>
#include <boost/lexical_cast.hpp>
#include <math.h>


using namespace puz;

bool GameScreen::setupBoard() {
	if (!_boardImage.LoadFromFile("puzzle.jpg"))
		return false;

	_boardGrid = boost::in_place<BoardGrid>(3, 3, _boardImage); 
	//_boardGrid->randomize();
	centerBoard();

	return true;
}

void GameScreen::initUIElements() {
	_allLabels.push_back(&_labelStatus);
	_allLabels.push_back(&_labelMovesTaken);
	_allLabels.push_back(&_labelTimeTaken);

	for (vpLabels::iterator it = _allLabels.begin(); it!=_allLabels.end(); it++) {
		(*it)->SetFont(ResourceManager::getFont());
		(*it)->SetColor(sf::Color(255,0,0));
	}

	_labelMovesTaken.SetText("0");
	_labelTimeTaken.SetText("00:00:00");
	
	const Layout & layout = ScreenManager::getLayout();
	layout.alignLabel(_labelMovesTaken, utl::Direction::right, utl::Direction::top);
	layout.alignLabel(_labelTimeTaken, utl::Direction::center, utl::Direction::top);
}

int GameScreen::onInit() {
	_isSolved = false; 
	_numMovesTaken = 0;
	_secondsTaken = 0;

	if (!setupBoard())
		return EXIT_FAILURE;

	initUIElements();
	_stopWatch.Reset();	

	return EXIT_SUCCESS;
}

void GameScreen::update() {
	checkUpdateTimeTaken();
}

void GameScreen::present() {

	for (vpLabels::iterator it = _allLabels.begin(); it!=_allLabels.end(); it++) {
		_app->Draw(*(*it));
	}
	_app->Draw(*_boardGrid);
}

void GameScreen::handleEvent(const sf::Event& e) {
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
				ScreenManager::activateScreen("MainMenu");
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

		_isSolved = _boardGrid->isSolved();
		if (_isSolved) {
			_labelStatus.SetText("Solved!");
			_boardGrid->setGridSpacing(0);
			_boardGrid->removeEmptyTile();
		}
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
