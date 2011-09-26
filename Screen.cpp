#include "Screen.h"
#include "ScreenManager.h"

using namespace puz;

Screen::Screen() : _isTerminated(false), _isInitialized(false)
{}

 Screen::~Screen() {
	 if (!_isTerminated)
		 terminate();
 }

 int Screen::run() {
	sf::Event e;
	while(_app->GetEvent(e)) {
		if (e.Type == sf::Event::Closed) {
			terminate();
			_app->Close();
			return EXIT_SUCCESS;
		} else {
			handleEvent(e);
		}
	}
		 
	update();
	present();

	 return EXIT_SUCCESS;
 }

 int Screen::init(sf::RenderWindow& app) {
	 _app = &app;
	 if (onInit() == EXIT_SUCCESS) {
		_isInitialized = true;
		return EXIT_SUCCESS;
	 }
	 return EXIT_FAILURE;
 }

 void Screen::terminate() {
	 _isTerminated = true;
	 onTerminate();
	 ScreenManager::notifyScreenTerminated(_screenId);
 }

void Screen::onTerminate() {}

int Screen::onInit() {return EXIT_SUCCESS;}

 void Screen::setScreenId(const std::string& newScreenId) {
	_screenId = newScreenId;
 }

 const std::string& Screen::getScreenId() const {
	return _screenId;
 }
