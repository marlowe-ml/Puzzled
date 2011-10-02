#include "Tile.h"

using namespace puz;

Tile::Tile(BoardCoordinates originalCoordinates, const sf::Image& image) 
	: sf::Sprite(image), _originalCoordinates(originalCoordinates)
{}


Tile::~Tile() {}

void Tile::swapPosition(Tile& other) {
	sf::Vector2f tempSpritePos = other.GetPosition();
	other.SetPosition(GetPosition());
	SetPosition(tempSpritePos);
}