#ifndef GameScreen_h__
#define GameScreen_h__

#include "Screen.h"
#include "BoardGrid.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <boost/optional/optional.hpp>
#include <vector>


namespace puz {
	
	typedef std::vector<sf::String*> vpLabels;

	class GameScreen : public Screen {

	protected:
		virtual int onInit();
		virtual void handleEvent(const sf::Event& e);
		virtual void update();
		virtual void present();

	private:
		boost::optional<BoardGrid> _boardGrid;
		sf::Image _boardImage;
		sf::Clock _stopWatch;
		float _secondsTaken;

		bool setupBoard();
		void centerBoard();
		void initUIElements();
		void move(int offsetX, int offsetY);
		void checkUpdateTimeTaken();

		sf::String _labelStatus;
		sf::String _labelMovesTaken;
		sf::String _labelTimeTaken;

		vpLabels _allLabels;

		bool _isSolved;
		unsigned int _numMovesTaken;

	};

}

#endif // GameScreen_h__