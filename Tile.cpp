#include "Tile.h"

using namespace puz;

Tile::Tile(BoardCoordinates originalCoordinates, const sf::Sprite& sprite) 
: _originalCoordinates(originalCoordinates), _sprite(sprite), _empty(false)
{}

Tile::Tile() 
: _empty(true), _originalCoordinates(BoardCoordinates(-1,-1))
{}

void Tile::init(BoardCoordinates originalCoordinates, const sf::Sprite& sprite) {
	_originalCoordinates = originalCoordinates; 
	_sprite = sprite;
	_empty = false;
}

Tile::~Tile() {}

void Tile::Render(sf::RenderTarget& target) const {	
	if (!_empty)
		target.Draw(_sprite);
}

void Tile::swapPosition(Tile& other) {
	sf::Vector2f tempSpritePos = other._sprite.GetPosition();
	other._sprite.SetPosition(_sprite.GetPosition());
	_sprite.SetPosition(tempSpritePos);
}