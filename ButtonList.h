#ifndef ButtonList_h__
#define ButtonList_h__

#include <SFML/Graphics.hpp>

namespace puz {

class MenuButton : public sf::String {
public:
	MenuButton() : Index(0) 
	{}

	MenuButton(const std::string& label, const int index) : sf::String(label), Index(index) 
	{}

	operator int() const {
		return Index;
	}

	int Index;
};

typedef std::vector<MenuButton> vLabels;

class ButtonList : public sf::Drawable {

public:
	ButtonList();
	void addButton(const std::string label, int index);
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
