#ifndef Tile_h__
#define Tile_h__

#include <SFML/Graphics.hpp>
#include "BoardCoordinates.h"

namespace puz {

class Tile : public sf::Drawable {
	
public:
	
	Tile(BoardCoordinates coordinates, const sf::Sprite& sprite);
	Tile();
	void init(BoardCoordinates originalCoordinates, const sf::Sprite& sprite);
	virtual ~Tile();
		
	virtual void Render(sf::RenderTarget& target) const;
	inline BoardCoordinates getOriginalCoordinates() const {return _originalCoordinates;}
	

	void swapPosition(Tile& other);


private:
	BoardCoordinates _originalCoordinates;
	sf::Sprite _sprite;
	bool _empty;
};

}

#endif // Tile_h__