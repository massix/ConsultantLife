#pragma once

#include <core_export.h>
#include <string>
#include <exception>

namespace cl {
	namespace core {
		class Bitmap;
		class EventQueue;
		class Timer;

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

			Timer* timer;
			Bitmap* bossBitmap;
			EventQueue* eq;
		};
	}
}
