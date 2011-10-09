#ifndef MainMenu_h__
#define MainMenu_h__

#include <SFML/Graphics.hpp>
#include "ButtonList.h"

namespace puz {

class MainMenu : public sf::Drawable {

public:
	enum MenuSelection {btnNone = -1, btnResumeGame, btnNewGame, btnAbout, btnExit, btnLength};

	MainMenu();
	virtual void Render(sf::RenderTarget& target) const;
	void handleEvent(const sf::Event& e);
	MenuSelection checkLastActivatedButton();

private:
	
	MenuSelection _lastActivatedButton;
	ButtonList _buttonList;
	void activateSelectedButton();
	

};

}

#endif // MainMenu_h__