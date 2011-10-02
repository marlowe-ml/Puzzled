#ifndef ButtonList_h__
#define ButtonList_h__

#include <SFML/Graphics.hpp>

namespace puz {

typedef std::vector<sf::String> vLabels;


class ButtonList : public sf::Drawable {

public:
	ButtonList();
	void addButton(const std::string label);
	void setSelectedButton(int index);
	int getSelectedButton() const;
	void selectPreviousButton();
	void selectNextButton();

	virtual void Render(sf::RenderTarget& target) const;
	sf::FloatRect GetRect() const;

private:
	vLabels _buttons;

	float _height;
	float _width;
	float _buttonMargin;

	void centerButtonsHorizontally();

	int _selectedButtonIndex;



	

};

}

#endif // ButtonList_h__
