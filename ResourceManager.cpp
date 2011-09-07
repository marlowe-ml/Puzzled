#include "ResourceManager.h"

using namespace puz;

sf::Font ResourceManager::_font;

void ResourceManager::init() {
	ResourceManager::_font.LoadFromFile("arial.ttf");
}

sf::Font const& ResourceManager::getFont() {
	return ResourceManager::_font;
}