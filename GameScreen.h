#ifndef GameScreen_h__
#define GameScreen_h__

#include "Screen.h"
#include "BoardGrid.h"
#include "MainMenu.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <boost/optional/optional.hpp>
#include <vector>


namespace puz {
	
	typedef std::vector<sf::String*> vpLabels;

	class GameScreen : public Screen {

	public:
		GameScreen();

	protected:
		virtual int onInit();
		virtual void handleEvent(const sf::Event& e);
		virtual void update();
		virtual void present();

	private:
		boost::optional<BoardGrid> _boardGrid;
		const int _defaultGridSpacing;
		sf::Image _boardImage;
		sf::Clock _stopWatch;
		MainMenu _mainMenu;

		float _secondsTaken;

		bool setupBoard();
		void centerBoard();
		void addLabels();
		void move(int offsetX, int offsetY);
		void checkUpdateTimeTaken();
		void checkIsSolved();

		void startGame();
		void resumeGame();

		sf::String _labelStatus;
		sf::String _labelMovesTaken;
		sf::String _labelTimeTaken;

		vpLabels _allLabels;

		bool _isSolved;
		bool _showMenu;
		bool _gameStarted;
		unsigned int _numMovesTaken;

	};

}

#endif // GameScreen_h__