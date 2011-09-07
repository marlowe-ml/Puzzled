#include "Label.h"

using namespace puz;

Label::Label(sf::String const text) : _text(text) 
{}

void Label::Render(sf::RenderTarget& target) const {
	target.Draw(_text);
}

sf::FloatRect Label::GetRect() const {
	return _text.GetRect();
}

void Label::SetColor(const sf::Color& color) {
	_text.SetColor(color);
}

