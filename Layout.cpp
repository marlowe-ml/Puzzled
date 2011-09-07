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

void Layout::alignLabel(sf::String& label, utl::Direction::e hSnap, utl::Direction::e vSnap) const {
	sf::Vector2f pos = getAlignedPosition(label.GetRect(), hSnap, vSnap);
	label.SetPosition(pos);
}

void Layout::alignLabel(Label& label, utl::Direction::e hSnap, utl::Direction::e vSnap) const {
	sf::Vector2f pos = getAlignedPosition(label.GetRect(), hSnap, vSnap);
	label.SetPosition(pos);
}


sf::Vector2f Layout::getAlignedPosition(sf::FloatRect objArea, utl::Direction::e hSnap, utl::Direction::e vSnap) const {
	sf::Vector2f newPos(objArea.Left, objArea.Top);
	
	float objWidth = objArea.GetWidth();
	float objHeight = objArea.GetHeight();

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
