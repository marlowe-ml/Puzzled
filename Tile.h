#ifndef Tile_h__
#define Tile_h__

#include <SFML/Graphics.hpp>
#include "BoardCoordinates.h"

namespace puz {

class Tile : public sf::Sprite {
	
public:
	
	Tile(BoardCoordinates coordinates, const sf::Image& image);
	virtual ~Tile();
		
	inline BoardCoordinates getOriginalCoordinates() const {return _originalCoordinates;}
	void swapPosition(Tile& other);

private:
	BoardCoordinates _originalCoordinates;
};

}

#endif // Tile_h__