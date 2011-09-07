#include "ScreenManager.h"
#include "IntroScreen.h"
#include "GameScreen.h"
#include "MainMenuScreen.h"

using namespace puz;

sf::RenderWindow* ScreenManager::_app = 0;
ScreenMap ScreenManager::_screens;
Screen* ScreenManager::_activeScreen = 0;
Layout ScreenManager::_screenLayout;

void ScreenManager::init(sf::RenderWindow& app)  
{
	ScreenManager::_app = &app;
	ScreenManager::_screenLayout = Layout(sf::FloatRect(0,0,(float)app.GetWidth(),(float)app.GetHeight()));
}

const Layout& ScreenManager::getLayout() {return _screenLayout;}

bool ScreenManager::activateScreen(const std::string& screenId) {
	ScreenMap::iterator it = _screens.find(screenId);
	
	Screen* screen = 0;

	if (it == _screens.end()) {
		screen = createScreen(screenId);
	} else {
		screen = it->second;		
	}
	
	if (screen != 0)
	{
		if (!screen->isInitialized())
			screen->init(*_app);

		_activeScreen = screen;
		return true;
	}
	
	return false;
}

void ScreenManager::cleanup() {
	for (ScreenMap::iterator it = _screens.begin(); it!=_screens.end(); it++) {
		delete it->second;
	}

	_screens.clear();
}

void ScreenManager::runActiveScreen() {
	_activeScreen->run();
}

Screen* ScreenManager::createScreen(const std::string& screenId) {
	Screen* newScreen = 0;

	if (screenId == "Intro")
		newScreen = new IntroScreen();
	
	if (screenId == "Game")
		newScreen = new GameScreen();

	if (screenId == "MainMenu")
		newScreen = new MainMenuScreen();

	return newScreen;
}

void ScreenManager::notifyScreenTerminated(const std::string& screenId) {
	ScreenMap::iterator it = _screens.find(screenId);
	if (it!=_screens.end()) {
		delete it->second;
		_screens.erase(it);
	}

}
