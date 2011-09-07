#ifndef IntroScreen_h__
#define IntroScreen_h__

#include "Screen.h"

namespace puz {
	class IntroScreen : public Screen {
		
	protected:
		virtual void handleEvent(const sf::Event& e);
		virtual void update();
		virtual void present();

		virtual int onInit();

	};

}

#endif // IntroScreen_h__