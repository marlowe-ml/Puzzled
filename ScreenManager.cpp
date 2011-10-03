#include "ScreenManager.h"
#include "IntroScreen.h"
#include "GameScreen.h"
#include "MainMenuScreen.h"

using namespace puz;

sf::RenderWindow* ScreenManager::_app = 0;
ScreenMap ScreenManager::_screens;
Screen* ScreenManager::_activeScreen = 0;
Layout ScreenManager::_screenLayout;
bool ScreenManager::_cleanupTerminatedScreens = false;

void ScreenManager::init(sf::RenderWindow& app)  
{
	ScreenManager::_app = &app;
	ScreenManager::_screenLayout = Layout(sf::FloatRect(0,0,(float)app.GetWidth(),(float)app.GetHeight()));
}

const Layout& ScreenManager::getLayout() {return _screenLayout;}

bool ScreenManager::terminateCurrentScreenAndActivate(const std::string& screenId) {
	if (_activeScreen != NULL) {
		_activeScreen->terminate();
	}
	return activateScreen(screenId);
}

bool ScreenManager::activateScreen(const std::string& screenId) {
	ScreenMap::iterator it = _screens.find(screenId);

	Screen* screen = 0;

	if (it == _screens.end()) {
		screen = createScreen(screenId);
		_screens.insert(std::pair<std::string, Screen*>(screenId, screen));
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

bool ScreenManager::runActiveScreen() {
	if (_cleanupTerminatedScreens)
		cleanupTerminatedScreens();

	if (_activeScreen == NULL || _activeScreen->isTerminated())
		return false;
		
	_activeScreen->run();
	return true;
}

Screen* ScreenManager::createScreen(const std::string& screenId) {
	Screen* newScreen = 0;

	if (screenId == "Intro")
		newScreen = new IntroScreen();
	
	if (screenId == "Game")
		newScreen = new GameScreen();

	if (screenId == "MainMenu")
		newScreen = new MainMenuScreen();

	if (newScreen != 0)
		newScreen->setScreenId(screenId);

	return newScreen;
}


void ScreenManager::notifyScreenTerminated(const std::string& screenId) {
	_cleanupTerminatedScreens = true;

	ScreenMap::iterator it = _screens.find(screenId);
	if (it!=_screens.end()) {
		if (_activeScreen != NULL && _activeScreen->getScreenId() == screenId)
			_activeScreen = NULL;			
	}

}


void ScreenManager::cleanup() {
	for (ScreenMap::iterator it = _screens.begin(); it!=_screens.end(); it++) {
		if (it->second != NULL && it->second->isTerminated() == false)
			it->second->terminate();

		delete it->second;
	}

	_screens.clear();
}

void ScreenManager::cleanupTerminatedScreens() {
	
	ScreenMap::iterator it = _screens.begin();
	
	while (it!=_screens.end()) {
		if (it->second->isTerminated()) {
			delete it->second;
			_screens.erase(it++);
		} else {
			it++;	
		}
	}

	_cleanupTerminatedScreens = false;
}
