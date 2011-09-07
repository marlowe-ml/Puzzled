#ifndef MainMenuScreen_h__
#define MainMenuScreen_h__

#include "Screen.h"
#include "Label.h"

namespace puz {

	typedef std::vector<Label> vLabels;

	class MainMenuScreen : public Screen {
	public:

	protected:
		virtual void handleEvent(const sf::Event& e);
		virtual void update();
		virtual void present();

		virtual int onInit();

	private:
		vLabels _menuButtons;

	};

}

#endif // MainMenuScreen_h__