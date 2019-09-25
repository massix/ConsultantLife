#pragma once

#include <core_export.h>
#include <string>
#include <exception>

extern "C" {
	struct ALLEGRO_DISPLAY;
	struct ALLEGRO_TIMER;
}

namespace cl {
	namespace core {
		class Bitmap;
		class EventQueue;

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

			ALLEGRO_DISPLAY* alDisplay;
			ALLEGRO_TIMER* alTimer;

			Bitmap* bossBitmap;
			EventQueue* eq;
		};
	}
}
