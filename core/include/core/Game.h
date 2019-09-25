#pragma once

#include <core_export.h>
#include <string>

extern "C" {
	struct ALLEGRO_DISPLAY;
	struct ALLEGRO_TIMER;
	struct ALLEGRO_EVENT_QUEUE;
	struct ALLEGRO_BITMAP;
}

namespace cl {
	namespace core {
		class Bitmap;

		class CORE_EXPORT Game {
		public:
			Game(std::string const&);
			~Game();
			bool init();
			void mainLoop();
			std::string const& getName() const;

		private:
			Game(Game const&) = delete;
			Game& operator=(Game const&) = delete;
			std::string gameName;
			bool over;

			ALLEGRO_DISPLAY* alDisplay;
			ALLEGRO_TIMER* alTimer;
			ALLEGRO_EVENT_QUEUE* alEventQueue;

			Bitmap* bossBitmap;
		};
	}
}
