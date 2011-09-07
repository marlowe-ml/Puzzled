#ifndef ResourceManager_h__
#define ResourceManager_h__

#include <SFML/Graphics.hpp>

namespace puz {

	class ResourceManager {

	public:
		static void init();
		static sf::Font const& getFont();

	private:
		static sf::Font _font;

	};

}

#endif // ResourceManager_h__