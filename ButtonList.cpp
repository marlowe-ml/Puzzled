#include "ButtonList.h"
#include "ResourceManager.h"

using namespace puz;

ButtonList::ButtonList() : _height(0), _width(0), _buttonMargin(10) {}

void ButtonList::addButton(const std::string label, const int index) {
	LabelList::iterator itExisting = iteratorToButton(_selectedButtonIndex);
	if (itExisting != _buttons.end())
		return;	// index must be unique

	MenuButton button(label, index);
	button.SetFont(ResourceManager::getFont());
	button.SetColor(sf::Color(255,255,255));

	float currentHeight = 0;

	// insert before first button with higher index
	LabelList::iterator it = _buttons.begin();
	for (; it != _buttons.end(); it++)
	{
		if ((*it).Index > index)
			break;
	}

	if (it == _buttons.end())
		_buttons.push_back(button);		
	else
		_buttons.insert(it, button);

	alignButtons();
}


void ButtonList::alignButtons() {
	float currentHeight = 0;

	// push remaining buttons down
	for (LabelList::iterator it = _buttons.begin(); it != _buttons.end(); it++)
	{
		(*it).SetY(currentHeight);
		currentHeight += (*it).GetRect().GetHeight() + _buttonMargin;
		
		float buttonWidth = (*it).GetRect().GetWidth();
		if (buttonWidth > _width)
			_width = buttonWidth;
	}

	_height = currentHeight;

	centerButtonsHorizontally();
}

/*
void ButtonList::hideButton() {
	
}*/

void ButtonList::selectPreviousButton() {
	LabelList::iterator it = iteratorToButton(_selectedButtonIndex);
	if (it == _buttons.end())
		return;

	if (it != _buttons.begin()) {
		_selectedButtonIndex = (*(--it)).Index;
		onSelectionChanged();
	}
}

void ButtonList::selectNextButton() {
	LabelList::iterator it = iteratorToButton(_selectedButtonIndex);
	if (it == _buttons.end())
		return;

	if (++it != _buttons.end()) {
		_selectedButtonIndex = (*it).Index;
		onSelectionChanged();

	}
}

LabelList::iterator ButtonList::iteratorToButton(int index) {
	LabelList::iterator it = _buttons.begin(); 
	while (it != _buttons.end()) {
		if ((*it).Index == index) {
			break;
		}
		it++;
	}

	return it;
}

void ButtonList::selectFirstButton() {
	if (!_buttons.empty()) {
		_selectedButtonIndex = _buttons.front().Index;
		onSelectionChanged();
	}
}

void ButtonList::onSelectionChanged() {
	for (LabelList::iterator it = _buttons.begin(); it != _buttons.end(); it++) {
		if ((*it).Index == _selectedButtonIndex)
			(*it).SetColor(sf::Color(255,0,0));
		else
			(*it).SetColor(sf::Color(255,255,255));
	}	
}

int ButtonList::getSelectedButton() const {
	return _selectedButtonIndex;
}

sf::FloatRect ButtonList::GetRect() const {
	return sf::FloatRect(0, 0, _width, _height);
}

void ButtonList::centerButtonsHorizontally() {
	for (LabelList::iterator it = _buttons.begin(); it!=_buttons.end(); it++) {
		float buttonWidth = (*it).GetRect().GetWidth();
		float offsetDistance = (_width - buttonWidth)/2.f;

		(*it).SetX(offsetDistance);
	}
}

void ButtonList::Render(sf::RenderTarget& target) const {
	for (LabelList::const_iterator it = _buttons.begin(); it!=_buttons.end(); it++) {
		target.Draw(*it);
	}
}