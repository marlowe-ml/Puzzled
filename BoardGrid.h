#ifndef BoardGrid_h__
#define BoardGrid_h__

#include "BoardCoordinates.h"
#include "Tile.h"
#include "SFML/Graphics.hpp"

namespace puz {

	typedef std::vector<Tile> TileVector;
	typedef std::vector< TileVector > TileVector2D;

	class BoardGrid : public sf::Drawable {
	
	public: 
		BoardGrid(unsigned int numColumns, unsigned int numRows, const sf::Image& image);
		unsigned int getWidth() const;
		unsigned int getHeight() const;
		sf::FloatRect getRect() const;
		void randomize();
		bool isSolved() const;
		bool moveEmptyTileBy(int xOffset, int yOffset);

		virtual void Render(sf::RenderTarget& target) const;

		void setGridSpacing(int gridSpacing);
		void removeEmptyTile();

	private:

		TileVector2D _tiles;

		unsigned int _numColumns;
		unsigned int _numRows;

		sf::IntRect _boardCoordinateArea;
		BoardCoordinates _emptyTileCoordinates;

		unsigned int _tileWidth;
		unsigned int _tileHeight;
		unsigned int _gridSpacing;
		unsigned int _boardOffsetX;
		unsigned int _boardOffsetY;
		
		void initializeTiles(const sf::Image& image);
		Tile createTile(const sf::Image& image,  const BoardCoordinates coords) const;		

		void swapTiles(BoardCoordinates c1, BoardCoordinates c2);
		Tile& tileAt(BoardCoordinates coords);
		const Tile& tileAt(BoardCoordinates coords) const;
		void setTileAt(BoardCoordinates coordinates, const Tile& tile);

		void setTilePositionOnBoard(const BoardCoordinates coords, Tile& tile);		
		void BoardGrid::placeTiles();
};

}

#endif // BoardGrid_h__