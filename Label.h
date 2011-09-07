#ifndef Label_h__
#define Label_h__

#include <SFML/Graphics.hpp>

namespace puz {

	class Label : public sf::Drawable {
	
	public:
		Label(sf::String const text);

		virtual void Render(sf::RenderTarget& target) const;
		sf::FloatRect GetRect() const;

		void SetColor(const sf::Color& color);

	private:
		sf::String _text;


	};
}

#endif // Label_h__