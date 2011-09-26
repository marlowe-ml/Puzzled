#ifndef Screen_h__
#define Screen_h__

#include <SFML/Graphics.hpp>
#include <iostream>

namespace puz {

	class Screen {
		public:
			Screen();
			virtual ~Screen();

			int init(sf::RenderWindow& app);
			int run();
			void terminate();
			void setScreenId(const std::string& newScreenId);
			const std::string& getScreenId() const;
			inline bool isTerminated() const {return _isTerminated;}
			inline bool isInitialized() const {return _isInitialized;}

		protected:
			sf::RenderWindow* _app;
			bool _isTerminated;
			bool _isInitialized;
			std::string _screenId;

			virtual void handleEvent(const sf::Event& e) = 0;
			virtual void update() = 0;
			virtual void present() = 0;
			virtual void onTerminate();
			virtual int onInit();			

	};

}

#endif // Screen_h__