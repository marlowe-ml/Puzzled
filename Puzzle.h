#ifndef Puzzle_h__
#define Puzzle_h__

#include "GameScreen.h"
#include "IntroScreen.h"

namespace puz {


	class Puzzle {
	public:
		Puzzle();
		int run();

	private:
		sf::RenderWindow _app;
	};
}


#endif // Puzzle_h__