#include "BoardGrid.h"
#include <stdlib.h>
#include <time.h>

using namespace puz;


BoardGrid::BoardGrid(unsigned int numColumns, unsigned int numRows, const sf::Image& image) 
{
	_numColumns=numColumns; 
	_numRows=numRows; 
	_boardCoordinateArea = sf::IntRect(0,0,numColumns-1,numRows-1);
	_gridSpacing=3;
	_emptyTileCoordinates = BoardCoordinates(numColumns-1,numRows-1);
	_tileWidth = (image.GetWidth() / numColumns);
	_tileHeight = (image.GetHeight() / numRows);
	_boardOffsetX=0;
	_boardOffsetY=0;
	
	initializeTiles(image);
}

unsigned int BoardGrid::getWidth() const {
	return _numColumns * (_tileWidth + _gridSpacing) - _gridSpacing;
}

unsigned int BoardGrid::getHeight() const {
	return _numRows * (_tileHeight + _gridSpacing) - _gridSpacing;
}

sf::FloatRect BoardGrid::getRect() const {
	sf::Vector2f pos = GetPosition();
	return sf::FloatRect(pos.x, pos.y, pos.x + getWidth(), pos.y + getHeight());
}


void BoardGrid::setTileAt(BoardCoordinates coordinates, const Tile& tile) {
	_tiles[coordinates.Column][coordinates.Row] = tile;
}

const Tile& BoardGrid::tileAt(BoardCoordinates coordinates) const {
	return _tiles[coordinates.Column][coordinates.Row];
}

void BoardGrid::swapTiles(BoardCoordinates c1, BoardCoordinates c2) {
	Tile t1 = tileAt(c1);
	Tile t2 = tileAt(c2);
	t1.swapPosition(t2);

	setTileAt(c1, t2);
	setTileAt(c2, t1);
}


void BoardGrid::initializeTiles(const sf::Image& image) {
	_tiles.reserve(_numColumns);

	for (unsigned int x=0; x < _numColumns; x++) {
		_tiles.push_back(TileVector());
		for (unsigned int y=0; y < _numRows; y++) {
			_tiles[x].push_back(createTile(image, BoardCoordinates(x,y)));
		}
	}
}

Tile BoardGrid::createTile(const sf::Image& image, const BoardCoordinates coords) const {

	sf::Sprite sprite(image);

	int startX = coords.Column*_tileWidth;
	int startY = coords.Row*_tileHeight;
	sprite.SetSubRect(sf::IntRect(startX,startY,startX+_tileWidth,startY+_tileHeight));

	startX = _boardOffsetX + coords.Column * (_tileWidth+_gridSpacing);
	startY = _boardOffsetY + coords.Row * (_tileHeight+_gridSpacing);
	sprite.SetPosition((float)startX,(float)startY);

	return Tile(coords, sprite);

}

void BoardGrid::randomize() {
	srand(static_cast<unsigned int>(time(NULL)));

	for (unsigned int steps=0; steps<(_numColumns*_numRows); steps++) {

		unsigned int x1 = rand() % _numColumns;
		unsigned int y1 = rand() % _numRows;
		unsigned int x2 = rand() % _numColumns;
		unsigned int y2 = rand() % _numRows;

		if (x1==x2 && y1==y2) {
			if (y2 < _numRows-1)
				y2++;
			else
				y2--;
		}

		swapTiles(BoardCoordinates(x1,y1), BoardCoordinates(x2,y2));
	}
}

bool BoardGrid::isSolved() const {

	for (unsigned int x=0; x<_numColumns; x++) {
		for (unsigned int y=0; y<_numRows; y++) {
			BoardCoordinates coords(x,y);
			if (tileAt(coords).getOriginalCoordinates() != coords)
				return false;
		}
	}

	return true;
}


bool BoardGrid::moveEmptyTileBy(int xOffset, int yOffset) {
	BoardCoordinates targetPos = _emptyTileCoordinates.offset(xOffset, yOffset);

	if(_boardCoordinateArea.Contains(targetPos.Column, targetPos.Row)) {
		swapTiles(_emptyTileCoordinates, targetPos);
		_emptyTileCoordinates = targetPos;
		return true;
	}
	return false;
}	

void BoardGrid::Render(sf::RenderTarget& target) const {	
	for (unsigned int x=0; x<_numColumns; x++) {
		for (unsigned int y=0; y<_numRows; y++) {
			BoardCoordinates coords(x,y);
			if (coords != _emptyTileCoordinates)
				tileAt(coords).Render(target);
		}
	}
}
