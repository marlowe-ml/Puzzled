#include "Layout.h"
#include <stdio.h>
#include <iostream>

using namespace puz;

Layout::Layout()
:_areaRect(sf::FloatRect(0,0,800,600)) 
{}

Layout::Layout(sf::FloatRect areaRect)
: _areaRect(areaRect)
{}

const sf::FloatRect Layout::GetRect() const {
	return _areaRect;
}

void Layout::alignString(sf::String& obj, utl::Direction::e hSnap, utl::Direction::e vSnap) const {
	sf::FloatRect rect = obj.GetRect();
	sf::Vector2f size = sf::Vector2f(rect.Right - rect.Left, rect.Bottom - rect.Top);
	alignDrawable(obj, size, hSnap, vSnap);
}

void Layout::alignSprite(sf::Sprite& obj, utl::Direction::e hSnap, utl::Direction::e vSnap) const {
	alignDrawable(obj, obj.GetSize(), hSnap, vSnap);
}


void Layout::alignDrawable(sf::Drawable& obj, sf::Vector2f size, utl::Direction::e hSnap, utl::Direction::e vSnap) const {
	sf::Vector2f centerPos = getAlignedPosition(size, hSnap, vSnap);
	obj.SetX(centerPos.x);
	obj.SetY(centerPos.y);
}

sf::Vector2f Layout::getAlignedPosition(sf::Vector2f objSize, utl::Direction::e hSnap, utl::Direction::e vSnap) const {
	sf::Vector2f newPos(0, 0);
	
	float objWidth = objSize.x;
	float objHeight = objSize.y;

	switch (hSnap) {
		case utl::Direction::left:
			newPos.x = _areaRect.Left;
			break;
		case utl::Direction::right:
			newPos.x = _areaRect.Right - objWidth;
			break;
		case utl::Direction::center:
			newPos.x = (_areaRect.GetWidth() / 2) - (objWidth / 2);
			break;
	}

	switch (vSnap) {
		case utl::Direction::top:
			newPos.y = _areaRect.Top;
			break;
		case utl::Direction::bottom:
			newPos.y = _areaRect.Bottom - objHeight;
			break;
		case utl::Direction::center:
			newPos.y = (_areaRect.GetHeight() / 2) - (objHeight / 2);
			break;
	}


	return newPos;

}
