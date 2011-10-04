#ifndef ScreenManager_h__
#define ScreenManager_h__

#include "Screen.h"
#include "Layout.h"
#include <sfml/Graphics.hpp>
#include <map>
#include <stack>

namespace puz {

	typedef std::map<std::string, Screen* > ScreenMap;
	typedef std::stack<Screen* > ScreenStack;

	class ScreenManager  {
	public:
		static void init(sf::RenderWindow& app);
		static bool activateScreen(const std::string& screenId);
		static bool activateOverlayScreen(const std::string& screenId);
		static bool runActiveScreen();
		static void notifyScreenTerminated(const std::string& screenId);
		static void cleanup();
		static const Layout& getLayout();
		

	private:
		static sf::RenderWindow* _app;
		static Layout _screenLayout;

		static ScreenMap _screens;
		static Screen* _activeScreen;
		//static ScreenStack _activeScreens;
		static bool _cleanupTerminatedScreens;

		static Screen* createScreen(const std::string& screenId);
		static void ScreenManager::cleanupTerminatedScreens();

	};
}

#endif // ScreenManager_h__