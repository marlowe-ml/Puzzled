#ifndef Label_h__
#define Label_h__

#include <SFML/Graphics.hpp>

namespace puz {

	class Label : public sf::Drawable {
	
	public:
		Label(const sf::String& text);

		virtual void Render(sf::RenderTarget& target) const;
		sf::FloatRect GetRect() const;

		void SetColor(const sf::Color& color);
		void SetFont(const sf::Font& font);

	private:
		sf::String _text;
		Label() {}

	};
}

#endif // Label_h__