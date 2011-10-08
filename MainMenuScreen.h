#ifndef MainMenuScreen_h__
#define MainMenuScreen_h__

#include "Screen.h"
#include "MainMenu.h"

namespace puz {

	class MainMenuScreen : public Screen {
	public:
		virtual ~MainMenuScreen();

	protected:
		virtual void handleEvent(const sf::Event& e);
		virtual void update();
		virtual void present();

	private:
		MainMenu _mainMenu;
	};

}

#endif // MainMenuScreen_h__