#ifndef ResourceManager_h__
#define ResourceManager_h__

#include <SFML/Graphics.hpp>
#include <boost/ptr_container/ptr_map.hpp>

namespace puz {

	typedef boost::ptr_map<std::string, sf::Image> ImageLookup;

	class ResourceManager {

	public:
		static void init(sf::RenderWindow& app);
		static sf::Font const& getFont();
		static sf::RenderWindow* ResourceManager::getApp();
		static const sf::Image& getImage(const std::string& fileName);

	private:
		static sf::Font _font;
		static sf::RenderWindow* _app;
		static ImageLookup _imageLookup;

	};

}

#endif // ResourceManager_h__