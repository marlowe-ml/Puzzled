#ifndef MainMenuScreen_h__
#define MainMenuScreen_h__

#include "Screen.h"
#include "ButtonList.h"

namespace puz {

	class MainMenuScreen : public Screen {
	public:
		virtual ~MainMenuScreen();

	protected:
		enum MenuSelection {btnNewGame, btnAbout, btnExit, btnLength};

		virtual void handleEvent(const sf::Event& e);
		virtual void update();
		virtual void present();

		virtual int onInit();

	private:
		ButtonList _buttonList;
		void activateSelectedButton();
	};

}

#endif // MainMenuScreen_h__