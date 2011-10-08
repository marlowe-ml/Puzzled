#ifndef MainMenu_h__
#define MainMenu_h__

#include <SFML/Graphics.hpp>
#include "ButtonList.h"

namespace puz {

class MainMenu : public sf::Drawable {

public:
	enum MenuSelection {btnNewGame, btnAbout, btnExit, btnLength};

	MainMenu();
	virtual void Render(sf::RenderTarget& target) const;
	void handleEvent(const sf::Event& e);

private:
	
	ButtonList _buttonList;
	void activateSelectedButton();

};

}

#endif // MainMenu_h__