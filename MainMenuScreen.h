#ifndef MainMenuScreen_h__
#define MainMenuScreen_h__

#include "Screen.h"
#include "Label.h"

namespace puz {

	typedef std::vector<Label> vLabels;

	class MainMenuScreen : public Screen {
	public:
		virtual ~MainMenuScreen();

	protected:
		enum MenuSelection {btnNewGame, btnExit, btnLength};

		virtual void handleEvent(const sf::Event& e);
		virtual void update();
		virtual void present();

		virtual int onInit();

	private:
		vLabels _menuButtons;
		int _selectedButtonIndex;

		void setSelectedButton(MenuSelection selectedButton);
		void selectPreviousButton();
		void selectNextButton();

		void activateSelectedButton();
	};

}

#endif // MainMenuScreen_h__