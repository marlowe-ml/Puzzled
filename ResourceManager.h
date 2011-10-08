#ifndef ResourceManager_h__
#define ResourceManager_h__

#include <SFML/Graphics.hpp>

namespace puz {

	class ResourceManager {

	public:
		static void init(sf::RenderWindow& app);
		static sf::Font const& getFont();
		static sf::RenderWindow* ResourceManager::getApp();

	private:
		static sf::Font _font;
		static sf::RenderWindow* _app;

	};

}

#endif // ResourceManager_h__