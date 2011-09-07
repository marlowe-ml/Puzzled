#ifndef ScreenManager_h__
#define ScreenManager_h__

#include "Screen.h"
#include "Layout.h"
#include <sfml/Graphics.hpp>
#include <map>

namespace puz {

	typedef std::map<std::string, Screen* > ScreenMap;

	class ScreenManager  {
	public:
		static void init(sf::RenderWindow& app);
		static bool activateScreen(const std::string& screenId);
		static void runActiveScreen();
		static void notifyScreenTerminated(const std::string& screenId);
		static void cleanup();
		static const Layout& getLayout();
		

	private:
		static sf::RenderWindow* _app;

		static ScreenMap _screens;
		static Screen* _activeScreen;

		static Screen* createScreen(const std::string& screenId);

		static Layout _screenLayout;
		
	};
}

#endif // ScreenManager_h__