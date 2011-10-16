#ifndef AboutScreen_h__
#define AboutScreen_h__

#include "Screen.h"
#include <SFML/Graphics.hpp>

namespace puz {
	class AboutScreen : public Screen {

	protected:
		virtual void handleEvent(const sf::Event& e);
		virtual void update();
		virtual void present();

		virtual int onInit();

	private:
		sf::String _labelAbout;

	};

}


#endif // AboutScreen_h__
