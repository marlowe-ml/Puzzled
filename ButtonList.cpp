#include "ButtonList.h"
#include "ResourceManager.h"

using namespace puz;

ButtonList::ButtonList() : _height(0), _width(0), _buttonMargin(10) {}

void ButtonList::addButton(const std::string label) {
	sf::String button(label);
	button.SetFont(ResourceManager::getFont());
	button.SetColor(sf::Color(255,255,255));
	button.SetY(_height);
	_buttons.push_back(button);

	_height += button.GetRect().GetHeight() + _buttonMargin;
	
	float buttonWidth = button.GetRect().GetWidth();
	if (buttonWidth > _width)
		_width = buttonWidth;

	centerButtonsHorizontally();
}

void ButtonList::selectPreviousButton() {
	if (_selectedButtonIndex > 0)
		setSelectedButton(_selectedButtonIndex-1);

}

void ButtonList::selectNextButton() {
	if (_selectedButtonIndex+1 < static_cast<int>(_buttons.size()))
		setSelectedButton(_selectedButtonIndex+1);
}

void ButtonList::setSelectedButton(int selectedButton) {
	_selectedButtonIndex = selectedButton;
	int index = 0;
	int len = _buttons.size();
	for (int i=0; i<len;i++) {
		if (i == _selectedButtonIndex)
			_buttons[i].SetColor(sf::Color(255,0,0));
		else
			_buttons[i].SetColor(sf::Color(255,255,255));
	}
}

int ButtonList::getSelectedButton() const {
	return _selectedButtonIndex;
}

sf::FloatRect ButtonList::GetRect() const {
	return sf::FloatRect(0, 0, _width, _height);
}

void ButtonList::centerButtonsHorizontally() {
	for (vLabels::iterator it = _buttons.begin(); it!=_buttons.end(); it++) {
		float buttonWidth = (*it).GetRect().GetWidth();
		float offsetDistance = (_width - buttonWidth)/2.f;

		(*it).SetX(offsetDistance);
	}

}

void ButtonList::Render(sf::RenderTarget& target) const {
	for (vLabels::const_iterator it = _buttons.begin(); it!=_buttons.end(); it++) {
		target.Draw(*it);
	}
}