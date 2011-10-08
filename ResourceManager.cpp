#include "ResourceManager.h"

using namespace puz;

sf::Font ResourceManager::_font;
sf::RenderWindow* ResourceManager::_app;

void ResourceManager::init(sf::RenderWindow& app) {
	ResourceManager::_font.LoadFromFile("arial.ttf");
	_app = &app;
}

sf::Font const& ResourceManager::getFont() {
	return ResourceManager::_font;
}

sf::RenderWindow* ResourceManager::getApp() {
	return ResourceManager::_app;
}