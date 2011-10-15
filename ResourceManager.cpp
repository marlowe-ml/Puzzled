#include "ResourceManager.h"

using namespace puz;

sf::Font ResourceManager::_font;
sf::RenderWindow* ResourceManager::_app;
ImageLookup ResourceManager::_imageLookup;

void ResourceManager::init(sf::RenderWindow& app) {
	ResourceManager::_font.LoadFromFile("Arial.ttf");
	_app = &app;
}

sf::Font const& ResourceManager::getFont() {
	return ResourceManager::_font;
}

sf::RenderWindow* ResourceManager::getApp() {
	return ResourceManager::_app;
}

const sf::Image& ResourceManager::getImage(const std::string& fileName) {
	ImageLookup::iterator it = _imageLookup.find(fileName);

	if (it != _imageLookup.end()) {
		return *(it->second);
	} else {
		sf::Image* img = new sf::Image();
		img->LoadFromFile(fileName);
		_imageLookup[fileName] = *img;
		return *img;
	}
}
