#ifndef IntroScreen_h__
#define IntroScreen_h__

#include "Screen.h"
#include <SFML/Graphics.hpp>

namespace puz {
	class IntroScreen : public Screen {
		
	protected:
		virtual void handleEvent(const sf::Event& e);
		virtual void update();
		virtual void present();

		virtual int onInit();

	private:
		sf::Sprite _logoSprite;

	};

}

#endif // IntroScreen_h__