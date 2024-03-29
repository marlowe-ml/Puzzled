#include "BoardGrid.h"
#include <stdlib.h>
#include <time.h>

using namespace puz;


BoardGrid::BoardGrid(unsigned int numColumns, unsigned int numRows, const sf::Image& image) : _image(image)
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

	reset();
}

unsigned int BoardGrid::getWidth() const {
	return _numColumns * (_tileWidth + _gridSpacing) - _gridSpacing;
}

unsigned int BoardGrid::getHeight() const {
	return _numRows * (_tileHeight + _gridSpacing) - _gridSpacing;
}

sf::Vector2f BoardGrid::getSize() const {
	return sf::Vector2f(getWidth(), getHeight());
}


void BoardGrid::setTileAt(BoardCoordinates coordinates, const Tile& tile) {
	_tiles[coordinates.Column][coordinates.Row] = tile;
}


Tile& BoardGrid::tileAt(BoardCoordinates coordinates) {
	return _tiles[coordinates.Column][coordinates.Row];
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

	if (c1 == _emptyTileCoordinates)
		_emptyTileCoordinates = c2;
	else if (c2 == _emptyTileCoordinates)
		_emptyTileCoordinates = c1;
}


void BoardGrid::initializeTiles(const sf::Image& image) {
	_tiles.clear();
	_tiles.reserve(_numColumns);

	for (unsigned int x=0; x < _numColumns; x++) {
		_tiles.push_back(TileVector());
		for (unsigned int y=0; y < _numRows; y++) {
			BoardCoordinates coords = BoardCoordinates(x,y);
			Tile tile = Tile(image, BoardCoordinates(x,y));
			
			int startX = coords.Column*_tileWidth;
			int startY = coords.Row*_tileHeight;
			tile.SetSubRect(sf::IntRect(startX,startY,startX+_tileWidth,startY+_tileHeight));
						
			_tiles[x].push_back(tile);
		}
	}
	
	placeTiles();

}

void BoardGrid::setGridSpacing(int gridSpacing) {
	_gridSpacing = gridSpacing;
	placeTiles();
}

void BoardGrid::placeTiles() {
	for (unsigned int x=0; x < _numColumns; x++) {
		for (unsigned int y=0; y < _numRows; y++) {
			BoardCoordinates coords = BoardCoordinates(x,y);
			setTilePositionOnBoard(coords, tileAt(coords));
		}
	}
}

void BoardGrid::reset() {
	initializeTiles(_image);	
	_emptyTileCoordinates = BoardCoordinates(_numColumns-1,_numRows-1);
}

void BoardGrid::setTilePositionOnBoard(const BoardCoordinates coords, Tile& tile) {
	int startX = _boardOffsetX + coords.Column * (_tileWidth+_gridSpacing);
	int startY = _boardOffsetY + coords.Row * (_tileHeight+_gridSpacing);
	tile.SetPosition((float)startX,(float)startY);
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
		return true;
	}
	return false;
}

void BoardGrid::removeEmptyTile() {
	_emptyTileCoordinates = BoardCoordinates(-1,-1);
}

void BoardGrid::Render(sf::RenderTarget& target) const {	
	for (unsigned int x=0; x<_numColumns; x++) {
		for (unsigned int y=0; y<_numRows; y++) {
			BoardCoordinates coords(x,y);
			if (coords != _emptyTileCoordinates)
				target.Draw(tileAt(coords));
		}
	}
}
