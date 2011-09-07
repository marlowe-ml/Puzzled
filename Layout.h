#ifndef Layout_h__
#define Layout_h__

#include "utils.h"
#include "Label.h"
#include <SFML/Graphics.hpp>

namespace puz {

	class Layout {
	public:
		Layout();
		Layout(sf::FloatRect areaRect);
		sf::Vector2f getAlignedPosition(sf::FloatRect objArea, utl::Direction::e horizontalSnap, utl::Direction::e verticalSnap) const;
		void alignLabel(sf::String& label, utl::Direction::e hSnap, utl::Direction::e vSnap) const;
		void alignLabel(puz::Label& label, utl::Direction::e hSnap, utl::Direction::e vSnap) const;


	private:
		sf::FloatRect _areaRect;

	};

}

#endif // Layout_h__